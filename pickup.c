/*
 * pickup.c
 *
 *  Created on: 16.12.2022
 *      Author: student
 */

#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Configuration.h"
#include "Console.h"

#include "pickup.h"
#include "Spiel.h"

Pickup *init_pickup()
{
	Pickup *pickup_ptr = (Pickup*) malloc(sizeof(Pickup));

	if (pickup_ptr == NULL)
	{
		fprintf(stderr, "Pickup konnte nicht erzeugt werden! \n");
		return NULL;
	}

	pickup_ptr->pickup_list = liste_erzeugen();

	pickup_ptr->last_time = clock();

	pickup_ptr->time_intervall = 10000;

	pickup_ptr->maxPickup = 10;
	pickup_ptr->pickupAmount = 0;

	return pickup_ptr;
}


void plaziere_Pickup(Spiel *spiel_ptr)
{
	if( 	((clock() - spiel_ptr->pickup_ptr->last_time) >= spiel_ptr->pickup_ptr->time_intervall) &&
			(spiel_ptr->pickup_ptr->pickupAmount < spiel_ptr->pickup_ptr->maxPickup))
	{

		Element *element = element_erzeugen();
		Element *snake1 = spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr;
		Element *snake2 = spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr;

		do
		{

			element->pos.x = SPIELFELD_OFFSET_X + 1 + rand() % (SPIELFELD_XSIZE - 1);
			element->pos.y = SPIELFELD_OFFSET_Y + 1 + rand() % (SPIELFELD_YSIZE - 1);

		}while(element_folge_pruefen(element, snake1) || element_folge_pruefen(element, snake2) );


		liste_einfuegen_kopf(spiel_ptr->pickup_ptr->pickup_list, element);

		spiel_ptr->pickup_ptr->last_time = clock();

		spiel_ptr->pickup_ptr->pickupAmount++;
	}
}

void print_Pickup(Spiel *spiel_ptr, int farbe)
{
	Element *element_ptr = spiel_ptr->pickup_ptr->pickup_list->kopf_ptr;

	attron(COLOR_PAIR(farbe));

	while(element_ptr != NULL)
	{
		console_zeichne_punkt(element_ptr->pos.x, element_ptr->pos.y, ' ');
		element_ptr = element_ptr->nachfolger_ptr;
	}
}

void handle_pickup_conflict(Spiel *spiel_ptr)
{

	Element *snake1 = spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr;
	Element *snake2 = spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr;
	Element *pickup = spiel_ptr->pickup_ptr->pickup_list->kopf_ptr;

	Liste *pickupListe = spiel_ptr->pickup_ptr->pickup_list;

	Element *delete = NULL;

	delete = element_folge_pruefen_index(snake2, pickup);

	if (delete != NULL)
	{
		liste_entferne_element_at_adress(pickupListe, delete);
		spiel_ptr->s2_ptr->wachsen++;
		spiel_ptr->pickup_ptr->pickupAmount--;
	}

	pickup = spiel_ptr->pickup_ptr->pickup_list->kopf_ptr;

	delete = element_folge_pruefen_index(snake1, pickup);

	if (delete != NULL)
	{
		liste_entferne_element_at_adress(pickupListe, delete);
		spiel_ptr->s1_ptr->wachsen++;
		spiel_ptr->pickup_ptr->pickupAmount--;
	}

}


