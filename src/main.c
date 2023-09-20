#include "library.h"

int main(){

    //Dicen que ser cordiales sube la nota
    saludar();

    char s;
    

    do
    {

        printf("Seleccionar opción\n");
        printf("\t| Reconocer una cadena de constantes [1]\n");
        printf("\t| Convertir un char a un int [2]\n");
        printf("\t| Realizar una operacion aritmetica [3]\n");
        printf("\t| Salir [Cualquier otro]\n");
        
        s = getchar();
        getchar();
        switch (s)
        {
        case '1':
            automata_uno();
            break;
        default:
            break;
        }

        if(s == '1' || s == '2' || s == '3'){
            printf("Volver al menú? s/n\n");
            s = getchar();
            getchar();
            if(s=='s'||s=='S'){ s = '1'; }
        }

    } while ( s == '1' || s == '2' || s == '3' );
    
    printf("Hasta luego!\n");

}
