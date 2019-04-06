#!/bin/bash

cd
cd 'Área de Trabalho'/Trabalhinho
mkdir Result

arq_atual=1
arq_comp=1

for arq in *; do
	for i in *; do
		if ! [ -d $arq ] && !  [ -d $i ];then
			if [ $arq_atual -lt $arq_comp ];then
				echo "Comparando o arquivo $arq com $i:" >> Result/result.txt
				diferenca="$(diff $arq $i)"
				if [ -z "$diferenca" ];then
					echo "SÃO IGUAIS" >> Result/result.txt
				else
					echo "Os arquivos $arq e $i são diferentes:" >> Result/result.txt
					echo $diferenca >> Result/result.txt
				
				fi
			fi
		fi
		arq_comp=$(($arq_comp+1))
	done
	arq_atual=$(($arq_atual+1))
	arq_comp=1
done
