rm -f Tiempo
for m in {0..3}
do
	echo $m
	for n in {2..40}
	do
		for i in {1..10}
		do
			python generarTest.py $n $m > test1
			for i in {1..10}
			do
				./ej3 < test1 > res
			done
		done
	done
	mv Tiempo Tiempo$m
done
rm test1
rm res
bash graficarn.sh
