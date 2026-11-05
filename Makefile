CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude
NCURSES_PREFIX = $(shell brew --prefix ncurses 2>/dev/null)
ifneq ($(NCURSES_PREFIX),)
CFLAGS += -I$(NCURSES_PREFIX)/include
NCURSES_LIBS = -L$(NCURSES_PREFIX)/lib -Wl,-rpath,$(NCURSES_PREFIX)/lib -lncursesw
else
NCURSES_LIBS = -lncursesw
endif

LIB = libListeElement.a
TEST = test_liste
GAME = c-dungeon
TEST_SOURCES = src/main.c src/liste_element.c tests/test_liste_element.c
GAME_SOURCES = src/game_main.c src/entity.c src/display.c
TEST_OBJECTS = $(patsubst %.c,build/%.o,$(TEST_SOURCES))
GAME_OBJECTS = $(patsubst %.c,build/%.o,$(GAME_SOURCES))

.PHONY: all test game run clean

all: $(TEST)

$(LIB): build/src/liste_element.o
	$(AR) rcs $@ $^

$(TEST): $(TEST_OBJECTS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(GAME): $(GAME_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(NCURSES_LIBS)

build/%.o: %.c $(wildcard include/*.h)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

game: $(GAME)

run: game
	./$(GAME)

test: $(TEST)
	./$(TEST)

clean:
	rm -rf build $(LIB) $(TEST) $(GAME)
