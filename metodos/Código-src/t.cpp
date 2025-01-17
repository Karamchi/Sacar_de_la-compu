//g++ main.cpp -o main
#include <iostream>
#include <fstream>
#include "aux/matriz.h"
#include "aux/Parabrisas.h"
#include <time.h>
#include <math.h>
#include <cmath>
using namespace std;

float tol=pow(10,-10);

bool enSanguijuela (vector <long double> vx, vector <long double> vy, double x, double y, int r) {
	for(unsigned int i=0;i<vx.size();i++) {
		if (sqrt((vx[i]-x)*(vx[i]-x)+(vy[i]-y)*(vy[i]-y)) <= r+tol) { ///La distancia debe ser menor al radio
			return true;
		}
	} return false;
}

bool esBorde (int l, int a, int x, int y) {
	if (x==a || y==l || x==1 || y==1) {
		return true;
	} return false;
}

Parabrisas cargar(char* in) {
	ifstream archivo;
	archivo.open(in);
	int anchoParab;
	int largoParab;
	double h;
	double radio;
	int cant;
	double Temp;
    	archivo >> anchoParab;
	archivo >> largoParab;
	archivo >> h;
	archivo >> radio;
	archivo >> Temp;
	archivo >> cant;
	Parabrisas p=Parabrisas(largoParab, anchoParab,h,radio,Temp,cant);
	long double xs;long double ys;
	for (int i=0;i<cant;i++) {
		archivo >> xs; 			//X de las sanguijuelas
		archivo >> ys;			//Y de las sanguijuelas
		p.agSanguijuela(xs,ys,i);
	} return p;
		// fin carga de argumentos
}

Matriz gMatriz(Parabrisas &p) {
	double h=p.h();
	int ancho=(p.ancho()/h)+1;
	int largo=(p.largo()/h)+1;
	Matriz m=Matriz(ancho*largo,ancho*largo);
	for (int i=1;i<=ancho*largo;i++) {
		int y=(i-1)/ancho+1; 	// x e y son el lugar del vector incógnita al que corresponde la fila i
		int x;
		if (i%ancho==0) {x = ancho;} else {x=i%ancho;}
		if (enSanguijuela(p.SangX(),p.SangY(),(x-1)*h,(y-1)*h,p.radio()) || esBorde (largo,ancho,x,y)) {
			for (int j=1;j<=ancho*largo;j++) { ///Defino la fila con un 1 en la diagonal
				if (i==j) {	
					m.Definir(1,i,j);
				} else {
					m.Definir(0,i,j);
				} if (esBorde(largo,ancho,x,y)) {
					m.DefinirB(-100,i);
				} else {
					m.DefinirB(p.temp(),i);
				}
			}
		} else {
			for (int j=1;j<=ancho*largo;j++) { 
				if (i==j) {
					m.Definir(-1,i,j); ///Defino la fila con un -1 en la diagonal...
				} else if (i==j-1 || i==j+1 || i-j==ancho || j-i==ancho) {
					m.Definir(0.25,i,j); /// ...y 1/4 en las columnas de las celdas adyacentes del parabrisas.
				} else { 
					m.Definir(0,i,j);
				} m.DefinirB(0,i); ///Agrega un 0 en los términos independientes
			} 
		}
	} return m;
}

Matriz gMatrizB(Parabrisas &p) {
	double h=p.h();
	int ancho=(p.ancho()/h)+1;
	int largo=(p.largo()/h)+1;
	
	Matriz m=Matriz(ancho*largo,ancho*largo,2*ancho+1);

	for (int i=1;i<=ancho*largo;i++) {
		int y=(i-1)/ancho+1; 	// x e y son el lugar del vector incógnita al que corresponde la fila i
		int x;
		if (i%ancho==0) {x = ancho;} else {x=i%ancho;}
		if (enSanguijuela(p.SangX(),p.SangY(),(x-1)*h,(y-1)*h,p.radio()) || esBorde (largo,ancho,x,y)) {
			for (int j=i-ancho;(j<=ancho*largo && j<=i+ancho);j++) { ///Defino la fila con un 1 en la diagonal
				if (j<1) {j=1;}
				if (i==j) {
					m.Definir(1,i,j);
				} else {
					m.Definir(0,i,j);
				} if (esBorde(largo,ancho,x,y)) {
					m.DefinirB(-100,i);
				} else {
					m.DefinirB(p.temp(),i);
				} 
			}
		} else {
			for (int j=i-ancho;(j<=ancho*largo && j<=i+ancho);j++) {
				if (j<1) {j=1;}
				if (i==j) {
					m.Definir(-1,i,j); ///Defino la fila con un -1 en la diagonal...
				} else if (i==j-1 || i==j+1 || i-j==ancho || j-i==ancho) {
					m.Definir(0.25,i,j); /// ...y 1/4 en las columnas de las celdas adyacentes del parabrisas.
				} else { 
					m.Definir(0,i,j);
				} m.DefinirB(0,i); ///Agrega un 0 en los términos independientes
			} 
		}
	}
	return m;
}

void EliminacionGaussiana (Matriz &mat){
	int filas = mat.Cfilas();

	for(int i=1; i<=filas; i++){
		
		for(int j=i+1; j<=filas; j++){

			if(abs(mat.Posicion(i,i))>=tol && abs(mat.Posicion(j,i))>=tol){ 
				long double mult = mat.Posicion(j,i) / (mat.Posicion(i,i));
				mat.restarFilas(j, i, mult);
			} /* else {
				mat.Definir(0,j,i)
			} */
		}
	}
}

void EliminacionGaussianaB (Matriz &mat){
	int filas = mat.Cfilas();

	for(int i=1; i<=filas; i++){
		
		for(int j=i+1; j<=filas && j<i+mat.anchoBanda(); j++){
			if(abs(mat.Posicion(i,i))>=tol && abs(mat.Posicion(j,i))>=tol){
				long double mult = mat.Posicion(j,i) / (mat.Posicion(i,i));
				mat.restarFilas(j, i, mult);
			} /* else {
				mat.Definir(0,j,i)
			} */
		}
	}
}


vector<long double> ResolucionFosquiMan (Matriz &mat){
	int n = mat.Cfilas();
	vector<long double> x(n);
	for (int i=0; i < n; i++ ){
		long double acum=mat.PosIndep(n-i);
		for(int j=n-i+1; j <=n; j++) {
			acum=acum-mat.Posicion(n-i, j)*x[j-1];
		}
		x[n-i-1] = acum/mat.Posicion(n-i,n-i);
	} return x;
}

void devolver (Parabrisas p, Matriz &matr, vector<long double> x, char* out) {
	double h=p.h();
	int divis = p.ancho()/h+1;
	ofstream f2;
    	f2.open(out);
	f2.setf(ios::fixed,ios::floatfield);
	f2.precision(5);
	for (int i=1;i<=matr.Cfilas();i++) {
		int ry=((i-1)/(divis)); 
		int rx=((i-1)%(divis));
		f2<< ry << "\t" << rx << "\t" << x[i-1] << endl;
	} 
}

int main(int argc, char *argv[])
{
	clock_t t;
	t = clock();

	Parabrisas p= cargar(argv[1]);
	Matriz matr;
	if (*argv[3]=='1') {
		matr=gMatrizB(p);
		EliminacionGaussianaB(matr);
	} else {
		matr=gMatriz(p);
		EliminacionGaussiana(matr);
	} 
	vector<long double> x=ResolucionFosquiMan(matr);
	devolver(p,matr,x,argv[2]);

	ofstream tiempo;
	t = clock() - t;
	tiempo.open("Tiempo");
	tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;

	if (argc>4) {
		int centro=x.size()/2;		
		ofstream f3;
	    	f3.open(argv[4]);
		int sx; int sy;
		while (x[centro]>235.0) {
			p.elimSanguijuelaMasCercana(sx, sy);
			matr=gMatrizB(p);
			EliminacionGaussianaB(matr);
			x=ResolucionFosquiMan(matr);
			f3 << sx << " " << sy << " " << x[centro] << endl;
		} t = clock() - t;
		tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;
	} return 0;
}
