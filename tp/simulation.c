/* 
 * File:   simulation.c
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 10 de Junho de 2020, 19:05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "utils.h"

#include "people.h"
#include "rooms.h"

#include "simulation.h"

#define CONNECTIONS 3
//#define SPREADRATE 0.05
#define SPREADRATE 0.05
#define IMMUNITYRATE 0.20


int interaction(pPerson person, pRoom r, int nRooms, int nPeoplelist){
    pPerson aux = NULL, p = NULL;
    p = aux = person;
    int index = 0,newInfected = 0, nPeople = 0, nPeopleInf = 0, 
            indP = 0, found = 0, isValid = 0, maxDaysInf= 0, age = 0,
            canBeImune = 0, day = 0;
    float prob =0;
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return day;
    }
    if(!r){
        printf("\n\t\t\t\t\t\tERROR: There are no rooms\n");
        return day;
    }
    
    while(p != NULL){
        for(int i = 0; i<nRooms;i++) {
            if(p->pR->id == r[i].id){
                index = i;
                break;
            }
        }
        
        if(p->state == 'D') //increase infected days
            p->infectedTime++;
        
        //recovery 
        canBeImune = 0;
        isValid = 0;
        maxDaysInf = 0;
        if(p->state == 'D'){
            if(p->age >= 10){ //recovery by days
                age = p->age;
                while(age >= 10){ //num dezenas
                    age = age / 10;
                }
                maxDaysInf = 5 + age;
            } else{
                maxDaysInf = 5;
            }
            if(p->infectedTime >= maxDaysInf){
                p->state = 'S';
                p->infectedTime = 0;
                canBeImune = 1;
            }

            prob = 1 / p->age; // recovery by prob
            isValid = probEvento(prob);
            if(isValid == 1){
                p->state = 'S';
                p->infectedTime = 0;
                canBeImune = 1;
            }
        }
        isValid = 0;
        if(canBeImune == 1){ // prob of being imune
            isValid = probEvento(IMMUNITYRATE);
                if(isValid == 1){
                    p->state = 'I';
            }
        }
        
        // infecting others
        nPeople = nPeopleInRoom(p,r,index);
        nPeopleInf = nPeopleInfectedInRoom(p,r,index);
        newInfected = (nPeopleInf * SPREADRATE);
        /*printf("\nRoom: %d\t nPeople: %d\t nInfected: %d \t WillBe: %d",p->pR->id,
                nPeople, nPeopleInf, newInfected);*/
        
        while (newInfected > 0){ // set new infected
            found = 0;
            indP = intUniformRnd(0,nPeoplelist);
            found = getPerson(p,indP,p->pR->id);
            
            if(found == 1){
                newInfected--;
                nPeopleInf++;
                //printf("\n\n%d %d \n\n", indP, newInfected);
            }
        }
        /*printf("\nRoom: %d\t nPeople: %d\t nInfected: %d \t WillBe: %d",p->pR->id,
                nPeople, nPeopleInf, newInfected);*/
      
        p = p->nextP;
    }
    day++;
    return day;
}

int nPeopleInRoom(pPerson person, pRoom r, int indexR){
    int nPeople=0;
    pPerson p = NULL;
    p = person;
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return 0;
    }
    
    while(p != NULL){
        if (p->pR->id == r[indexR].id)
            nPeople++;
        p = p->nextP;
    }
    return nPeople;
}

int nPeopleInfectedInRoom(pPerson person, pRoom r, int indexR){
    int nPeopleInf=0;
    pPerson p = NULL;
    p = person;
    if(!p){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return 0;
    }
    
    while(p != NULL){
        if ((p->pR->id == r[indexR].id) && p->state == 'I')
            nPeopleInf++;
        p = p->nextP;
    }
    return nPeopleInf;
}

int getPerson(pPerson person, int index, int idRoom){
    int aux = 0;
    pPerson p = NULL;
    p = person;
    while(p != NULL){
        if((aux == index) && (p->pR->id == idRoom)){
            if(p->state == 'S'){
                p->state = 'D';
                p->infectedTime = 0;
                return 1;
            }
            else if(p->state == 'I'){
                p->state = 'I';
                return 1;
            }
            else{
                p->state = 'D';
                return 1;
            }
        }
        p = p->nextP;
        aux++;
    }
   return 0;  
}

void informationBoard(pPerson person, pRoom r, int nRooms, int nPeoplelist, int day){
    pPerson p = NULL;
    
    int i, nPeople = 0, nPeopleInf = 0, nHealthy = 0, nImune = 0;
    float ratei = 0, rates = 0, rated = 0, aux1 = 0, aux2 = 0, aux3 = 0, aux0 = 0;
    printf("\n\t\t\t\t\t\tDay %d of the simulation.\n", day);
    
    for(i = 0; i < nRooms; i++){ //rooms
        p = person;
        printf("\n\t\t\t\t\t\tRoom: [%02d]\n", r[i].id);
        while(p != NULL){
            if(p->pR->id == r[i].id)
                printf("\t\t\t\t\t\t\tID: %s\t State: %c\n", p->id, p->state);
            p = p->nextP;
        }
    }
    
    //healthy rate
    for(i = 0; i < nRooms; i++){ //rooms
        p = person;
        while(p != NULL){
            if(p->pR->id == r[i].id){
                nPeople++;
                if(p->state == 'S'){
                    nHealthy++;
                }
                else if(p->state == 'I'){
                    nImune++;
                }
                else if(p->state == 'D'){
                    nPeopleInf++;
                }
            }
            p = p->nextP;
            
        }
        aux0 = nPeople; aux1 = nHealthy; aux2 = nImune; aux3 = nPeopleInf;
        if(aux0 == 0){
            rates = 0; ratei = 0;rated = 0;
        }else{
            rates = (aux1 * 100) / aux0;
            ratei = (aux2 * 100) / aux0;
            rated = (aux3 * 100) / aux0;
        }
        printf("\n\t\t\t\t\t\tRoom: [%02d]\n", r[i].id);
        printf("\t\t\t\t\t\t\tHealthy Rate: %0.2f%%\n", rates);
        printf("\t\t\t\t\t\t\tImune Rate: %0.2f%%\n", ratei);
        printf("\t\t\t\t\t\t\tInfected Rate: %0.2f%%\n", rated);
        nPeople = 0; nPeopleInf = 0; nHealthy = 0; nImune = 0; 
    }
    return;
}

pPerson addPerson(pPerson person, pRoom r, int nRooms){
    pPerson newp = NULL, aux = NULL;
    int idR = 0, i=0, isValid =0;
    char aux1[5];
    
    newp = (pPerson) malloc(sizeof(Person));
    
    if(!newp){
        printf("\n\t\t\t\t\t\tERROR: There are no people\n");
        return NULL;
    }
    
    do{
        isValid = 0;
        printf("\n\t\t\t\tPersonID: ");
        scanf(" %49s", &newp->id);
        aux = person;
        while (aux != NULL){
            if(strcmp(aux->id, newp->id) == 0){
                isValid = 0;
                printf("\n\t\t\t\t\t\tERROR: Person's id already exists\n");
                break;
            }
            else{
                isValid = 1;
            }
            aux = aux->nextP;
        }
    }while(isValid == 0);
    
    do{
        printf("\n\t\t\t\t\t\tAge: ");
        scanf(" %d", &newp->age);
    }while(newp->age <= 0 );
    //aux->age = age;
    
    newp->state = 'D';
    do{
        printf("\n\t\t\t\t\t\tDays infected: ");
        scanf(" %d", &newp->infectedTime);
    }while(newp->infectedTime <= 0);
    //aux->infectedTime = infTime;
    
    
    do{
        isValid = 0;
        do{
            printf("\n\t\t\t\t\t\tRoomID: ");
            scanf(" %d", &idR);
        }while(idR <= 0);

        for(i = 0; i<nRooms; i++){ //find the room
            if((idR == r[i].id) && r[i].capacity > 0){
                newp->pR = &r[i];
                isValid = 1;
                r[i].capacity--;
                printf("\n\t\t\t\t\t\tPerson added succesfully\n");
                break;
            }
        }
        if(isValid == 0)
            printf("\n\t\t\t\t\t\tERROR: Room's id doesn't exist\n");
    }while(isValid == 0);
    
    newp->nextP = NULL;

    if(!person)
        person = newp;
    else{
        aux = person;
        while(aux->nextP != NULL)
            aux = aux->nextP;
        
        newp->nextP = aux->nextP;
        aux->nextP = newp;
    }
    return person;
}

void moveRoom(pPerson person, pRoom r, int nRooms, int nPeoplelist){
    int N=0, isValid = 0, idRO = 0, idRD = 0, i = 0, aux = 0, indP = 0, found = 0, 
            nP = 0, indR = 0;
    pPerson p = NULL, paux = NULL;
    do{
        printf("\n\t\t\t\t\t\tNumber of People to move: ");
        scanf(" %d", &N);
    }while(N <= 0 );
    
    do{
        isValid = 0;
        do{
            printf("\n\t\t\t\t\t\tRoomID Origin: ");
            scanf(" %d", &idRO);
        }while(idRO <= 0);
        
        for(i=0; i<nRooms; i++){
            if(idRO == r[i].id)
                indR=i;
        }
        paux = person;
        nP = nPeopleInRoom(paux, r, indR);
        for(i = 0; i<nRooms; i++){ //find the room
            if((idRO == r[i].id) && nP >= N){
                isValid = 1;
                break;
            }
            if((idRO == r[i].id) && nP < N){
                isValid = 0;
                printf("\n\t\t\t\t\t\tERROR: Room's doesn't have %d people\n", N);
                break;
            }
            else{
                aux++;
            }
            if(aux == nRooms)
                printf("\n\t\t\t\t\t\tERROR: Room's id doesn't exist\n");
        }
    }while(isValid == 0);   
    
    
    do{
        isValid = 0;
        aux = 0;
        do{
            printf("\n\t\t\t\t\t\tRoomID Destiny: ");
            scanf(" %d", &idRD);
        }while(idRD <= 0);
        
        for(i = 0; i<nRooms; i++){ //find the room
            if((idRD == r[i].id) && (r[i].capacity - N) >= 0){
                isValid = 1;
                break;
            }
            if((idRD == r[i].id) && (r[i].capacity - N) < 0){
                isValid = 0;
                printf("\n\t\t\t\t\t\tERROR: Room's doesn't have %d of capacity\n", N);
                break;
            }
            else{
                aux++;
            }
            if(aux == nRooms){
                printf("\n\t\t\t\t\t\tERROR: Room's id doesn't exist\n");
                isValid == 0;
            }
        }
        
    }while(isValid == 0);
    
    p = person;
    
    while(N>0){
        indP = intUniformRnd(0,nPeoplelist);
        found = getPersonToMove(p, r,indP,nRooms,idRO, idRD);
        
        if(found == 1){
            N--;
        }
    }
    return;
}

int getPersonToMove(pPerson person,pRoom r, int index, int nRooms,int idRO, int idRD){
    int aux = 0, i = 0, k=0, indexRO=0, indexRD = 0;
    pPerson p = NULL, paux = NULL;
    p = paux = person;
    while(p != NULL){
        if((aux == index) && (p->pR->id == idRO)){ // procura nas pessoas o quarto com id x de origem
            //p->pR = NULL;
            for (i = 0; i < nRooms; i++) { // indica o index do quarto de origem
                if(r[i].id == idRO)
                    indexRO = i;
                if(r[i].id == idRD)
                    indexRD = i;
            }

            p->pR = &r[indexRD]; // ponteiro do quarto de destino passa para a pessoa
            //paux->pR = &r[i];
            r[indexRD].capacity--; //  capacidade destino --
            r[indexRO].capacity++; // capacidade origem ++
            person = p;
            return 1;
        }
        p = p->nextP;
        aux++;
    }
   return 0;  
}

void saveInfo(pPerson person, pRoom r, int nRooms, int day){
    FILE *f;
    pPerson p = NULL;
    int i, nPeople = 0, nPeopleInf = 0, nHealthy = 0, nImune = 0;
    float ratei = 0, rates = 0, rated = 0, aux1 = 0, aux2 = 0, aux3 = 0, aux0 = 0;
    f = fopen("report.txt", "w");
    
    if(!f){
        printf("ERROR: Opening file: report.txt\n");
        return;
    }

    fprintf(f,"Simulation lasted %d days.\n", day);
    
    for(i = 0; i < nRooms; i++){ //rooms
        p = person;
        fprintf(f,"\nRoom: [%02d]\n", r[i].id);
        while(p != NULL){
            if(p->pR->id == r[i].id)
                fprintf(f,"ID: %s\t State: %c\n", p->id, p->state);
            p = p->nextP;
        }
    }
    
    //healthy rate
    for(i = 0; i < nRooms; i++){ //rooms
        p = person;
        while(p != NULL){
            if(p->pR->id == r[i].id){
                nPeople++;
                if(p->state == 'S'){
                    nHealthy++;
                }
                else if(p->state == 'I'){
                    nImune++;
                }
                else if(p->state == 'D'){
                    nPeopleInf++;
                }
            }
            p = p->nextP;
            
        }
        aux0 = nPeople; aux1 = nHealthy; aux2 = nImune; aux3 = nPeopleInf;
        if(aux0 == 0){
            rates = 0; ratei = 0;rated = 0;
        }else{
            rates = (aux1 * 100) / aux0;
            ratei = (aux2 * 100) / aux0;
            rated = (aux3 * 100) / aux0;
        }
        fprintf(f,"Room: [%02d]\n", r[i].id);
        fprintf(f,"Healthy Rate: %0.2f%%\n", rates);
        fprintf(f,"Imune Rate: %0.2f%%\n", ratei);
        fprintf(f,"Infected Rate: %0.2f%%\n", rated);
        nPeople = 0; nPeopleInf = 0; nHealthy = 0; nImune = 0; 
    }
    fclose(f);
    return;
}

void saveLastPopulation(pPerson person){
    FILE *f;
    pPerson p = NULL;
    int isValid = 0;
    char filename[50];
    
    do{
        printf("\n\t\t\t\t\t\tLast Populations's File: ");
        scanf(" %s", &filename);
        isValid = verifiesFileP(filename);
    }while(isValid == 0);
    
    f = fopen(filename, "w");
    
    if(!f){
        printf("ERROR: Opening file: report.txt\n");
        return;
    }
    p = person;
    while(p != NULL){
        if(p->infectedTime != 0)
            fprintf(f,"%s %d %c %d %d\n",
                p->id, p->age, p->state, 
                p->infectedTime, p->pR->id);
        else
            fprintf(f,"%s %d %c %d\n",
                p->id, p->age, p->state, p->pR->id);
        p = p->nextP;
    }
    fclose(f);
    return;
}

