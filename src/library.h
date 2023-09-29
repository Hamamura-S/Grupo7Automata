#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lists.h"
#include "automata.h"
#include "infix.h"
#include "postfix.h"

#define MAX_ERROR_SIZE 20
#define MAX_PALABRA_SIZE 20
#define MAX_STRING_SIZE 100

// Constante simbólica para el nombre de la carpeta files
#define FILES_FOLDER "../files/"
// Constante simbólica para el tamaño del arreglo nombre_archivo
#define FILE_NAME_SIZE 100

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

// Función para leer una cadena desde un archivo o desde el teclado
char* leer_cadena() {
  // Declarar e inicializar la variable string con un valor nulo
  char *string = NULL;
  // Declarar e inicializar la variable opcion con un valor por defecto
  int opcion = 0;
  // Mostrar el menú de opciones al usuario
  puts("Leer un archivo o escribir en el teclado? (1/2)");
  // Leer la opción elegida por el usuario
  scanf("%d", &opcion);
  getchar();
  // Usar un bloque switch-case para ejecutar la acción correspondiente a la opción
  switch (opcion) {
    case 1: { // Leer desde archivo
      puts("El archivo debe encontrarse en la carpeta files");
      puts("\t| Ingresar nombre de archivo: ../files/");
      // Declarar e inicializar el arreglo nombre_archivo con la constante FILES_FOLDER
      char nombre_archivo[FILE_NAME_SIZE] = FILES_FOLDER;
      // Declarar el arreglo name
      char name[40];
      // Usar fgets para leer el nombre del archivo
      fgets(name, 40, stdin);
      // Eliminar el carácter de nueva línea al final del nombre del archivo
      name[strlen(name)-1]='\0';
      // Usar strncat para concatenar el nombre del archivo
      strncat(nombre_archivo, name, FILE_NAME_SIZE - strlen(FILES_FOLDER) - 1);
      // Asignar el valor devuelto por la función leer_archivo a la variable string
      string = leer_archivo(nombre_archivo);
      // Verificar si la función leer_archivo devolvió un valor nulo
      if (string == NULL) {
        // Mostrar un mensaje de error
        puts("No se pudo abrir o leer el archivo");
        // Volver a llamar a la función leer_cadena
        return leer_cadena();
      }
      break;
    }
    case 2: { // Leer desde teclado
      // Asignar el valor devuelto por la función leer_teclado a la variable string
      string = leer_teclado();
      // Verificar si la función leer_teclado devolvió un valor nulo
      if (string == NULL) {
        // Mostrar un mensaje de error
        puts("No se pudo asignar memoria para la cadena");
        // Volver a llamar a la función leer_cadena
        return leer_cadena();
      }
      // Eliminar el carácter de nueva línea al final de la cadena
      string[strlen(string)-1]='\0';
      break;
    }
    default: { // Opción inválida
      puts("Opcion invalida.");
      // Volver a llamar a la función leer_cadena
      return leer_cadena();
    }
  }
  // Devolver la cadena leída
  return string;
}

int operacion_aritmetica(){
    line();
    char *expresion= (char*)malloc(100);// Se declara un puntero a char para guardar la expresión
    expresion = leer_cadena();

    if(expresion != NULL){
        int d=0,o=0,h=0,e=0;
        char* errores_lexicos[10];
        int i=0,j=0;
        char palabra[MAX_PALABRA_SIZE];
        int charAmount=strlen(expresion)-1;
        printf("%s (%d car.)\n\n", expresion,charAmount+1);
        printf("La cadena leida es: %s\n",expresion);

        while(i<=charAmount){
            j=0;
            printf("Operandos validos-> ");
            while((expresion[i] != '+' && expresion[i] != '-' && expresion[i] != '*' && expresion[i] != '/') && i <=charAmount){
                printf("%c",expresion[i]);
                palabra[j]=expresion[i];
                i++;
                j++;
            }
            printf("%c\n",expresion[i]);
            switch(reconocerTipo(palabra, j)){
                case 'd': d++;
                break;
                case 'o': o++;
                break;
                case 'h': h++;
                break;
                default:
                    //cadena no reconocida se agrega al vector de cadenas  
                    errores_lexicos[e]=(char*)malloc(j+1); 
                    memcpy(errores_lexicos[e], palabra, j);
                    errores_lexicos[e][j]='\0';
                    e++;
                    break;
            }i++;
        }
        printf("Cantidad de errores lexicos: %d\n", e);
        if(e>0){
        for(int i=0;i<e;i++){
            printf("\t%d. %s\n",i+1, errores_lexicos[i]);
            free(errores_lexicos[i]);
        }
        }else if (e==0){
            char* postfija = infixToPostfix(expresion);
            printf("Cadena procesada correctamente.\n\n");
            printf("Cantidad de decimales: %d\n", d);
            if (validarCadena(postfija)) { // Se llama a la función validarCadena para comprobar si la expresión es válida
                printf("La operación ingresada es: %s\n", expresion); // Se imprime la cadena de la operación infija
                printf("La operación en notación postfija es: %s\n", postfija); // Se imprime la cadena de la operación postfija
                printf("El resultado es: %.2f\n", evaluarPostfijo(postfija));
            }
            else{ // Si la expresión no es válida, se imprime un mensaje de error
                printf("La expresión no es válida\n");
            }
            free(postfija); // Se libera la memoria reservada para la expresión postfija
        }
    }
    line();
    return 0;
}
