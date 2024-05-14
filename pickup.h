/*
 * pickup.h
 *
 *  Created on: 16.12.2022
 *      Author: student
 */

#ifndef PICKUP_H_
#define PICKUP_H_


#include "Liste.h"

struct Pickup
{
	Liste *pickup_list;

	clock_t last_time;
	long time_intervall;
	int maxPickup;
	int pickupAmount;

};
typedef struct Pickup Pickup;



#endif /* PICKUP_H_ */
