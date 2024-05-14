/*
 * pixelgruppe.c
 *
 *  Created on: Dec 19, 2022
 *      Author: maximilian
 */

#include "Configuration.h"
#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pixelgruppe.h"


PixelCharacter *createCharacter(char character, char *characterString, int xSize, int ySize)
{
	PixelCharacter *characterElement = (PixelCharacter*) malloc(sizeof(PixelCharacter));
	if (characterElement == NULL)
	{
		fprintf(stderr, "CharacterElement konnte nicht erzeugt werden! \n");
		return NULL;
	}

	characterElement->bitMap = malloc(ySize * sizeof(int *));
	if (characterElement->bitMap == NULL)
	{
		fprintf(stderr, "BitMap konnte nicht erzeugt werden! \n");
		return NULL;
	}

	for (int i = 0; i < xSize + 1; i++)
	{
		characterElement->bitMap[i] = malloc(xSize * sizeof(int));
		if (characterElement->bitMap[i] == NULL)
		{
			fprintf(stderr, "BitMap konnte nicht erzeugt werden! \n");
			return NULL;
		}
	}

	characterElement->character = character;
	characterElement->xLen = xSize;
	characterElement->yLen = ySize;

	int counter = 0;
	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			characterElement->bitMap[y][x] = characterString[counter];
			counter++;
		}
	}

	return characterElement;
}


CharacterList *createCharacterList()
{
	CharacterList *list = (CharacterList*) malloc(sizeof(CharacterList));
	if (list == NULL)
	{
		fprintf(stderr, "Character Liste konnte nicht erzeugt werden! \n");
		return NULL;
	}

	list->head = NULL;
	list->leangh = 0;

	return list;
}

void pushCharacterElement(CharacterList *list, PixelCharacter *pixel)
{
	pixel->next = list->head;
	list->head = pixel;
	list->leangh++;
}

PixelCharacter *getPixelCharacter(CharacterList *list, char c)
{
	PixelCharacter *pixel = list->head;

	while(pixel != NULL)
	{
		if (pixel->character == c)
		{
			return pixel;
		}

		pixel = pixel->next;
	}

	return NULL;
}

void clearPixelCharacter(CharacterList *list, int xPos, int yPos, int xSize, int ySize)
{
	attron(COLOR_PAIR(SPIELFELD_HINTERGRUND_FARBE));

	for (int y = 0; y < ySize; y++)
	{
		for (int x = 0; x < xSize; x++)
		{
			console_zeichne_punkt(xPos + x, yPos + y , ' ');
		}
	}
}

void printPixelCharcter(CharacterList *list, char c, int xPos, int yPos, int farbe)
{

	PixelCharacter *pixel = getPixelCharacter(list, c);

	clearPixelCharacter(list, xPos, yPos, pixel->xLen, pixel->yLen);

	if (pixel == NULL)
	{
		fprintf(stderr, "Den gesuchten Character gibt es in der Liste noch nicht! \n");
		return;
	}

	attron(COLOR_PAIR(farbe));

	for (int y = 0; y < pixel->yLen; y++)
	{
		for (int x = 0; x < pixel->xLen; x++)
		{
			if (pixel->bitMap[y][x] == '1')
			{
				console_zeichne_punkt(xPos + x, yPos + y , ' ');
			}
		}
	}
}

void printPixelNumber(CharacterList *list, int num, int xPos, int yPos, int farbe)
{

	char localString[128];
	int inputLen = 0;
	int characterLen = 0;
	PixelCharacter *pixel = NULL;

	sprintf(localString, "%d", num);
	inputLen = strlen(localString);

	for (int i = 0; i < inputLen; i++)
	{
		printPixelCharcter(list, localString[i], xPos + characterLen, yPos, farbe);
		pixel = getPixelCharacter(list, localString[i]);
		characterLen += 1 + pixel->xLen;
	}
}

void printPixelString(CharacterList *list, char *string, int xPos, int yPos, int farbe)
{
	int inputLen = 0;
	int characterLen = 0;
	PixelCharacter *pixel = NULL;

	inputLen = strlen(string);

	for (int i = 0; i < inputLen; i++)
	{
		printPixelCharcter(list, string[i],	xPos + characterLen, yPos, farbe);
		pixel = getPixelCharacter(list, string[i]);
		characterLen += 1 + pixel->xLen;
	}
}

CharacterList *initPixelGroup()
{
	CharacterList *list = createCharacterList();


	pushCharacterElement(list, createCharacter('0', "111111110011110011110011111111", 6, 5));
	pushCharacterElement(list, createCharacter('1', "001100001100001100001100001100", 6, 5));
	pushCharacterElement(list, createCharacter('2', "111111000011111111110000111111", 6, 5));
	pushCharacterElement(list, createCharacter('3', "111111000011111111000011111111", 6, 5));
	pushCharacterElement(list, createCharacter('4', "110011110011111111000011000011", 6, 5));
	pushCharacterElement(list, createCharacter('5', "111111110000111111000011111111", 6, 5));
	pushCharacterElement(list, createCharacter('6', "111111110000111111110011111111", 6, 5));
	pushCharacterElement(list, createCharacter('7', "111111000011000011000011000011", 6, 5));
	pushCharacterElement(list, createCharacter('8', "111111110011111111110011111111", 6, 5));
	pushCharacterElement(list, createCharacter('9', "111111110011111111000011111111", 6, 5));

	pushCharacterElement(list, createCharacter('A', "111111110011111111110011110011", 6, 5));
	pushCharacterElement(list, createCharacter('B', "111111110011111110110011111111", 6, 5));
	pushCharacterElement(list, createCharacter('C', "111111110000110000110000111111", 6, 5));
	pushCharacterElement(list, createCharacter('D', "111110110011110011110011111110", 6, 5));
	pushCharacterElement(list, createCharacter('E', "111111110000111111110000111111", 6, 5));
	pushCharacterElement(list, createCharacter('F', "111111110000111111110000110000", 6, 5));
	pushCharacterElement(list, createCharacter('G', "111111110000110111110011111111", 6, 5));
	pushCharacterElement(list, createCharacter('H', "110011110011111111110011110011", 6, 5));
	pushCharacterElement(list, createCharacter('I', "001100001100001100001100001100", 6, 5));
	pushCharacterElement(list, createCharacter('J', "000011000011000011000011111110", 6, 5));
	pushCharacterElement(list, createCharacter('K', "110001110110111000110110110001", 6, 5));
	pushCharacterElement(list, createCharacter('L', "110000110000110000110000111111", 6, 5));
	pushCharacterElement(list, createCharacter('N', "100001101001100101100011100001", 6, 5));
	pushCharacterElement(list, createCharacter('M', "100001110011101101100001100001", 6, 5));
	pushCharacterElement(list, createCharacter('O', "011110110011110011110011011110", 6, 5));
	pushCharacterElement(list, createCharacter('P', "111110110011111110110000110000", 6, 5));
	pushCharacterElement(list, createCharacter('Q', "011110100001100001100011011111", 6, 5));
	pushCharacterElement(list, createCharacter('R', "111110110011111110111000110011", 6, 5));
	pushCharacterElement(list, createCharacter('S', "111111110000111111000011111111", 6, 5));
	pushCharacterElement(list, createCharacter('T', "111111001100001100001100001100", 6, 5));
	pushCharacterElement(list, createCharacter('U', "110011110011110011110011011110", 6, 5));
	pushCharacterElement(list, createCharacter('V', "100001110011010010011110001100", 6, 5));
	pushCharacterElement(list, createCharacter('W', "100001100001100001101101110011", 6, 5));
	pushCharacterElement(list, createCharacter('X', "100001010010001100010010100001", 6, 5));
	pushCharacterElement(list, createCharacter('Y', "100001010010001100001100001100", 6, 5));
	pushCharacterElement(list, createCharacter('Z', "111111000011001100110000111111", 6, 5));


	pushCharacterElement(list, createCharacter(' ', "000000000000000000000000000000", 6, 5));

	pushCharacterElement(list, createCharacter('#', "111111111111111111111111111111", 6, 5));


	pushCharacterElement(list, createCharacter(':', "000000001100000000001100000000", 6, 5));


	return list;
}

