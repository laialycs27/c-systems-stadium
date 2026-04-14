//
// Created by D on 3/6/2024.
//

#ifndef EX3_STAND_H
#define EX3_STAND_H

#include <stdbool.h>

#define NO_SEAT (-1)

typedef unsigned int Seat;
typedef struct Stand* Stand;

/*
 * Creates a Stand object and returns a pointer to it
 */
Stand StandCreate(const char* name, unsigned int num_seats);

/*
 * Frees memory for the object stand
 */
void StandDestroy(Stand stand);

/*
 * Return the maximum capacity of the stadium
 */
unsigned int StandMaxCapacity(Stand stand);

/*
 * Returns the stand name
 */
const char* StandName(Stand stand);

/*
 * Returns the number of seats that are available in the stand
 */
unsigned int StandSeatsAvailable(Stand stand);

/*
 * Returns true if seat is taken or false if it is available
 */
unsigned int StandSeatTaken(Stand stand, Seat seat);

/*
 * Returns true if seat is available or false if it is taken
 */
bool StandSeatAvailable(Stand stand, Seat seat);

/*
 * If seat is available - mark it as taken and return true.
 * Otherwise: return false.
 */
bool StandBuyTicket(Stand stand, Seat seat);

/*
 * Buy num_seats seats according to the list in seats.
 * If all seats are available - mark them as taken and return true.
 * Otherwise - return false.
 */
bool StandBuyNTickets(Stand stand, Seat seats[], unsigned int num_seats);

/*
 * Look for num_seats consecutive seats.
 * If no num_seats consecutive seats are available - return -1.
 * Otherwise - mark the first num_seats consecutive seats as taken and return
 * the index of the first seat
 */
Seat StandBuyNConsecutiveTickets(Stand stand, unsigned int num_seats);

#endif //EX3_STAND_H