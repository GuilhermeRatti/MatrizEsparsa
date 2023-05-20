all: soma

CODIGOS = matriz/*.c
HEADERS = matriz/*.h
override CFLAGS += -ggdb3 -Wall -lm -g
libmatriz.a: $(CODIGOS) $(HEADERS)
	gcc -c $(CODIGOS)
	ar crs libmatriz.a *.o
	rm -f *.o

soma: libmatriz.a casos_de_testes/teste_soma.c
	gcc -o main.exe casos_de_testes/teste_soma.c -I matriz -L . -lmatriz $(CFLAGS)

mult_ponto: libmatriz.a casos_de_testes/teste_mult_p_a_p.c
	gcc -o main.exe casos_de_testes/teste_mult_p_a_p.c -I matriz -L . -lmatriz $(CFLAGS)

mult_escalar: libmatriz.a casos_de_testes/teste_mult_escalar.c
	gcc -o main.exe casos_de_testes/teste_mult_escalar.c -I matriz -L . -lmatriz $(CFLAGS)

mult_matriz: libmatriz.a casos_de_testes/teste_mult_mat.c
	gcc -o main.exe casos_de_testes/teste_mult_mat.c -I matriz -L . -lmatriz $(CFLAGS)

convolucao: libmatriz.a casos_de_testes/teste_convolucao.c
	gcc -o main.exe casos_de_testes/teste_convolucao.c -I matriz -L . -lmatriz $(CFLAGS)

swap: libmatriz.a casos_de_testes/teste_swap.c
	gcc -o main.exe casos_de_testes/teste_swap.c -I matriz -L . -lmatriz $(CFLAGS)

bin: libmatriz.a casos_de_testes/teste_binario.c
	gcc -o main.exe casos_de_testes/teste_binario.c -I matriz -L . -lmatriz $(CFLAGS)

slice: libmatriz.a casos_de_testes/teste_slice.c
	gcc -o main.exe casos_de_testes/teste_slice.c -I matriz -L . -lmatriz $(CFLAGS)

transposta: libmatriz.a casos_de_testes/teste_transposta.c
	gcc -o main.exe casos_de_testes/teste_transposta.c -I matriz -L . -lmatriz $(CFLAGS)

gauss: libmatriz.a casos_de_testes/teste_gauss.c
	gcc -o main.exe casos_de_testes/teste_gauss.c -I matriz -L . -lmatriz $(CFLAGS)
run:
	./main.exe
clean:
	rm -f main.exe libmatriz.a
val:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s --log-file="valgrind.txt" ./main.exe
