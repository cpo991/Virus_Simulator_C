/* 
 * File:   people.h
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 31 de Março de 2020, 19:07
 */

#ifndef PEOPLE_H
#define	PEOPLE_H
    pPerson newVectorP(char* filename, int *tam);
    int verefiesDataP(pPerson p);
    void printPeople(pPerson p);
    void addRoomPerson (pPerson p, pRoom r, int nRooms);
    void printConnections(pPerson p);
#endif	/* PEOPLE_H */

