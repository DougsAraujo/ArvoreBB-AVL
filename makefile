ABB: UsaTabela.o ArvoreBinariaBusca.o
	gcc UsaTabela.o ArvoreBinariaBusca.o -o ABB -lm

UsaTabela.o: UsaTabela.c TabSimb.h
	gcc -c UsaTabela.c

ArvoreBinariaBusca.o: ArvoreBinariaBusca.c TabSimb.h
	gcc -c ArvoreBinariaBusca.c
