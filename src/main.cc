#include <curses.h>

#include "grid.h"
#include "config.h"

#define NCURSES_ERROR(func, msg) do { if (!isendwin()) { curs_set(1); clear(); endwin(); delwin(stdscr); } \
fputs("ncurses error (" #func "): " msg "\n", stderr); return -1; } while (0)

constexpr bool strings_equal(char const * a, char const * b) {
	return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1));
}

std::size_t badlog2 (short n) {
	switch (n) {
	case 1:
		return 0;
	case 2:
		return 1;
	case 4:
		return 2;
	case 8:
		return 3;
	case 16:
		return 4;
	case 32:
		return 5;
	case 64:
		return 6;
	case 128:
		return 7;
	case 256:
		return 8;
	case 512:
		return 9;
	case 1024:
		return 10;
	case 2048:
		return 11;
	case 4096:
		return 12;
	case 8192:
		return 13;
	case 16384:
		return 14;
	}
	return -1;
}

int main () {
	WINDOW *board = NULL;
	int ch = 0;
	short *number_colors = NULL;
	short *number_pairs = NULL;
	twentyfortyeight::Grid game(4);
	game.add(); game.add();
	initscr();
	raw();
	curs_set(0);
	noecho();
	if (has_colors()) {
		if (start_color() == ERR) NCURSES_ERROR(start_color, "Initializing color");
		number_pairs = new short[7 + 1]();
		for (int i = 0; i < 8; ++i) number_pairs[i] = i + 1;
		if (init_pair(number_pairs[0], COLOR_WHITE, COLOR_BLACK) == ERR) NCURSES_ERROR(init_pair, "Empty cell");
		if (can_change_color()) {
			number_colors = new short[7 + 1]();
			for (int i = 0; i < 7 + 8; ++i) number_colors[i] = i + 8;
			#define NCURSES_INIT_NUM_COLOR(i, r, b, g) if (init_color(number_colors[ i ], r, b, g) == ERR) NCURSES_ERROR(init_color, "Setting up colors for different numbers.")
			NCURSES_INIT_NUM_COLOR(1, 937, 898, 843);
			NCURSES_INIT_NUM_COLOR(2, 921, 875, 789);
			NCURSES_INIT_NUM_COLOR(3, 937, 703, 468);
			NCURSES_INIT_NUM_COLOR(4, 957, 582, 382);
			NCURSES_INIT_NUM_COLOR(5, 992, 464, 355);
			NCURSES_INIT_NUM_COLOR(6, 960, 367, 210);
			NCURSES_INIT_NUM_COLOR(7, 929, 800, 449);
			#undef NCURSES_INIT_NUM_COLOR

			for (int i = 1; i < 8; ++i) {
				#ifdef HAVE_ALLOC_PAIR
				number_pairs[i] = alloc_pair((i < 3 ? COLOR_BLACK : COLOR_WHITE), number_colors[i]);
				if (number_pairs[i] == -1) NCURSES_ERROR(alloc_pair, "Setting up changed color pairs.");
				#else
				if (init_pair(number_pairs[i], (i < 3 ? COLOR_BLACK : COLOR_WHITE), number_colors[i]) == ERR) NCURSES_ERROR(init_pair, "Setting up changed color pairs.");
				#endif
			}
		} else {
			#ifdef HAVE_ALLOC_PAIR
			#define NCURSES_INIT_NUM_PAIR(i, col) if ((number_pairs[ i ] = alloc_pair(COLOR_WHITE, COLOR_ ## col)) == -1) NCURSES_ERROR(alloc_pair, "Setting up non-changeable color pairs.")
			#else
			#define NCURSES_INIT_NUM_PAIR(i, col) if (init_pair(number_pairs[ i ], COLOR_WHITE, COLOR_ ## col) == ERR) NCURSES_ERROR(init_pair, "Setting up non-changeable color pairs.")
			#endif
			NCURSES_INIT_NUM_PAIR(1, BLACK);
			NCURSES_INIT_NUM_PAIR(2, RED);
			NCURSES_INIT_NUM_PAIR(3, GREEN);
			NCURSES_INIT_NUM_PAIR(4, YELLOW);
			NCURSES_INIT_NUM_PAIR(5, BLUE);
			NCURSES_INIT_NUM_PAIR(6, MAGENTA);
			NCURSES_INIT_NUM_PAIR(7, CYAN);
			#undef NCURSES_INIT_NUM_PAIR
		}
	}

	board = newwin(4 + 5 + 1, 4 * 5 + 5, 0, 0);
	wtimeout(board, -1);
	keypad(board, TRUE);

	// Draw box
	for (decltype(game.size()) y = 0; y < game.size(); ++y) {
		for (decltype(game.size()) x = 0; x <= game.size(); ++x) {
			mvwaddch(board, y * 2 + 1, x * 6, ACS_VLINE);
		}
		mvwhline(board, y * 2, 0, ACS_HLINE, 24);
		mvwaddch(board, y * 2, 0, ACS_LTEE);
		mvwaddch(board, y * 2, 6, ACS_PLUS);
		mvwaddch(board, y * 2, 12, ACS_PLUS);
		mvwaddch(board, y * 2, 18, ACS_PLUS);
		mvwaddch(board, y * 2, 24, ACS_RTEE);
	}

	// Top row
	mvwaddch(board, 0, 0, ACS_ULCORNER);
	mvwaddch(board, 0, 6, ACS_TTEE);
	mvwaddch(board, 0, 12, ACS_TTEE);
	mvwaddch(board, 0, 18, ACS_TTEE);
	mvwaddch(board, 0, 24, ACS_URCORNER);

	// Bottom row
	mvwhline(board, 8, 0, ACS_HLINE, 24);
	mvwaddch(board, 8, 0, ACS_LLCORNER);
	mvwaddch(board, 8, 6, ACS_BTEE);
	mvwaddch(board, 8, 12, ACS_BTEE);
	mvwaddch(board, 8, 18, ACS_BTEE);
	mvwaddch(board, 8, 24, ACS_LRCORNER);

	while (ch != 'q') {
		switch (ch) {
		case KEY_UP:
		case 'w':
			game.move(game.up);
			break;
		case KEY_DOWN:
		case 's':
			game.move(game.down);
			break;
		case KEY_LEFT:
		case 'a':
			game.move(game.left);
			break;
		case KEY_RIGHT:
		case 'd':
			game.move(game.right);
			break;
		}

		if (game.moved()) game.add();
		for (decltype(game.size()) y = 0; y < game.size(); ++y) {
			for (decltype(game.size()) x = 0; x < game.size(); ++x) {
				if (has_colors()) {
					if (game(x, y) > 128) {
						wattron(board, A_BLINK);
						wattron(board, COLOR_PAIR(number_pairs[badlog2(game(x, y) >> 7)]));
						mvwprintw(board, y * 2 + 1, x * 6 + 1, "%5d", game(x, y));
						wattroff(board, COLOR_PAIR(number_pairs[badlog2(game(x, y) >> 7)]));
						wattroff(board, A_BLINK);
					} else {
						wattron(board, COLOR_PAIR(number_pairs[badlog2(game(x, y))]));
						mvwprintw(board, y * 2 + 1, x * 6 + 1, "%5d", game(x, y));
						wattroff(board, COLOR_PAIR(number_pairs[badlog2(game(x, y))]));
					}
				}
			}
		}
		if (game.unmovable()) mvwaddstr(board, 9, 0, "You lose! :(");
		wnoutrefresh(stdscr);
		wnoutrefresh(board);
		doupdate();
		ch = wgetch(board);
		ch = tolower(ch);
	}
	if (has_colors() && number_pairs != NULL) delete[] number_pairs;
	if (can_change_color() && number_pairs != NULL) delete[] number_colors;
	#ifdef HAVE_USE_DEFAULT_COLORS
	use_default_colors();
	#endif
	#ifdef HAVE_RESET_COLOR_PAIRS
	reset_color_pairs();
	#endif
	werase(board);
	delwin(board);
	endwin();
	delwin(stdscr);
	return 0;
}
