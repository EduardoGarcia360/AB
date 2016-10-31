#include <QCoreApplication>
#include "stdlib.h"
#include "stdio.h"
#include "pagina.h"
#include "arbolb.h"

using namespace std;

pagina* rarbol;
arbolb* miarbol;
void Nclaves(pagina** arbol, int n);

int main()
{
    miarbol->crearArbolB(&rarbol);
    miarbol->insertar(&rarbol, 6);
    miarbol->insertar(&rarbol, 11);
    miarbol->insertar(&rarbol, 5);
    miarbol->insertar(&rarbol, 4);
    miarbol->insertar(&rarbol, 8);
    miarbol->insertar(&rarbol, 9);
    miarbol->insertar(&rarbol, 12);
    miarbol->insertar(&rarbol, 21);
    miarbol->insertar(&rarbol, 14);
    miarbol->insertar(&rarbol, 10);
    miarbol->insertar(&rarbol, 19);
    miarbol->insertar(&rarbol, 28);
    miarbol->insertar(&rarbol, 3);
    miarbol->insertar(&rarbol, 17);
    miarbol->insertar(&rarbol, 32);
    miarbol->insertar(&rarbol, 15);
    miarbol->insertar(&rarbol, 16);
    miarbol->insertar(&rarbol, 26);
    miarbol->insertar(&rarbol, 27);
    miarbol->listarC(rarbol);
}

void Nclaves(pagina **arbol, int n){

}
