#include <stdlib.h>


/*  ------------------   README   ------------------

FUNCIONES DE INTERÉS PARA EL TRABAJO PRÁCTICO "AUTOMATAS"

List createList();

    EJEMPLO: List operadores = createList(); 
        operadores es LISTA VACIA (puntero a NULL)


int listSize(List lista);

    EJEMPLO: int len = listSize(operadores);
        len sera la CANTIDAD DE OPERADORES almacenados


void push(List *lista, int data);

    EJEMPLO: push(&operadores, 5);
        se agrega el 5 al final de la lista operadores


int pop(List *lista);

    EJEMPLO: int n = pop(&operadores);
        n tiene el valor del ultimo operador almacenado


void enqueue(List *lista, int data);

    EJEMPLO: enqueue(&operadores, 5);
        se agrega el 5 al comienzo de la lista operadores


int dequeue(List* lista);

    EJEMPLO: int n = dequeue(&operadores);
        n tiene el valor del primer operador almacenado


NO SE REQUIRIERON FUNCIONES DE ACCESO POR INDICE

*/


struct Node{
    int value;
    struct Node *next;
};

typedef struct Node Node;

typedef Node* List;

//asigna memoria dinamica para guardar un nuevo nodo
Node* createNode(int data){

    Node * newNode = (Node*)malloc(sizeof(Node));

    newNode->next=NULL;
    newNode->value=data;

    return newNode;

}

//Crea una lista vacia
List createList(){
    List newList=NULL;
    return newList;
}

int listSize(List lista){

    if(lista==NULL){
        //lista no inicializada, no hay nodos
        return 0;
    }else{
        //hay al menos 1 nodo, aumento por cada iteracion
        int count=1;
        Node* nodo = lista;
        while(nodo->next!=NULL){
            nodo=nodo->next;
            count++;
        }
        return count;
    }

}

Node* getNode(List lista, int index){

    if(lista==NULL){
        //lista no inicializada, no hay nodos
        return NULL;
    }else{
        Node* nodo = lista; 
        //itero hasta el nodo en la posicion [index]
        for(int i=0; i<index; i++){
            
            nodo=nodo->next;

            //chequeo no haberme excedido del ultimo nodo
            if(nodo==NULL){
                return NULL;
            }

        }

        return nodo;
    }

}

//devuelve el ultimo nodo de la lista
Node* lastNode(List lista){

    Node* last = getNode(lista, listSize(lista)-1);

    return last;
}

//asigna memoria dinamica, creando un nodo y agregandolo al final
void push(List *lista, int data){

    Node* newNode = createNode(data);

    if(*lista==NULL){
        //la lista esta declarada pero no inicializada
        *lista=newNode;

    }else{
        //iterar hasta hallar el ultimo nodo
        Node* last=lastNode(*lista);
        last->next=newNode;
    }

}

//quita el ultimo nodo de la lista y devuelve el valor almacenado
    //devuelve -1 si la lista estaba vacia
int pop(List *lista){
    
    int length = listSize(*lista);

    if(*lista==NULL){
        //la lista esta vacia

        return -1;

    }else if(length==1){
        //la lista solo tiene un elemento

        int value=(*lista)->value;
            //libero el nodo
        free(*lista);
        *lista=NULL;
            //listo!
        return value;

    }else{
        //busco el ultimo
        Node* last = lastNode(*lista);
        //y busco el anteulitmo
        Node* newLast = getNode(*lista, length-2);

        //ahora puedo liberar el ultimo y actualizar el anteultimo
        int value=last->value;
        free(last);

        newLast->next=NULL;

        return value;

    }
}

void enqueue(List *lista, int data){
    
    Node* newNode = createNode(data);

    //hago que el siguiente al nuevo nodo sea el primero de la lista
    newNode->next=*lista;

    //y ajusto lista para que apunte al nuevo primer nodo
    *lista=newNode;

}

//devuelve el primer elemento
    //-1 si esta vacia
int dequeue(List* lista){

    if(*lista==NULL){
        //la lista esta vacia
        return -1;

    }

    Node* firstNode = *lista;

    //hago que lista apunte al segundo nodo
    *lista=(*lista)->next;

    //libero el primer nodo
    int value = firstNode->value;
    free(firstNode);
    return value;

}

void freeList(List *lista){
    while(*lista!=NULL){
        dequeue(lista);
    }
}
