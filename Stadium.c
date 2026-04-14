//
// Created by D on 3/6/2024.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Stadium.h"

struct Stadium{
    Stand* stands;
    unsigned int num_stands;
    unsigned int total_capacity;
};

Stadium StadiumCreate(const char** stand_names, const unsigned int capacities[], unsigned int num_stands) {
    Stadium stadium = (Stadium) malloc(sizeof(Stadium));
    if(stadium == NULL){
        return NULL;// Memory allocation failed
    }

    stadium->stands = (Stand*) malloc(num_stands * sizeof(Stand));
    if(stadium->stands == NULL){
        free(stadium);
        return NULL;
    }

    stadium->num_stands = num_stands;
    stadium->total_capacity = 0;
    for (unsigned int i=0; i < num_stands; i++){
        stadium->stands[i] = StandCreate(stand_names[i], capacities[i]);
        if(stadium->stands[i] == NULL){
            for(unsigned int j=0; j<i; j++){
                StandDestroy(stadium->stands[j]);
            }
            free(stadium->stands);
            free(stadium);
            return NULL;
        }
        stadium->total_capacity += StandMaxCapacity(stadium->stands[i]);
    }
    return stadium;
}



Stadium StadiumCreateFromFile(const char* fileName){
    FILE* file = fopen(fileName, "r");
    if(file == NULL){
        return NULL; //failed to open file!
    }
    char stand_name[512];
    unsigned int stand_capacity;
    unsigned int num_stands = 0;

    // Count the number of stands in the file
    while(fscanf(file,"%s %u",stand_name,&stand_capacity) == 2){
        num_stands++;
    }

    rewind(file);//to reset the file pointer to beginning

    //Allocate memory for stand names and capacities
    const char** stand_names = (const char**) malloc(num_stands * sizeof(const char*));
    unsigned int* stand_capacities = (unsigned int*) malloc(num_stands * sizeof(unsigned int));
    if(stand_names == NULL || stand_capacities == NULL){
        fclose(file);
        free(stand_names);
        free(stand_capacities);
        return NULL; //Memory allocation failed
    }
    for (unsigned int i = 0; i < num_stands ; i++) {
        if(fscanf(file,"%s %u", stand_name, &stand_capacity) != 2){
            fclose(file);
            free(stand_names);
            free(stand_capacities);
            return NULL;
        }
        stand_names[i] = strdup(stand_name);
        stand_capacities[i] = stand_capacity;
    }

    fclose(file);
    Stadium stadium = StadiumCreate((const char**)stand_names, stand_capacities, num_stands);

    //Free allocated memory for stand names and capacities
    for (unsigned int i = 0; i < num_stands; i++) {
        free(stand_names);
        free(stand_capacities);

        return stadium;
    }
}

void StadiumDestroy(Stadium stadium) {
    if (stadium == NULL) {
        return;
    }

    //Destroy stands
    for(unsigned int i=0; i < stadium->num_stands; i++){
        StandDestroy(stadium->stands[i]);
    }
    free(stadium->stands);
    free(stadium);
}

unsigned int StadiumNumStands(Stadium stadium){
    if(stadium == NULL){
        return 0;
    }
    return stadium->num_stands;
}

unsigned int StadiumCapacity(Stadium stadium) {
    if (stadium == NULL) {
        return 0;
    }
    return stadium->total_capacity;
}

Stand StadiumGetStandByName(Stadium stadium, const char* stand_name) {
    if (stadium == NULL || stand_name == NULL) {
        return NULL;
    }

    for (unsigned int i = 0; i < stadium->num_stands; i++) {
        if (strcmp(StandName(stadium->stands[i]), stand_name) == 0) {
            return stadium->stands[i];
        }
    }
    return NULL; // Stand not found
}

Stand StadiumGetStandByIndex(Stadium stadium, unsigned int index) {
    if (stadium == NULL || index >= stadium->num_stands) {
        return NULL;
    }
    return stadium->stands[index];
}