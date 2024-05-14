/*
 * spielstand.c
 *
 *  Created on: Dec 17, 2022
 *      Author: maximilian
 */
#include "Configuration.h"
#include "Console.h"
#include "Spiel.h"
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "spielstand.h"
#include "pixelgruppe.h"



Spielstand *inti_PixelGruppe(int x, int y)
{
	Spielstand *spielstand = (Spielstand*) malloc(sizeof(Spielstand));

	if (spielstand == NULL)
	{
		fprintf(stderr, "Der Spielstand konnte nicht erzeugt werden !\n");
		return NULL;
	}

	spielstand->x = x;
	spielstand->y = y;

	return spielstand;
}

void print_spielstand(Spielstand *spielstand, CharacterList *list, int farbe)
{
	int local_spielstand[2];
	local_spielstand[0] = spielstand->spielstand_spieler1 - SPIEL_SCHLANGEN_LAENGE;
	local_spielstand[1] = spielstand->spielstand_spieler2 - SPIEL_SCHLANGEN_LAENGE;

	local_spielstand[0] = (local_spielstand[0] < 0) ? 0 : local_spielstand[0];
	local_spielstand[1] = (local_spielstand[1] < 0) ? 0 : local_spielstand[1];

	int start_x = spielstand->x;
	int start_y = spielstand->y;

	char spielstandString[128];
	sprintf(spielstandString, "%d:%d", local_spielstand[0], local_spielstand[1]);
	printPixelString(list, spielstandString, start_x, start_y, farbe);
}

void update_Spielstand(Spielstand *spielstand_ptr, Spiel *spiel_ptr, CharacterList *list)
{
	attron(COLOR_PAIR(SPIELFELD_HINTERGRUND_FARBE));

	int laenge_spieler1 = spiel_ptr->s1_ptr->positionen_ptr->laenge;
	int laenge_spieler2 = spiel_ptr->s2_ptr->positionen_ptr->laenge;

	//mvprintw(10,10, "(%d) (%d) ", laenge_spieler1, laenge_spieler2);


	if (laenge_spieler1 > SPIEL_SCHLANGEN_LAENGE && laenge_spieler2 > SPIEL_SCHLANGEN_LAENGE)
	{
		spielstand_ptr->spielstand_spieler1 = laenge_spieler1 - 1;
		spielstand_ptr->spielstand_spieler2 = laenge_spieler2 - 1;
	}

	attron(COLOR_PAIR(SPIELER_1_FARBE));
	print_spielstand(spielstand_ptr, list, SPIELER_1_FARBE);
}

