#include "pagina.h"
#include "iostream"
#include "strstream"

int nodoLLeno(Pagina *actual){
    return (actual->cuenta==m-1);
}

int nodoSemiVacio(Pagina *actual){
    return (actual->cuenta<m/2);
}

void escribeNodo(Pagina *actual){
    int k;
    printf("\n Nodo: ");
    for(k=1; k<=actual->cuenta; k++)
        printf(" %d ", actual->claves[k]);
    printf("\n");
}
