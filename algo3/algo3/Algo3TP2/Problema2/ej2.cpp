#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <time.h>

using namespace std;

struct __attribute__((packed)) datos{
   bool tocado;
   int soldados;
   short direccion;
};

struct __attribute__((packed)) nodo_t {
    nodo_t* proximo;
    nodo_t* anterior;
    int vertice;
};

struct __attribute__((packed)) lista_t {
    nodo_t* primero;
    nodo_t* ultimo;
    int cardinal;
};

lista_t* lista_crear();
void lista_borrar(lista_t* lista);
void eliminar_nodo(lista_t* lista, nodo_t* nodo);
void lista_agregar_nodo(lista_t* lista, int n);
void mirar_hijos(vector<datos>* vertices, vector<vector<int> >* LDA, lista_t* vecinos,int vertice, int m, int n, int s, int cont);
int perdidas_necesarias(vector<datos>* vertices, vector<vector<int> >* LDA, int vertice, int m, int s, int dir);
void imprimir_estado(vector<datos>* vertices, lista_t* vecinos, int n, int m);

int main(){
    //Cargar
    int n,m,s; //Calles Horizontales, Verticales y Soldados
    cin >> n >> m >> s;

    int ih,iv,bh,bv; //Ih Iv calle inicial, Bh Bv bunker
    cin >> ih >> iv >> bh >> bv;

    ih--;
    iv--;
    bh--;
    bv--;

    vector<vector<int> > LDA (n*m);
    vector<datos> vertices (n*m);
    lista_t* vecinos = lista_crear();
    int base = bh*m+bv;
    int inicio = ih*m+iv;

    for (int i=0;i<n*m;i++){
            LDA[i].resize(4);
    }
    int buff;
    
    int i = 0;
    int j;

    while(i<n-1){
            for (j=0;j<m-1;j++){
                    cin >> buff;
                    LDA[(i*m)+j][1] = buff;
                    LDA[(i*m)+j+1][3] = buff;
            }
            for (j=0;j<m;j++){
                    cin >> buff;
                    LDA[(i*m)+j][2] = buff;
                    LDA[(i+1)*m+j][0] = buff;
            }
            i++;
    }

    for(j=0;j<m-1;j++){
                    cin >> buff;
                    LDA[(i*m)+j][1] = buff;
                    LDA[(i*m)+j+1][3] = buff;
            }

    clock_t t;
    t = clock();

    for (i=0;i<n;i++){
            for (j=0;j<m;j++){
                    vertices[(i*m)+j].tocado = false;
                    vertices[(i*m)+j].soldados = -1;
                    vertices[(i*m)+j].direccion = 4;
            }
    }

    vertices[inicio].tocado = true;
    vertices[inicio].soldados = 0;

    if((inicio/m)>0){
            vertices[inicio-m].soldados = perdidas_necesarias(&vertices, &LDA, inicio-m, m, s, 2);
            vertices[inicio-m].direccion = 2;
            lista_agregar_nodo(vecinos, inicio-m);
    }
    if((inicio/m)<n-1){
            vertices[inicio+m].soldados = perdidas_necesarias(&vertices, &LDA, inicio+m, m, s, 0);
            vertices[inicio+m].direccion = 0;
            lista_agregar_nodo(vecinos, inicio+m);
    }
    if((inicio%m)!=m-1){
            vertices[inicio+1].soldados = perdidas_necesarias(&vertices, &LDA, inicio+1, m, s, 3);
            vertices[inicio+1].direccion = 3;
            lista_agregar_nodo(vecinos, inicio+1);
    }
    if((inicio%m)!=0){
            vertices[inicio-1].soldados = perdidas_necesarias(&vertices, &LDA, inicio-1, m, s, 1);
            vertices[inicio-1].direccion = 1;
            lista_agregar_nodo(vecinos, inicio-1);
    }

    int cont = 0;
    nodo_t* actual = vecinos->primero;
    nodo_t* eliminar;

    while((cont <= s) and (vecinos->cardinal>0) and (!vertices[base].tocado)){
            while(actual){
                    if(!vertices[actual->vertice].tocado){
                            if(cont==vertices[actual->vertice].soldados){
                                    //cout << 'h';
                                    vertices[actual->vertice].tocado = true;
                                    mirar_hijos(&vertices, &LDA, vecinos, actual->vertice, m, n, s, cont);
                                    eliminar = actual;
                                    actual = actual->proximo;
                                    eliminar_nodo(vecinos, eliminar);
                            }else{
                                    actual = actual->proximo;
                            }
                    }else{
                            eliminar = actual;
                            actual = actual->proximo;
                            eliminar_nodo(vecinos, eliminar);
                    }
            }
            actual = vecinos->primero;
            cont++;
    }

    //imprimir_estado(&vertices, vecinos, n, m);

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo",ios::app);

	//Ojo que si hay que dar vuelta la lista el clock tiene que ir abajo

	if(vertices[base].tocado and vertices[base].soldados <= s){

//		int pasos=0;
//		vector<int> resi(n*m);
//		vector<int> resj(n*m);

        cout << s-vertices[base].soldados << endl;
        cout << base/m+1 << ' ' << base%m+1 << endl;
        while(base != inicio){
            switch (vertices[base].direccion){
                case 0:
                    base -= m;
                break;
                case 1:
                    base += 1;
                break;
                case 2:
                    base += m;
                break;
                case 3:
                    base -= 1;
                break;
            }
            cout << base/m+1 << ' ' << base%m+1 << endl;
//			pasos++;
        }
		tiempo << 1 << ' ' << (long int)t << endl;
    }else{
        cout << 0 << endl;
		tiempo << 0 << ' ' << (long int)t << endl;
    }

    lista_borrar(vecinos);
}

lista_t* lista_crear(){

    lista_t* lista = (lista_t*) malloc(20);
    lista->primero = (nodo_t*)0;
    lista->ultimo = (nodo_t*)0;
    lista->cardinal = 0;

    return lista;
}

void eliminar_nodo(lista_t* lista, nodo_t* nodo){
    
    if (nodo->proximo != (nodo_t*)0){
        nodo->proximo->anterior = nodo->anterior;
    }
    if (nodo->anterior != (nodo_t*)0){
        nodo->anterior->proximo = nodo->proximo;
    }
    if(lista->primero == (nodo_t*)nodo){
        lista->primero = (nodo_t*)nodo->proximo;
    }
    if(lista->ultimo == (nodo_t*)nodo){
        lista->ultimo = (nodo_t*)nodo->anterior;
    }
    free(nodo);

    lista->cardinal--;

    return;
}

//Esta funcion borra una lista y todos los nodos contenidos en ella

void lista_borrar(lista_t* lista){

    nodo_t* nodo = (nodo_t*)lista->primero;
    nodo_t* prox;

    while(nodo!= (nodo_t*) 0){
        prox = nodo->proximo;
        free(nodo);
        nodo = prox;
    }

    free(lista);

    return;
}

//Esta funcion agrega un nodo a la lista con los atributos pasados por parametro

void lista_agregar_nodo(lista_t* lista, int n){

    nodo_t* nodo = (nodo_t*) malloc(20);
    nodo->vertice = n;

    nodo->anterior = (nodo_t*)(lista->ultimo);
    nodo->proximo = (nodo_t*)0;
    
    if(lista->primero == (nodo_t*)0){
        lista->primero = (nodo_t*)nodo;
    }else{
        ((nodo_t*)(lista->ultimo))->proximo = nodo;
    }

    lista->ultimo = (nodo_t*)nodo;

    lista->cardinal++;

    return;
}

void mirar_hijos(vector<datos>* vertices, vector<vector<int> >* LDA, lista_t* vecinos, int vertice, int m, int n, int s, int cont){

    int perdidas_requeridas;
    if((vertice/m)>0){
            if(!vertices[0][vertice-m].tocado){
                    perdidas_requeridas = perdidas_necesarias(vertices, LDA, vertice-m, m, s, 2);
                    if((vertices[0][vertice-m].soldados<0) or (perdidas_requeridas == cont)){
                            //cout << perdidas_requeridas << ' ';
                            lista_agregar_nodo(vecinos, vertice-m);
                            vertices[0][vertice-m].soldados = perdidas_requeridas;
                            vertices[0][vertice-m].direccion = 2;  
                    }else if(vertices[0][vertice-m].soldados>perdidas_requeridas){
                            vertices[0][vertice-m].soldados = perdidas_requeridas;
                            vertices[0][vertice-m].direccion = 2;
                    }
            }
    }
    if((vertice/m)<n-1){
            if(!vertices[0][vertice+m].tocado){
                    perdidas_requeridas = perdidas_necesarias(vertices, LDA, vertice+m, m, s, 0);
                    if((vertices[0][vertice+m].soldados<0) or (perdidas_requeridas == cont)){
                            lista_agregar_nodo(vecinos, vertice+m);
                            //cout << perdidas_requeridas << ' ';
                            vertices[0][vertice+m].soldados = perdidas_requeridas;
                            vertices[0][vertice+m].direccion = 0;   
                    }else if(vertices[0][vertice+m].soldados>perdidas_requeridas){
                            vertices[0][vertice+m].soldados = perdidas_requeridas;
                            vertices[0][vertice+m].direccion = 0;
                    }
            }
    }
    if((vertice%m)!=m-1){
            if(!vertices[0][vertice+1].tocado){
                    perdidas_requeridas = perdidas_necesarias(vertices, LDA, vertice+1, m, s, 3);
                    if((vertices[0][vertice+1].soldados<0) or (perdidas_requeridas == cont)){
                            lista_agregar_nodo(vecinos, vertice+1);
                            //cout << perdidas_requeridas << ' ';
                            vertices[0][vertice+1].soldados = perdidas_requeridas;
                            vertices[0][vertice+1].direccion = 3; 
                    }else if(vertices[0][vertice+1].soldados>perdidas_requeridas){
                            vertices[0][vertice+1].soldados = perdidas_requeridas;
                            vertices[0][vertice+1].direccion = 3;
                    }
            }
    }
    if((vertice%m)!=0){
            if(!vertices[0][vertice-1].tocado){
                    perdidas_requeridas = perdidas_necesarias(vertices, LDA, vertice-1, m, s, 1);
                    if((vertices[0][vertice-1].soldados<0) or (perdidas_requeridas == cont)){
                            lista_agregar_nodo(vecinos, vertice-1);
                            //cout << perdidas_requeridas << ' ';
                            vertices[0][vertice-1].soldados = perdidas_requeridas;
                            vertices[0][vertice-1].direccion = 1;   
                    }else if(vertices[0][vertice-1].soldados>perdidas_requeridas){
                            vertices[0][vertice-1].soldados = perdidas_requeridas;
                            vertices[0][vertice-1].direccion = 1;
                    }
            }
    }
    return;
}

int perdidas_necesarias(vector<datos>* vertices, vector<vector<int> >* LDA, int vertice, int m, int s, int dir){

    int anterior = vertice;
    switch (dir){
        case 0:
            anterior -= m;
        break;
        case 1:
            anterior += 1;
        break;
        case 2:
            anterior += m;
        break;
        case 3:
            anterior -= 1;
        break;
    }

    int cantsoldados = s-vertices[0][anterior].soldados;
    if(cantsoldados>=LDA[0][vertice][dir]){
        return vertices[0][anterior].soldados;
    }else{
        return LDA[0][vertice][dir]-cantsoldados+vertices[0][anterior].soldados;
    }
}

void imprimir_estado(vector<datos>* vertices, lista_t* vecinos, int n, int m){

    for (int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                    cout << "nodo " << (i*m)+j << ':' << ' ';
                    cout << vertices[0][(i*m)+j].tocado << ' ';
                    cout << vertices[0][(i*m)+j].soldados << ' ';
                    cout << vertices[0][(i*m)+j].direccion << endl;
            }
    }
    nodo_t* nodo = vecinos->primero;
    cout << "Lista: ";
    if(!nodo){
        cout << "-vacia-";
    }
    while(nodo){
        cout << nodo->vertice << ' ';
        nodo = nodo->proximo;
    }
    cout << endl;

    return;
}
