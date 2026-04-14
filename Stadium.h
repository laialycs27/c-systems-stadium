//
// Created by D on 3/6/2024.
//

#ifndef EX3_STADIUM_H
#define EX3_STADIUM_H

#include "Stand.h"

typedef struct Stadium* Stadium;

Stadium StadiumCreate(const char* stand_names[], const unsigned int capacities[], unsigned int num_stands);
Stadium StadiumCreateFromFile(const char* fileName);
void StadiumDestroy(Stadium stadium);
unsigned int StadiumNumStands(Stadium stadium);
unsigned int StadiumCapacity(Stadium stadium);
Stand StadiumGetStandByName(Stadium stadium, const char* stand_name);
Stand StadiumGetStandByIndex(Stadium stadium, unsigned int index);

#endif //EX3_STADIUM_H
