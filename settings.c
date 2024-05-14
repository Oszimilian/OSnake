/*
 * settings.c
 *
 *  Created on: 21.12.2022
 *      Author: maximilian
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Configuration.h"
#include "pixelgruppe.h"
#include "Spiel.h"
#include "settings.h"
#include "Eingabe.h"
#include "Console.h"

void clearScreen(int farbe)
{
	attron(COLOR_PAIR(farbe));

	for (int y = 0; y < MAX_SCREEN_SIZE_Y; y++)
	{
		for (int x = 0; x < MAX_SCREEN_SIZE_X; x++)
		{
			console_zeichne_punkt(x, y, ' ');
		}
	}
}

void printSettingMenue(CharacterList *list, int farbe)
{
	printPixelString(list, "PICKUPS", 10, 10, farbe);
	printPixelString(list, "WURMHOLE", 10, 18, farbe);
	printPixelString(list, "START", 10, 26, farbe);
	printPixelString(list, "QUIT", 10, 34, farbe);
}

int settingsChooser(CharacterList *list, int farbe, int updown)
{
	static int pos = 10;

	printPixelString(list, "#", 2, pos, 4);

	//up
	if (updown == 1)
	{
		pos = (pos < 34) ? pos + 8 : pos;
	} else {
		pos = (pos > 10) ? pos - 8 : pos;
	}

	printPixelString(list, "#", 2, pos, 1);

	return pos;
}

int valueChooser(CharacterList *list, int farbe, int pos,  int defaultValue)
{
	char str[128];
	char input = 0;

	do
	{

		sprintf(str, "%d", defaultValue);
		printPixelString(list, str, 80, pos, farbe);

		input = getch();

		if (input == 'w')
		{
			defaultValue++;
		}
		else if(input == 's' && defaultValue > 0)
		{
			defaultValue--;
		}

		printPixelString(list, str, 80, pos, 4);

	}while(input!= 'm');




	return defaultValue;
}

void displayWinningScreen(Spiel *spiel_ptr, CharacterList *list, int farbe)
{
	char str[4][128];
	int winner = 0;
	static int start = 1;

	if(spiel_ptr->winner == spiel_ptr->s1_ptr)
	{
		winner = 1;
	}
	else if (spiel_ptr->winner == spiel_ptr->s2_ptr)
	{
		winner = 2;
	}
	else
	{
		winner = 0;
	}

	sprintf(str[0], " ");
	sprintf(str[1], "GEWINNER IST");
	sprintf(str[2], "SPIELER %d", winner);
	sprintf(str[3], "NICHT ERMITTELBAR %d", winner);

	if (winner == 0 && start == 0)
	{
		printPixelString(list, str[1],100, 30, 1);
		printPixelString(list, str[3],100, 38, 1);
	}
	else if (winner == 0 && start == 1)
	{

	} else {
		printPixelString(list, str[1],100, 30, 1);
		printPixelString(list, str[2],100, 38, 1);
	}

	start = 0;
}

void displaySettingsScreen(Spiel *spiel_ptr, CharacterList *list)
{
	char input = 0;
	static int pos = 10;

	clearScreen(SPIELFELD_HINTERGRUND_FARBE);
	printSettingMenue(list, 1);
	printPixelString(list, "SNAKE BY OSZIMILIAN", 50, 1, SPIELER_1_FARBE);
	printPixelString(list, "#", 2, pos, 1);

	displayWinningScreen(spiel_ptr, list, 1);

	nodelay(stdscr, FALSE);


	do
	{
		input = getch();

		if (input == 'w') pos = settingsChooser(list, 1, 0);
		else if (input == 's') pos = settingsChooser(list, 1, 1);

		if (pos == 10 && input == 'm')
		{
			spiel_ptr->pickup_ptr->maxPickup = valueChooser(list, 1, pos, 10);
		}
		if (pos == 18 && input == 'm')
		{
			spiel_ptr->wormhole_ptr->maxWormhole = valueChooser(list, 1, pos, 1);
		}
		if (pos == 26 && input == 'm')
		{
			input = 'q';
		}
		if (pos == 34 && input == 'm')
		{
			exit(-1);
		}

	}while(input != 'q');


	nodelay(stdscr, TRUE );


	clearScreen(SPIELFELD_HINTERGRUND_FARBE);

}
