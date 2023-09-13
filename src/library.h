#include <stdio.h>
#include "lists.h"

void saludar(){
    printf("Hola mundo");
}
/*
void leer_teclado(){
    char string[100];
    int i,j,k=0;
    char numero[20];
    long array[20];
    printf("Introduce una cadena de numeros separados por '$': ");
    scanf("%s", string);
    while(string[i] != '\0'){
        if(string[i] == '$'){
            k=0;
            array[j] = numero;
            j++;
        }
        numero[k] = string[i];
        k++;
        i++;
    }

}

void leer_archivo(){
    FILE *archivo;
    char string[100];
    int i,j,k=0;
    char numero[20];
    long array[20];
    archivo = fopen("numeros.txt", "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo");
    }else{
        while(fgets(string, 100, (FILE*) archivo)){
            while(string[i] != '\0'){
                if(string[i] == '$'){
                    k=0;
                    array[j] = numero;
                    j++;
                }
                numero[k] = string[i];
                k++;
                i++;
            }
        }
    }
    fclose(archivo);
}
*/