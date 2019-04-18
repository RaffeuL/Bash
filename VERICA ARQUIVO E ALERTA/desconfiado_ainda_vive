#!/bin/bash

cd
cd 'Área de Trabalho'/Diretorios
mkdir Log

diretorio=Log/log.txt
dif=false

date > $diretorio
echo "Início da verificação" >> $diretorio

for modelo in Modelo/*; do
	crp=false
	for analisado in Analisado/*; do 
		if ! [ -d $modelo ] && ! [ -d $analisado ];then
			if [ "${modelo/Modelo/Arquivo}" = "${analisado/Analisado/Arquivo}" ];then
				crp=true
				echo "Comparando os arquivo $modelo e $analisado:" >> $diretorio
				diferenca="$(diff $modelo $analisado)"
				if [ -z "$diferenca" ];then
					echo "SÃO IGUAIS!" >> $diretorio
					echo "Nenhuma restauração é necessária!" >> $diretorio
				else    #conteudo diferente
					dif=true
					echo "Os arquivos $modelo e $analisado são DIFERENTES!" >> $diretorio
					echo $diferenca >> $diretorio
					echo "Restauração necessária!" >> $diretorio
					cp $modelo Analisado
				fi
			fi
		fi
	done
	if [ $crp = false ];then #arquivo faltando
		dif=true
		echo "O arquivo $modelo NÃO EXISTE no diretório Analisado!" >> $diretorio
		echo "Restauração necessária!" >> $diretorio
		cp $modelo Analisado
	fi
done

#arquivo extra
for analisado in Analisado/*; do
	crp=false
	for modelo in Modelo/*;do
		if [ "${analisado/Analisado/Modelo}" = "$modelo" ];then
			crp=true
		fi
	done
	if [ $crp = false ];then
		dif=true
		echo "O arquivo $analisado NÃO EXISTE no diretório Modelo" >> $diretorio
		echo "Exclusão necessária!" >> $diretorio
		rm $analisado
	fi
done

echo "Fim da verificação" >> $diretorio

if [ $dif = true ];then
	sendEmail -f giovannrcesar10@gmail.com -t rafael91.lisboa@gmail.com -u "RELATÓRIO" -o message-file=/home/giovanne/'Área de Trabalho'/Diretorios/Log/log.txt -s smtp.gmail.com:587 -xu giovannrcesar10@gmail.com -xp SENHA
fi
