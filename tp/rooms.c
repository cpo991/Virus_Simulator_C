/* 
 * File:   rooms.c
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 31 de Março de 2020, 20:09
 */

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"
#include "rooms.h"

#define CONNECTIONS 3
#define SPREADRATE 0.05
//#define RECOVERYPROB 1/age
#define IMMUNITYRATE 0.20

pRoom initRooms(char* filename, int* tam){
    FILE *f;
    pRoom paux, plist = NULL;
    Room newRoom;
    *tam = 0;
    
    f = fopen(filename, "rb");
    
    if (f==NULL) {
        printf("ERROR: Opening file: %s\n", filename);
        return NULL;
    }
    
    while ((fread(&newRoom,sizeof(newRoom),1,f)) == 1){
        
        paux = realloc(plist, (sizeof(Room)*((*tam)+1)));
        
        if(!paux){
            printf("ERROR: Alocating memory\n");
            fclose(f);
            return NULL;
        }

        
        plist = paux;
        paux = NULL;
        plist[*tam].id = newRoom.id;
        plist[*tam].capacity = newRoom.capacity;
        
        for(int i=0; i < CONNECTIONS ;i++)
            plist[*tam].connection[i] = newRoom.connection[i];
        (*tam)++;
    }
    fclose(f);
    return plist;
}  

int verefiesDataR(pRoom r, int nRooms){
    int aux = 0, ID, auxnRooms;
    auxnRooms = nRooms;
    if(!r){
        printf("\n\t\t\t\t\t\tERROR: There are no rooms \n");
        return 1;
    }
    
    for (int i = 0; i < nRooms; i++) {
        aux = 0;
        int nConections = 0;
        
        if(r[i].id <= 0){
            printf("\n\t\t\t\t\t\tERROR: All IDs must be positive\n");
            return 1;
        }
        
        for (int j = 0; j < auxnRooms; j++ )
        if(r[i].id == r[j].id){
            if(i != j){
                printf("\n\t\t\t\t\t\tERROR: All IDs must be unique\n");
                return 1;
            }
        }
        
        for (int k = 0; k < CONNECTIONS; k++){
            if(r[i].connection[k] != -1){
                for (int j = 0; j < CONNECTIONS; j++){
                    if(r[i].connection[k] != -1){
                        nConections++;
                        ID = r[i].connection[k];
                        if(ID != r[k].connection[j]){
                            aux++;
                        }
       
                    }
                }
            }
            if (aux == nConections){
                printf("\n\t\t\t\t\t\tERROR: Rooms are incorrectly connected\n");
                return 1;
            }
            else {
                printf("\n\t\t\t\t\t\tUpdate: Rooms are successfully Loaded\n");
                return 0;
            }
        }
    }
    return 1;
}
void printRooms(pRoom r, int nRooms){
    printRooms_menu();

    if(!r){
        printf("\n\t\t\t\t\t\tERROR: There are no rooms \n");
        return;
    }
       
    for (int i = 0; i < nRooms; i++) {
        printf("Id [%02d]\t Capacity: %d\t", r[i].id, r[i].capacity);
        for (int k = 0; k < CONNECTIONS; k++)
            if(r[i].connection[k] != -1)
                printf("Connection %d: %3d \t", k+1 ,r[i].connection[k]);
        putchar('\n');
    }
    return;
}

int getMaxID(pRoom r, int nRooms){
    int idMax = 0;
    for (int i = 0; i < nRooms; i++) {
        if (r[i].id > idMax)
            idMax = r[i].id;
    }
    return idMax;
}

int getMinID(pRoom r, int nRooms){
    int idMin = 0;
    for (int i = 0; i < nRooms; i++) {
        if (r[i].id < idMin)
            idMin = r[i].id;
    }
    return idMin;
}