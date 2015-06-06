#include "pelicula.h"
#include "lista.h"
#include "ticket.h"
#include "tipos.h"

  Ticket::Ticket(const Pelicula &p, Sala s, bool u)
{
    pelicula_ = p;
    sala_ = s;
    usado_ = u;
}

  const Pelicula& Ticket::peliculaT() const
{
    return pelicula_;
}

  Sala Ticket::salaT() const
  {
      return sala_;
  }
  bool Ticket::usadoT() const
  {
      return usado_;
  }


  void Ticket::usarT(){ const
      usado_ = true;
  }
  Pelicula Ticket::peliculaMenosVistaT(const Lista<Ticket> &ts) const
  {
	Lista<Pelicula> h;
	int j = 0;
	while (j < ts.longitud()){
		h.agregar(ts.iesimo(j).peliculaT());
		j++;}//genera la lista de peliculas h
	j = 0;
	Pelicula a = h.cabeza();
	while (j < ts.longitud()){
		if (h.cantidadDeApariciones(a)>=h.cantidadDeApariciones(h.iesimo(j))){
			a = h.iesimo(j);

		}
		j++;
	}//compara apariciones
		return a;


    }

  bool Ticket::todosLosTicketsParaLaMismaSalaT(const Lista<Ticket> &ts) const
  {
      Ticket h = ts.cabeza();
      int j = 1;
      int a = ts.longitud();
      bool b = true;
      while (j<a && b==true);
      {
          b = (h.salaT() == (ts.iesimo(j)).salaT());
          j++;
      }
      return b;
  }
  Lista<Ticket> Ticket::cambiarSalaT(const Lista<Ticket> &ts, Sala vieja, Sala nueva) const
  {

      Lista<Ticket> t;
      int j = 0;
      while (j<ts.longitud()) {
            if ((ts.iesimo(j)).salaT() == vieja)
                {t.agregar(Ticket(ts.iesimo(j).peliculaT(), nueva,ts.iesimo(j).usadoT()));
                }
                else {t.agregar(ts.iesimo(j));}
      j++;
      }

    return t;
  }
