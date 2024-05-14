/*
 ============================================================================
 Name        : SimpleSnake.c
 Author      : StudentT
 Version     :
 Copyright   : Hochschule Augsburg
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// Informationen zu ncurses => https://de.wikibooks.org/wiki/Ncurses:_Grundlegendes#ncurses_und_I/O-Befehle_von_C
// Informationen zu ncurses => https://openbook.rheinwerk-verlag.de/linux_unix_programmierung/Kap13-002.htm

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Configuration.h"
#include "Console.h"
#include "Eingabe.h"

#include "Schlange.h"
#include "pickup.h"
#include "wormhole.h"
#include "spielstand.h"
#include "pixelgruppe.h"

#include "settings.h"

#include "Spiel.h"

int main(void) {

	console_init();

	Spielstand *spielstand_ptr = inti_PixelGruppe(5, 1);

	CharacterList *pixelList = initPixelGroup();

	Eingabe* eingabe_ptr = eingabe_erzeugen();

	Spiel* spiel_ptr = spiel_erzeugen();



	displaySettingsScreen(spiel_ptr, pixelList);


	printPixelString(pixelList, "SNAKE BY OSZIMILIAN", 50, 1, SPIELER_1_FARBE);

	spiel_zeichne_rand();

	refresh();
	getchar();



	while(1)
	{
		//spiel_ptr->winner = NULL;

		while(spiel_ptr->run == 1)
		{
			//Zeichnet den Spielstand
			update_Spielstand(spielstand_ptr, spiel_ptr, pixelList);
			//Einlesen der Eingabe
			eingabe_einlesen(eingabe_ptr);

			//Zeichne Schlange 1
			schlange_zeichne(spiel_ptr->s1_ptr, SPIELFELD_HINTERGRUND_FARBE);
			schlange_bewege(spiel_ptr->s1_ptr, eingabe_ptr->letzte_eingabe_spieler_1);
			schlange_zeichne(spiel_ptr->s1_ptr, SPIELER_1_FARBE);

			//Zeichne Schlange 2
			schlange_zeichne(spiel_ptr->s2_ptr, SPIELFELD_HINTERGRUND_FARBE);
			schlange_bewege(spiel_ptr->s2_ptr, eingabe_ptr->letzte_eingabe_spieler_2);
			schlange_zeichne(spiel_ptr->s2_ptr, SPIELER_2_FARBE);

			print_Pickup(spiel_ptr, SPIELFELD_HINTERGRUND_FARBE);
			plaziere_Pickup(spiel_ptr);
			print_Pickup(spiel_ptr, SPIELER_1_FARBE);



			//Prüfe auf Kollission => Relevant für Spielende
			spiel_pruefe_kollission(spiel_ptr);

			//Zeichnet die Pickups
			handle_pickup_conflict(spiel_ptr);

			printWormhole(spiel_ptr, SPIELFELD_HINTERGRUND_FARBE);
			sparnRandomWormholeElement(spiel_ptr);
			handleWormholeCollision(spiel_ptr);
			printWormhole(spiel_ptr, SPIELER_2_FARBE);

			//Spielzeit erhöhen
			spiel_ptr->schritte++;

			refresh();
			//Pausieren des Main-Thread - Spielgeschwindigkeit
			usleep(SPIEL_GESCHWINDIGKEIT);
		}

		//spiel_ptr = spiel_erzeugen();


		displaySettingsScreen(spiel_ptr, pixelList);

		printPixelString(pixelList, "SNAKE BY OSZI", 50, 1, SPIELER_1_FARBE);

		spiel_zeichne_rand();

		eingabe_init(eingabe_ptr);

		resetGame(spiel_ptr);

		spielstand_ptr->spielstand_spieler1 = 0;
		spielstand_ptr->spielstand_spieler2 = 0;

		spiel_init(spiel_ptr);
	}

	//Warte auf Tastendruck
	getchar();
	endwin();

	return EXIT_SUCCESS;
}
