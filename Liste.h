/*
 * Liste.h
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#ifndef LISTE_H
#define LISTE_H
#include "Element.h"

struct Liste
{
	Element* kopf_ptr;
	Element* ende_ptr;
	int laenge;
};
typedef struct Liste Liste;
Liste* liste_erzeugen();

void liste_einfuegen_kopf(Liste* liste_ptr, Element* element_ptr);
Element* liste_entferne_ende(Liste* liste_ptr);
void liste_entferne_element_at_adress(Liste *liste_ptr, Element *element_ptr);

#endif /* LISTE_H_ */
