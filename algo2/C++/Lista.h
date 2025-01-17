/**
 * Modulo Lista
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef AED2_LISTA_H_INCLUDED
#define AED2_LISTA_H_INCLUDED

#include "TiposBasicos.h"

#include <ostream>

/* Descomentar este flag para habilitar los chequeos internos de PRE
 * OJO que invalida las complejidades exportadas de algunas funciones
 */
//#define DEBUG 1

namespace aed2
{

/**
 * Implementación del módulo Lista Enlazada(alpha) con su const_Iterador correspondiente.
 * Como estamos en C++, en lugar de alpha vamos a usar T.
 * Del parámetro formal T, sólo se supone la existencia de su constructor por copia.
 */
template <typename T>
class Lista
{
	private:

		struct Nodo;

	public:

		//forward declarations
		class Iterador;
		class const_Iterador;

		/// Crea una lista enlazada vacía. (Operación Vacia())
		Lista();
		/// Crea por copia una lista enlazada (operación Copiar())
		Lista(const Lista& otra);
		/// Destruye la lista, incluyendo los T alojados
		~Lista();
		/// Operacion de asignacion
		Lista<T>& operator=(const Lista<T>& otra);

		/// Opreaciones básicas
		bool EsVacia() const;
		Nat Longitud() const;

		/// Acceso al primero y último elemento (en O(1) )
		/// Versiones modificables y no modificables
		T& Primero();
		const T& Primero() const;
		T& Ultimo();
		const T& Ultimo() const;
		/// Operador "iésimo"
		T& operator[](Nat i);
		const T& operator[](Nat i) const;

		/// Elimina el primer elemento
		void Fin();
		/// Elimina el último elemento
		void Comienzo();

		/// Inserción de elementos
		Iterador AgregarAdelante(const T& elem);
		Iterador AgregarAtras(const T& elem);

		/// Creación del Iterador
		Iterador CrearIt();
		Iterador CrearItUlt();

		/// Creación del const_Iterador
		const_Iterador CrearIt() const;
		const_Iterador CrearItUlt() const;

		/**********************************
		 * Iterador de Lista, modificable *
		 **********************************/
		class Iterador
		{
			public:

				Iterador();

				Iterador(const typename Lista<T>::Iterador& otro);

				Iterador& operator = (const typename Lista<T>::Iterador& otro);

				bool HayAnterior() const;
				bool HaySiguiente() const;

				T& Anterior() const;
				T& Siguiente() const;

				void Avanzar();
				void Retroceder();

				void EliminarAnterior();
				void EliminarSiguiente();

				void AgregarComoAnterior(const T& elem);
				void AgregarComoSiguiente(const T& elem);

				bool operator==(const typename Lista<T>::Iterador& otro) const;

			private:

				/// El constructor es privado, necesitamos el friend.
				Iterador(Lista<T>* _lista, typename Lista<T>::Nodo* _proximo)
				: lista(_lista), nodo_siguiente(_proximo) {};
				friend typename Lista<T>::Iterador Lista<T>::CrearIt();
				friend typename Lista<T>::Iterador Lista<T>::CrearItUlt();
				friend class Lista<T>::const_Iterador;

				Lista<T>* lista;
				typename Lista<T>::Nodo* nodo_siguiente;

				//devuelve el nodo siguiente en la lista circular
				typename Lista<T>::Nodo* SiguienteReal() const;

		}; // class Iterador

		/*************************************
		 * const_Iterador de Lista, no modificable *
		 *************************************/
		class const_Iterador
		{
			public:

				const_Iterador();

				const_Iterador(const typename Lista<T>::const_Iterador& otro);

				const_Iterador(const typename Lista<T>::Iterador& otro);

				const_Iterador& operator=(const typename Lista<T>::const_Iterador& otro);

				bool HayAnterior() const;
				bool HaySiguiente() const;

				const T& Anterior() const;
				const T& Siguiente() const;

				void Avanzar();
				void Retroceder();

				bool operator == (const typename Lista<T>::const_Iterador& otro) const;

			private:

				/// El constructor es privado, necesitamos el friend.
				const_Iterador(const Lista<T>* _lista, const typename Lista<T>::Nodo* _proximo)
				: lista(_lista), nodo_siguiente(_proximo) {};
				friend typename Lista<T>::const_Iterador Lista<T>::CrearIt() const;
				friend typename Lista<T>::const_Iterador Lista<T>::CrearItUlt() const;

				const Lista<T>* lista;
				const typename Lista<T>::Nodo* nodo_siguiente;

				//devuelve el nodo siguiente en la lista circular
				const typename Lista<T>::Nodo* SiguienteReal() const;
		}; // class const_iterador

    private:

        struct Nodo
        {
            Nodo(const T& d) : dato(d), anterior(NULL), siguiente(NULL) {};

            T dato;
            Nodo* anterior;
            Nodo* siguiente;
        };

        Nodo* primero;
        Nat longitud;
};

template<class T>
std::ostream& operator << (std::ostream& os, const Lista<T>& l);

template<class T>
bool operator == (const Lista<T>&, const Lista<T>&);

	// ---------------------------------------------------------
	//  class Lista
	// ---------------------------------------------------------

template <typename T>
Lista<T>::Lista() : primero(NULL), longitud(0)
{}

template <typename T>
Lista<T>::Lista(const Lista<T>& otra) : primero(NULL), longitud(0)
{
    *this = otra;
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
    if(this != &otra) {
        while(!EsVacia()) Fin();
        for(const_Iterador it = otra.CrearIt(); it.HaySiguiente(); it.Avanzar())
            this->AgregarAtras(it.Siguiente());
    }
    return *this;
}

template <typename T>
Lista<T>::~Lista()
{
    while(!EsVacia()) Fin();
}

template <typename T>
bool Lista<T>::EsVacia() const
{
    return primero == NULL;
}

template <typename T>
Nat Lista<T>::Longitud() const
{
    return longitud;
}

template <typename T>
T& Lista<T>::Primero()
{
    assert(not EsVacia());
    return CrearIt().Siguiente();
}

template <typename T>
const T& Lista<T>::Primero() const
{
    assert(not EsVacia());
    return CrearIt().Siguiente();
}

template <typename T>
T& Lista<T>::Ultimo()
{
    assert(not EsVacia());
    return CrearItUlt().Anterior();
}

template <typename T>
const T& Lista<T>::Ultimo() const
{
    assert(not EsVacia());
    return CrearItUlt().Anterior();
}

template <typename T>
const T& Lista<T>::operator[](Nat i) const
{
    assert(i < longitud);
    const_Iterador it = CrearIt();
    while(i > 0) {
        it.Avanzar();
        --i;
    }

    return it.Siguiente();
}

template <typename T>
T& Lista<T>::operator[](Nat i)
{
    assert(i < longitud);
    Iterador it = CrearIt();
    while(i > 0)
    {
        it.Avanzar();
        --i;
    }

    return it.Siguiente();
}

template <typename T>
void Lista<T>::Fin()
{
    assert(not EsVacia());
    CrearIt().EliminarSiguiente();
}

template <typename T>
void Lista<T>::Comienzo()
{
    assert(not EsVacia());
    CrearItUlt().EliminarAnterior();
}

template <typename T>
typename Lista<T>::const_Iterador Lista<T>::CrearIt() const
{
	return const_Iterador(this, primero);
}

template <typename T>
typename Lista<T>::const_Iterador Lista<T>::CrearItUlt() const
{
	return const_Iterador(this, NULL);
}

template <typename T>
typename Lista<T>::Nodo* Lista<T>::Iterador::SiguienteReal() const
{
	return nodo_siguiente == NULL ? lista->primero : nodo_siguiente;
}

	// ---------------------------------------------------------
	//  class Iterador
	// ---------------------------------------------------------

template <typename T>
Lista<T>::Iterador::Iterador()
	: lista(NULL), nodo_siguiente(NULL)
{}

template <typename T>
Lista<T>::Iterador::Iterador(const typename Lista<T>::Iterador& otro)
	: lista(otro.lista), nodo_siguiente(otro.nodo_siguiente)
{}

template <typename T>
typename Lista<T>::Iterador& Lista<T>::Iterador::operator = (const typename Lista<T>::Iterador& otro)
{
	lista = otro.lista;
	nodo_siguiente = otro.nodo_siguiente;
	
	return *this;
}

template <typename T>
bool Lista<T>::Iterador::HayAnterior() const
{
	return nodo_siguiente != lista->primero;
}

template <typename T>
bool Lista<T>::Iterador::HaySiguiente() const
{
	return nodo_siguiente != NULL;
}

template <typename T>
T& Lista<T>::Iterador::Anterior() const
{
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return SiguienteReal()->anterior->dato;
}

template <typename T>
T& Lista<T>::Iterador::Siguiente() const
{
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return nodo_siguiente->dato;
}

template <typename T>
void Lista<T>::Iterador::Avanzar()
{
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	nodo_siguiente = nodo_siguiente->siguiente;
	if(nodo_siguiente == lista->primero)
		nodo_siguiente = NULL;
}

template <typename T>
void Lista<T>::Iterador::Retroceder()
{
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	nodo_siguiente = SiguienteReal()->anterior;
}

template <typename T>
void Lista<T>::Iterador::AgregarComoAnterior(const T& dato)
{
	Nodo* sig = SiguienteReal();
	Nodo* nuevo = new Nodo(dato);

	//asignamos anterior y siguiente de acuerdo a si el nodo es el primero
	//o no de la lista circular
	nuevo->anterior = sig == NULL ? nuevo : sig->anterior;
	nuevo->siguiente = sig == NULL ? nuevo : sig;

	//reencadenamos los otros nodos (notar que no hay problema cuando nuevo
	//es el primer nodo creado de la lista)
	nuevo->anterior->siguiente = nuevo;
	nuevo->siguiente->anterior = nuevo;

	//cambiamos el primero en el caso que nodo_siguiente == primero
	if(nodo_siguiente == lista->primero)
		lista->primero = nuevo;

	lista->longitud++;
}

template <typename T>
void Lista<T>::Iterador::AgregarComoSiguiente(const T& dato)
{
	AgregarComoAnterior(dato);
	Retroceder();
}

template <typename T>
void Lista<T>::Iterador::EliminarAnterior()
{
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	Retroceder();
	EliminarSiguiente();
}

template <typename T>
void Lista<T>::Iterador::EliminarSiguiente()
{
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	Nodo* tmp = nodo_siguiente;

	//reencadenamos los nodos
	tmp->siguiente->anterior = tmp->anterior;
	tmp->anterior->siguiente = tmp->siguiente;

	//borramos el unico nodo que habia?
	nodo_siguiente = tmp->siguiente == tmp ? NULL : tmp->siguiente;
	//borramos el último?
	nodo_siguiente = tmp->siguiente == lista->primero ? NULL : tmp->siguiente;

	if(tmp == lista->primero)    //borramos el primero?
			lista->primero = nodo_siguiente;

	delete tmp;
	lista->longitud--;
}

template<class T>
bool Lista<T>::Iterador::operator == (const typename Lista<T>::Iterador& otro) const
{
  return lista == otro.lista && nodo_siguiente == otro.nodo_siguiente;
}

template <typename T>
typename Lista<T>::Iterador Lista<T>::AgregarAdelante(const T& dato)
{
	typename Lista<T>::Iterador res = CrearIt();
	res.AgregarComoSiguiente(dato);

	return res;
}

template <typename T>
typename Lista<T>::Iterador Lista<T>::AgregarAtras(const T& dato)
{
	typename Lista<T>::Iterador res = CrearItUlt();
	res.AgregarComoSiguiente(dato);

	return res;
}

	// ---------------------------------------------------------
	//  class const_Iterador
	// ---------------------------------------------------------

template <typename T>
Lista<T>::const_Iterador::const_Iterador()
	: lista(NULL), nodo_siguiente(NULL)
{}

template <typename T>
Lista<T>::const_Iterador::const_Iterador(const typename Lista<T>::const_Iterador& otro)
	: lista(otro.lista), nodo_siguiente(otro.nodo_siguiente)
{}

template <typename T>
Lista<T>::const_Iterador::const_Iterador(const typename Lista<T>::Iterador& otro)
	: lista(otro.lista), nodo_siguiente(otro.nodo_siguiente)
{}

template <typename T>
typename Lista<T>::const_Iterador& Lista<T>::const_Iterador::operator = (const typename Lista<T>::const_Iterador& otro)
{
	lista = otro.lista;
	nodo_siguiente = otro.nodo_siguiente;

	return *this;
}

template <typename T>
bool Lista<T>::const_Iterador::HaySiguiente() const
{
	return nodo_siguiente != NULL;
}

template <typename T>
bool Lista<T>::const_Iterador::HayAnterior() const
{
	return nodo_siguiente != lista->primero;
}

template <typename T>
const T& Lista<T>::const_Iterador::Siguiente() const
{
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	return nodo_siguiente->dato;
}

template <typename T>
const T& Lista<T>::const_Iterador::Anterior() const
{
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	return SiguienteReal()->anterior->dato;
}

template <typename T>
void Lista<T>::const_Iterador::Avanzar()
{
	#ifdef DEBUG
	assert(HaySiguiente());
	#endif

	nodo_siguiente = nodo_siguiente->siguiente;
	if(nodo_siguiente == lista->primero) nodo_siguiente = NULL;
}

template <typename T>
void Lista<T>::const_Iterador::Retroceder()
{
	#ifdef DEBUG
	assert(HayAnterior());
	#endif

	nodo_siguiente = SiguienteReal()->anterior;
}

template <typename T>
const typename Lista<T>::Nodo* Lista<T>::const_Iterador::SiguienteReal() const
{
	return nodo_siguiente == NULL ? lista->primero : nodo_siguiente;
}

template <typename T>
typename Lista<T>::Iterador Lista<T>::CrearIt()
{
	return Iterador(this, primero);
}

template <typename T>
typename Lista<T>::Iterador Lista<T>::CrearItUlt()
{
	return Iterador(this, NULL);
}

template<class T>
bool Lista<T>::const_Iterador::operator == (const typename Lista<T>::const_Iterador& otro) const
{
  return lista == otro.lista && nodo_siguiente == otro.nodo_siguiente;
}

	// ---------------------------------------------------------
	//  Funciones auxiliares
	// ---------------------------------------------------------

template <typename T>
std::ostream& operator << (std::ostream& os, const Lista<T>& lista)
{
	return Mostrar(os, lista, '<', '>');
}

template <typename T>
bool operator == (const Lista<T>& l1, const Lista<T>& l2)
{
	typename Lista<T>::const_Iterador it1 = l1.CrearIt();
	typename Lista<T>::const_Iterador it2 = l2.CrearIt();

	while(it1.HaySiguiente() and it2.HaySiguiente() and it1.Siguiente() == it2.Siguiente())
	{
		it1.Avanzar(); it2.Avanzar();
	}
	return not it1.HaySiguiente() and not it2.HaySiguiente();
}

}

#endif // AED2_LISTA_H_INCLUDED
