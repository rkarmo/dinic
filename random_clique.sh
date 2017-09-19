#!/bin/sh
m=`expr $1 \* $1`
echo $1" "$m" 2 4"
n=`expr $1 - 1`
for i in `seq 0 $n`; do
	for j in `seq 0 $n`; do
		echo $i" "$j" "$RANDOM
	done
done
