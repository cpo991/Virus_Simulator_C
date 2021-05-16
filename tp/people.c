/* 
 * File:   people.c
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 31 de Março de 2020, 19:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utils.h"
#include "people.h"
#include "rooms.h"

#define CONNECTIONS 3

pPerson newVectorP(char* filename, int *tam){ //initializes vectorPeople
    FILE *f;
    pPerson newPerson = NULL, lastPerson = NULL, list = NULL;
    *tam = 0;
    f = fopen(filename, "rt");  // opens the file
    
    if (f == NULL){ // if it doesn't open
        printf("\n\t\t\t\t\t\tERROR: Opening file: %s\n", filename);
        return NULL;
    }
    
    newPerson = (pPerson) malloc(sizeof(Person));
        
    if(!newPerson){
        printf("\n\t\t\t\t\t\tERROR: Alocating memory\n");
        return NULL;
    }
    
    while(fscanf(f," %49s %d %c", &(newPerson->id), &(newPerson->age), &(newPerson->state))==3){
        if(newPerson->state == 'D' && (fscanf(f," %d", &(newPerson->infectedTime))==1)){
            // if it has infected time and the state is D -> keeps the infected time
        }
        else{
            newPerson->infectedTime = 0; // if it doesn't, sets infectedTime to NULL
        }
        
        newPerson->pR = NULL; // setting room null bc no association yet
        
        if(list == NULL &&  lastPerson == NULL){
            list = newPerson;
            lastPerson = newPerson;
        }
        else{
            lastPerson->nextP = newPerson;
            lastPerson = lastPerson->nextP;
        }
        lastPerson->nextP = NULL;
        (*tam)++;
        newPerson = (pPerson) malloc(sizeof(Person));    
    }
    
    fclose(f); // closes file
    return list;
}

int verefiesDataP(pPerson person){
    pPerson aux = NULL, p = NULL;
    p = aux = person;
    
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no rooms \n");
        return 1;
    }  
    aux = aux->nextP;
    while(p != NULL){     
        while(aux != NULL){
            if(strcmp(p->id, aux->id) == 0) {
                    printf("\n\t\t\t\t\t\tERROR: All IDs must be unique\n");
                    return 1;
                }
            aux = aux->nextP;
        }
        if(p->age <= 0){
            printf("\n\t\t\t\t\t\tERROR: Age must be higher than 0\n");
            return 1;
        }
        if(p->state != 'S' && p->state != 'D' && p->state != 'I'){
            printf("\n\t\t\t\t\t\tERROR: State must be S / D / I\n");
            return 1;
        }
        if(p->infectedTime < 0){
            printf("\n\t\t\t\t\t\tERROR: Infected Time can't be negative\n");
            return 1;
        }
        else{
            printf("\n\t\t\t\t\t\tUpdate: People are successfully Loaded\n");
            return 0;
        }
        p = p->nextP;
    }
    return 1;
}

void printPeople(pPerson person){
    printPeople_menu();
    pPerson p = NULL;
    p = person;
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return;
    }
    
    while(p != NULL){
        if(p->infectedTime != 0)
            printf("ID: %s\t Age: %d\t State: %c\t Infected Time: %d\n",
                p->id, p->age, p->state, 
                p->infectedTime);
        else
            printf("ID: %s\t Age: %d\t State: %c\n",
                p->id, p->age, p->state);
        p = p->nextP;
    }
    return;
}

void addRoomPerson (pPerson person, pRoom r, int nRooms){
    int min = 0, i, max = 0, aux, index = 0, cont=0;
    pPerson p = NULL;
    p = person;
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return;
    }
    if(!r){
        printf("\n\t\t\t\t\t\tERROR: There are no rooms\n");
        return;
    }
    
    max = getMaxID(r, nRooms);
    min = getMinID(r, nRooms);
    
    while(p != NULL){
        while(p->pR == NULL){
            index = 0; aux = 0;
            while (aux == 0){
                index = intUniformRnd(min, max);
                for (i = 0; i < nRooms; i++) {
                    if(r[i].capacity < 0){
                        cont++;
                    }
                    if((r[i].id == index) && (r[i].capacity > 0)){
                        r[i].capacity--;
                        p->pR = &r[i];
                        aux = 1;
                        break;
                    }
                }
                if(cont == nRooms){
                    printf("\n\t\t\t\t\t\tWARNING: Some People where not included in the rooms\n");
                    aux = 1;
                    break;
                }
            }
        }
        p = p->nextP;
    }
    return;
}

void printConnections(pPerson person){
    pPerson p = NULL;
    p = person;
    printConnec_menu();
    
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return;
    }
    
    while(p != NULL){
        printf("ID: %s \t Room: %d\n", p->id, p->pR->id);
        p = p->nextP;
    }
    return;
}

void mediaIdades (pPerson person, int *tam){
    pPerson p = NULL;
    p = person;
    float somaI=0, nPessoas = 0, media = 0;
    
    
    if(!p){
        return;
    }
    
    while(p != NULL){
        if(p->state == 'S'){
            somaI = somaI + p->age;
            nPessoas++;
        }
    }
    
    media = somaI / nPessoas;
    printf("media: %0.2f", media);
    return;
}