rm -f Tiempo
for n in {60..100..40}
do
	echo $n
	for m in {1..190}
	do
		for i in {1..10}
		do
			python generarTestm.py $n $m > test1
			for i in {1..10}
			do
				./ej3 < test1 > res
			done
		done
	done
	mv Tiempo Tiempo$n
done
rm test1
rm res
bash graficarm.sh
