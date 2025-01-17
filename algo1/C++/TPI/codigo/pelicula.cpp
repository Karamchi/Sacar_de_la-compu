 #include "pelicula.h"
#include "lista.h"
#include <iostream>
#include <fstream>

using namespace std;

void sinRepesGenero(Lista<Genero> &l) {
    int j=0;
    int i=0;
    Genero h;
    while (j<l.longitud()) {
        h=l.iesimo(j);
        i=j+1;
        while (i<l.longitud()) {
            if (h==l.iesimo(i)) {
                l.eliminarPosicion(i);
            } else {i++;}
        }
        j++;
    }
}

void sinRepesActor(Lista<Actor> &l) {
    int j=0;
    int i=0;
    Actor h;
    while (j<l.longitud()) {
        h=l.iesimo(j);
        i=j+1;
        while (i<l.longitud()) {
            if (h==l.iesimo(i)) {
                l.eliminarPosicion(i);
            } else {i++;}
        }
        j++;
    }
}

Pelicula::Pelicula(Nombre n, Lista<Genero> gs, Lista<Actor> as, bool b){
    sinRepesGenero(gs);
    sinRepesActor(as);
    nombre_ = n;
    generos_= gs;
    actores_= as;
    es3D_ = b;
}

string Pelicula::nombreP() const {
        return nombre_;
}

Lista<Genero> Pelicula::generosP() const {
        return generos_;
}

Lista<Actor> Pelicula::actoresP() const {
    return actores_;
}

bool Pelicula::es3DP() const {
        return es3D_;
}



Lista<std::pair<Genero,Lista<Pelicula> > > Pelicula::agruparPelisPorGeneroP(Lista<Pelicula> ps) const{
    Lista <Pelicula> pAv;
    Lista <Pelicula> pC;
    Lista <Pelicula> pD;
    Lista <Pelicula> pT;
    Lista <Pelicula> pR;

    int i=0;
    while (i<(ps.longitud())) {
        if (((ps.iesimo(i)).generosP()).pertenece(Aventura)){
            pAv.agregarAtras(ps.iesimo(i));}
        if (((ps.iesimo(i)).generosP()).pertenece(Comedia)){
            pC.agregarAtras(ps.iesimo(i));}
        if (((ps.iesimo(i)).generosP()).pertenece(Drama)){
            pD.agregarAtras(ps.iesimo(i));}
        if (((ps.iesimo(i)).generosP()).pertenece(Terror)){
            pT.agregarAtras(ps.iesimo(i));}
        if (((ps.iesimo(i)).generosP()).pertenece(Romantica)){
            pR.agregarAtras(ps.iesimo(i));}
        i++;
    }

    Lista<std::pair<Genero,Lista<Pelicula> > > g;
    std::pair<Genero, Lista<Pelicula> > av = make_pair(Aventura,pAv);
    std::pair<Genero, Lista<Pelicula> > ac = make_pair(Comedia,pC);
    std::pair<Genero, Lista<Pelicula> > ad = make_pair(Drama,pD);
    std::pair<Genero, Lista<Pelicula> > ate = make_pair(Terror,pT);
    std::pair<Genero, Lista<Pelicula> > ar = make_pair(Romantica,pR);

    if( (av.second).longitud() > 0){
        g.agregarAtras(av);
        }
    if( (ac.second).longitud() > 0){
        g.agregarAtras(ac);
        }
    if( (ad.second).longitud() > 0){
        g.agregarAtras(ad);
        }
    if( (ar.second).longitud() > 0){
        g.agregarAtras(ar);
        }
    if( (ate.second).longitud() > 0){
        g.agregarAtras(ate);
        }
    return g;
}

Lista<Pelicula> Pelicula::generarSagaDePeliculasP(Lista<Actor> as, Lista<Genero> gs, Lista<Nombre> nombres) const{;
        Lista<Pelicula> lp;
        int i=0;
        while (i<nombres.longitud()) {
                lp.agregar(Pelicula(nombres.iesimo(i),gs,as,false));
                i++;
        }
        return lp;
}

std::ostream& operator<<(std::ostream &os, const Pelicula &p){
      os << "Nombre: "<< p.nombreP() << endl << "Actores: " << p.actoresP() << endl << "G�neros: " << p.generosP() << endl << "3D: " << p.es3DP();
      cout << os;
      return os;
}

void Pelicula::cargar (std::istream& is) {

    char c;
    string np;
    Actor ap;
    Lista<Actor> asp;
    string gp1;
    Genero gp2;
    Lista<Genero> gsp;
    //define variables
    is>>c;
    is>>c;

    getline(is,np,'|');
    nombre_ = np;
    is>>c;
    while (c!=']') {
        is>>c;
        getline(is,gp1,'|');
        if (gp1=="Aventura") {
            gp2=Aventura;
        } if (gp1=="Comedia") {
            gp2=Comedia;
        } if (gp1=="Drama") {
            gp2=Drama;
        } if (gp1=="Terror") {
            gp2=Terror;
        } if (gp1=="Romantica") {
            gp2=Romantica;
        }
        gsp.agregar(gp2);
        is>>c;
    } is>>c;
    while (c!=']') {
        is>>c;
        getline(is,ap,'|');
        asp.agregar(ap);
        is>>c;
        actores_ = asp;
    } is>>c;
        is>>c;
        if(c == 'V') es3D_ = true; else es3D_ = false;
        generos_ = gsp;
}

  void Pelicula::guardar(std::ostream& os) const
  {
      int i = 0;
      os << 'P';
      os << " ";
      os << '|';
      os << nombre_;
      os << '|';
      os << " ";
      os << '[';
      while (i<generos_.longitud())
      {
          os << '|';
          if(generos_.iesimo(i)==0)
            {os << "Aventura";}
        if(generos_.iesimo(i)==1)
            {os << "Comedia";}
        if(generos_.iesimo(i)==2)
            {os << "Drama";}
        if(generos_.iesimo(i)==3)
            {os << "Terror";}
        if(generos_.iesimo(i)==4)
            {os << "Romantica";}
          os << '|';
          if(i != generos_.longitud()-1){os << ',';}
          i++;
      }
      i = 0;
      os << ']';
      os << " ";
      os << '[';
      while (i<actores_.longitud())
      {
          os << '|';
          os << actores_.iesimo(i);
          os << '|';
          if(i != actores_.longitud()-1){os << ',';}
          i++;
      }
      os << ']';
      os << " ";
      if (es3D_ == true) {os << 'V';} else {os << 'F';}
    }


void Pelicula::mostrar(std::ostream& os) const
      {
      int i = 0;
      cout << "Nombre: " << nombre_ << endl;
      cout << "G�neros: ";
      while (i<generos_.longitud())
      {
          cout << generos_.iesimo(i);
          if(i != generos_.longitud()-1){cout << ", ";}
          i++;
      }
      i = 0;
      cout << endl << "Actores: ";
      while (i<actores_.longitud())
      {
          cout << actores_.iesimo(i);
          if(i != actores_.longitud()-1){cout << ", ";}
          i++;
      } cout << endl;
      if (es3D_ == true) {cout << "3D";} else {cout << "2D";}
}
