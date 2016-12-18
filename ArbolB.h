#pragma once
#include "pagina.h"
#include "Clases/tablahash.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

std::stringstream cont;
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
	string nodos, relaciones, extranjeras, nodos_hash;
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

	void insertar(pagina** raiz, int cl, char* fecha, char* periodo, long int dpi, char* placa){
		int subeArriba;
		int mediana;
		pagina *p, *nd;
		empujar(*raiz, cl, fecha, periodo, dpi, placa, &subeArriba, &mediana, &nd);
		if (subeArriba){
			p = (pagina*)malloc(sizeof(pagina));
			p->cuenta = 1;
			p->claves[1] = mediana;
			p->fecha[1] = fecha;
			p->periodo[1] = periodo;
			p->dpi[1] = dpi;
			p->placa[1] = placa;
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
		/*
		if (actual != NULL){
		int j;
		listarCreciente(actual->ramas[0]);
		for (j = 1; j <= actual->cuenta; j++){
		printf("%d -> %d \t", j, actual->claves[j]);
		listarCreciente(actual->ramas[j]);
		}
		}
		*/
		mostrar(actual);
		cout << nodos << endl;
		cout << relaciones << endl;
	}

	void mostrar(pagina* actual){
		if (actual != NULL){
			int j, i = 0;
			mostrar(actual->ramas[0]);
			nodos += "node" + to_string(i) + " [label=\"{<n> ";
			for (j = 1; j <= actual->cuenta; j++){
				printf("%d -> %d \n", j, actual->claves[j]);
				nodos += to_string(actual->claves[j]) + " | ";
			}
			nodos += "<p> }\"];\n";
			i++;
			for (j = 1; j <= actual->cuenta; j++){
				if (actual->ramas[j] != NULL){
					relaciones += "node" + to_string(i) + ":" + "f" + to_string(i) + "->";
					relaciones += "node" + to_string(i + 1) + ":n; \n";
				}
				mostrar(actual->ramas[j]);
			}
		}
	}

	void graficar_individual(pagina* actual){
		string encabezado = "digraph grafica{\n rankdir=TB;\n node[shape=record, style=filled];\n";
		mo(actual, 0);
		string contenido = encabezado + nodos + relaciones + " \n}";
		ofstream escritura;
		escritura.open("C:\\Users\\Edu\\Downloads\\arbolb.dot", ios::out);
		if (escritura.is_open()){
			cout << "abrio el archivo" << endl;
			escritura << contenido << endl;
			escritura.close();
			system("dot -Tpng C:\\Users\\Edu\\Downloads\\arbolb.dot -O");
		}
		else{
			cout << "nell prro" << endl;
		}
		
	}

	string arbolb_subgraph(pagina* actual){
		string encabezado = "subgraph cluster2 {\n nodesep=.05;\n rankdir=TB;\n node[shape=record,width=.1,height=.1];\n";
		mo(actual, 0);
		string contenido = encabezado + nodos + relaciones + "label=\"ArbolB: Polizas\";\ncolor=blue\n}";
		return contenido;
	}

	void llenar_nodos_hash(string h){
		this->nodos_hash = h;
	}

	string arbolb_relaciones_externas(pagina* actual){
		extranjeras = "";
		ex(actual, 0);
		return extranjeras;
	}

	bool modificar(pagina* actual, int clave, char* fecha, char* periodo, long int dpi, char* placa){
		bool modificado = false, seguir = true;
		mod(actual, clave, fecha, periodo, dpi, placa, modificado, seguir);
		return modificado;
	}

	string obtener_placa(pagina* actual, int clave){
		string pla = "n";
		bool seguir = true;
		op(actual, clave, pla, seguir);
		return pla;
	}

	string buscar_contenido(pagina* actual, int clave){
		cont.str("");
		bool seguir = true;
		bc(actual, clave, seguir);
		string todo = cont.str();
		return todo;
	}

private:

	void bc(pagina* raiz, int clave, bool seguir){
		if (raiz){
			for (int i = 1; i <= raiz->cuenta; i++){
				if (clave == raiz->claves[i]){
					cont << raiz->fecha[i] << ";" << raiz->periodo[i] << ";" << to_string(raiz->dpi[i]) << ";" << raiz->placa << ";";
					seguir = false;
					break;
				}
			}
			if (seguir == true){
				for (int j = 0; j <= raiz->cuenta; j++){
					if (raiz->ramas[j] != NULL){
						bc(raiz->ramas[j], clave, seguir);
					}
				}
			}
		}
	}

	void op(pagina* raiz, int clave, string a, bool seguir){
		if (raiz){
			for (int i = 1; i <= raiz->cuenta; i++){
				if (clave==raiz->claves[i]){
					a = string(raiz->placa[i]);
					seguir = false;
					break;
				}
			}
			if (seguir == true){
				for (int j = 0; j <= raiz->cuenta; j++){
					if (raiz->ramas[j] != NULL){
						op(raiz->ramas[j], clave, a, seguir);
					}
				}
			}
		}
	}

	void mod(pagina* raiz, int clave, char* fecha, char* periodo, long int dpi, char* placa, bool modificado, bool seguir){
		if (raiz){
			for (int i = 1; i <= raiz->cuenta; i++){
				if (clave == raiz->claves[i]){
					if (strcmp(fecha, "n") != 0){
						raiz->fecha[i] = fecha;
					}
					if (strcmp(periodo, "n") != 0){
						raiz->periodo[i] = periodo;
					}
					if (dpi != 0){
						raiz->dpi[i] = dpi;
					}
					if (strcmp(placa, "n") != 0){
						raiz->placa[i] = placa;
					}
					modificado = true;
					seguir = false;
					break;
				}
			}
			if (seguir == true){
				for (int j = 0; j <= raiz->cuenta; j++){
					if (raiz->ramas[j] != NULL){
						mod(raiz->ramas[j], clave, fecha, periodo, dpi, placa, modificado, seguir);
					}
				}
			}
		}
	}

	void ex(pagina* raiz, int n){
		if (raiz){
			string no = to_string(n);
			for (int i = 1; i <= raiz->cuenta; i++){
				string t = string(raiz->periodo[i]);
				if (strcmp(raiz->periodo[i], "z") != 0){
					string a = to_string(raiz->claves[i]);
					if (strcmp(raiz->placa[i], "n") != 0){
						extranjeras += "node" + no + ":" + a + " -> \"" + string(raiz->placa[i]) + "\"\n";
					}
					if (raiz->dpi[i] != 0){
						int nodo = validar_ubicacion_hash(to_string(raiz->dpi[i]));
						if (nodo != -1){
							extranjeras += "node" + no + ":" + a + " -> node" + to_string(nodo) + ":" + to_string(raiz->dpi[i]) + ";\n";
						}
					}
				}

			}
			
			for (int j = 0; j <= raiz->cuenta; j++){
				if (raiz->ramas[j] != NULL){
					n += 1;
					ex(raiz->ramas[j], n);
				}
			}
		}
	}

	int validar_ubicacion_hash(string dpi){
		int numero = -1;
		string todo = nodos_hash;
		nodos_hash = "";
		char* ctodo = new char[todo.length() + 1];
		strcpy(ctodo, todo.c_str());
		char* datos;
		datos = strtok(ctodo, ";");
		bool igual = false;
		while (datos != NULL){
			if (strcmp(datos, dpi.data()) == 0){
				/*[dpi][nodo][dpi][nodo][dpi]...*/
				/*comparo si el dpi es igual al que tiene el arbol b*/
				/*en caso sea correcto, en la sig. iteracion entrara en if de abajo.*/
				igual = true;
			}
			else if(igual == true){
				/*retorno el nodo en el que se encuentra el dato en la tabla hash.*/
				numero = atoi(datos);
				break;
			}
			datos = strtok(NULL, ";");
		}
		return numero;
	}

	void mo(pagina* raiz, int n){
		//funciona solo para raiz y 5 hijos :,v
		if (raiz){
			nodos += "node" + to_string(n) + " [label=\"{ ";
			for (int i = 1; i <= raiz->cuenta; i++){
				string a = to_string(raiz->claves[i]);
				nodos += "<" + a + "> " + a + " | ";
			}
			nodos += " }\"]; \n";
			for (int j = 0; j <= raiz->cuenta; j++){
				if (raiz->ramas[j] != NULL){
					n += 1;
					relaciones += "node0 -> node" + to_string(n) + "; \n";
					mo(raiz->ramas[j], n);
				}
			}
		}
	}

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

	void empujar(pagina* actual, int cl, char* fecha, char* periodo, long int dpi, char* placa, int* subeArriba, int* mediana, pagina** nuevo){
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
			empujar(actual->ramas[k], cl, fecha, periodo, dpi, placa, subeArriba, mediana, nuevo);
			if (*subeArriba){
				if (instancia.nodoLLeno(actual))
					dividirNodo(actual, *mediana, fecha, periodo, dpi, placa, *nuevo, k, mediana, nuevo);
				else{
					*subeArriba = 0;
					meterHoja(actual, *mediana, fecha, periodo, dpi, placa, *nuevo, k);
				}
			}
		}
	}

	void meterHoja(pagina* actual, int cl, char* fecha, char* periodo, long int dpi, char* placa, pagina* rd, int k){
		int i;
		for (i = actual->cuenta; i >= k + 1; i--){
			actual->claves[i + 1] = actual->claves[i];
			actual->fecha[i + 1] = actual->fecha[i];
			actual->periodo[i + 1] = actual->periodo[i];
			actual->dpi[i + 1] = actual->dpi[i];
			actual->placa[i + 1] = actual->placa[i];
			actual->ramas[i + 1] = actual->ramas[i];
		}
		actual->claves[k + 1] = cl;
		actual->fecha[k + 1] = fecha;
		actual->periodo[k + 1] = periodo;
		actual->dpi[k + 1] = dpi;
		actual->placa[k + 1] = placa;
		actual->ramas[i + 1] = rd;
		actual->cuenta++;
	}

	void dividirNodo(pagina* actual, int cl, char* fecha, char* periodo, long int dpi, char* placa, pagina* rd, int k, int* mediana, pagina** nuevo){
		int i, posMdna;
		posMdna = (k <= m / 2) ? m / 2 : m / 2 + 1;
		(*nuevo) = (pagina*)malloc(sizeof(pagina));
		for (i = posMdna + 1; i < m; i++){
			(*nuevo)->claves[i - posMdna] = actual->claves[i];
			(*nuevo)->fecha[i - posMdna] = actual->fecha[i];
			(*nuevo)->periodo[i - posMdna] = actual->periodo[i];
			(*nuevo)->dpi[i - posMdna] = actual->dpi[i];
			(*nuevo)->placa[i - posMdna] = actual->placa[i];
			(*nuevo)->ramas[i - posMdna] = actual->ramas[i];
		}
		(*nuevo)->cuenta = (m - 1) - posMdna;
		actual->cuenta = posMdna;
		if (k <= m / 2)
			meterHoja(actual, cl, fecha, periodo, dpi, placa, rd, k);
		else
			meterHoja(*nuevo, cl, fecha, periodo, dpi, placa, rd, k - posMdna);

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
			actual->fecha[j - 1] = actual->fecha[j];
			actual->periodo[j - 1] = actual->periodo[j];
			actual->dpi[j - 1] = actual->dpi[j];
			actual->placa[j - 1] = actual->placa[j];
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
		actual->dpi[k] = q->dpi[1];
		actual->fecha[k] = q->fecha[1];
		actual->periodo[k] = q->periodo[1];
		actual->placa[k] = q->periodo[1];
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
			nodoProblema->dpi[j + 1] = nodoProblema->dpi[j];
			nodoProblema->fecha[j + 1] = nodoProblema->fecha[j];
			nodoProblema->periodo[j + 1] = nodoProblema->periodo[j];
			nodoProblema->placa[j + 1] = nodoProblema->placa[j];
			nodoProblema->ramas[j + 1] = nodoProblema->ramas[j];
		}
		nodoProblema->cuenta++;
		nodoProblema->ramas[1] = nodoProblema->ramas[0];
		nodoProblema->claves[1] = actual->claves[k];
		nodoProblema->dpi[1] = actual->dpi[k];
		nodoProblema->fecha[1] = actual->fecha[k];
		nodoProblema->periodo[1] = actual->periodo[k];
		nodoProblema->placa[1] = actual->placa[k];
		actual->claves[k] = nodoIzqdo->claves[nodoIzqdo->cuenta];
		actual->dpi[k] = nodoIzqdo->dpi[nodoIzqdo->cuenta];
		actual->fecha[k] = nodoIzqdo->fecha[nodoIzqdo->cuenta];
		actual->periodo[k] = nodoIzqdo->periodo[nodoIzqdo->cuenta];
		actual->placa[k] = nodoIzqdo->placa[nodoIzqdo->cuenta];
		nodoProblema->ramas[0] = nodoIzqdo->ramas[nodoIzqdo->cuenta];
		nodoIzqdo->cuenta--;
	}

	void moverIzqda(pagina* actual, int k){
		int j;
		pagina* nodoProblema = actual->ramas[k - 1];
		pagina* nodoDrcho = actual->ramas[k];

		nodoProblema->cuenta++;
		nodoProblema->claves[nodoProblema->cuenta] = actual->claves[k];
		nodoProblema->dpi[nodoProblema->cuenta] = actual->dpi[k];
		nodoProblema->fecha[nodoProblema->cuenta] = actual->fecha[k];
		nodoProblema->periodo[nodoProblema->cuenta] = actual->periodo[k];
		nodoProblema->placa[nodoProblema->cuenta] = actual->placa[k];
		nodoProblema->ramas[nodoProblema->cuenta] = nodoDrcho->ramas[0];

		actual->claves[k] = nodoDrcho->claves[1];
		actual->dpi[k] = nodoDrcho->dpi[1];
		actual->fecha[k] = nodoDrcho->fecha[1];
		actual->periodo[k] = nodoDrcho->periodo[1];
		actual->placa[k] = nodoDrcho->placa[1];
		nodoDrcho->ramas[1] = nodoDrcho->ramas[0];
		nodoDrcho->cuenta--;

		for (j = 1; j <= nodoDrcho->cuenta; j++){
			nodoDrcho->claves[j] = nodoDrcho->claves[j + 1];
			nodoDrcho->dpi[j] = nodoDrcho->dpi[j + 1];
			nodoDrcho->fecha[j] = nodoDrcho->fecha[j + 1];
			nodoDrcho->periodo[j] = nodoDrcho->periodo[j + 1];
			nodoDrcho->placa[j] = nodoDrcho->placa[j + 1];
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
		nodoIzqdo->dpi[nodoIzqdo->cuenta] = actual->dpi[k];
		nodoIzqdo->fecha[nodoIzqdo->cuenta] = actual->fecha[k];
		nodoIzqdo->periodo[nodoIzqdo->cuenta] = actual->periodo[k];
		nodoIzqdo->placa[nodoIzqdo->cuenta] = actual->placa[k];
		nodoIzqdo->ramas[nodoIzqdo->cuenta] = q->ramas[0];

		for (j = 1; j <= q->cuenta; j++){
			nodoIzqdo->cuenta++;
			nodoIzqdo->claves[nodoIzqdo->cuenta] = q->claves[j];
			nodoIzqdo->dpi[nodoIzqdo->cuenta] = q->dpi[j];
			nodoIzqdo->fecha[nodoIzqdo->cuenta] = q->fecha[j];
			nodoIzqdo->periodo[nodoIzqdo->cuenta] = q->periodo[j];
			nodoIzqdo->placa[nodoIzqdo->cuenta] = q->placa[j];
			nodoIzqdo->ramas[nodoIzqdo->cuenta] = q->ramas[j];
		}

		for (j = k; j <= actual->cuenta - 1; j++){
			actual->claves[j] = actual->claves[j + 1];
			actual->dpi[j] = actual->dpi[j + 1];
			actual->fecha[j] = actual->fecha[j + 1];
			actual->periodo[j] = actual->periodo[j + 1];
			actual->placa[j] = actual->placa[j + 1];
			actual->ramas[j] = actual->ramas[j + 1];
		}
		actual->cuenta--;
		free(q);
	}

};