/*
 * wormhole.c
 *
 *  Created on: Dec 20, 2022
 *      Author: maximilian
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"
#include "Console.h"
#include "wormhole.h"
#include "pickup.h"
#include "Spiel.h"

WormholeList *createWormholeList(void)
{
	WormholeList *wormhole = (WormholeList*) malloc(sizeof(WormholeList));

	if (wormhole == NULL)
	{
		fprintf(stderr, "WormholeList konnte nicht erzeugt werden! \n");
		return NULL;
	}

	wormhole->head = NULL;
	wormhole->tail = NULL;

	return wormhole;
}

WormholeElement *createWormholeElement()
{
	WormholeElement *element = (WormholeElement*) malloc(sizeof(WormholeElement));

	if (element == NULL)
	{
		fprintf(stderr, "WormholeElement konnte nicht erstellt werden! \n");
		return NULL;
	}

	element->next = NULL;
	element->prev = NULL;

	return element;
}

void pushWormholeElement(WormholeList *list, WormholeElement *element)
{
	element->next = list->head;
	if (element->next == NULL)
	{
		list->head = element;
		list->tail = element;
		list->leangh++;
	} else {
		list->head = element;
		element->next->prev = element;
		list->leangh++;
	}
}

void removeWormholeElement(WormholeList *liste_ptr, WormholeElement *element_ptr)
{
	WormholeElement *local_element = liste_ptr->head;

	while(local_element != NULL)
	{
		if(local_element == element_ptr)
		{
			if (liste_ptr->leangh == 1)
			{
				liste_ptr->head = NULL;
				liste_ptr->tail = NULL;
				liste_ptr->leangh--;
			}
			else if (local_element->prev == NULL)
			{
				liste_ptr->head = local_element->next;
				local_element->next->prev = NULL;
				liste_ptr->leangh--;
			}

			else if (local_element->next == NULL)
			{
				liste_ptr->tail = local_element->prev;
				local_element->prev->next = NULL;
				liste_ptr->leangh--;
			}
			else{
				local_element->prev->next = local_element->next;
				local_element->next->prev = local_element->prev;
				liste_ptr->leangh--;
			}

			free(local_element);

			return;

		}

		local_element = local_element->next;
	}
}

Wormhole *initWormhole()
{
	Wormhole *wormhole = (Wormhole*) malloc(sizeof(Wormhole));
	if (wormhole == NULL)
	{
		fprintf(stderr, "Wormhole konnte nicht erzeugt werden! \n");
		return NULL;
	}

	//WormholeList *wormholeList = createWormholeList();
	//wormhole->wormholeList_ptr = wormholeList;
	wormhole->wormholeList_ptr = createWormholeList();
	wormhole->last_time = clock();
	wormhole->time_intervall = 50000;
	wormhole->wormholeAmount = 0;
	wormhole->maxWormhole = 1;

	return wormhole;
}

void sparnRandomWormholeElement(Spiel *spiel_ptr)
{
	if( (	(clock() - spiel_ptr->wormhole_ptr->last_time) >= spiel_ptr->wormhole_ptr->time_intervall) &&
			(spiel_ptr->wormhole_ptr->maxWormhole > spiel_ptr->wormhole_ptr->wormholeAmount))
	{

		WormholeElement *wormhole = createWormholeElement();
		do
		{

			wormhole->x1 = SPIELFELD_OFFSET_X + 1 + rand() % (SPIELFELD_XSIZE - 1);
			wormhole->y1 = SPIELFELD_OFFSET_Y + 1 + rand() % (SPIELFELD_YSIZE - 1);
			wormhole->x2 = SPIELFELD_OFFSET_X + 1 + rand() % (SPIELFELD_XSIZE - 1);
			wormhole->y2 = SPIELFELD_OFFSET_Y + 1 + rand() % (SPIELFELD_YSIZE - 1);
		}while(wormhole->x1 != wormhole->x2 && wormhole->y1 != wormhole->y2);

		pushWormholeElement(spiel_ptr->wormhole_ptr->wormholeList_ptr, wormhole);

		spiel_ptr->wormhole_ptr->last_time = clock();

		spiel_ptr->wormhole_ptr->wormholeAmount++;
	}
}

void printWormhole(Spiel *spiel_ptr, int farbe)
{
	WormholeElement *wormhole = spiel_ptr->wormhole_ptr->wormholeList_ptr->head;

	attron(COLOR_PAIR(farbe));

	while(wormhole != NULL)
	{
		console_zeichne_punkt(wormhole->x1, wormhole->y1, ' ');
		console_zeichne_punkt(wormhole->x2, wormhole->y2, ' ');

		wormhole = wormhole->next;
	}
}

WormholeElement *checkSnakeWormholeCollision(Element *snake_ptr, WormholeElement *wormhole_ptr)
{

	int snakeX = snake_ptr->pos.x;
	int snakeY = snake_ptr->pos.y;

	while(wormhole_ptr != NULL)
	{
		if ( (snakeX == wormhole_ptr->x1 && snakeY == wormhole_ptr->y1) || (snakeX == wormhole_ptr->x2 && snakeY == wormhole_ptr->y2))
		{
			return wormhole_ptr;
		}
		wormhole_ptr = wormhole_ptr->next;
	}

	return NULL;
}


void handleWormholeCollision(Spiel *spiel_ptr)
{
	Element *schlangen_kopf_ptr = spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr;
	WormholeElement *wormhole_head_ptr = spiel_ptr->wormhole_ptr->wormholeList_ptr->head;
	WormholeElement *wormhole_element_ptr = checkSnakeWormholeCollision(schlangen_kopf_ptr, wormhole_head_ptr);


	if (wormhole_element_ptr != NULL)
	{
		if (schlangen_kopf_ptr->pos.x == wormhole_element_ptr->x1 && schlangen_kopf_ptr->pos.y == wormhole_element_ptr->y1)
		{
			setNewSnakeHeadPosition(spiel_ptr->s1_ptr, wormhole_element_ptr->x2, wormhole_element_ptr->y2);
		} else {
			setNewSnakeHeadPosition(spiel_ptr->s1_ptr, wormhole_element_ptr->x1, wormhole_element_ptr->y1);
		}

		removeWormholeElement(spiel_ptr->wormhole_ptr->wormholeList_ptr, wormhole_element_ptr);

		spiel_ptr->wormhole_ptr->wormholeAmount--;

		spiel_ptr->wormhole_ptr->last_time = clock();
	}

	schlangen_kopf_ptr = spiel_ptr->s2_ptr->positionen_ptr->kopf_ptr;

	wormhole_element_ptr = checkSnakeWormholeCollision(schlangen_kopf_ptr, wormhole_head_ptr);

	if (wormhole_element_ptr != NULL)
	{
		if (schlangen_kopf_ptr->pos.x == wormhole_element_ptr->x1 && schlangen_kopf_ptr->pos.y == wormhole_element_ptr->y1)
		{
			setNewSnakeHeadPosition(spiel_ptr->s2_ptr, wormhole_element_ptr->x2, wormhole_element_ptr->y2);
		} else {
			setNewSnakeHeadPosition(spiel_ptr->s2_ptr, wormhole_element_ptr->x1, wormhole_element_ptr->y1);
		}

		removeWormholeElement(spiel_ptr->wormhole_ptr->wormholeList_ptr, wormhole_element_ptr);

		spiel_ptr->wormhole_ptr->wormholeAmount--;

		spiel_ptr->wormhole_ptr->last_time = clock();
	}
}



