/**
 * Modulo Diccionario
 * Algoritmos y Estructuras de Datos 2
 */

#ifndef AED2_DICC_H_INCLUDED
#define	AED2_DICC_H_INCLUDED

#include "Lista.h"

#include <ostream>

/* Descomentar este flag para habilitar los chequeos internos de PRE
 * OJO que invalida las complejidades exportadas de algunas funciones
 */
#define DEBUG 1

namespace aed2
{

template<class K,class S>
class Dicc
{
	public:

		// Forward declarations. Las definiciones estan mas abajo.
		class Iterador;
		class const_Iterador;

		Dicc();

		Dicc(const Dicc<K,S>& otro);

		Dicc<K,S>& operator = (const Dicc<K,S>& otro);

		Iterador Definir(const K& clave, const S& significado);
		Iterador DefinirRapido(const K& clave, const S& significado);

		bool Definido(const K& clave) const;

		const S& Significado(const K& clave) const;
		S& Significado(const K& clave);

		void Borrar(const K& clave);

		Nat CantClaves() const;

		Iterador CrearIt();
		const_Iterador CrearIt() const;

		/**
		 * Estas funciones son utiles para saber si algo esta definido
		 * y ver cual es su signficado, sin recorrer dos veces.
		 * Si la clave no esta definida, Iterador.HaySiguiente()
		 * retorna falso. Si la clave esta definida, Iterador.Siguiente()
		 * retorna el elemento buscado.
		 */
		Iterador Buscar(const K&);
		const_Iterador Buscar(const K&) const;

        class const_Iterador
		{
			public:

				const_Iterador();

				const_Iterador(const typename Dicc<K,S>::const_Iterador& otro);

				const_Iterador(const typename Dicc<K,S>::Iterador& otro);

				const_Iterador& operator=(const typename Dicc<K,S>::const_Iterador& otro);

				bool HayAnterior() const;
				bool HaySiguiente() const;

				const T& Anterior() const;
				const T& Siguiente() const;

				void Avanzar();
				void Retroceder();

				bool operator == (const typename Lista<T>::const_Iterador& otro) const;

			private:

				// El constructor es privado, necesitamos el friend.
				const_Iterador(const Dicc<K,S>* _dicc, const typename Lista<K>::Nodo* _proximosig, const typename Lista<S>::Nodo* _proximaclave)
				: lista(_lista), nodo_siguiente(struct{_proximaclave,_proximosig}) {};
				friend typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearIt() const;
				friend typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearItUlt() const;

				const Dicc<K,S>* dicc;
				const typename Lista<T>::Nodo* nodo_siguiente;

				//devuelve el nodo siguiente en la lista circular
				const typename Lista<T>::Nodo* SiguienteReal() const;
		};// COMPLETAR ...

	private:

		Lista<K> claves_;

		Lista<S> significados_;

}; // class Dicc

/**
 * Operador ostream de Dicc
 */
template<class K, class S>
std::ostream& operator << (std::ostream& os, const Dicc<K,S>& d);

/**
 * Operador comparacion
 */
template<class K, class S>
bool operator == (const Dicc<K,S>& d1, const Dicc<K,S>& d2);

	// ---------------------------------------------------------
	//  class Dicc
	// ---------------------------------------------------------

template<class K, class S>
Dicc<K,S>::Dicc()
{}

template<class K, class S>
Dicc<K,S>::Dicc(const Dicc<K,S>& otro)
	: claves_(otro.claves_), significados_(otro.significados_)
{}

template<class K, class S>
Dicc<K,S>& Dicc<K,S>::operator=(const Dicc<K,S>& otro)
{
	claves_ = otro.claves_;
	significados_ = otro.significados_;

	return *this;
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::Definir(const K& clave, const S& significado)
{
	Iterador it = Buscar(clave);

	// Si la clave existe, cambio el significado
	if(it.HaySiguiente()) {
		it.Siguiente().significado = significado;
	// Si la clave no existe, agrego la definicion
	} else {
		it = DefinirRapido(clave, significado);
	}

	return it;
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::DefinirRapido(const K& clave, const S& significado)
{
	// Me aseguro que se cumpla la precondicion
	// OJO que esto invalida la complejidad
	#ifdef DEBUG
	assert( !Definido(clave) );
	#endif

	claves_.AgregarAdelante(clave);
	significados_.AgregarAdelante(significado);

	return CrearIt();
}

template<class K, class S>
bool Dicc<K,S>::Definido(const K& clave) const
{
	return Buscar(clave).HaySiguiente();
}

template<class K, class S>
const S& Dicc<K,S>::Significado(const K& clave)const
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	return Buscar(clave).Siguiente().significado;
}

template<class K, class S>
S& Dicc<K,S>::Significado(const K& clave)
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	return Buscar(clave).Siguiente().significado;
}

template<class K, class S>
void Dicc<K,S>::Borrar(const K& clave)
{
	// Me aseguro que se cumpla la precondicion
	#ifdef DEBUG
	assert( Definido(clave) );
	#endif

	Buscar(clave).EliminarSiguiente();
}

template<class K, class S>
Nat Dicc<K,S>::CantClaves() const
{
	return claves_.Longitud();
}

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::CrearIt()
{
	return Iterador(this);
}

template<class K, class S>
typename Dicc<K,S>::const_Iterador Dicc<K,S>::CrearIt() const
{
	return const_Iterador(this);
}

	// ---------------------------------------------------------
	//  class Dicc::Iterador
	// ---------------------------------------------------------

	// COMPLETAR ...

	// ---------------------------------------------------------
	//  class Dicc::const_Iterador
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
	//  funciones auxiliares
	// ---------------------------------------------------------

template<class K, class S>
typename Dicc<K,S>::Iterador Dicc<K,S>::Buscar(const K& clave)
{
	typename Dicc<K,S>::Iterador it = CrearIt();

	while(it.HaySiguiente() && it.Siguiente().clave != clave)
	{
		it.Avanzar();
	}

	return it;
}

template<class K, class S>
typename Dicc<K,S>::const_Iterador Dicc<K,S>::Buscar(const K& clave) const
{
	typename Dicc<K,S>::const_Iterador it = CrearIt();

	while(it.HaySiguiente() && it.Siguiente().clave != clave)
	{
		it.Avanzar();
	}

	return it;
}

template<class K, class S>
std::ostream& operator<<(std::ostream& os, const Dicc<K,S>& d)
{
	return Mostrar(os, d, '{', '}');
}

template<class K, class S>
bool operator == (const Dicc<K,S>& d1, const Dicc<K,S>& d2)
{
	bool retval = d1.CantClaves() == d2.CantClaves();

	typename Dicc<K,S>::const_Iterador it1 = d1.CrearIt();

	while(retval and it1.HaySiguiente())
	{
		typename Dicc<K,S>::const_Iterador it2 = d2.Buscar(it1.Siguiente().clave);

		retval = it2.HaySiguiente() and it1.Siguiente().significado == it2.Siguiente().significado;

		it1.Avanzar();
	}

	return retval;
}

} // namespace aed2


#endif	//AED2_DICC_H_INCLUDED
