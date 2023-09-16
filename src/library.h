#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"

long array[20];

void saludar(){
    printf("Hola mundo\n");
}

void mostrar_array(long array[]){
    int i;
    for(i=0; i<20; i++){
        printf("%ld", array[i]);
    }
}

long* recorrer_string(char string[]){
    char digitos[] = "0123456789xABCDEF";
    char numero[20];
    int i,j,k=0;
    while(string[i] != '\0'){
        if(strchr(digitos, string[i]) == NULL){
            k=0;
            array[j] = *numero;
            j++;
            array[j] = string[i];
            j++;
        }
        numero[k] = string[i];
        k++;
        i++;
    }
    mostrar_array(array);
    return array;
}

long leer_teclado(){
    char string[100];
    printf("Introduce una cadena de numeros: ");
    scanf("%s", string);
    long *array = recorrer_string(string);
    return array;
}

long leer_archivo(){
    FILE *archivo;
    char string[100];
    archivo = fopen("numeros.txt", "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo");
        return -1;
    }
    long *array = recorrer_string(string);
    fclose(archivo);
    return *array;
}
