/* 
 * File:   simulation.h
 * Author: CAROL
 *
 * Created on 10 de Junho de 2020, 19:05
 */

#ifndef SIMULATION_H
#define	SIMULATION_H
int interaction(pPerson person, pRoom r, int nRooms, int nPeoplelist);
int nPeopleInRoom(pPerson p, pRoom r, int indexR);
int nPeopleInfectedInRoom(pPerson p, pRoom r, int indexR);
int getPerson(pPerson p, int index, int idRoom);
void informationBoard(pPerson person, pRoom r, int nRooms, int nPeoplelist, int day);
pPerson addPerson(pPerson person, pRoom r, int nRooms);
int getPersonToMove(pPerson person, pRoom r, int index, int nRooms,int idRO, int idRD);
void moveRoom(pPerson person, pRoom r, int nRooms, int nPeoplelist);
void saveInfo(pPerson person, pRoom r, int nRooms, int day);
void saveLastPopulation(pPerson person);
#endif	/* SIMULATION_H */

