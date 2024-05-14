/*
 * Spiel.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Configuration.h"
#include "Console.h"

#include "pickup.h"
#include "wormhole.h"
#include "Spiel.h"

void spiel_init(Spiel* spiel_ptr)
{
	spiel_ptr->s1_ptr = schlange_erzeugen();
	spiel_ptr->s2_ptr = schlange_erzeugen();

	liste_einfuegen_kopf(spiel_ptr->s1_ptr->positionen_ptr, element_erzeugen());
	liste_einfuegen_kopf(spiel_ptr->s2_ptr->positionen_ptr, element_erzeugen());

	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_1_XPOS;
	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s1_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.x = SPIELER_2_XPOS;
	spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr->pos.y = SPIELER_YPOS;
	spiel_ptr->s2_ptr->wachsen = SPIEL_SCHLANGEN_LAENGE;

	spiel_ptr->run = 1;
}

Spiel* spiel_erzeugen()
{
	srand(time(NULL));

	Spiel *spiel_ptr = (Spiel*) malloc(sizeof(Spiel));
	spiel_init(spiel_ptr);

	spiel_ptr->pickup_ptr = init_pickup();
	spiel_ptr->wormhole_ptr = initWormhole();

	spiel_ptr->winner = NULL;

	return spiel_ptr;
}

void spiel_zeichne_rand()
{
	attron(COLOR_PAIR(SPIELFELD_RAND_FARBE));



	for (int i = 0; i < SPIELFELD_XSIZE; i++)
	{
		console_zeichne_punkt(i + SPIELFELD_OFFSET_X, SPIELFELD_OFFSET_Y, ' ');
		console_zeichne_punkt(i + SPIELFELD_OFFSET_X, SPIELFELD_OFFSET_Y + SPIELFELD_YSIZE, ' ');
	}
	for (int i = 0; i <= SPIELFELD_YSIZE; i++)
	{
		console_zeichne_punkt(SPIELFELD_OFFSET_X, SPIELFELD_OFFSET_Y + i, ' ');
		console_zeichne_punkt(SPIELFELD_OFFSET_X + SPIELFELD_XSIZE, SPIELFELD_OFFSET_Y + i, ' ');
	}
}

void spiel_pruefe_kollission(Spiel* spiel_ptr)
{
	Element *snake[2] = { 	spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr,
							spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr};

	//Schlange 1 hat Schlange 2 gebissen
	if (element_folge_pruefen(snake[0], snake[1]))
	{
		spiel_ptr->run = 0;
		spiel_ptr->winner = spiel_ptr->s2_ptr;
		return;
	}

	//Schlange 2 hat Schlange 1 gebissen
	if (element_folge_pruefen(snake[1], snake[0]))
	{
		spiel_ptr->run = 0;
		spiel_ptr->winner = spiel_ptr->s2_ptr;
		return;
	}

	//Schlange 1 hat sich selber gebissen
	if (element_folge_pruefen(snake[0], snake[0]->nachfolger_ptr))
	{
		spiel_ptr->run = 0;
		spiel_ptr->winner = spiel_ptr->s2_ptr;
		return;
	}

	//Schlange 2 hat sich selber gebissen
	if (element_folge_pruefen(snake[1], snake[1]->nachfolger_ptr))
	{
		spiel_ptr->run = 0;
		spiel_ptr->winner = spiel_ptr->s1_ptr;
		return;
	}

	//Schlange 1 oder schlange zwei hat den Rand berührt
	for(int i = 0; i < 2; i++)
	{
		if(snake[i]->pos.x >= SPIELFELD_OFFSET_X && snake[i]->pos.x <= (SPIELFELD_OFFSET_X + SPIELFELD_XSIZE) )
		{
			if (snake[i]->pos.y == SPIELFELD_OFFSET_Y || snake[i]->pos.y == (SPIELFELD_OFFSET_Y + SPIELFELD_YSIZE))
			{
				spiel_ptr->run = 0;
				spiel_ptr->winner = (i == 0) ? spiel_ptr->s2_ptr : spiel_ptr->s1_ptr;
				return;
			}
		}

		if (snake[i]->pos.y >= SPIELFELD_OFFSET_Y && snake[i]->pos.y <= (SPIELFELD_OFFSET_Y + SPIELFELD_YSIZE))
		{
			if (snake[i]->pos.x == SPIELFELD_OFFSET_X || snake[i]->pos.x == (SPIELFELD_OFFSET_X + SPIELFELD_XSIZE))
			{
				spiel_ptr->run = 0;
				spiel_ptr->winner = (i == 0) ? spiel_ptr->s2_ptr : spiel_ptr->s1_ptr;
				return;
			}
		}
	}
}

void spiel_zeichne_spielstand()
{
	//Aufgabe 4e)     OPTIONAL
	//TODO
}

void resetGame(Spiel *spiel_ptr)
{
	int maxWormhole = spiel_ptr->wormhole_ptr->maxWormhole;
	int maxPickup = spiel_ptr->pickup_ptr->maxPickup;

	free(spiel_ptr->pickup_ptr);
	free(spiel_ptr->wormhole_ptr);

	spiel_ptr->pickup_ptr = init_pickup();
	spiel_ptr->pickup_ptr->maxPickup = maxPickup;

	spiel_ptr->wormhole_ptr = initWormhole();
	spiel_ptr->wormhole_ptr->maxWormhole = maxWormhole;

	spiel_ptr->winner = NULL;

	spiel_ptr->s1_ptr->punkte = 0;
	spiel_ptr->s2_ptr->punkte = 0;

	spiel_ptr->s1_ptr->positionen_ptr->laenge = SPIEL_SCHLANGEN_LAENGE;
	spiel_ptr->s2_ptr->positionen_ptr->laenge = SPIEL_SCHLANGEN_LAENGE;



}


