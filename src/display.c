#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <wchar.h>
#include <ncursesw/curses.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "display.h"

#define MIN_COLS 80
#define MIN_ROWS 24
#define FOOTER_HEIGHT 4
#define BAR_WIDTH 40

static WINDOW *hero_win = NULL;
static WINDOW *environment_win = NULL;
static WINDOW *monster_win = NULL;
static WINDOW *footer_win = NULL;

static int layout_ready = 0;

static void destroy_windows(void)
{
    if (hero_win != NULL) {
        delwin(hero_win);
        hero_win = NULL;
    }
    if (environment_win != NULL) {
        delwin(environment_win);
        environment_win = NULL;
    }
    if (monster_win != NULL) {
        delwin(monster_win);
        monster_win = NULL;
    }
    if (footer_win != NULL) {
        delwin(footer_win);
        footer_win = NULL;
    }

    layout_ready = 0;
}

static int create_windows(void)
{
    int rows;
    int cols;
    int panel_height;
    int footer_y;
    int hero_width;
    int monster_width;
    int environment_width;

    destroy_windows();

    getmaxyx(stdscr, rows, cols);

    if (cols < MIN_COLS || rows < MIN_ROWS) {
        erase();
        mvaddstr(0, 0, "Terminal trop petit pour C-Dungeon.");
        mvaddstr(1, 0, "Il faut au minimum 80 colonnes et 24 lignes.");
        mvaddstr(2, 0, "Agrandissez le terminal puis appuyez sur une touche.");
        refresh();
        return -1;
    }

    panel_height = rows - FOOTER_HEIGHT;
    footer_y = panel_height;

    hero_width = cols /3 ;
    monster_width = cols /3;
    environment_width = cols /3;

    hero_win = newwin(panel_height, hero_width, 0, 0);
    environment_win = newwin(
        panel_height, environment_width, 0, hero_width
    );
    monster_win = newwin(
        panel_height, monster_width, 0,
        hero_width + environment_width
    );
    footer_win = newwin(FOOTER_HEIGHT, cols, footer_y, 0);

    if (hero_win == NULL || environment_win == NULL ||
        monster_win == NULL || footer_win == NULL) {
        destroy_windows();
        return -1;
    }

    keypad(stdscr, TRUE);
    keypad(footer_win, TRUE);

    layout_ready = 1;
    return 0;
}

int display_init(void)
{
    setlocale(LC_ALL, "");

    if (initscr() == NULL) {
        return -1;
    }

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        use_default_colors();

        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_CYAN, -1);
        init_pair(4, COLOR_YELLOW, -1);
        init_pair(5, COLOR_WHITE, -1);
    }

    if (create_windows() != 0) {
        endwin();
        return -1;
    }

    return 0;
}

/* Affiche un fichier texte dans une fenetre sans depasser ses limites. */
static void draw_ascii_file(
    WINDOW *win,
    const char *path,
    int start_y,
    int start_x,
    int max_lines,
    int max_width
)
{
    FILE *file;
    wchar_t line[512];
    int line_number = 0;

    if (path == NULL) {
        mvwaddstr(win, start_y, start_x, "(Aucun decor)");
        return;
    }

    file = fopen(path, "r");
    if (file == NULL) {
        mvwaddstr(win, start_y, start_x, "(Fichier introuvable)");
        return;
    }

    while (line_number < max_lines &&
           fgetws(line, (int)(sizeof(line) / sizeof(line[0])), file) != NULL) {
        int length = (int)wcslen(line);
        int i;

        while (length > 0 &&
               (line[length - 1] == L'\n' ||
                line[length - 1] == L'\r')) {
            line[--length] = L'\0';
        }

        for (i = 0; i < length && i < max_width; i++) {
            mvwaddnwstr(win, start_y + line_number, start_x,
                        line, i + 1);
        }

        line_number++;
    }

    fclose(file);
}

static void draw_bar(
    WINDOW *win,
    int y,
    int x,
    int width,
    int value,
    int max_value,
    int color_pair
)
{
    int i;
    int filled;

    if (width <= 0) {
        return;
    }

    if (max_value <= 0) {
        value = 0;
        max_value = 1;
    }

    if (value < 0) {
        value = 0;
    }
    if (value > max_value) {
        value = max_value;
    }

    filled = value * width / max_value;

    wattron(win, COLOR_PAIR(color_pair));

    for (i = 0; i < width; i++) {
        mvwaddnwstr(win, y, x + i,
                    i < filled ? L"█" : L"░", 1);
    }

    wattroff(win, COLOR_PAIR(color_pair));

    wrefresh(win);
}



static void draw_hero(const Joueur *joueur)
{
    int y = 1;
    const Item *item;

    box(hero_win, 0, 0);
    wattron(hero_win, A_BOLD);
    mvwaddstr(hero_win, 0, 2, " HEROS ");
    wattroff(hero_win, A_BOLD);

    mvwprintw(hero_win, 2, 2, "Nom: %.40s", joueur->nom);


    mvwaddstr(hero_win, 4, 2, "PV");
    draw_bar(hero_win, 5, 2, BAR_WIDTH,
            joueur->hp, joueur->max_hp, 2);

    mvwaddstr(hero_win, 8, 2, "MANA");
    draw_bar(hero_win, 9, 2, BAR_WIDTH,
            joueur->mana, joueur->max_mana, 3);

    mvwprintw(hero_win, 12, 2, "Or : %d", joueur->gold);
    mvwaddstr(hero_win, 14, 2, "INVENTAIRE");

    item = joueur->inventaire;
    y = 15;

    if (item == NULL) {
        mvwaddstr(hero_win, y, 2, "(vide)");
    }

    while (item != NULL && y < getmaxy(hero_win) - 2) {
        mvwprintw(hero_win, y, 2, "- %.30s", item->nom);
        y++;
        item = item->next;
    }

    wrefresh(hero_win);
}

static void draw_environment(const char *path)
{
    int height;
    int width;

    getmaxyx(environment_win, height, width);
    box(environment_win, 0, 0);

    wattron(environment_win, A_BOLD);
    mvwaddstr(environment_win, 0, 2, " ENVIRONNEMENT ");
    wattroff(environment_win, A_BOLD);

    draw_ascii_file(
        environment_win, path,
        2, 2, height - 4, width - 4
    );

    wrefresh(environment_win);
}

static void draw_monster(
    const char *name,
    const char *path,
    int hp,
    int max_hp
)
{
    int height;
    int width;

    getmaxyx(monster_win, height, width);
    box(monster_win, 0, 0);

    wattron(monster_win, A_BOLD);
    mvwaddstr(monster_win, 0, 2, " MONSTRE ");
    wattroff(monster_win, A_BOLD);

    mvwprintw(monster_win, 2, 2, "%.25s", name);

    mvwaddstr(monster_win, 4, 2, "PV");
        draw_ascii_file(
        monster_win, path,
        9, 2, height - 11, width - 4
    );

    draw_bar(monster_win, 5, 1, width - 2, hp, max_hp, 2);


    wrefresh(monster_win);
}


static void draw_footer(const char *message)
{
    int height;
    int width;

    getmaxyx(footer_win, height, width);
    (void)height;

    werase(footer_win);
    box(footer_win, 0, 0);

    mvwaddnstr(
        footer_win, 1, 2,
        "[A] Attaquer  [S] Sort  [P] Potion  [F] Fuir  [Q] Quitter",
        width - 4
    );

    if (message != NULL) {
        mvwaddnstr(footer_win, 2, 2, message, width - 4);
    }

    wrefresh(footer_win);
}


void display_render(
    const Joueur *joueur,
    const char *environment_path,
    const char *monster_name,
    const char *monster_path,
    int monster_hp,
    int monster_max_hp,
    const char *message
)
{
    if (joueur == NULL) {
        return;
    }

    if (is_term_resized(LINES, COLS)) {
        endwin();
        refresh();
        clear();
        if (create_windows() != 0) {
            return;
        }
    }

    if (!layout_ready) {
        return;
    }

    draw_hero(joueur);
    draw_environment(environment_path);
    draw_monster(monster_name, monster_path,
                 monster_hp, monster_max_hp);
    draw_footer(message);
}

int display_get_action(void)
{
    int key;

    if (!layout_ready) {
        return 'q';
    }

    key = wgetch(footer_win);

    if (key == KEY_RESIZE) {
        endwin();
        refresh();
        clear();
        create_windows();
        return '\0';
    }

    return tolower((unsigned char)key);
}

void display_shutdown(void)
{
    destroy_windows();
    endwin();
}
