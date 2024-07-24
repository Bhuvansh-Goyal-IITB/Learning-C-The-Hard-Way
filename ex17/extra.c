#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
  int id;
  int set;
  char *name;
  char *email;
};

struct Database {
  int MAX_DATA;
  int MAX_ROWS;
  struct Address *rows;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close(struct Connection *);

void die(struct Connection *conn, const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  Database_close(conn);
  exit(1);
}

void Address_print(struct Address *addr) {
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS) {
  conn->db->MAX_DATA = MAX_DATA;
  conn->db->MAX_ROWS = MAX_ROWS;

  conn->db->rows = malloc(sizeof(struct Address) * conn->db->MAX_ROWS);
  if (!conn->db->rows) {
    die(conn, "Memory Error.");
  }

  for (int i = 0; i < conn->db->MAX_ROWS; i++) {
    struct Address *addr = &conn->db->rows[i];

    addr->id = i;
    addr->set = 0;

    addr->name = malloc(sizeof(char) * conn->db->MAX_DATA);
    addr->email = malloc(sizeof(char) * conn->db->MAX_DATA);

    if (!addr->name || !addr->email) {
      die(conn, "Memory Error.");
    }
  }
}

void Database_set(struct Connection *conn, int id, const char *name,
                  const char *email) {
  struct Address *addr = &conn->db->rows[id];
  int MAX_DATA = conn->db->MAX_DATA;

  if (addr->set) {
    die(conn, "Entry already exists, delete it first.");
  }

  const char *res = strncpy(addr->name, name, MAX_DATA);

  if (!res) {
    die(conn, "Failed to copy name.");
  }

  res = strncpy(addr->email, email, MAX_DATA);

  if (!res) {
    die(conn, "Failed to copy email.");
  }

  addr->name[MAX_DATA - 1] = '\0';
  addr->email[MAX_DATA - 1] = '\0';
  addr->set = 1;
}

void Database_get(struct Connection *conn, int id) {
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  }
}

void Database_list(struct Connection *conn) {
  for (int i = 0; i < conn->db->MAX_ROWS; i++) {
    struct Address *curr = &conn->db->rows[i];

    if (curr->set) {
      Address_print(curr);
    }
  }
}

void Database_delete(struct Connection *conn, int id) {
  struct Address *addr = &conn->db->rows[id];

  if (!addr->set) {
    die(conn, "Row is not set, set it first to delete it.");
  }

  addr->set = 0;
}

void Database_write(struct Connection *conn) {
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(int) * 2, 1, conn->file);

  if (rc != 1) {
    die(conn, "Filed to write to database.");
  }

  for (int i = 0; i < conn->db->MAX_ROWS; i++) {
    struct Address *addr = &conn->db->rows[i];
    rc = fwrite(addr, sizeof(int) * 2, 1, conn->file);
    rc += fwrite(addr->name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
    rc += fwrite(addr->email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);

    if (rc != 3) {
      die(conn, "Filed to write to database.");
    }
  }

  rc = fflush(conn->file);
  if (rc == -1) {
    die(conn, "Cannot flush database.");
  }
}

void Database_load(struct Connection *conn) {
  int rc = fread(conn->db, sizeof(int) * 2, 1, conn->file);
  if (rc != 1) {
    die(conn, "Memory Error.");
  }

  conn->db->rows = malloc(sizeof(struct Address) * conn->db->MAX_ROWS);
  if (!conn->db->rows) {
    die(conn, "Memory Error.");
  }
  for (int i = 0; i < conn->db->MAX_ROWS; i++) {
    struct Address *addr = &conn->db->rows[i];

    addr->name = malloc(sizeof(char) * conn->db->MAX_DATA);
    addr->email = malloc(sizeof(char) * conn->db->MAX_DATA);

    if (!addr->name || !addr->email) {
      die(conn, "Memory Error.");
    }

    rc = fread(addr, sizeof(int) * 2, 1, conn->file);
    rc += fread(addr->name, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);
    rc += fread(addr->email, sizeof(char) * conn->db->MAX_DATA, 1, conn->file);

    if (rc != 3) {
      die(conn, "Failed to load database.");
    }
  }
}

void Database_close(struct Connection *conn) {
  if (conn) {
    if (conn->file) {
      fclose(conn->file);
    }
    if (conn->db) {
      for (int i = 0; i < conn->db->MAX_ROWS; i++) {
        if (conn->db->rows[i].name) {
          free(conn->db->rows[i].name);
        }
        if (conn->db->rows[i].email) {
          free(conn->db->rows[i].email);
        }
      }
      if (conn->db->rows) {
        free(conn->db->rows);
      }
      free(conn->db);
    }
    free(conn);
  }
}

struct Connection *Database_open(const char *filename, char action) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) {
    die(conn, "Memory error.");
  }

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) {
    die(conn, "Memory error.");
  }

  if (action == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");
    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) {
    die(conn, "Failed to open the file.");
  }

  return conn;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("USAGE: ./main <db file> <action> [action parameters]\n");
    return 1;
  }

  char *filename = argv[1];
  char action = argv[2][0];

  struct Connection *conn = Database_open(filename, action);

  int id = 0;
  if (argc > 3) {
    id = atoi(argv[3]);
  }

  if (action != 'c' && id >= conn->db->MAX_ROWS) {
    die(conn, "There's not that many records.");
  }

  switch (action) {
    case 'c':
      if (argc != 5) {
        die(conn, "Need MAX_DATA, MAX_ROWS to create.");
      }
      int MAX_DATA = atoi(argv[3]);
      int MAX_ROWS = atoi(argv[4]);

      Database_create(conn, MAX_DATA, MAX_ROWS);
      Database_write(conn);
      break;
    case 's':
      if (argc != 6) {
        die(conn, "Need id, name, email to set.");
      }
      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;
    case 'd':
      if (argc != 4) {
        die(conn, "Need an id to delete.");
      }
      Database_delete(conn, id);
      Database_write(conn);
      break;
    case 'g':
      if (argc != 4) {
        die(conn, "Need an id to get.");
      }
      Database_get(conn, id);
      break;
    case 'l':
      Database_list(conn);
      break;
    default:
      die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close(conn);
  return 0;
}
