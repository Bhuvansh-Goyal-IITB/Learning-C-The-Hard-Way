CFLAGS=-g -O2 -Wall -Wextra -Isrc -Iinclude -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

HEADERS=$(wildcard include/**/*.h include/*.h)

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Iinclude -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build

.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name  "*.dSYM" -print` 

install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install -d $(DESTDIR)/$(PREFIX)/include/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
	install $(HEADERS) $(DESTDIR)/$(PREFIX)/include/

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
				|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
