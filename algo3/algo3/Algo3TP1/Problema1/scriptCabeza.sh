rm Tiempo
for m in {0..2}
do
	for n in {100..2000..100} 
	do
		i=$n$m
		echo $i
		./tests/TR $n $m > tests/test$i;
		for j in {1..100}
		do
			./Ej1 < tests/test$i > res
		done
	done
done
rm res
rm *.o
