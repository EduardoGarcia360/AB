#pragma once
#include <stdlib.h>
#define m 5

using namespace std;

/* Creado a partir del libro:
	<<Algoritmos y estructuras de datos una perspectiva en C>>
	de los autores:
	<<Luis Joyanes Aguilar & Ignacio Zahonero Mat�nez>>
	utilizando:
	<<Visual Studio Express 2013>>
*/

class pagina{
public:
	int claves[m];
	pagina* ramas[m];
	int cuenta;
	bool nodoLLeno(pagina* actual){
		return (actual->cuenta == m - 1);
	}
private:
};