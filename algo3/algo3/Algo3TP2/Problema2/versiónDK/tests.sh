python generarTest.py 250 20 0 > test1
./ej2 < test1 > res
rm Tiempo
bash tests2.sh
mv Tiempo Tiempos_250
bash graficar.sh
rm test1
rm res
rm test2
