#ifndef PAGINA_H
#define PAGINA_H
#define m 5

typedef int tipoClave;

typedef struct pagina{
    tipoClave claves[m];
    struct pagina* ramas[m];
    int cuenta;
} Pagina;

int nodoLLeno(Pagina* actual);
int nodoSemiVacio(Pagina* actual);
void escribeNodo(Pagina* actual);

#endif // PAGINA_H
