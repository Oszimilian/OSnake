/*
 * spielstand.h
 *
 *  Created on: Dec 17, 2022
 *      Author: maximilian
 */



#ifndef SPIELSTAND_H_
#define SPIELSTAND_H_

#include "pixelgruppe.h"
#include "Spiel.h"


#define PIXEL_SIZE_X 7
#define PIXEL_SIZE_Y 5

#define TERMINAL_MODE  2



struct Spielstand
{
	int spielstand_spieler1;
	int spielstand_spieler2;

	int x;
	int y;

	//struct Pixelgruppe *zahlen[12];
};
typedef struct Spielstand Spielstand;

Spielstand *inti_PixelGruppe(int x, int y);
void print_spielstand(Spielstand *spielstand, CharacterList *list, int farbe);
void update_Spielstand(Spielstand *spielstand_ptr, Spiel *spiel_ptr, CharacterList *list);




#endif /* SPIELSTAND_H_ */
