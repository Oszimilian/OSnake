/*
 * Eingabe.h
 *
 *  Created on: 12.12.2022
 *      Author: student
 */

#ifndef EINGABE_H_
#define EINGABE_H_

#ifdef _WIN32
#include <Windows.h> //Sleep
#include <conio.h>	 //Nicht-blockierendes Einlesen
#else
#include <unistd.h>  //Sleep usleep();
#endif
#include <stdlib.h>
#include <stdio.h>

struct Eingabe
{
	char letzte_eingabe_spieler_1;
	char letzte_eingabe_spieler_2;

	int flushEnable;

	char input;
};
typedef struct Eingabe Eingabe;

Eingabe* eingabe_erzeugen ();

void eingabe_init(struct Eingabe* eingabe_ptr);

void eingabe_einlesen(struct Eingabe* eingabe_ptr);

#endif /* EINGABE_H_ */
