#include "arbolb.h"
#include "pagina.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "cstdlib"
#include "fstream"
#include "iostream"

using namespace std;

void arbolb::crearArbolB(pagina **raiz){
    *raiz = NULL;
}

void arbolb::insertar(pagina **raiz, tipoClave cl){
    int subeArriba;
    tipoClave mediana;
    pagina *p, *nd;
    empujar(*raiz, cl, &subeArriba, &mediana, &nd);
    if(subeArriba){
        p=(pagina*) malloc(sizeof(pagina));
        p->cuenta=1;
        p->claves[1]=mediana;
        p->ramas[0]=*raiz;
        p->ramas[1]=nd;
        *raiz = p;
    }
}

void arbolb::empujar(pagina *actual, tipoClave cl, int *subeArriba, tipoClave *mediana, pagina **nuevo){
    int k;
    if(actual==NULL){
        *subeArriba=1;
        *mediana=cl;
        *nuevo=NULL;
    }else{
        int esta;
        esta=buscarNodo(actual, cl, &k);
        if(esta){
            cout<<"\nClave duplicada"<<endl;
            *subeArriba=0;
            return;
        }
        empujar(actual->ramas[k], cl, subeArriba, mediana, nuevo);
        if(*subeArriba){
            if(nodoLLeno(actual)){
                dividirNodo(actual, *mediana, *nuevo, k, mediana, nuevo);
            }else{
                *subeArriba=0;
                meterHoja(actual, *mediana, *nuevo, k);
            }
        }
    }
}

pagina* arbolb::buscar(pagina *actual, tipoClave cl, int *indice){
    if(actual==NULL){
        return NULL;
    }else{
        int esta;
        esta = buscarNodo(actual, cl, indice);
        if(esta){
            return actual;
        }else{
            return buscar(actual->ramas[*indice], cl, indice);
        }
    }
}

int arbolb::buscarNodo(pagina *actual, tipoClave cl, int *k){
    int encontrado;
    if(cl<actual->claves[1]){
        encontrado=0;
        *k=0;
    }else{
        //examina claves del nodo en orden descendente
        *k=actual->cuenta;
        while((cl<actual->claves[*k]) && (*k>1)){
            (*k)--;
        }
        encontrado=(cl==actual->claves[*k]);
    }
    return encontrado;
}

void arbolb::meterHoja(pagina *actual, tipoClave cl, pagina *rd, int k){
    int i;
    for(i=actual->cuenta; i>=k+1; i--){
        actual->claves[i+1]=actual->claves[i];
        actual->ramas[i+1]=actual->ramas[i];
    }
    actual->claves[k+1]=cl;
    actual->ramas[i+1]=rd;
    actual->cuenta++;
}

void arbolb::dividirNodo(pagina *actual, tipoClave cl, pagina *rd, int k, tipoClave *mediana, pagina **nuevo){
    int i, posMdna;
    posMdna=(k<=m/2)? m/2: m/2+1;
    (*nuevo)=(pagina*) malloc(sizeof(pagina));
    for(i=posMdna+1; i<m; i++){
        (*nuevo)->claves[i-posMdna]=actual->claves[i];
        (*nuevo)->ramas[i-posMdna]=actual->ramas[i];
    }
    (*nuevo)->claves[i-posMdna]=actual->claves[i];
    actual->cuenta=posMdna;
    if(k<=m/2){
        meterHoja(*nuevo, cl, rd, k);
    }else{
        meterHoja(*nuevo, cl, rd, k-posMdna);
    }
    *mediana=actual->claves[actual->cuenta];
    (*nuevo)->ramas[0]=actual->ramas[actual->cuenta];
    actual->cuenta--;
}

void arbolb::eliminar(pagina **raiz, tipoClave cl){
    int encontrado;
    eliminarRegistro(*raiz, cl, &encontrado);
    if(encontrado){
        printf("clave %d eliminada\n",cl);
        if((*raiz)->cuenta==0){
            pagina* p= *raiz;
            *raiz=(*raiz)->ramas[0];
            free(p);
        }
    }else{
        cout<<"clave no encontrada"<<endl;
    }
}

void arbolb::eliminarRegistro(pagina *actual, tipoClave cl, int *encontrado){
    int k;
    if(actual!=NULL){
        *encontrado=buscarNodo(actual, cl, &k);
        if(*encontrado){
            if(actual->ramas[k-1]==NULL){
                quitar(actual, k);
            }else{
                sucesor(actual, k);
                eliminarRegistro(actual->ramas[k], actual->claves[k], encontrado);
            }
        }else{
            eliminarRegistro(actual->ramas[k], cl, encontrado);
        }
        if(actual->ramas[k]!=NULL)
            if(actual->ramas[k]->cuenta < m/2)
                restablecer(actual, k);
    }else{
        *encontrado = 0;
    }
}

void arbolb::quitar(pagina *actual, int k){
    for(int j=k+1; j<=actual->cuenta; j++){
        actual->claves[j-1]=actual->claves[j];
        actual->ramas[j-1]=actual->ramas[j];
    }
    actual->cuenta--;
}

void arbolb::sucesor(pagina *actual, int k){
    pagina* q;
    q=actual->ramas[k];
    while(q->ramas[0]!=NULL){
        q = q->ramas[0];
    }
    actual->claves[k]=q->claves[1];
}

void arbolb::restablecer(pagina *actual, int k){
    if(k>0){
        if(actual->ramas[k-1]->cuenta > m/2){
            moverDerecha(actual, k);
        }else{
            combinar(actual, k);
        }
    }else{
        if(actual->ramas[1]->cuenta > m/2){
            moverIzquierda(actual, 1);
        }else{
            combinar(actual, 1);
        }
    }
}

void arbolb::moverDerecha(pagina *actual, int k){
    pagina* nodoProb = actual->ramas[k];
    pagina* nodoIzq = actual->ramas[k-1];
    for(int j=nodoProb->cuenta; j>=1; j--){
        nodoProb->claves[j+1]=nodoProb->claves[j];
        nodoProb->ramas[j+1]=nodoProb->ramas[j];
    }
    nodoProb->cuenta++;
    nodoProb->ramas[1]=nodoProb->ramas[0];
    nodoProb->claves[1]=actual->claves[k];
    actual->claves[k]=nodoIzq->claves[nodoIzq->cuenta];
    nodoProb->ramas[0]=nodoIzq->ramas[nodoIzq->cuenta];
    nodoIzq->cuenta--;
}

void arbolb::moverIzquierda(pagina *actual, int k){
    pagina* nodoProb=actual->ramas[k-1];
    pagina* nodoDer=actual->ramas[k];
    nodoProb->cuenta++;
    nodoProb->claves[nodoProb->cuenta]=actual->claves[k];
    nodoProb->ramas[nodoProb->cuenta]=nodoDer->ramas[0];
    actual->claves[k]=nodoDer->claves[1];
    nodoDer->ramas[1]=nodoDer->ramas[0];
    nodoDer->cuenta--;
    for(int j=1; j<=nodoDer->cuenta; j++){
        nodoDer->claves[j]=nodoDer->claves[j+1];
        nodoDer->ramas[j]=nodoDer->ramas[j+1];
    }
}

void arbolb::combinar(pagina *actual, int k){
    pagina *nodoIzq, *q;
    q=actual->ramas[k];
    nodoIzq=actual->ramas[k-1];
    nodoIzq->cuenta++;
    nodoIzq->claves[nodoIzq->cuenta]=actual->claves[k];
    nodoIzq->ramas[nodoIzq->cuenta]=q->ramas[0];
    for(int i=1; i<=q->cuenta; i++){
        nodoIzq->cuenta++;
        nodoIzq->claves[nodoIzq->cuenta]=q->claves[i];
        nodoIzq->ramas[nodoIzq->cuenta]=q->ramas[i];
    }

    for(int i=k; i<=actual->cuenta-1; i++){
        actual->claves[i]=actual->claves[i+1];
        actual->ramas[i]=actual->ramas[i+1];
    }

    actual->cuenta--;
    free(q);
}

void arbolb::listarC(pagina *actual){
    if(actual!=NULL){
        listarC(actual->ramas[0]);
        for(int i=0; i<=actual->cuenta; i++){
            printf("%d \t", actual->claves[i]);
            listarC(actual->ramas[i]);
        }
    }
}
