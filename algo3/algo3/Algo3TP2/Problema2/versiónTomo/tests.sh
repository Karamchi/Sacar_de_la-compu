for n in {50..250..50}
do
	echo $n
	python generarTest.py $n 20 20 > test1
	./ej2 < test1 > res
	rm Tiempo
	#python modificarBash.py tests2.sh res
	bash tests2.sh
	mv Tiempo Tiempos_$n
done
bash graficar.sh
rm test1
rm res
rm test2
