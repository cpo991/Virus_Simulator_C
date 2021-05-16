/* 
 * File:   rooms.h
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 8 de Junho de 2020, 20:09
 */

#ifndef ROOMS_H
#define	ROOMS_H

pRoom initRooms(char* filename, int* tam);
int verefiesDataR(pRoom r, int nRooms);
void printRooms(pRoom r, int tam);
int getMinID(pRoom r, int nRooms);
int getMaxID(pRoom r, int nRooms);

#endif	/* ROOMS_H */

