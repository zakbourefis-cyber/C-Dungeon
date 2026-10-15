CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
AR = ar
ARFLAGS = rcs

LIB = libListeElement.a
PROGRAM = test_liste
LIB_OBJECT = build/liste_element.o
TEST_OBJECTS = build/main.o build/test_liste_element.o

.PHONY: all test clean

all: $(LIB) $(PROGRAM)

$(LIB): $(LIB_OBJECT)
	$(AR) $(ARFLAGS) $@ $^

$(PROGRAM): $(TEST_OBJECTS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJECTS) -L. -lListeElement

build/liste_element.o: src/liste_element.c include/liste_element.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/main.o: src/main.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/test_liste_element.o: tests/test_liste_element.c include/liste_element.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

test: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -rf build $(LIB) $(PROGRAM)