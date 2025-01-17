#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

struct GastoXCiudad{
        int ciudad;
        int gasto;    
};

void heapify(GastoXCiudad* array, int size){
    int j = (size-2)/2;
    int i;
    int izq;
    int der;
    int x;
    while(j >= 0){
        i = j;
        izq = i*2+1;
        der = izq+1;
        while(izq<size){
            if((der >= size) or (array[izq].gasto < array[der].gasto)){
                if(array[i].gasto>array[izq].gasto){
                    x = array[i].gasto;
                    array[i].gasto = array[izq].gasto;
                    array[izq].gasto = x;
                    i = izq;
                    izq = i*2+1;
                    der = izq+1;
                }else{
                    izq = size;
                }
            }else{
                if(array[i].gasto>array[der].gasto){
                    x = array[i].gasto;
                    array[i].gasto = array[der].gasto;
                    array[der].gasto = x;
                    i = der;
                    izq = i*2+1;
                    der = izq+1;
                }else{
                    izq = size;
                }
            }
        }
        j--;        
    }
    return;
}


void heap_bajar(GastoXCiudad* array, int k){
    int x;
    int i = 0;
    int izq = 1;
    int der = 2;
    while(izq<k){
        if((der>=k) or (array[izq].gasto<array[der].gasto)){
            if(array[izq].gasto<array[i].gasto){
                x = array[i].gasto;
                array[i].gasto = array[izq].gasto;
                array[izq].gasto = x;
                i = izq;
                izq = i*2+1;
                der = izq+1;
            }else{
                izq = k;
            }              
        }else{
            if(array[der].gasto<array[i].gasto){
                x = array[i].gasto;
                array[i].gasto = array[der].gasto;
                array[der].gasto = x;
                i = der;
                izq = i*2+1;
                der = izq+1;
            }else{
                izq = k;
            }
        }
    }
}

int resolver(int zombies[], int soldados[], int costos[], int cant, int pres, int res[]) {

        GastoXCiudad gastos[cant];
        int k=0;
        int j;
        int i=0;
        while(i<cant){
            j = (((zombies[i]+9)/10)-soldados[i])*costos[i];
            if(j>0){
                gastos[k].gasto=j;
                gastos[k].ciudad=i;
                k++;
            }
            i++;
        }

        if(k==0){
            return cant;
        }

        heapify(gastos, k);

        while(k>0 and gastos[0].gasto<=pres){
            k--;
            pres = pres - gastos[0].gasto;
            j=gastos[0].ciudad;
            res[j] = gastos[0].gasto/costos[j];
            gastos[0] = gastos[k];
            heap_bajar(gastos, k);
        }

        return cant-k;
    }

int devolver (int sol, int res[], int cant) {

        cout << sol << ' ';
        for (int i=0;i<cant;i++) cout << res[i] << ' ';
        cout << endl;
     
}

int main(){

    int cant;
    cin >> cant;
    int pres;
    cin >> pres;
    int zombies[cant];
    int soldados[cant];
    int costos[cant];
    int res[cant];
    for(int i=0;i<cant;i++){
        cin >> zombies[i];
        cin >> soldados[i];
        cin >> costos[i];
        res[i] = 0;
    }
   
/*
        clock_t t;
        t = clock();*/

    int sol=resolver(zombies, soldados, costos, cant, pres, res);

        /*ofstream tiempo;
        t = clock() - t;
        tiempo.open("Tiempo",ios::app);
        tiempo << "Clocks: "<< (long int)t << " segundos: " << ((float)t)/CLOCKS_PER_SEC << endl;
*/
    devolver(sol, res, cant);
}
