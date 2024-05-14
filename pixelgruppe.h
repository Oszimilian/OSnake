/*
 * pixelgruppe.h
 *
 *  Created on: Dec 19, 2022
 *      Author: maximilian
 */

#ifndef PIXELGRUPPE_H_
#define PIXELGRUPPE_H_

struct PixelCharacter
{
	char character;
	int **bitMap;
	int xLen;
	int yLen;

	struct PixelCharacter *next;
};
typedef struct PixelCharacter PixelCharacter;

struct CharacterList
{
	struct PixelCharacter *head;
	int leangh;
};
typedef struct CharacterList CharacterList;


PixelCharacter *createCharacter(char character, char *characterString, int xSize, int ySize);
CharacterList *createCharacterList();
void pushCharacterElement(CharacterList *list, PixelCharacter *pixel);
PixelCharacter *getPixelCharacter(CharacterList *list, char c);
void printPixelCharcter(CharacterList *list, char c, int xPos, int yPos, int farbe);
CharacterList *initPixelGroup();
void printPixelNumber(CharacterList *list, int num, int xPos, int yPos, int farbe);
void printPixelString(CharacterList *list, char *string, int xPos, int yPos, int farbe);

#endif /* PIXELGRUPPE_H_ */
