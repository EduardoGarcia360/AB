#ifndef ARBOLB_H
#define ARBOLB_H
#include "pagina.h"

class arbolb
{
public:
    arbolb();
    void crearArbolB(pagina** raiz);
    pagina* buscar(pagina* actual, tipoClave cl, int* k);
    void insertar(pagina** raiz, tipoClave cl);

    void eliminar(pagina** raiz, tipoClave cl);
    void eliminarRegistro(pagina* actual, tipoClave cl, int* encontrado);
    void quitar(pagina* actual, int k);
    void sucesor(pagina* actual, int k);
    void restablecer(pagina* actual, int k);
    void moverDerecha(pagina* actual, int k);
    void moverIzquierda(pagina* actual, int k);
    void combinar(pagina* actual, int k);
    void listarC(pagina* actual);
    int buscarNodo(pagina* actual, tipoClave cl, int* k);
    void empujar(pagina* actual, tipoClave cl, int* subeArriba, tipoClave* mediana, pagina** nuevo);
    void meterHoja(pagina* actual, tipoClave cl, pagina* rd, int k);
    void dividirNodo(pagina* actual, tipoClave cl, pagina* rd, int k, tipoClave* mediana, pagina** nuevo);
};

#endif // ARBOLB_H
