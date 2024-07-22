#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
  char *name;
  int age;
  int weight;
  int height;
};

struct Person *Person_create(char *name, int age, int weight, int height) {
  struct Person *p = malloc(sizeof(struct Person));
  assert(p != NULL);

  p->name = strdup(name);
  p->age = age;
  p->weight = weight;
  p->height = height;

  return p;
}

void Person_destroy(struct Person *p) {
  assert(p != NULL);

  free(p->name);
  free(p);
}

void Person_print(struct Person *p) {
  printf("Name: %s\n", p->name);
  printf("\tAge: %d\n", p->age);
  printf("\tWeight: %d\n", p->weight);
  printf("\tHeight: %d\n", p->height);
}

int main(int argc, char *argv[]) {
  struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
  struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

  printf("Joe's memory location is %p\n", joe);
  Person_print(joe);

  printf("Frank's memory location is %p\n", frank);
  Person_print(frank);

  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
