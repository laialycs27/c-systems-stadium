//
// Created by D on 3/6/2024.
//

#include <stdlib.h>
#include <string.h>
#include "Stand.h"

struct Stand {
    char* name;
    unsigned char* seats;
    unsigned int num_seats;
};


Stand StandCreate(const char* name, unsigned int num_seats){
    Stand stand = (Stand)malloc(sizeof (struct Stand));
    if(stand == NULL){
        return NULL; //allocated failed!
    }
    stand->name = strdup(name);//copy stand name
    stand->num_seats = num_seats;

    //calculate the number of bytes to store the bits of the seats
    unsigned int num_bytes = (num_seats + 7) / 8;
    stand->seats = (unsigned char*)calloc(num_bytes, sizeof(unsigned char));
    if(stand->seats == NULL){
        free(stand->name);//free allocated name
        free(stand);//free allocated stand
        return NULL;//allocation failed!
    }
    return stand;
}

void StandDestroy(Stand stand){
    if(stand != NULL){
        free(stand->name);
        free(stand->seats);
        free(stand);
    }
}

unsigned int StandMaxCapacity(Stand stand){
    return stand->num_seats;
}

const char* StandName(Stand stand){
    return stand->name;
}

unsigned int StandSeatsAvailable(Stand stand){
    unsigned int availableSeats = 0;
    for(unsigned int i=0; i<stand->num_seats; i++){
        if(!StandSeatTaken(stand,i)){
            availableSeats++;
        }
    }
    return availableSeats;
}

unsigned int StandSeatTaken(Stand stand, Seat seat){
    unsigned int byteIndex = seat / 8;
    unsigned int bitIndex = seat % 8;
    return (stand->seats[byteIndex] >> bitIndex) & 1;
}

bool StandSeatAvailable(Stand stand, Seat seat){
    return !StandSeatTaken(stand, seat);
}

bool StandBuyTicket(Stand stand, Seat seat){
    if(StandSeatAvailable(stand, seat)){
        unsigned int byteIndex = seat / 8;
        unsigned int bitIndex = seat % 8;
        stand->seats[byteIndex] |= (1 << bitIndex);
        return true;
    }
    return false;
}


bool StandBuyNTickets(Stand stand, Seat seats[], unsigned int num_seats){
   //Check if there are enough available seats
    if (StandSeatsAvailable(stand) < num_seats){
       return false;
    }

    for(unsigned int i=0; i<num_seats ; i++){
        if(!StandSeatAvailable(stand,seats[i])){
            return false;
        }
    }

    for(unsigned int i=0 ; i<num_seats; i++){
        StandBuyTicket(stand,seats[i]);
    }

    return true;
}

Seat StandBuyNConsecutiveTickets(Stand stand, unsigned int num_seats){
    unsigned int consecutive = 0;
    for(unsigned int i=0; i<stand->num_seats; i++){
        if(StandSeatAvailable(stand,i)){
            consecutive++;
            if(consecutive == num_seats){
                for(unsigned int j = i - num_seats + 1; j<=i ; j++){
                    StandBuyTicket(stand,j);
                }
                return i - num_seats + 1;
            }
        }else {
            consecutive = 0;
        }
    }return NO_SEAT;
}