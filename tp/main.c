/* 
 * File:   main.c
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 30 de Março de 2020, 18:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "utils.h"
#include "people.h"
#include "rooms.h"
#include "simulation.h"

#define peopleFile "pessoasB.txt" 
#define roomsFile "E3.bin"
/*
 * 
 */

int simulationMenu(pPerson person, pRoom room, int totalP, int totalR){
    char aux[1];
    int op, isEnded = 0, day = 0;
    
    do{
        do{
            Simulation_menu();
            printf("\n\t\t\t\t\t\tOption: ");
            scanf(" %s", &aux);
            op = atoi(aux);     
        }while(aux == 0);       // verifies if it's receiving an intiger
        switch (op){
            case 1:
                day = interaction(person, room, totalR, totalP);
                break;
            case 2:
                informationBoard(person, room, totalR, totalP, day);
                break;
            case 3:
                person = addPerson(person, room, totalR);
                break;
            case 4:
                moveRoom(person, room, totalR, totalP);
                break;
            case 5:
                saveInfo(person, room, totalR, day);
                saveLastPopulation(person);
                isEnded = 1;
                return 1;
                break;
        }
    }while (isEnded == 0);
    return 1;
}

int main(int argc, char** argv) {
    char aux[1], rFile[50], pFile[50];
    int op = 0, isEnded = 0, totalP = 0, totalR = 0, vFR = 0, vFP = 0;
    
    initRandom();
    pPerson people = NULL;
    pRoom rooms = NULL;
    
    header();
    do{
        do{
            main_menu();
            printf("\n\t\t\t\t\t\tOption: ");
            scanf(" %s", &aux);
            op = atoi(aux);     
        }while(op == 0);       // verifies if it's receiving an intiger
        switch (op){
            case 1:
                preparation_menu();
                do{
                    printf("\n\t\t\t\t\t\tRoom's File: ");
                    scanf(" %s", &rFile);
                    vFR = verifiesFileR(rFile);
                }while(vFR == 0);
                do{
                    printf("\n\t\t\t\t\t\tPeople's File: ");
                    scanf(" %s", &pFile);
                    vFP = verifiesFileP(pFile);
                }while(vFP == 0);
                rooms = initRooms(rFile, &totalR);
                people = newVectorP(pFile, &totalP);
                
                //rooms = initRooms(roomsFile, &totalR);
                //people = newVectorP(peopleFile, &totalP);
                isEnded = verefiesDataR(rooms, totalR);
                isEnded = verefiesDataP(people);
                if(isEnded == 0){
                    printRooms(rooms, totalR);
                    printPeople(people);
                    addRoomPerson (people, rooms, totalR);
                    printConnections(people);
                    printRooms(rooms, totalR);
                    isEnded = simulationMenu(people, rooms,totalP,totalR);
                }
                break;
            case 2:
                isEnded = shutdown();
                break;
        }
    }while (isEnded == 0);
    return (EXIT_SUCCESS);
}