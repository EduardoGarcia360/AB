// Win32Project1.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "pagina.h"
#include "ArbolB.h"

using namespace std;

pagina* arbol;
pagina* p;
arbolb instancia;
void meter(pagina** arbol, int n);

int _tmain(int argc, _TCHAR* argv[])
{
	instancia.crearArbolB(&arbol);
	meter(&arbol, 4);
	meter(&arbol, 5);
	meter(&arbol, 6);
	meter(&arbol, 8);
	meter(&arbol, 11);
	instancia.listarCreciente(arbol);
	system("pause");
}

void meter(pagina** arbol, int n){
	instancia.insertar(arbol, n);
}