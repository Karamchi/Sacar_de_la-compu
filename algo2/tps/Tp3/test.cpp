//g++ Promesa.cpp Titulo.cpp DiccT.h DiccOrd2.h Wolfie.cpp Driver.cpp Dcheck.cpp -o Dcheck

#include "Driver.h"
#include "Modulos-CPP/mini_test.h"
#include "Modulos-CPP/aed2/Lista.h"
#include "Modulos-CPP/aed2/Conj.h"

#include <string>
#include <iostream>

using namespace aed2;

/**
 * Imprime un elemento a un string, en vez de a una pantalla,
 * a través del operador <<
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename S::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
	it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

	while( it1.HaySiguiente() )
	{
		bool esta = false;
		it2 = s.CrearIt();

		while( it2.HaySiguiente() ) {
		  if ( it1.Siguiente() == it2.Siguiente() ) {
			esta = true;
			break;
		  }
		  it2.Avanzar();
		}

		if ( !esta ) {
			return false;
		}

		it1.Avanzar();
	}

  return true;
}


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de Dcheck, con llamadas a las rutinas de aserción
 * definidas en mini_TEST.h
 */
void test_wolfie_simple()
{
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

    Driver wolfie(clientes);
	int a = clientes.Cardinal();
	ASSERT_EQ(wolfie.CantidadDeClientes(), a);
	//por esas cosas de la vida, esto no anda:
	//ASSERT_EQ(wolfie.CantidadDeClientes(), clientes.Cardinal());

	for(Nat i=0; i<wolfie.CantidadDeClientes(); i++) {
		ASSERT( clientes.Pertenece( wolfie.IesimoCliente(i) ) );
	}

	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);
}

const Nat compraVenta(Nat d,const Conj<Promesa> ps);
const Conj<Promesa> promesasSobreTitulo(Nombre n, TipoPromesa t, Conj<Promesa> ps);

void cambiarCotTs(Nombre nt, Dinero c, Conj<Titulo> &ts);
Nat limTen(Nombre nt, Conj<Titulo> ts);
bool titEnAlza(Nombre nt, Conj<Titulo> ts);
Nat cotActual(Nombre nt, Conj<Titulo> ts);

//--------------------Promesa.cpp---------------------
void Pcheck_Crear(){
	Promesa pr;
	pr.crearPromesa("prom", comprar, 10, 11);
}

void Pcheck_Observadores(){
	Promesa pr;
	pr.crearPromesa("prom", comprar, 10, 11);
	ASSERT_EQ(pr.titulo(), "prom");
	ASSERT_EQ(pr.tipo(), comprar);
	ASSERT_EQ(pr.limite(), 10);
	ASSERT_EQ(pr.cantidad(), 11);
}

void Pcheck_PromNoEjecVENTA(){
	Promesa pr;
	pr.crearPromesa("prom", vender, 5, 10);
	ASSERT(not(pr.promesaEjecutable(6,100)));
}

void Pcheck_PromEjecVENTA(){
	Promesa pr;
	pr.crearPromesa("prom", vender, 5, 10);
	ASSERT(pr.promesaEjecutable(4,100));
}

void Pcheck_PromNoEjecCOMPRA(){
	Promesa pr;
	pr.crearPromesa("prom", comprar, 5, 10);
	ASSERT(not(pr.promesaEjecutable(4,100)));
	ASSERT(not(pr.promesaEjecutable(6,9)));

}

void Pcheck_PromEjecCOMPRA(){
	Promesa pr;
	pr.crearPromesa("prom", comprar, 5, 10);
	ASSERT(pr.promesaEjecutable(6,10));
}

void Pcheck_compraVenta(){
	Promesa pr1c;
	pr1c.crearPromesa("t1", comprar, 5, 10);
	Promesa pr2c;
	pr2c.crearPromesa("t2", comprar, 5, 10);
	Promesa pr3c;
	pr3c.crearPromesa("T1", comprar, 5, 20);
	Promesa pr1v;
	pr1v.crearPromesa("t11", vender, 5, 10);
	Promesa pr2v;
	pr2v.crearPromesa("t22", vender, 5, 10);
	Promesa pr3v;
	pr3v.crearPromesa("T13", vender, 5, 10);
	Conj<Promesa> c;
	c.AgregarRapido(pr1c);
	c.AgregarRapido(pr2c);
	c.AgregarRapido(pr3c);
	c.AgregarRapido(pr1v);
	c.AgregarRapido(pr2v);
	c.AgregarRapido(pr3v);
	ASSERT_EQ(compraVenta(0, c), 10);
}

void Pcheck_promesasSobreTitulo(){
	Promesa pr1c;
	pr1c.crearPromesa("t1", comprar, 5, 10);
	Promesa pr2c;
	pr2c.crearPromesa("t2", comprar, 5, 10);
	Promesa pr3c;
	pr3c.crearPromesa("t1", comprar, 5, 20);
	Promesa pr1v;
	pr1v.crearPromesa("t1", vender, 5, 10);
	Promesa pr2v;
	pr2v.crearPromesa("T1", vender, 5, 10);
	Promesa pr3v;
	pr3v.crearPromesa("t2", vender, 5, 10);
	Conj<Promesa> c;
	c.AgregarRapido(pr1c);
	c.AgregarRapido(pr2c);
	c.AgregarRapido(pr3c);
	c.AgregarRapido(pr1v);
	c.AgregarRapido(pr2v);
	c.AgregarRapido(pr3v);
	c = promesasSobreTitulo("t1", comprar, c);

	Conj<Promesa> res;
	res.AgregarRapido(pr1c);
	res.AgregarRapido(pr3c);

	ASSERT(c == res);
}
//--------------------Titulo.cpp---------------------

void Tcheck_Crear(){
	Titulo t;
	t.nuevoT("titOriginal", 10, 11);
}

void Tcheck_Observadores(){
	Titulo t;
	t.nuevoT("titOriginal", 10, 11);
	ASSERT_EQ(t.nombre(), "titOriginal");
	ASSERT_EQ(t.cot(), 10);
	ASSERT_EQ(t.cantmax(), 11);
	ASSERT_EQ(t.enalza(), true);
}

void Tcheck_Recotizar(){
	Titulo t;
	t.nuevoT("titOriginal", 10, 11);
	t.recotizar(9);
	ASSERT_EQ(t.cot(), 9);
	ASSERT_EQ(t.enalza(), false);

	t.recotizar(12);
	ASSERT_EQ(t.cot(), 12);
	ASSERT_EQ(t.enalza(), true);
}

void Tcheck_cotActual(){
	Titulo t1;
	t1.nuevoT("t1", 10, 11);
	Titulo t2;
	t2.nuevoT("t2", 12, 13);
	Titulo T1;
	T1.nuevoT("T1", 14, 15);
	Titulo T2;
	T2.nuevoT("T2", 16, 17);
	Conj<Titulo> c;
	c.AgregarRapido(t1);
	c.AgregarRapido(t2);
	c.AgregarRapido(T1);
	c.AgregarRapido(T2);
	ASSERT_EQ(14, cotActual("T1", c));
}

void Tcheck_titEnAlza(){
	Titulo t1;
	t1.nuevoT("t1", 10, 11);
	Titulo t2;
	t2.nuevoT("t2", 12, 13);
	Titulo T1;
	T1.nuevoT("T1", 14, 15);
	Titulo T2;
	T2.nuevoT("T2", 16, 17);
	Conj<Titulo> c;
	c.AgregarRapido(t1);
	c.AgregarRapido(t2);
	c.AgregarRapido(T1);
	c.AgregarRapido(T2);
	ASSERT_EQ(true, titEnAlza("T1", c));
}

void Tcheck_limTen(){
	Titulo t1;
	t1.nuevoT("t1", 10, 11);
	Titulo t2;
	t2.nuevoT("t2", 12, 13);
	Titulo T1;
	T1.nuevoT("T1", 14, 15);
	Titulo T2;
	T2.nuevoT("T2", 16, 17);
	Conj<Titulo> c;
	c.AgregarRapido(t1);
	c.AgregarRapido(t2);
	c.AgregarRapido(T1);
	c.AgregarRapido(T2);
	ASSERT_EQ(17, limTen("T2", c));
}

void Tcheck_cambiarCotTs(){
	Titulo t1;
	t1.nuevoT("t1", 10, 11);
	Titulo t2;
	t2.nuevoT("t2", 12, 13);
	Titulo T1;
	T1.nuevoT("T1", 14, 15);
	Titulo T2;
	T2.nuevoT("T2", 16, 17);
	Conj<Titulo> c;
	c.AgregarRapido(t1);
	c.AgregarRapido(t2);
	c.AgregarRapido(T1);
	c.AgregarRapido(T2);
	cambiarCotTs("t2", 5, c);

	ASSERT_EQ(5, cotActual("t2", c));
	ASSERT_EQ(false, titEnAlza("t2", c));

	cambiarCotTs("t1", 20, c);
	ASSERT_EQ(20, cotActual("t1", c));
	ASSERT_EQ(true, titEnAlza("t1", c));
}
//--------------------DiccOrd.h--------------------

void DOcheck_diccVacio(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
    ASSERT_EQ(d.CantClaves(),0);
    ASSERT_EQ(d.MaxClaves(),10);
}

void DOcheck_diccDefinir1(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);

	ASSERT(d.Definido(1));
	ASSERT(!(d.Definido(2)));
}

void DOcheck_diccDefinir10(){
	DiccAcot<char, Nat> d;
	d = DiccAcot<char, Nat>(11);
	d.Definir('a','1');
	d.Definir('b','2');
	d.Definir('c','3');
	d.Definir('d','4');
	d.Definir('e','5');
	d.Definir('f','5');
	d.Definir('g','5');
	d.Definir('h','5');
    d.Definir('i','5');
    d.Definir('j','5');

	ASSERT(d.Definido('a'));
	ASSERT(d.Definido('b'));
	ASSERT(d.Definido('c'));
	ASSERT(d.Definido('d'));
	ASSERT(d.Definido('e'));
	ASSERT(d.Definido('f'));
	ASSERT(d.Definido('g'));
	ASSERT(d.Definido('h'));
	ASSERT(d.Definido('i'));
	ASSERT(d.Definido('j'));
}

void DOcheck_diccSignificado(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);
	d.Definir(2, 4);

	ASSERT_EQ(d.Significado(2),4);
	ASSERT(d.Definido(1));
}

void DOcheck_diccBorrar(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);
	d.Definir(2, 4);
	d.Definir(3, 6);
    ASSERT((d.Definido(2)));
	d.Borrar(2);
    ASSERT(!(d.Definido(2)));
}

void DOcheck_cantClaves(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);
	d.Definir(2, 4);
	d.Definir(3, 6);
    ASSERT_EQ(d.CantClaves(),3);
}

void DOcheck_iterador(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);
	d.Definir(2, 4);
	d.Definir(3, 6);
    DiccAcot<Nat, Nat>::Iterador itd=d.CrearIt();
    ASSERT_EQ(itd.SiguienteClave(),1);
    ASSERT_EQ(itd.SiguienteSignificado(),2);
    ASSERT(itd.HaySiguiente());
}

void DOcheck_iteradorfin(){
	DiccAcot<Nat, Nat> d = DiccAcot<Nat, Nat>(10);
	d.Definir(1, 2);
	d.Definir(2, 4);
	d.Definir(3, 6);
    DiccAcot<Nat, Nat>::Iterador itd=d.CrearIt();
    itd.Avanzar();
    itd.Avanzar();
    ASSERT_EQ(itd.Siguiente().clave,3);
    ASSERT(itd.HaySiguiente());
    itd.Avanzar();
    ASSERT(!(itd.HaySiguiente()));
}
//--------------------DiccT.h----------------------

void DTcheck_DiccVacio(){
	DiccT<Nat> d;
    ASSERT(!(d.Definido("hola")))
}

void DTcheck_Definir1(){
	DiccT<Nat> d;
	Nat a=2;
	d.Definir("hola", a);
    ASSERT(d.Definido("hola"));
    ASSERT_EQ(d.Significado("hola"),2);
}

void DTcheck_Definir10(){
    DiccT<Nat> dicc;
	Nat a=1;
    Nat b=2;
    Nat c=3;
    Nat d=4;
    Nat e=5;
    Nat f=6;
    Nat g=7;
    Nat h=8;
    Nat i=9;
    Nat j=10;
    dicc.Definir("hola", a);
    dicc.Definir("chau", b);
    dicc.Definir("baba", c);
    dicc.Definir("juajua", d);
    dicc.Definir("juanjuan", e);
    dicc.Definir("pedropedro", f);
    dicc.Definir("orale", g);
    dicc.Definir("trie", h);
    dicc.Definir("estoesuntrie", i);
    dicc.Definir("thistrieisatrie", j);
    ASSERT_EQ(dicc.Significado("hola"),1);
    ASSERT_EQ(dicc.Significado("chau"),2);
    ASSERT(dicc.Definido("baba"));
    ASSERT(dicc.Definido("juajua"));
    ASSERT(dicc.Definido("juanjuan"));
    ASSERT(dicc.Definido("pedropedro"));
    ASSERT(dicc.Definido("orale"));
    ASSERT(dicc.Definido("trie"));
    ASSERT(dicc.Definido("estoesuntrie"));
    ASSERT(dicc.Definido("thistrieisatrie"));
}


//--------------------Wolfie.cpp---------------------

void Wcheck_1Cliente(){
    Conj<Cliente> a;
    a.Agregar(1);
    Wolfie w=w.inaugurarWolfie(a);
    Titulo t;
    t=t.nuevoT("LCDTMAB",8,8);
    w.agregarTitulo(t);
    ASSERT_EQ(w.accionesPorCliente(1,"LCDTMAB"),0);
}


void Wcheck_1ClienteP(){
    Conj<Cliente> a;
    a.Agregar(1);
    Wolfie w=w.inaugurarWolfie(a);
    Titulo t;
    t=t.nuevoT("LCDTMAB",8,8);
    w.agregarTitulo(t);
	Promesa p;
	p=p.crearPromesa("LCDTMAB",comprar,2,2);
	w.agregarPromesa(1,p);
	Promesa p2;
	Conj<Promesa>::const_Iterador it=w.promesasDe(1);
	p2=it.Siguiente();
    ASSERT_EQ(p.titulo(),p2.titulo());
    it.Avanzar();
}

void Wcheck_2Clients1Title(){
    Conj<Cliente> a;
    a.Agregar(1);
	a.Agregar(2);
    Wolfie w=w.inaugurarWolfie(a);
    Titulo t;
    t =t.nuevoT("LCDTMAB",8,8);
	Titulo t2;
	t2=t2.nuevoT("VCTS",8,8);
    w.agregarTitulo(t);
    w.agregarTitulo(t2);
    ASSERT_EQ(w.accionesPorCliente(2,"LCDTMAB"),0)
    ASSERT_EQ(w.accionesPorCliente(1,"VCTS"),0)
}

void Wcheck_cantClientes(){
    Conj<Cliente> a;
    a.Agregar(1);
	a.Agregar(2);
    Wolfie w=w.inaugurarWolfie(a);

    ASSERT_EQ(w.cantClientes(),2)
}

//--------------------Driver.cpp---------------------

void Dcheck_agregar_titulo() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 0);
	wolfie.AgregarTitulo("T1",4,25);
	ASSERT_EQ(wolfie.EnAlza("T1"), true);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 1);
	ASSERT_EQ(wolfie.CotizacionDe("T1"), 4);
	ASSERT_EQ(wolfie.MaxAccionesDe("T1"), 25);
	wolfie.AgregarTitulo("T2",6,32);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 2);
	wolfie.AgregarTitulo("T3",1,30);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 3);
}

void Dcheck_actualizar_cotizacion() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	wolfie.ActualizarCotizacion("T1", 5);
 	ASSERT_EQ(wolfie.EnAlza("T1"), true);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 1);
	ASSERT_EQ(wolfie.CotizacionDe("T1"), 5);
	ASSERT_EQ(wolfie.MaxAccionesDe("T1"), 25);	
	wolfie.ActualizarCotizacion("T1", 4);
	ASSERT_EQ(wolfie.EnAlza("T1"), false);
	ASSERT_EQ(wolfie.CotizacionDe("T1"), 4);
	wolfie.ActualizarCotizacion("T1", 0);
	ASSERT_EQ(wolfie.CotizacionDe("T1"), 0);
	ASSERT_EQ(wolfie.EnAlza("T1"), false);
}

void Dcheck_agregar_promesa_compra() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	wolfie.AgregarTitulo("T2",3,30);
	wolfie.AgregarTitulo("T3",2,40);
	wolfie.AgregarTitulo("T4",5,10);	
	wolfie.AgregarPromesaDeCompra(1, "T3", 5, 10);
	ASSERT_EQ(wolfie.CotizacionDe("T1"), 4);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T1"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T2"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T3"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T4"), 0);
	wolfie.ActualizarCotizacion("T3", 6);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T3"), 10);
	ASSERT_EQ(wolfie.AccionesTotalesDe(1), 10);
	ASSERT_EQ(wolfie.CotizacionDe("T4"), 5);
//	wolfie.ActualizarCotizacion("T4", 5);
	ASSERT_EQ(wolfie.AccionesTotalesDe(1), 10);
	ASSERT_EQ(wolfie.CotizacionDe("T4"), 5);
	wolfie.AgregarPromesaDeCompra(1, "T4", 4, 10);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T4"), 0);
	wolfie.ActualizarCotizacion("T4", 5); 
	ASSERT_EQ(wolfie.CotizacionDe("T4"), 5);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T4"), 10);
	ASSERT_EQ(wolfie.AccionesTotalesDe(1), 20);
}

void Dcheck_agregar_promesa_venta() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);	
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 1);
	wolfie.AgregarPromesaDeCompra(1, "T1", 5, 10);
	wolfie.ActualizarCotizacion("T1", 6);
	wolfie.AgregarPromesaDeVenta(1, "T1", 3, 10);
	wolfie.ActualizarCotizacion("T1", 2);
}

void Dcheck_cantidad_clientes() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);
	Driver wolfie(clientes);
	ASSERT_EQ(wolfie.CantidadDeClientes(), 4)
}

void Dcheck_iesimo_cliente(){
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);
	Driver wolfie(clientes);
	ASSERT_EQ(wolfie.IesimoCliente(3), 9)
	ASSERT_EQ(wolfie.IesimoCliente(0), 1)
}

void Dcheck_promete_comprar() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	
	ASSERT_EQ(wolfie.PrometeComprar(1,"T1"), false);
	
	wolfie.AgregarPromesaDeCompra(1, "T1", 5, 10);
	ASSERT_EQ(wolfie.PrometeComprar(1,"T1"), true);
	
	wolfie.ActualizarCotizacion("T1", 6);
	ASSERT_EQ(wolfie.PrometeComprar(1,"T1"), false);


}

void Dcheck_promete_vender() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);

	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);	
	wolfie.AgregarPromesaDeCompra(1, "T1", 5, 10);
	wolfie.ActualizarCotizacion("T1", 6);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T1"), 10);
	wolfie.AgregarPromesaDeVenta(1, "T1", 4, 10);
	ASSERT_EQ(wolfie.PrometeVender(1,"T1"), true);
	wolfie.ActualizarCotizacion("T1", 3);
	ASSERT_EQ(wolfie.PrometeComprar(1,"T1"), false);
}

void Dcheck_compraDeAcciones() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	wolfie.AgregarTitulo("T2",3,30);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 2);
	ASSERT_EQ(wolfie.MaxAccionesDe("T2"), 30);
	ASSERT_EQ(wolfie.CotizacionDe("T2"), 3);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 0);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), false);
	wolfie.AgregarPromesaDeCompra(9, "T2", 4, 15);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), true);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 0);
	wolfie.ActualizarCotizacion("T2", 5);
  	ASSERT_EQ(wolfie.CotizacionDe("T2"), 5);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), false);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 15);
}

void Dcheck_no_vender_mas_del_maximo(){
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(2);
	clientes.Agregar(3);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1", 5, 10);
	wolfie.AgregarTitulo("T2", 7, 20);
	wolfie.AgregarPromesaDeCompra(2,"T1",6,10);
	wolfie.AgregarPromesaDeCompra(1,"T2",7,20);
	wolfie.ActualizarCotizacion("T2", 10);
	ASSERT_EQ(wolfie.AccionesDisponibles("T2"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T2"), 20);
	wolfie.AgregarPromesaDeCompra(2,"T2",15,20);
	wolfie.ActualizarCotizacion("T2", 20);
	ASSERT_EQ(wolfie.AccionesDisponibles("T2"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1,"T2"), 20);
	ASSERT_EQ(wolfie.AccionesPorCliente(2,"T2"), 0);
}


void Dcheck_VentaDeAcciones() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	wolfie.AgregarTitulo("T2",3,30);
	ASSERT_EQ(wolfie.CantidadDeTitulos(), 2);
	ASSERT_EQ(wolfie.MaxAccionesDe("T2"), 30);
	ASSERT_EQ(wolfie.CotizacionDe("T2"), 3);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 0);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), false);
	wolfie.AgregarPromesaDeCompra(9, "T2", 4, 15);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), true);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 0);
	wolfie.ActualizarCotizacion("T2", 5);
	ASSERT_EQ(wolfie.CotizacionDe("T2"), 5);
	ASSERT_EQ(wolfie.PrometeComprar(9, "T2"), false);
  	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 15);
	wolfie.AgregarPromesaDeVenta(9, "T2", 3, 15);
	ASSERT_EQ(wolfie.PrometeVender(9, "T2"), true);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 15);
	wolfie.ActualizarCotizacion("T2", 2);
	ASSERT_EQ(wolfie.PrometeVender(9, "T2"), false);
	ASSERT_EQ(wolfie.AccionesPorCliente(9, "T2"), 0);
}

void Dcheck_cuando_se_vende_se_puede_comprar(){
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1", 10, 50);
	wolfie.AgregarPromesaDeCompra(1, "T1", 20, 50);
	wolfie.ActualizarCotizacion("T1", 21);
	ASSERT_EQ( wolfie.AccionesPorCliente(1, "T1"), 50);
	ASSERT_EQ( wolfie.AccionesDisponibles("T1"), 0 );

	wolfie.AgregarPromesaDeCompra(5, "T1", 25, 10);
	wolfie.ActualizarCotizacion("T1", 50);

	ASSERT_EQ( wolfie.AccionesPorCliente(1, "T1"), 50);
	ASSERT_EQ( wolfie.AccionesPorCliente(5, "T1"), 0);

	wolfie.AgregarPromesaDeVenta(1, "T1", 30, 10);
	wolfie.ActualizarCotizacion("T1", 27);

	ASSERT_EQ( wolfie.AccionesPorCliente(1, "T1"), 40);
	ASSERT_EQ( wolfie.AccionesPorCliente(5, "T1"), 10);
}


void Dcheck_varias_promesas() {
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	clientes.Agregar(8);
	clientes.Agregar(9);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	wolfie.AgregarTitulo("T2",3,100);
	ASSERT_EQ(wolfie.PrometeVender(1, "T2"), false);
	ASSERT_EQ(wolfie.PrometeComprar(1, "T2"), false);
	ASSERT_EQ(wolfie.PrometeVender(1, "T1"), false);
	ASSERT_EQ(wolfie.PrometeComprar(1, "T1"), false);
	wolfie.AgregarPromesaDeCompra(1, "T2", 4, 15); 
	wolfie.AgregarPromesaDeCompra(1, "T1", 5, 10); 
	wolfie.AgregarPromesaDeCompra(5, "T2", 7, 15); 
	wolfie.AgregarPromesaDeCompra(5, "T1", 10, 10); 
	ASSERT_EQ(wolfie.PrometeComprar(1, "T2"), true);
	ASSERT_EQ(wolfie.PrometeComprar(1, "T1"), true);
	ASSERT_EQ(wolfie.AccionesTotalesDe(1), 0);
	ASSERT_EQ(wolfie.AccionesTotalesDe(5), 0);
	wolfie.ActualizarCotizacion("T2", 5);
	ASSERT_EQ(wolfie.AccionesPorCliente(5, "T2"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1, "T2"), 15);
	ASSERT_EQ(wolfie.PrometeComprar(1, "T2"), false);
	wolfie.AgregarPromesaDeCompra(1, "T2", 8, 15); 
	wolfie.AgregarPromesaDeVenta(1, "T2", 3, 15); 
	wolfie.ActualizarCotizacion("T2", 8);
	ASSERT_EQ(wolfie.AccionesPorCliente(5, "T2"), 15);
	ASSERT_EQ(wolfie.AccionesPorCliente(1, "T2"), 15);
	wolfie.AgregarPromesaDeVenta(5, "T2", 2, 15); 
	ASSERT_EQ(wolfie.PrometeVender(1, "T2"), true);
	ASSERT_EQ(wolfie.PrometeVender(5, "T2"), true);
	wolfie.ActualizarCotizacion("T2", 1);
	ASSERT_EQ(wolfie.AccionesPorCliente(5, "T2"), 0);
	ASSERT_EQ(wolfie.AccionesPorCliente(1, "T2"), 0);
	ASSERT_EQ(wolfie.PrometeVender(1, "T2"), false);
	ASSERT_EQ(wolfie.PrometeVender(5, "T2"), false);
	
}

void Dcheck_en_alza(){
	Conj<Cliente> clientes;
	clientes.Agregar(1);
	clientes.Agregar(5);
	Driver wolfie(clientes);
	wolfie.AgregarTitulo("T1",4,25);
	ASSERT_EQ(wolfie.EnAlza("T1"), true);
	wolfie.ActualizarCotizacion("T1", 6);
	ASSERT_EQ(wolfie.EnAlza("T1"), true);
	wolfie.ActualizarCotizacion("T1", 2);
	ASSERT_EQ(wolfie.EnAlza("T1"), false);
}



int main(int argc, char **argv)
{
	/******************************************************************
	 * TODO: escribir casos de Dcheck exhaustivos para todas          *
	 * las funcionalidades del módulo.                                *
	 * La interacción con el TAD Wolfie se debe hacer exclusivamente  *
	 * a través de la interfaz del driver.                            *
	 ******************************************************************/
//TESTRUN 	Promesa.cpp---------------------
RUN_TEST(Pcheck_Crear);

RUN_TEST(Pcheck_Observadores);
RUN_TEST(Pcheck_PromNoEjecVENTA);
RUN_TEST(Pcheck_PromEjecVENTA);
RUN_TEST(Pcheck_PromNoEjecCOMPRA);
RUN_TEST(Pcheck_PromEjecCOMPRA);
RUN_TEST(Pcheck_compraVenta);
RUN_TEST(Pcheck_promesasSobreTitulo);
//TESTRUN 	Titulo.cpp----------------------
RUN_TEST(Tcheck_Crear);
RUN_TEST(Tcheck_Observadores);
RUN_TEST(Tcheck_Recotizar);
RUN_TEST(Tcheck_cotActual);
RUN_TEST(Tcheck_titEnAlza);
RUN_TEST(Tcheck_cambiarCotTs);
RUN_TEST(Tcheck_limTen);

//TESTRUN 	DiccOrd.h---------------------
RUN_TEST(DOcheck_diccVacio);
RUN_TEST(DOcheck_diccDefinir1);
RUN_TEST(DOcheck_diccDefinir10);
RUN_TEST(DOcheck_diccSignificado);
RUN_TEST(DOcheck_diccBorrar);
RUN_TEST(DOcheck_cantClaves);
RUN_TEST(DOcheck_iterador);
RUN_TEST(DOcheck_iteradorfin);
//TESTRUN 	DiccT.h-----------------------
RUN_TEST(DTcheck_DiccVacio);
RUN_TEST(DTcheck_Definir1);
RUN_TEST(DTcheck_Definir10);
//TESTRUN 	Wolfie.cpp----------------------
RUN_TEST(Wcheck_1Cliente);
RUN_TEST(Wcheck_2Clients1Title);
RUN_TEST(Wcheck_1ClienteP);
RUN_TEST(Wcheck_cantClientes);
//TESTRUN 	Driver.cpp----------------------
RUN_TEST(test_wolfie_simple);
RUN_TEST(Dcheck_agregar_titulo);
RUN_TEST(Dcheck_actualizar_cotizacion);
RUN_TEST(Dcheck_agregar_promesa_compra);
RUN_TEST(Dcheck_agregar_promesa_venta);
RUN_TEST(Dcheck_cantidad_clientes);
RUN_TEST(Dcheck_iesimo_cliente);
RUN_TEST(Dcheck_promete_comprar);
RUN_TEST(Dcheck_promete_vender);
RUN_TEST(Dcheck_compraDeAcciones);
RUN_TEST(Dcheck_no_vender_mas_del_maximo);
RUN_TEST(Dcheck_VentaDeAcciones);
RUN_TEST(Dcheck_cuando_se_vende_se_puede_comprar);
RUN_TEST(Dcheck_varias_promesas);
RUN_TEST(Dcheck_en_alza);
	return 0;
}
