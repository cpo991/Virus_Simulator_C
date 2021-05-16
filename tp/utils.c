/* 
 * File:   utils.c
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 30 de Março de 2020, 18:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

void Simulation_menu(){
    separator();
    printf("\t\t\t\t\t\t  Simulation Menu\n");
    separator();
    printf("\t\t\t\t\t\t1 - Increments 1 in simulation\n");
    printf("\t\t\t\t\t\t2 - Show Statistics\n");
    printf("\t\t\t\t\t\t3 - Add sick person\n");
    printf("\t\t\t\t\t\t4 - Transfer People\n");
    printf("\t\t\t\t\t\t5 - End Simulation\n");
    separator();
}

void exit_menu(){
    separator();
    printf("\t\t\t\t\t  Are you sure you want to exit?\n");
    separator();
    printf("\t\t\t\t\t\t1 - Yes\n");
    printf("\t\t\t\t\t\t2 - No\n");
    separator();
}

int shutdown() {     
    char aux[1];
    int op;
    do{
        do{
            exit_menu();
            printf("\n\t\t\t\t\t\tOption: ");
            scanf(" %s", &aux);
            op = atoi(aux);     
        }while(aux == 0);       // verifies if it's receiving an intiger
        switch (op){
            case 1:
                return 1;
                break;
            case 2:
                return 0;
                break;
        }
    }while (op != 2);
    return 0;
}

int verifiesFileR(char* filenameR){
    int tam = 0;
    for(int i = 0; i < strlen(filenameR); i++) {  
        if(filenameR[i] != ' ')  
            tam++;  
    }
    if((filenameR[tam-1] != 'n') || (filenameR[tam-2] != 'i') || 
            (filenameR[tam-3] != 'b') || (filenameR[tam-4] != '.') ){
        printf("\n\t\t\t\t\t\tERROR: Filename must end in .bin");
        return 0;
    }
    return 1;
}

int verifiesFileP(char* filenameP){
    int tam = 0;
    for(int i = 0; i < strlen(filenameP); i++) {  
        if(filenameP[i] != ' ')  
            tam++;  
    }
    if((filenameP[tam-1] != 't') || (filenameP[tam-2] != 'x') || 
            (filenameP[tam-3] != 't') || (filenameP[tam-4] != '.') ){
        printf("\n\t\t\t\t\t\tERROR: Filename must end in .txt");
        return 0;
    }
    return 1;
}

void separator() {
    printf("------------------------------------------------------------");
    printf("------------------------------------------------------------");
}

void header(){
    char a = 92;
 printf("\n\n\n\n\t\t   __     ___                  ____  _                 _       _   _             \n");
 printf("\t\t   %c %c   / (_)_ __ _   _ ___  / ___|(_)_ __ ___  _   _| | __ _| |_(_) ___  _ __  \n",a,a);
 printf("\t\t    %c %c / /| | '__| | | / __| %c___ %c| | '_ ` _ %c| | | | |/ _` | __| |/ _ %c| '_ %c \n",a,a,a,a,a,a,a);
 printf("\t\t     %c V / | | |  | |_| %c__ %c  ___) | | | | | | | |_| | | (_| | |_| | (_) | | | |\n",a,a,a);
 printf("\t\t      %c_/  |_|_|   %c__,_|___/ |____/|_|_| |_| |_|%c__,_|_|%c__,_|%c__|_|%c___/|_| |_|\n\n\n",a,a,a,a,a,a);
}

void main_menu(){
    separator();
    printf("\t\t\t\t\t\t  Main Menu\n");
    separator();
    printf("\t\t\t\t\t\t1 - Preparation & Simulation\n");
    printf("\t\t\t\t\t\t2 - Exit\n");
    separator();
}

void preparation_menu(){
    separator();
    printf("\t\t\t\t\t\t Preparation Menu\n");
    separator();
}

void printPeople_menu(){
    separator();
    printf("\t\t\t\t\t\t  List of People\n");
    separator();
}

void printConnec_menu(){
    separator();
    printf("\t\t\t\t\t\t  List of People in each Room\n");
    separator();
}

void printRooms_menu(){
    separator();
    printf("\t\t\t\t\t\t List of Rooms\n");
    separator();
}

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}