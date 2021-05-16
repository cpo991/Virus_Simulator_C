/* 
 * File:   structs.h
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 30 de Março de 2020, 18:21
 */

#ifndef STRUCTS_H
#define	STRUCTS_H

typedef struct room Room, *pRoom;
struct room{
    int id;                 // id number of the local
    int capacity;           // max capacity 
    int connection[3];      // id of the connections (-1 when not used)
};

typedef struct person Person, *pPerson;
struct person{
    char id[50];                 // unique id of the person
    int age;                // age of the person
    char state;             // can be S (ealthy), D (sick), I (immune)
    int infectedTime;       // number of days infected if is sick
    pRoom pR;               // pointer for Room
    pPerson nextP;           // pointer for the next Person
};





#endif	/* STRUCTS_H */

