//Laialy Abu Awad, Fadi Amasha
//id: 325142297, 212812341


#include <stdio.h>
#include <stdlib.h>
#include "Stadium.h"
#include "Stand.h"

void run_test_1(Stadium stadium) {
    printf("\n*** Test 1: general information about the stadium ***\n");
    printf("Number of stands: %u\nTotal capacity: %u\n", StadiumNumStands(stadium), StadiumCapacity(stadium));
    for(unsigned int i=0; i< StadiumNumStands(stadium); i++) {
        Stand stand = StadiumGetStandByIndex(stadium, i);
        printf("%u\t%u\t%s\n", i, StandMaxCapacity(stand), StandName(stand));
    }
}

void run_test_2(Stadium stadium) {
    printf("\n*** Test 2: Trying to get an illegal stand ***\n");
    Stand stand = StadiumGetStandByIndex(stadium, StadiumNumStands(stadium));
    if(!stand)
        printf("ok\treturned NULL\n");
    else
        printf("FAILED\treturned an illegal address\n");
}

/*
 * This function chooses num_seats random empty seats in stand. The function can be very slow
 * if the stand is nearly full
 */
bool find_random_empty_seats(Stand stand, Seat* seats, unsigned int num_seats) {
    if(StandSeatsAvailable(stand) < num_seats)
        return false;

    for(unsigned int i=0; i<num_seats; i++) {
        Seat wanted_seat = rand()%StandMaxCapacity(stand);
        if(!StandSeatAvailable(stand, wanted_seat)) {
            i--;
            continue;
        }

        seats[i] = wanted_seat;
        for(unsigned int j=0; j<i; j++) {
            if(seats[j] == wanted_seat) {
                i--;
                break;
            }
        }
    }
    return true;
}

void run_test_3(Stand stand) {
    printf("\n*** Test 3: buying one ticket at a time ***\n");
    printf("Stand %s, available: %u, max capacity: %u\n\n", StandName(stand), StandSeatsAvailable(stand),
           StandMaxCapacity(stand));

    // Choose 5 unique seats
    Seat seats[5];

    if(StandSeatsAvailable(stand) < 5) {
        printf("Not enough available seats in stand (need at least 5), aborting test\n");
        return;
    }

    find_random_empty_seats(stand, seats, 5);
    for(unsigned int i=0; i<5; i++) {
        bool got_seat = StandBuyTicket(stand, seats[i]);
        const char* status = got_seat? "ok" : "FAILED";
        printf("%s\tBought seat %u, available seats: %u\n", status, seats[i], StandSeatsAvailable(stand));

        got_seat = StandBuyTicket(stand, seats[i]);
        status = got_seat? "FAILED" : "ok";
        printf("%s\tTried to buy seat %u again, available seats: %u\n", status, seats[i], StandSeatsAvailable(stand));
    }
}

void run_test_4(Stand stand) {
    printf("\n*** Test 4: buying consecutive tickets ***\n");
    printf("Stand %s, available: %u, max capacity: %u\n\n", StandName(stand), StandSeatsAvailable(stand),
           StandMaxCapacity(stand));

    // First three capacities should be ok, last one should fail
    unsigned int num_tickets[] = {10, 2, 14, RAND_MAX};
    for(unsigned int i=0; i<4; i++) {
        Seat seat = StandBuyNConsecutiveTickets(stand, num_tickets[i]);
        if(seat == NO_SEAT) {
            const char* test_status = (num_tickets[i] > StandSeatsAvailable(stand))? "ok" : "FAILED";
            printf("%s\tTried to buy %u tickets in stand %s (max capacity: %u), purchase failed\n", test_status,
                   num_tickets[i], StandName(stand), StandMaxCapacity(stand));
            continue;
        }
        const char* test_status = (num_tickets[i] <= StandSeatsAvailable(stand))? "ok" : "FAILED";
        printf("%s\tTried to buy %u tickets in stand %s, got seat %u (new available: %u)\n", test_status, num_tickets[i],
               StandName(stand), seat, StandSeatsAvailable(stand));
    }
}

void run_test_5(Stand stand) {
    printf("\n*** Test 5: buying multiple tickets at a time ***\n");
    printf("Stand %s, available: %u, max capacity: %u\n\n", StandName(stand), StandSeatsAvailable(stand),
           StandMaxCapacity(stand));

    if(StandSeatsAvailable(stand) < 2000) {
        fprintf(stderr, "Not enough seats to perform test, needs at least 2000. Aborting test\n");
        return;
    }
    // Choose 5 unique seats
    Seat seats[500];

    for(unsigned int i=0; i<4; i++) {
        find_random_empty_seats(stand, seats, 500);
        bool success = StandBuyNTickets(stand, seats, 500);
        const char* status = success? "ok" : "FAILED";
        printf("%s\tTried to buy 500 tickets available, purchase %s (%u seats available after purchase)\n",
               success? "ok" : "FAILED", success? "succeeded" : "failed", StandSeatsAvailable(stand));
    }
}

int main(int argc, const char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "\nUsage: %s <stadium-info>\n\n", argv[0]);
        return 1;
    }
    const char* stadium_file = argv[1];

    // We want to get the same sequence of numbers each time
    srand(1984);

    printf("Creating a stadium from file %s\n", stadium_file);
    Stadium stadium = StadiumCreateFromFile(stadium_file);

    run_test_1(stadium);
    run_test_2(stadium);
    run_test_3(StadiumGetStandByIndex(stadium, 0));
    run_test_4(StadiumGetStandByIndex(stadium, 1));
    run_test_5(StadiumGetStandByIndex(stadium, 1));

    return 0;
}
