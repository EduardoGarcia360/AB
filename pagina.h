#pragma once
#include <stdlib.h>
#include "Clases/listadc.h"
#define m 5

using namespace std;

/* Creado a partir del libro:
<<Algoritmos y estructuras de datos una perspectiva en C>>
de los autores:
<<Luis Joyanes Aguilar & Ignacio Zahonero Matínez>>
utilizando:
<<Visual Studio Express 2013>>
*/

class pagina{
public:
	int claves[m];
	char* fecha[m];
	char* periodo[m];
	long int dpi[m];
	char* placa[m];
	listadc* Lista;
	pagina* ramas[m];
	int cuenta;
	bool nodoLLeno(pagina* actual){
		return (actual->cuenta == m - 1);
	}
private:
};