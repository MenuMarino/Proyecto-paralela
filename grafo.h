#ifndef GRAFODEF
#define GRAFODEF

#include <stdio.h>

#define LIMA_CENTRO 0
#define LINCE 1
#define MIRAFLORES 2
#define BARRANCO 3
#define RIMAC 4
#define LOS_OLIVOS 5
#define LA_MOLINA 6
#define LA_VICTORIA 7
#define MAGDALENA_DEL_MAR 8
#define SAN_BORJA 9

// Numero de ciudades
const int N = 10;

// Gasolina
const int G = 20;

/*
    Distancias:
    https://docs.google.com/spreadsheets/d/1lsCQ1IrTcD3foA8NmEVia2dVjoIufwvP7GhyRsfiShM/edit?usp=sharing 
*/

double GRAFITO[N][N] = {
    {0.0,  4.4,  7.1,  10.5, 3.8,  13.4, 13.7, 3.3,  6.8,  7.1},  /* Distancias de LIMA CENTRO a todos los demas */
    {4.4,  0.0,  3.2,  6.9,  7.4,  16.8, 14.3, 2.8,  4.6,  5.8},  /* Distancias de LINCE a todos los demas */
    {7.1,  3.2,  0.0,  3.9,  10.7, 20.0, 13.5, 5.4,  5.7,  5.2},  /* Distancias de MIRAFLORES a todos los demas */
    {10.5, 6.9,  3.9,  0.0,  14.1, 23.4, 14.5, 8.3,  8.7,  7.4},  /* Distancias de BARRANCO a todos los demas */
    {3.8,  7.4,  10.7, 14.1, 0.0,  11.4, 15.9, 6.6,  9.6,  10.3}, /* Distancias de RIMAC a todos los demas */
    {13.4, 16.8, 20.0, 23.4, 11.4, 0.0,  26.5, 16.5, 16.5, 20.2}, /* Distancias de LOS OLIVOS a todos los demas */
    {13.7, 14.3, 13.5, 14.5, 15.9, 26.5, 0.0,  13.2, 17.9, 8.8},  /* Distancias de LA MOLINA a todos los demas */
    {3.3,  2.8,  5.4,  8.3,  6.6,  16.5, 12.3, 0.0,  6.8,  4.3},  /* Distancias de LA VICTORIA a todos los demas */
    {6.8,  4.6,  5.7,  8.7,  9.6,  16.5, 17.9, 6.8,  0.0,  9.2},  /* Distancias de MAGDALENA DEL MAR a todos los demas */
    {7.1,  5.8,  5.2,  7.4,  10.3, 20.2, 8.8,  4.3,  9.2,  0.0}   /* Distancias de SAN BORJA a todos los demas */
};

void print_ciudad(int ciudad, bool newline = false) {
    switch(ciudad) {
        case LIMA_CENTRO:
            printf("Lima Centro ");
            if (newline) printf("\n");
            break;
        case LINCE:
            printf("Lince ");
            if (newline) printf("\n");
            break;
        case MIRAFLORES:
            printf("Miraflores ");
            if (newline) printf("\n");
            break;
        case BARRANCO:
            printf("Barranco ");
            if (newline) printf("\n");
            break;
        case RIMAC:
            printf("Rimac ");
            if (newline) printf("\n");
            break;
        case LOS_OLIVOS:
            printf("Los Olivos ");
            if (newline) printf("\n");
            break;
        case LA_MOLINA:
            printf("La Molina ");
            if (newline) printf("\n");
            break;
        case LA_VICTORIA:
            printf("La Victoria ");
            if (newline) printf("\n");
            break;
        case MAGDALENA_DEL_MAR:
            printf("Magdalena del Mar ");
            if (newline) printf("\n");
            break;
        case SAN_BORJA:
            printf("San Borja ");
            if (newline) printf("\n");
            break;
        default:
            break;
    }
}

#endif