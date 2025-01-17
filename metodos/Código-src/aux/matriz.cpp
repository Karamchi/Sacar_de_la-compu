#include <vector>
#include "matriz.h"
#include <cmath>
#include <iostream>

using namespace std;

typedef vector<long double> fila;

float tolerancia=pow(10,10);

Matriz::Matriz(){}

Matriz::Matriz( int cantfilas, int cantcolumnas){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){

		_array[i].resize(cantcolumnas);
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps.resize(cantfilas);
	_banda=false;
}

Matriz::Matriz( int cantfilas, int cantcolumnas, int semiancho){
	_array.resize(cantfilas); 
	for (int i = 0; i < cantfilas; i++){

		_array[i].resize(semiancho);
	}
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_anchoBanda=semiancho;
	_indeps.resize(cantfilas);
	_banda=true;
}

Matriz::Matriz(vector< vector<long double> > filas, int cantfilas, int cantcolumnas, vector<long double> indeps){

	_array = filas;
	_Cfilas = cantfilas;
	_Ccolumnas = cantcolumnas;
	_indeps = indeps;
	_banda=false;
	

}

void Matriz::Definir(long double def,int fila, int columna) {
	if (_banda) {
		_array[fila-1][columna-fila+_anchoBanda/2]=def;
	} else {
		_array[fila - 1][columna - 1] = def; 
	}

}

void Matriz::DefinirB(long double def,int fila) {

	_indeps[fila - 1] = def; 

}

void Matriz::restarFilas(int filaRestada, int filaQueResta, long double multFilaARestar){
	if (_banda) {
		for (int i=filaRestada-_anchoBanda/2; i<=filaRestada+_anchoBanda/2 && i<=_Ccolumnas; i++){
			if (i<1) {i=1;}
			double adefinir=Posicion(filaRestada,i)-Posicion(filaQueResta,i)* multFilaARestar;
			//if (abs(adefinir)>=tolerancia) {
				Definir(adefinir,filaRestada,i);
			//} else {
			//	Definir(0,filaRestada,i);
			//}
		}
	} else {
		for (int i=1; i<=_Ccolumnas; i++){
			double adefinir=Posicion(filaRestada,i)-Posicion(filaQueResta,i)* multFilaARestar;
			//if (abs(adefinir)>=tolerancia) {
				Definir(adefinir,filaRestada,i);
			//} else {
			//	Definir(0,filaRestada,i);
			//}
		}
	}
	_indeps[filaRestada-1] = _indeps[filaRestada-1] - (_indeps[filaQueResta-1]* multFilaARestar);

}

long double Matriz::Posicion(int fila, int columna){
	if (_banda) {
		if (columna-fila+_anchoBanda/2>=0 && columna-fila+_anchoBanda/2<_anchoBanda) {
			return _array[fila-1][columna-fila+_anchoBanda/2];
		} else {
			return 0;
		}
	} else {
		return _array[fila - 1][columna - 1];
	}

}

long double Matriz::PosIndep(int fila){

	return _indeps[fila - 1];

}

int Matriz::Cfilas(){

	return _Cfilas;

}

int Matriz::Ccolumnas(){

	return _Ccolumnas;

}

int Matriz::TamTotal(){

	return (_Cfilas * _Ccolumnas);

}

int Matriz::anchoBanda(){

	return _anchoBanda;

}

void Matriz::mostrar() {
    for (int i=1;i<=_Cfilas;i++) {
	    for (int j=1;j<=_Ccolumnas;j++){
           cout << Posicion(i,j) << "\t";
	    }  cout << "|" << _indeps[i-1] <<endl;
    }
}

