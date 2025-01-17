// g++ Promesa.cpp Titulo.cpp DiccT.h DiccOrd2.h Wolfie.cpp main.cpp -o main
//./main

#include <iostream>
#include "Modulos-CPP/aed2/TiposBasicos.h"
#include "Modulos-CPP/aed2/Arreglo.h"
#include "Modulos-CPP/aed2/Vector.h"
#include "Modulos-CPP/aed2/Conj.h"

using namespace std;
using namespace aed2;

template<class S>
struct DiccT {

public:

    struct Elem;
    struct const_Elem;

    class Iterador;
    class const_Iterador;

    DiccT();
    ~DiccT();
    //DiccT(const DiccT<S>& otro);
    //DiccT<S>& operator=(const DiccT<S>& otro);

    void Definir(const string& clave, S& significado);

    bool Definido(const string& clave) const;
    const S& const_Significado(const string& clave) const;
    S& Significado(const string& clave);
    bool operator == (DiccT<S>) const;
    Iterador CrearIt();
    const_Iterador CrearIt() const;



        class Iterador
    {
      public:

        Iterador();

        Iterador(const typename DiccT<S>::Iterador& otro);

        Iterador& operator = (const typename DiccT<S>::Iterador& otro);

        bool operator == (const typename DiccT<S>::Iterador&) const;

        bool HaySiguiente() const;
        const string& SiguienteClave() const;
        S& SiguienteSignificado();
        void Avanzar();

      private:

        ///Al iterar las claves vamos iterando el diccionario
        Conj<string>::Iterador itConj;

        ///Nos llevamos el diccionario por referencia, para hacer SiguienteSignificado
        DiccT<S>* elDicc;

        Iterador(DiccT<S>* d);

        friend typename DiccT<S>::Iterador DiccT<S>::CrearIt();
        friend class DiccT<S>::const_Iterador;
    };

 /*   class const_Iterador
    {
      public:

        const_Iterador();

        const_Iterador(const typename DiccT<S>::Iterador& otro);

        const_Iterador(const typename DiccT<S>::const_Iterador& otro);

        const_Iterador& operator = (const typename DiccT<S>::const_Iterador& otro);

        bool operator==(const typename DiccT<S>::const_Iterador&) const;

        bool HaySiguiente() const;
        const string& SiguienteClave() const;
        const S& SiguienteSignificado() const;
        const_Elem Siguiente() const;
        void Avanzar();

    private:

        ///Al iterar las claves vamos iterando el diccionario
        Conj<string>::Iterador itConj;

        ///Nos llevamos el diccionario por referencia, para hacer SiguienteSignificado
        DiccT<S>* elDicc;

        const_Iterador(const DiccT<S>* d);

        friend typename DiccT<S>::const_Iterador DiccT<S>::CrearIt() const;

     };*/

  private:

   struct Nodo {


       Nodo():Definido(false),significado(NULL){
            arPunteros = Arreglo<Nodo*>(256);
            for(Nat i=0;i<256;i++) {
                arPunteros.Definir(i,NULL);
            }
		};
        //bool SonIguales(const DiccT<S>::Nodo n2);
        Arreglo<Nodo*> arPunteros;
        bool Definido;
        S* significado;

    };

void borrarNodo(Nodo* n);

    Arreglo<Nodo*> _primAr;
    Conj<string> _claves;
};

/*//-----------------------Auxiliares--------------------------

template<class S>
bool DiccT<S>::Nodo::SonIguales(const DiccT<S>::Nodo n2){return true;}*/

//-----------------------FinAux------------------------------

template<class S>
DiccT<S>::DiccT() {
    _claves=Conj<string> ();
    _primAr= Arreglo<Nodo*> (256);
    for(Nat i=0;i<256;i++) {
        _primAr.Definir(i,NULL);
    }
}
///Hay que valgrindear pero parece al menos no rompe nada
template<class S>
void DiccT<S>::borrarNodo(Nodo* n) {
    for(Nat i=0;i<256;i++)    {
        if(n->arPunteros[i] != NULL)    {
            borrarNodo(n->arPunteros[i]);
        }
    } delete n;
}

template<class S>
DiccT<S>::~DiccT()  {
    for(Nat i=0;i<256;i++)    {
        if(_primAr[i] != NULL)    {
            borrarNodo(_primAr[i]);
        }
    }
}

template<class S>
void DiccT<S>::Definir(const string& c, S& s) {
    #ifdef DEBUG
    assert(c.length()>0);
    #endif
    Nat longC = c.length();
    Nodo* nodAux;

    ///inicializo arrAux con el primer arreglo (por referencia, si no se rompe)
    Arreglo<Nodo*>* arrAux = &_primAr;
    for (Nat i = 0; i < longC; i++){
        Nat caracterActual = c[i];
        ///si en la posici�n correspondiente hab�a un NULL, tengo que crear arreglo nuevo
        if ((*arrAux)[caracterActual]==NULL){
            Nodo* nodoNuevo = new Nodo;
            (*arrAux).Definir(caracterActual, nodoNuevo);
        }
        ///reasigno arrAux para seguir iterando
        nodAux = (*arrAux)[caracterActual];
        arrAux = &(nodAux->arPunteros);
    }
    nodAux->Definido = true;
    nodAux->significado = &s;

    //Finalmente agrego la clave en el conjunto de claves
    _claves.Agregar(c);
}

template<class S>
bool DiccT<S>::Definido(const string& c) const {
    Nat longC = c.length();
    Nodo nodAux;

    ///inicializo arrAux con el primer arreglo
    Arreglo<Nodo*> arrAux = _primAr;
    for (Nat i = 0; i < longC; i++){
        Nat caracterActual = c[i];

        ///si en la posici�n correspondiente hab�a un NULL, no estaba definido!
        if (arrAux[caracterActual] == NULL){
            //fuerzo la salida del ciclo
            return false;
        }

        ///reasigno arrAux para seguir iterando
        nodAux = *arrAux[caracterActual];
        arrAux = nodAux.arPunteros;
    }

    return true;
}


template<class S>
S& DiccT<S>::Significado(const string& c) {
    #ifdef DEBUG
    assert(Definido(c));
    #endif
    Nat longC = c.length();
    Nodo nodAux;

    //inicializo arrAux con el primer arreglo
    Arreglo<Nodo*> arrAux = _primAr;

    for (Nat i = 0; i < longC; i++){
        Nat caracterActual = c[i];
        //reasigno arrAux para seguir iterando
        nodAux = *arrAux[caracterActual];
        arrAux = nodAux.arPunteros; ///Es O(256)=O(1)
    }

    return *nodAux.significado;
}

template<class S>
const S& DiccT<S>::const_Significado(const string& c) const {
    #ifdef DEBUG
    assert(Definido(c));
    #endif
    Nat longC = c.length();
    Nodo nodAux;
    Arreglo<Nodo*> arrAux = _primAr;

    for (Nat i = 0; i < longC; i++){
        Nat caracterActual = c[i];
        nodAux = *arrAux[caracterActual];
        arrAux = nodAux.arPunteros; 
    }

    return *nodAux.significado;
}

template<class S>
bool DiccT<S>::operator == (const DiccT<S> d2) const{

	if (_claves != d2._claves) {return false;}
	int i = 0;
	while (i < 256){

		if((_primAr[i]==NULL) != (d2._primAr[i]==NULL)) 			{return false;}

		else{

			if(_primAr[i]!= NULL) {

				if (*(_primAr[i]).SonIguales(*(d2._primAr[i])) == false)  {return false;}

				}

		}

	}
	return true;
}

template<class S>
typename DiccT<S>::Iterador DiccT<S>::CrearIt()
{
  return Iterador(this);
}

template<class S>
DiccT<S>::Iterador::Iterador(DiccT<S>* d){
   itConj = d->_claves.CrearIt();
   elDicc = d;
}

template<class S>
DiccT<S>::Iterador::Iterador(const typename DiccT<S>::Iterador& otro){
    itConj = otro.itConj;
    elDicc = otro.elDicc;
}


template<class S>
bool DiccT<S>::Iterador::HaySiguiente() const{
    return itConj.HaySiguiente();
}

template<class S>
const string& DiccT<S>::Iterador::SiguienteClave() const{
    return itConj.Siguiente();
}

template<class S>
S& DiccT<S>::Iterador::SiguienteSignificado(){
    return elDicc.Significado(itConj.Siguiente());
}

template<class S>
void DiccT<S>::Iterador::Avanzar(){
    itConj.Avanzar();
}
