/*
 * Schlange.h
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#ifndef SCHLANGE_H_
#define SCHLANGE_H_
#include "Liste.h"

struct Schlange
{
	Liste* positionen_ptr;
	int wachsen;
	int punkte;
};
typedef struct Schlange Schlange;

//Initialisiert alle Attribute
void schlange_init (Schlange* schlange_ptr);

Schlange* schlange_erzeugen();


//Funktion bewegt die Schlange in die angegebene Richtung
void schlange_bewege (Schlange* schlange_ptr, int richtung);

//Verändert den Spieler in Abhängigkeit des Zustands, z.B. timer-Dekrement
void schlange_aktualisiere(Schlange* schlange_ptr);

//Funktion zur Bearbeitung eines eingesammelten PickUps
void schlange_bearbeite_pickup(Schlange* schlange_ptr, char pickup);

//Zeichnet die Schlange auf der Konsole
void schlange_zeichne(Schlange* schlange_ptr, int farbe);


#endif /* SCHLANGE_H_ */
