#ifndef CONSOLE_H
#define CONSOLE_H

//https://ansi.gabebanks.net/
//https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit

void console_init();				//Leere Terminal, verstecke Cursor, Position 0,0
void console_leeren();				//Leere Terminal

void console_cursor_verstecken();			//Verstecke Cursor
void console_cursor_zeigen();				//Zeige Cursor

void console_cursor_bewegen(int x, int y); //Bewege Cursor auf Position x, y

void console_zeichne_punkt(int x, int y, char c); //Zeichne Zeichen c an Position x, y

#endif

