#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"
#include "automata.h"

#define MAX_ERROR_SIZE 20
#define MAX_PALABRA_SIZE 20

int reconocerTipo(char palabra[], int len);

void saludar(){
    printf("Hola mundo\n");
}

char* leer_teclado(){
    char *string_teclado = malloc(sizeof(char) * 50);
    printf("Introduce una cadena de numeros: ");
    fgets(string_teclado, 50, stdin);
    return string_teclado;
}

char* leer_archivo(char nombre_archivo[]){
    FILE *archivo;
    char *string_archivo = malloc(sizeof(char)*50);
    int i=0; //longitud de la cadena
    char c=0; //caracter a leer
    archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo");
        return (NULL);
    }
    while((c=fgetc(archivo))!=EOF){
        string_archivo[i]=c;
        i++;
    }
    string_archivo[i]='\0';
    fclose(archivo);
    return string_archivo;
}

char* automata_uno(){
    printf("Queres leer un archivo o escribir en el teclado? (1/2)\n");
    int opcion;
    scanf("%d", &opcion);
    char *string;
    if(opcion==1){
        printf("Introduce el nombre del archivo: ");
        char nombre_archivo[50];
        scanf("%s", nombre_archivo);
        string = leer_archivo(nombre_archivo);
    }
    else{
        string = leer_teclado();
    }
    int d,o,h,e=0;
    char **errores_lexicos = malloc(sizeof(char) * MAX_ERROR_SIZE);
    int i,j,k =0;
    char palabra[MAX_PALABRA_SIZE];
    while(i<strlen(string)){
        if(string[i]=='$'){
            j=0;
            switch(reconocerTipo(palabra, strlen(palabra)-1)){
                case 'd':
                    d++;
                    break;
                case 'o':
                    o++;
                    break;
                case 'h':
                    h++;
                    break;
                default:
                    e++;
                    strcpy(errores_lexicos[k], palabra);
                    k++;
                    break;
            i++;
            }
        }
        while(string[i]!='$'){
            palabra[j]=string[i];
            j++;
            i++;
        }
    }
    printf("Cantidad de decimales: %d\n", d);
    printf("Cantidad de octales: %d\n", o);
    printf("Cantidad de hexadecimales: %d\n", h);
    printf("Cantidad de errores lexicos: %d\n", e);
    printf("Errores lexicos: %s\n", errores_lexicos);
}

//devuelve 'd': decimal, 'o': octal, 'h': hexadecimal o -1 para ninguno
int reconocerTipo(char palabra[], int len){

    int state=0;
        //considero -1 al estado de rechazo
    for(int i=0; i<len; i++){
        state = transition(state, palabra[i]);
    }
        //LA NUMERACIÓN DE ESTADOS ES ACORDE AL DIAGRAMA DOCUMENTADO
    return (state==1||state==5)?('d'):((state==3)?('h'):((state==4)?('o'):-1));

}

int reconocer_int(char numero){
    switch (numero){
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break; 
        case '3':
            return 3;
            break; 
        case '4':
            return 4;
            break; 
        case '5':
            return 5;
            break; 
        case '6':
            return 6;
            break; 
        case '7':
            return 7;
            break; 
        case '8':
            return 8;
            break; 
        case '9':
            return 9;
            break; 
        default:
            return -1;
            break;
    }
}