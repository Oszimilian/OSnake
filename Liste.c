/*
 * Liste.c
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#include "Liste.h"
#include <ncurses.h>

Liste* liste_erzeugen()
{
	Liste *list = (Liste*) malloc(sizeof(Liste));

	if (list == NULL)
	{
		fprintf(stderr, "Liste konnte nicht erzeugt werden \n");
		return NULL;
	}

	list->kopf_ptr = NULL;
	list->ende_ptr = NULL;
	list->laenge = 0;
	return list;
}

void liste_einfuegen_kopf(Liste* liste_ptr, Element* element_ptr)
{
	element_ptr->nachfolger_ptr = liste_ptr->kopf_ptr;
	if (element_ptr->nachfolger_ptr == NULL)
	{
		liste_ptr->kopf_ptr = element_ptr;
		liste_ptr->ende_ptr = element_ptr;
		liste_ptr->laenge++;
	} else {
		liste_ptr->kopf_ptr = element_ptr;
		element_ptr->nachfolger_ptr->vorgaenger_ptr = element_ptr;
		liste_ptr->laenge++;
	}
}

Element* liste_entferne_ende(Liste* liste_ptr)
{
	Element* letztesElement = liste_ptr->ende_ptr;
	letztesElement->vorgaenger_ptr->nachfolger_ptr = NULL;
	liste_ptr->ende_ptr = letztesElement->vorgaenger_ptr;
	return letztesElement;
}

void liste_entferne_element_at_adress(Liste *liste_ptr, Element *element_ptr)
{
	Element *local_element = liste_ptr->kopf_ptr;

	while(local_element != NULL)
	{
		if(local_element == element_ptr)
		{
			if (liste_ptr->laenge == 1)

			{
				liste_ptr->kopf_ptr = NULL;
				liste_ptr->ende_ptr = NULL;
				liste_ptr->laenge--;
			}
			else if (local_element->vorgaenger_ptr == NULL)
			{
				liste_ptr->kopf_ptr = local_element->nachfolger_ptr;
				local_element->nachfolger_ptr->vorgaenger_ptr = NULL;
				liste_ptr->laenge--;
			}

			else if (local_element->nachfolger_ptr == NULL)
			{
				liste_ptr->ende_ptr = local_element->vorgaenger_ptr;
				local_element->vorgaenger_ptr->nachfolger_ptr = NULL;
				liste_ptr->laenge--;
			}
			else{
				local_element->vorgaenger_ptr->nachfolger_ptr = local_element->nachfolger_ptr;
				local_element->nachfolger_ptr->vorgaenger_ptr = local_element->vorgaenger_ptr;
				liste_ptr->laenge--;
			}

			free(local_element);

			return;

		}

		local_element = local_element->nachfolger_ptr;
	}
}




