#include "Console.h"
#include <ncurses.h>
#include "Configuration.h"

//Initialisiert ncurses
void console_init()
{
	initscr();				/* Starte curses  		  */
	clear();
	noecho();				// Eingaben werden nicht angezeigt
	cbreak();
	nodelay(stdscr, TRUE);	// Keine Pufferung von getch()
	curs_set(0);			// Verstecke Cursor
	start_color();			// Aktiviere Farbunterstützung

	//Initialisiere Farben
	init_pair(SPIELER_1_FARBE, COLOR_RED, COLOR_GREEN);
	init_pair(SPIELER_2_FARBE, COLOR_RED, COLOR_RED);
	init_pair(SPIELFELD_RAND_FARBE, COLOR_RED, COLOR_BLUE);
	init_pair(SPIELFELD_HINTERGRUND_FARBE, COLOR_RED, COLOR_BLACK);
	attrset(COLOR_PAIR(SPIELFELD_HINTERGRUND_FARBE));

	if (!has_colors())
	{
		printw("Keine Farbunterstützung!!!!!");
	}
	console_leeren();
	console_cursor_verstecken();
}


//Leere Terminal
void console_leeren()
{
	clear();
}

//Verstecke Cursor
void console_cursor_verstecken()
{
	curs_set(0);			// Verstecke Cursor
}

//Zeigt den Cursor
void console_cursor_zeigen()
{
	curs_set(1);			// Zeige Cursor
}

//Gebe Zeichen c an Position x, y aus
void console_zeichne_punkt(int x, int y, char c)
{
	mvaddch(y, x, c);
}

//Positioniere Cursor an Position x,y
void console_cursor_bewegen(int x, int y)
{
	move(y,x);
}


