#!/bin/bash

if (( $# == 0 ))
then
	gcc -O3 -o "rotation" "rotation.c" -lm &&
	echo "./rotation готовий"
elif (( $# == 1 ))
then
	gcc -O3 -o "rotation-$1" "rotation-$1.c" -lm &&
	echo "./rotation-$1 готовий"
else
	echo "Шо ти хочеш???"
fi

