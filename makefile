compilar:
	gcc -g -Wall -Wextra main.c src/*.c -o programa
compilar_t_lista:
	gcc -g -Wall -Wextra tests/pruebas_lista.c src/*.c -o tests_lista
compilar_t_pila:
	gcc -g -Wall -Wextra tests/pruebas_pila.c src/*.c -o tests_pila
compilar_t_cola:
	gcc -g -Wall -Wextra tests/pruebas_cola.c src/*.c -o tests_cola
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./programa assets/pokemones.csv buscar id 10
valgrind_t_lista:
	valgrind --leak-check=full --show-leak-kinds=all ./tests_lista
valgrind_t_cola:
	valgrind --leak-check=full --show-leak-kinds=all ./tests_cola
valgrind_t_pila:
	valgrind --leak-check=full --show-leak-kinds=all ./tests_pila
