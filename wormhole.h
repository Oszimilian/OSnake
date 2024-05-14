/*
 * wormhole.h
 *
 *  Created on: Dec 20, 2022
 *      Author: maximilian
 */

#ifndef WORMHOLE_H_
#define WORMHOLE_H_

#include <stdio.h>
#include <stdlib.h>

struct WormholeElement
{
	int x1;
	int y1;

	int x2;
	int y2;

	struct WormholeElement *next;
	struct WormholeElement *prev;
};
typedef struct WormholeElement WormholeElement;

struct WormholeList
{
	struct WormholeElement *head;
	struct WormholeElement *tail;

	int leangh;
};
typedef struct WormholeList WormholeList;

struct Wormhole
{
	WormholeList *wormholeList_ptr;

	clock_t last_time;
	long time_intervall;
	int wormholeAmount;
	int maxWormhole;
};
typedef struct Wormhole Wormhole;



#endif /* WORMHOLE_H_ */
