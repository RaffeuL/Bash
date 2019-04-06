#!/bin/bash

cd
cd 'Área de Trabalho'
mkdir Trabalhinho
cd Trabalhinho

lista=("a" "b" "c" "d" "e" "f" "g" "h" "i" "j")

for i in ${lista[*]}; do
	echo $i >> $i.txt
done
