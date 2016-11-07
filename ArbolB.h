#pragma once
#include "pagina.h"
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

/* Creado a partir del libro:
<<Algoritmos y estructuras de datos una perspectiva en C>>
de los autores:
<<Luis Joyanes Aguilar & Ignacio Zahonero Matínez>>
utilizando:
<<Visual Studio Express 2013>>
*/

class arbolb{
	pagina instancia;
	pagina* nuevo;

public:
	void crearArbolB(pagina** raiz){
		*raiz = NULL;
	}

	pagina* buscar(pagina* actual, int cl, int* indice){
		if (actual == NULL){
			return NULL;
		}
		else{
			int esta;
			esta = buscarNodo(actual, cl, indice);
			if (esta)
				return actual;
			else
				return buscar(actual->ramas[*indice], cl, indice);
		}
	}

	void insertar(pagina** raiz, int cl){
		int subeArriba;
		int mediana;
		pagina *p, *nd;
		empujar(*raiz, cl, &subeArriba, &mediana, &nd);
		if (subeArriba){
			p = (pagina*)malloc(sizeof(pagina));
			p->cuenta = 1;
			p->claves[1] = mediana;
			p->ramas[0] = *raiz;
			p->ramas[1] = nd;
			*raiz = p;
		}
	}

	void eliminar(pagina** raiz, int cl){
		int encontrado;
		eliminarRegistro(*raiz, cl, &encontrado);
		if (encontrado){
			printf("clave %d eliminada.\n", cl);
			if ((*raiz)->cuenta == 0){
				pagina* p = *raiz;
				*raiz = (*raiz)->ramas[0];
				free(p);
			}
		}
		else{
			printf("clave no encontrada\n");
		}
	}

	void listarCreciente(pagina* actual){
		if (actual != NULL){
			int j;
			listarCreciente(actual->ramas[0]);
			for (j = 1; j <= actual->cuenta; j++){
				printf("%d \t", actual->claves[j]);
				listarCreciente(actual->ramas[j]);
			}
		}
	}

private:

	int buscarNodo(pagina* actual, int cl, int* k){
		int encontrado;
		if (cl < actual->claves[1]){
			encontrado = 0;
			*k = 0;
		}
		else{
			*k = actual->cuenta;
			while ((cl < actual->claves[*k]) && (*k>1))
				(*k)--;
			encontrado = (cl == actual->claves[*k]);
		}
		return encontrado;
	}

	void empujar(pagina* actual, int cl, int* subeArriba, int* mediana, pagina** nuevo){
		int k;
		if (actual == NULL){
			*subeArriba = 1;
			*mediana = cl;
			*nuevo = NULL;
		}
		else{
			int esta;
			esta = buscarNodo(actual, cl, &k);
			if (esta){
				puts("\nClave duplicada");
				*subeArriba = 0;
				return;
			}
			empujar(actual->ramas[k], cl, subeArriba, mediana, nuevo);
			if (*subeArriba){
				if (instancia.nodoLLeno(actual))
					dividirNodo(actual, *mediana, *nuevo, k, mediana, nuevo);
				else{
					*subeArriba = 0;
					meterHoja(actual, *mediana, *nuevo, k);
				}
			}
		}
	}

	void meterHoja(pagina* actual, int cl, pagina* rd, int k){
		int i;
		for (i = actual->cuenta; i >= k + 1; i--){
			actual->claves[i + 1] = actual->claves[i];
			actual->ramas[i + 1] = actual->ramas[i];
		}
		actual->claves[k + 1] = cl;
		actual->ramas[i + 1] = rd;
		actual->cuenta++;
	}

	void dividirNodo(pagina* actual, int cl, pagina* rd, int k, int* mediana, pagina** nuevo){
		int i, posMdna;
		posMdna = (k <= m / 2) ? m / 2 : m / 2 + 1;
		(*nuevo) = (pagina*)malloc(sizeof(pagina));
		for (i = posMdna + 1; i < m; i++){
			(*nuevo)->claves[i - posMdna] = actual->claves[i];
			(*nuevo)->ramas[i - posMdna] = actual->ramas[i];
		}
		(*nuevo)->cuenta = (m - 1) - posMdna;
		actual->cuenta = posMdna;
		if (k <= m / 2)
			meterHoja(actual, cl, rd, k);
		else
			meterHoja(*nuevo, cl, rd, k - posMdna);

		*mediana = actual->claves[actual->cuenta];
		(*nuevo)->ramas[0] = actual->ramas[actual->cuenta];
		actual->cuenta--;
	}

	void eliminarRegistro(pagina* actual, int cl, int* encontrado){
		int k;
		if (actual != NULL){
			*encontrado = buscarNodo(actual, cl, &k);
			if (*encontrado){
				if (actual->ramas[k - 1] == NULL)
					quitar(actual, k);
				else{
					sucesor(actual, k);
					eliminarRegistro(actual->ramas[k], actual->claves[k], encontrado);
				}
			}
			else{
				eliminarRegistro(actual->ramas[k], cl, encontrado);
			}
			if (actual->ramas[k] != NULL)
				if (actual->ramas[k]->cuenta < m / 2)
					restablecer(actual, k);
		}
		else{
			*encontrado = 0;
		}
	}

	void quitar(pagina* actual, int k){
		int j;
		for (j = k + 1; j <= actual->cuenta; j++){
			actual->claves[j - 1] = actual->claves[j];
			actual->ramas[j - 1] = actual->ramas[j];
		}
		actual->cuenta--;
	}

	void sucesor(pagina* actual, int k){
		pagina* q;
		q = actual->ramas[k];
		while (q->ramas[0] != NULL)
			q = q->ramas[0];

		actual->claves[k] = q->claves[1];
	}

	void restablecer(pagina* actual, int k){
		if (k > 0){
			if (actual->ramas[k - 1]->cuenta > m / 2){
				moverDrcha(actual, k);
			}
			else{
				combina(actual, k);
			}
		}
		else{
			if (actual->ramas[1]->cuenta > m / 2){
				moverIzqda(actual, 1);
			}
			else{
				combina(actual, 1);
			}
		}
	}

	void moverDrcha(pagina* actual, int k){
		int j;
		pagina* nodoProblema = actual->ramas[k];
		pagina* nodoIzqdo = actual->ramas[k - 1];
		for (j = nodoProblema->cuenta; j >= 1; j--){
			nodoProblema->claves[j + 1] = nodoProblema->claves[j];
			nodoProblema->ramas[j + 1] = nodoProblema->ramas[j];
		}
		nodoProblema->cuenta++;
		nodoProblema->ramas[1] = nodoProblema->ramas[0];
		nodoProblema->claves[1] = actual->claves[k];
		actual->claves[k] = nodoIzqdo->claves[nodoIzqdo->cuenta];
		nodoProblema->ramas[0] = nodoIzqdo->ramas[nodoIzqdo->cuenta];
		nodoIzqdo->cuenta--;
	}

	void moverIzqda(pagina* actual, int k){
		int j;
		pagina* nodoProblema = actual->ramas[k - 1];
		pagina* nodoDrcho = actual->ramas[k];

		nodoProblema->cuenta++;
		nodoProblema->claves[nodoProblema->cuenta] = actual->claves[k];
		nodoProblema->ramas[nodoProblema->cuenta] = nodoDrcho->ramas[0];

		actual->claves[k] = nodoDrcho->claves[1];
		nodoDrcho->ramas[1] = nodoDrcho->ramas[0];
		nodoDrcho->cuenta--;

		for (j = 1; j <= nodoDrcho->cuenta; j++){
			nodoDrcho->claves[j] = nodoDrcho->claves[j + 1];
			nodoDrcho->ramas[j] = nodoDrcho->ramas[j + 1];
		}
	}

	void combina(pagina* actual, int k){
		int j;
		pagina* nodoIzqdo, *q;
		q = actual->ramas[k];
		nodoIzqdo = actual->ramas[k - 1];

		nodoIzqdo->cuenta++;
		nodoIzqdo->claves[nodoIzqdo->cuenta] = actual->claves[k];
		nodoIzqdo->ramas[nodoIzqdo->cuenta] = q->ramas[0];

		for (j = 1; j <= q->cuenta; j++){
			nodoIzqdo->cuenta++;
			nodoIzqdo->claves[nodoIzqdo->cuenta] = q->claves[j];
			nodoIzqdo->ramas[nodoIzqdo->cuenta] = q->ramas[j];
		}

		for (j = k; j <= actual->cuenta - 1; j++){
			actual->claves[j] = actual->claves[j + 1];
			actual->ramas[j] = actual->ramas[j + 1];
		}
		actual->cuenta--;
		free(q);
	}

};