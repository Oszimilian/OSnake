/*
 * Eingabe.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#include "Configuration.h"
#include "Eingabe.h"
#include <ncurses.h>

Eingabe* eingabe_erzeugen ()
{
	Eingabe* e_ptr = (Eingabe*)malloc(sizeof(Eingabe));
	eingabe_init(e_ptr);
	return e_ptr;
}

void eingabe_init(struct Eingabe* eingabe_ptr)
{
	eingabe_ptr->letzte_eingabe_spieler_1 = BEWEGUNG_RECHTS;
	eingabe_ptr->letzte_eingabe_spieler_2 = BEWEGUNG_LINKS;

	eingabe_ptr->flushEnable = 1;
}

void eingabe_einlesen(struct Eingabe* eingabe_ptr)
{
	char c = 'X';

	char *spieler1 = &eingabe_ptr->letzte_eingabe_spieler_1;
	char *spieler2 = &eingabe_ptr->letzte_eingabe_spieler_2;

	for (int i = 0; i < 100; i++)
	{
		c = getch();
		eingabe_ptr->input = c;

		switch (c)
		{
			case SPIELER_1_HOCH:
				*spieler1 = (*spieler1 == BEWEGUNG_RUNTER) ? *spieler1 : BEWEGUNG_HOCH;
				break;
			case SPIELER_2_HOCH:
				*spieler2 = (*spieler2 == BEWEGUNG_RUNTER) ? *spieler2 : BEWEGUNG_HOCH;
				break;
			case SPIELER_1_RUNTER:
				*spieler1 = (*spieler1 == BEWEGUNG_HOCH) ? *spieler1 : BEWEGUNG_RUNTER;
				break;
			case SPIELER_2_RUNTER:
				*spieler2 = (*spieler2 == BEWEGUNG_HOCH) ? *spieler2 : BEWEGUNG_RUNTER;
				break;
			case SPIELER_1_LINKS:
				*spieler1 = (*spieler1 == BEWEGUNG_RECHTS) ? *spieler1 : BEWEGUNG_LINKS;
				break;
			case SPIELER_2_LINKS:
				*spieler2 = (*spieler2 == BEWEGUNG_RECHTS) ? *spieler2 : BEWEGUNG_LINKS;
				break;
			case SPIELER_1_RECHTS:
				*spieler1 = (*spieler1 == BEWEGUNG_LINKS) ? *spieler1 : BEWEGUNG_RECHTS;
				break;
			case SPIELER_2_RECHTS:
				*spieler2 = (*spieler2 == BEWEGUNG_LINKS) ? *spieler2 : BEWEGUNG_RECHTS;
				break;
			default:
				break;

				//UNGÜLTIG / UNBEKANNT
		}

		if (eingabe_ptr->flushEnable)
		{
			flushinp(); 	// Leert den Puffer
		}

		usleep(100); 	// Hält den Thread für 100 us an.
	}


}

