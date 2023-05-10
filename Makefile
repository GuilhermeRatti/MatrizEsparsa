all:
	gcc -Wall -g -o main.exe *.c -lm
clean:
	rm -f main
val:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s --log-file="valgrind.txt" ./main.exe