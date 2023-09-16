#include "library.h"

int main(){
    saludar();
    //leer_teclado();
    char *palabra="+1";
    printf("palabra de tipo %c\n", reconocerTipo(palabra, 2));
}
