CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
AR = ar
ARFLAGS = rcs

LIB = libListeElement.a
PROGRAM = test_liste
GAME_PROGRAM = c-dungeon

LIB_OBJECT = build/liste_element.o
TEST_OBJECTS = build/main.o build/test_liste_element.o
GAME_OBJECTS = build/game_main.o build/entity.o build/display.o

.PHONY: all test game run clean

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

game: $(GAME_PROGRAM)

$(GAME_PROGRAM): $(GAME_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(GAME_OBJECTS) -lncursesw

build/game_main.o: src/game_main.c include/display.h include/entity.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/entity.o: src/entity.c include/entity.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/display.o: src/display.c include/display.h include/entity.h
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(MAKE) clean
	$(MAKE) test
	$(MAKE) game
	./$(GAME_PROGRAM)

test: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -rf build $(LIB) $(PROGRAM) $(GAME_PROGRAM)
