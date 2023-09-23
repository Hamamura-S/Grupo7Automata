#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"
#include "automata.h"

#define MAX_ERROR_SIZE 20
#define MAX_PALABRA_SIZE 20
#define MAX_STRING_SIZE 100

int reconocerTipo(char palabra[], int len);

void line(){
    printf("--------------------------------------\n");
}

void saludar(){
    printf("Bienvenido.\n");
    line();
}

char keyRequest(){
    char c = getchar();
    //se debe limpiar el \n residual en stdin para evitar conflictos
    getchar();
    return c;
}

char* leer_teclado(){
    char *string_teclado = malloc(MAX_STRING_SIZE);
    printf("Introduce tu cadena: ");
    fgets(string_teclado, 50, stdin);
    return string_teclado;
}

char* leer_archivo(char nombre_archivo[]){
    FILE *archivo;
    char *string_archivo = malloc(MAX_STRING_SIZE);
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
    printf("Leer un archivo o escribir en el teclado? (1/2)\n");
    int opcion;
    scanf("%d", &opcion);
    getchar();
    char *string;
    if(opcion==1){
        printf("El archivo debe encontrarse en la carpeta files\n");
        printf("\t| Ingresar nombre de archivo: ../files/");
        char nombre_archivo[50]="../files/";
        char name[40];
        scanf("%s", name);
        strcat(nombre_archivo, name);
        string = leer_archivo(nombre_archivo);
    }
    else if(opcion==2){
        string = leer_teclado();
        string[strlen(string)-1]='\0';
    }
    else{
        printf("Opcion invalida.\n");
        automata_uno();
    }
    int d=0,o=0,h=0,e=0;
    char* errores_lexicos[10];
    int i=0,j=0;
    char palabra[MAX_PALABRA_SIZE];
    int charAmount=strlen(string)-1;
    printf("%s (%d car.)\n", string,charAmount+1);
    
    while(i<charAmount){
        j=0;
        while(string[i]!='$' && i<charAmount){
            palabra[j]=string[i];
            i++;
            j++;
        }
        switch(reconocerTipo(palabra, j)){
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
                //cadena no reconocida se agrega al vector de cadenas  
                errores_lexicos[e]=malloc(j+1); 
                memcpy(errores_lexicos[e], palabra, j);
                errores_lexicos[e][j]='\0';
                e++;
                break;
        }i++;
    }
        //IMPRIMIENDO RESULTADOS

    line();
    printf("Cadena procesada correctamente.\n");
    printf("Cantidad de decimales: %d\n", d);
    printf("Cantidad de octales: %d\n", o);
    printf("Cantidad de hexadecimales: %d\n", h);
    printf("Cantidad de errores lexicos: %d\n", e);
    if(e>0){
        for(int i=0;i<e;i++){
            printf("\t%d. %s\n",i+1, errores_lexicos[i]);
            free(errores_lexicos[i]);
        }
    }
    line();

    //liberando memoria
    free(string);
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

int charToInt(char c){
    if(c>=48 && c<=57){
        //todo bien, se ingreso un numero
        return c  - '0';
    }
    else{
        //todo mal, no es un numero
        return -1;
    }
}

void reconocer_int(){
    
    printf("Ingrese su digito: ");
    char c=keyRequest();
    int number;
    if((number=charToInt(c))!=-1){
        //todo bien, se tecleo un digito
        printf("El digito %d se reconoció correctamente\n", number);

    }else{
        //todo mal, no se ingreso un digito entre 0-9
        printf("El carácter %c no es un digito numérico válido.\n", c);
    }
    line();
}