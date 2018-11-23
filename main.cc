#include "ncurses.h"

#include "grid.h"

int main () {
	WINDOW *board = NULL;
	int ch = 0;
	twentyfortyeight::Grid game(4);
	game.add(); game.add();
	initscr();
	raw();
	curs_set(0);
	noecho();
	board = newwin(4 + 5, 4 * 5 + 5, 0, 0);
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
				mvwprintw(board, y * 2 + 1, x * 6 + 1, "%5d", game(x, y));
			}
		}
		wnoutrefresh(stdscr);
		wnoutrefresh(board);
		doupdate();
		ch = wgetch(board);
		ch = tolower(ch);
	}
	werase(board);
	delwin(board);
	endwin();
	delwin(stdscr);
	return 0;
}
