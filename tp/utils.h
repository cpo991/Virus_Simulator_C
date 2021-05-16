/* 
 * File:   utils.h
 * Author: Carolina Oliveira - 2017011988
 *
 * Created on 30 de Março de 2020, 18:49
 */

#ifndef UTILS_H
#define UTILS_H

void Simulation_menu();

void exit_menu();

int shutdown();

int verifiesFileP(char* filenameP);

int verifiesFileR(char* filenameR);

void separator();

void header();

void preparation_menu();

void printConnec_menu();

void printRooms_menu();

void printPeople_menu();

void main_menu();
// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

#endif /* UTILS_H */
