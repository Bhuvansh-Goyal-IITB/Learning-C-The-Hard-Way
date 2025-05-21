all: libex29.so main

libex29.so: libex29.c
	$(CC) -shared -o $@ $^	

main: main.c
	$(CC) -ldl -Wall -DNDEBUG -g $^ -o $@	

clean:
	rm -rf *.so *.o main
