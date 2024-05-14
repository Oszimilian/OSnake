/*
 * Element.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */
#include <stdio.h>
#include <stdlib.h>

// p spiel_ptr->s1_ptr->positionen_ptr->kopf_ptr->nachfolger_ptr

#include "Element.h"
Element* element_erzeugen()
{
	Element *element = (Element*) malloc(sizeof(Element));

	if (element == NULL)
	{
		fprintf(stderr, "Element konnte nicht erzeugt werden!");
		return NULL;
	}

	element->pos.x = 0;
	element->pos.y = 0;
	element->nachfolger_ptr = NULL;
	element->vorgaenger_ptr = NULL;
	return element;
}
/* Prüfe, ob e1 mit einem seiner Nachfolger übereinstimmt */
char element_folge_pruefen (Element* pruef_ptr, Element* e_ptr)
{
	while(e_ptr->nachfolger_ptr != NULL)
	{
		if (e_ptr->pos.x == pruef_ptr->pos.x && e_ptr->pos.y == pruef_ptr->pos.y)
		{
			return 1;
		} else {
			e_ptr = e_ptr->nachfolger_ptr;
		}
	}
	return 0;
}


Element *element_folge_pruefen_index (Element *pruef_ptr, Element *e_ptr)
{

	while(e_ptr != NULL)
	{
		if (e_ptr->pos.x == pruef_ptr->pos.x && e_ptr->pos.y == pruef_ptr->pos.y)
		{
			return e_ptr;
		} else {
			e_ptr = e_ptr->nachfolger_ptr;
		}
	}
	return NULL;
}
