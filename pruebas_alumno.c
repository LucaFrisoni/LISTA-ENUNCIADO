#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include "src/tp1.h"

void agregando_elementos_dinamicos(lista_t *lista, size_t cantidad)
{
	for (size_t i = 0; i < cantidad; i++) {
		int *n = malloc(sizeof(int));
		*n = i;
		if (!lista_agregar(lista, n)) {
			free(n);
			break;
		}
	}
}

void tests_lista_crear()
{
	//1
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se crea la lista correctamente");
	//2
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true, "Una lista recién creada está vacía");

	lista_destruir(lista);
}

void tests_lista_vacia()
{
	lista_t *lista = lista_crear();
	bool vacia;
	//1
	vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true,
		     "Si se le pasa una lista vacia devuelve 'true'");
	//2
	int n = 20;
	lista_agregar(lista, &n);
	vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == false,
		     "Si se le pasa una lista con elementos devuelve 'false'");
	//3
	vacia = lista_vacia(NULL);
	pa2m_afirmar(vacia == true, "Una lista nula se considera vacía");

	lista_destruir(lista);
}

void tests_lista_cantidad()
{
	lista_t *lista = lista_crear();
	size_t cant;
	//1
	cant = lista_cantidad(lista);
	pa2m_afirmar(cant == 0, "Una lista vacía devuelve cantidad 0");

	//2
	cant = lista_cantidad(NULL);
	pa2m_afirmar(cant == 0, "Una lista nula devuelve cantidad 0");

	//3
	agregando_elementos_dinamicos(lista, 3);
	cant = lista_cantidad(lista);
	pa2m_afirmar(cant == 3,
		     "Devuelve la cantidad correcta tras insertar 3 elementos");

	int *n = lista_eliminar_elemento(lista, 2);
	int *n2 = lista_eliminar_elemento(lista, 1);
	int *n3 = lista_eliminar_elemento(lista, 0);

	free(n);
	free(n2);
	free(n3);
	cant = lista_cantidad(lista);
	pa2m_afirmar(cant == 0,
		     "Después de eliminar todos, la cantidad vuelve a ser 0");

	//4
	agregando_elementos_dinamicos(lista, 20000);
	cant = lista_cantidad(lista);
	pa2m_afirmar(
		cant == 20000,
		"Prueba de estrés: se agregaron 20000 elementos y la cantidad es correcta");

	lista_destruir_todo(lista, free);
}

void tests_lista_agregar()
{
	lista_t *lista = lista_crear();
	int *elem;

	// 1. Agregar un elemento
	int *n = malloc(sizeof(int));
	*n = 1;
	pa2m_afirmar(lista_agregar(lista, n) == true,
		     "Puedo agregar un elemento en una lista vacía");
	pa2m_afirmar(lista_cantidad(lista) == 1,
		     "La lista tiene la cantidad correcta después de agregar");
	elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(*elem == 1, "El primer elemento es el agregado");

	// 2. Agregar un segundo elemento
	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	pa2m_afirmar(lista_agregar(lista, n2) == true,
		     "Puedo agregar un elemento en una lista con elementos");
	pa2m_afirmar(lista_cantidad(lista) == 2,
		     "La lista ahora tiene la cantidad correcta");
	elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(*elem == 2, "El último elemento es el recién agregado");

	// 3. Agregar en lista NULL
	int *n3 = malloc(sizeof(int));
	*n3 = 0;
	pa2m_afirmar(lista_agregar(NULL, n3) == false,
		     "No se puede agregar en una lista NULL");
	free(n3); // libero directamente porque no se inserto en lista

	// 4. Prueba de stress
	agregando_elementos_dinamicos(lista, 100000);
	pa2m_afirmar(
		lista_cantidad(lista) == 100002,
		"Prueba de estres: Se puedieron agregar +100000 elementos");

	// destruir todo
	lista_destruir_todo(lista, free);
}

void tests_lista_insertar()
{
	lista_t *lista = lista_crear();
	int *elem;
	// 1. Insertar en lista NULL
	int *n = malloc(sizeof(int));
	*n = 0;
	pa2m_afirmar(lista_insertar(NULL, n, 0) == false,
		     "No se puede insertar en lista NULL");
	free(n); // libero directamente porque no se inserto en lista

	// 2. Insertar en posición 0 de una lista vacía
	int *n2 = malloc(sizeof(int));
	*n2 = 1;
	pa2m_afirmar(lista_insertar(lista, n2, 0) == false,
		     "No se puede insertar en una lista vacía");
	free(n2); // libero directamente porque no se inserto en lista

	// 3. Insertar en posición inválida (mayor que cantidad - 1)
	int *n3 = malloc(sizeof(int));
	*n3 = 2;
	pa2m_afirmar(lista_insertar(lista, n3, 5) == false,
		     "No puedo insertar en una posición inválida ");

	// 4. Insertar en posición 0 cuando ya hay elementos
	int *n4 = malloc(sizeof(int));
	*n4 = 3;
	lista_agregar(lista, n3);
	pa2m_afirmar(lista_insertar(lista, n4, 0) == true,
		     "Puedo insertar en posición 0 cuando ya hay elementos");
	elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(*elem == 3,
		     "El nuevo primer elemento es el recién insertado");

	// 5. Insertar en el medio (posición válida intermedia)
	int *n5 = malloc(sizeof(int));
	*n5 = 4;
	lista_agregar(lista, n5);
	int *n6 = malloc(sizeof(int));
	*n6 = 5;
	pa2m_afirmar(lista_insertar(lista, n6, 2) == true,
		     "Puedo insertar en una posición intermedia válida");
	elem = lista_buscar_elemento(lista, 2);
	pa2m_afirmar(*elem == 5,
		     "El elemento en la posición intermedia es el insertado");

	// 6. Prueba de stress
	agregando_elementos_dinamicos(lista, 100000);

	int *n7 = malloc(sizeof(int));
	*n7 = 42;
	pa2m_afirmar(
		lista_insertar(lista, n7, 896) == true,
		"Prueba de estres: puedo insertar correctamente en una lista muy grande");
	elem = lista_buscar_elemento(lista, 896);
	pa2m_afirmar(
		*elem == 42,
		"Prueba de estres: el elemento insertado está en la posición correcta");

	// destruir toda la lista liberando memoria
	lista_destruir_todo(lista, free);
}

void tests_lista_eliminar_elemento()
{
	lista_t *lista = lista_crear();
	int *elem;

	// 1. Eliminar de lista NULL
	pa2m_afirmar(lista_eliminar_elemento(NULL, 0) == NULL,
		     "Tratar de eliminar de una lista NULL devuelve NULL");

	// 2. Eliminar de lista vacía
	pa2m_afirmar(lista_eliminar_elemento(lista, 0) == NULL,
		     "Tratar de eliminar de una lista vacía devuelve NULL");

	// 3.
	int *n1 = malloc(sizeof(int));
	*n1 = 10;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 20;
	lista_agregar(lista, n2);

	int *n3 = malloc(sizeof(int));
	*n3 = 30;
	lista_agregar(lista, n3);

	// 4. Eliminar lista con elementos
	elem = lista_eliminar_elemento(lista, 0);
	free(elem); // liberar la memoria del elemento eliminado

	elem = lista_eliminar_elemento(lista, 1);
	free(elem);

	elem = lista_eliminar_elemento(lista, 0);
	free(elem);
	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "Se eliminan correctamente los elementos");

	// 7. Prueba de stress
	agregando_elementos_dinamicos(lista, 100000);

	for (size_t i = 0; i < 50000; i++) {
		elem = lista_eliminar_elemento(lista, 0);
		free(elem);
	}
	pa2m_afirmar(
		lista_cantidad(lista) == 50000,
		"Prueba de estres:Se eliminaron 50000 elementos correctamente");

	lista_destruir_todo(lista, free);
}

int comparador_enteros(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;
	return x - y;
}
void tests_lista_lista_buscar_posicion()
{
	lista_t *lista = lista_crear();
	int num;
	// 1. Lista NULL
	pa2m_afirmar(lista_buscar_posicion(NULL, NULL, comparador_enteros) ==
			     -1,
		     "Buscar en lista NULL devuelve -1");

	// 2. Lista vacía
	pa2m_afirmar(lista_buscar_posicion(lista, NULL, comparador_enteros) ==
			     -1,
		     "Buscar en lista vacía devuelve -1");

	// 3. Sin comparador
	num = 5;
	pa2m_afirmar(lista_buscar_posicion(lista, &num, NULL) == -1,
		     "No pasarle comparador devuelve -1");

	//4 Buscar elementos existentes
	agregando_elementos_dinamicos(lista, 100000);

	pa2m_afirmar(lista_buscar_posicion(lista, &num, comparador_enteros) ==
			     5,
		     "Devuelve la posicion correcta del elemento de la lista");

	// 5. Buscar elemento no existente
	num = 100056;
	pa2m_afirmar(lista_buscar_posicion(lista, &num, comparador_enteros) ==
			     -1,
		     "Si no existe el elemento, devuelve -1");
	//6
	num = 89632;
	pa2m_afirmar(
		lista_buscar_posicion(lista, &num, comparador_enteros) == 89632,
		"Prueba de estres: Devuelve la posicion correcta del elemento de una lista muy grande");
	lista_destruir_todo(lista, free);
}

void tests_lista_lista_buscar_elemento()
{
	lista_t *lista = lista_crear();
	int *elem;

	// 1. Lista NULL
	pa2m_afirmar(lista_buscar_elemento(NULL, 0) == NULL,
		     "Buscar en lista NULL devuelve NULL");

	// 2. Lista vacía
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == NULL,
		     "Buscar en lista vacía devuelve NULL");

	agregando_elementos_dinamicos(lista, 100000);

	// 3. Buscar elementos válidos
	elem = lista_buscar_elemento(lista, 56);
	pa2m_afirmar(*elem == 56, "Devuelve el elemento correctamente");

	// 4. Buscar posiciones inválidas (fuera de rango)
	pa2m_afirmar(lista_buscar_elemento(lista, 100001) == NULL,
		     "Buscar en posición fuera de rango devuelve NULL");

	// 5. Prueba de stress
	elem = lista_buscar_elemento(lista, 59654);
	pa2m_afirmar(
		*elem == 59654,
		"Prueba de estres: Encuentra el elemento en una lista muy grande(posicion 59654)");

	lista_destruir_todo(lista, free);
}

bool sumar_10(void *dato, void *extra)
{
	int *num = dato;
	long long int *acumulador = extra;
	*acumulador += *num;
	return true; // siempre continuar
}
bool detener_en_5(void *dato, void *extra)
{
	(void)extra;
	int *num = dato;
	return (*num != 5); // parar si el valor es 5
}
void tests_lista_con_cada_elemento()
{
	lista_t *lista = lista_crear();
	size_t procesados;
	long long int acumulador = 0;

	// 1. Lista NULL
	procesados = lista_con_cada_elemento(NULL, sumar_10, &acumulador);
	pa2m_afirmar(procesados == 0, "Lista NULL no procesa elementos");

	// 2. Lista vacía
	procesados = lista_con_cada_elemento(lista, sumar_10, &acumulador);
	pa2m_afirmar(procesados == 0, "Lista vacía no procesa elementos");

	// 3. Agregar elementos
	agregando_elementos_dinamicos(lista, 10);

	// 4. Función que siempre devuelve true
	acumulador = 0;
	procesados = lista_con_cada_elemento(lista, sumar_10, &acumulador);
	pa2m_afirmar(
		procesados == 10,
		"Devuelve correctamente la cantidad de elementos procesados");
	pa2m_afirmar(acumulador == 45,
		     "El parametro extra funciona correctamante");

	// 5. Función que detiene en un valor específico
	procesados = lista_con_cada_elemento(lista, detener_en_5, NULL);
	pa2m_afirmar(
		procesados == 6,
		"Funcion detener_en_5:Iteración se detuvo al encontrar el valor 5");
	//6. Prueba de estres
	acumulador = 0;
	agregando_elementos_dinamicos(lista, 50000);
	procesados = lista_con_cada_elemento(lista, sumar_10, &acumulador);
	pa2m_afirmar(
		procesados == 50010 && acumulador == 1249975045,
		"Prueba de estres:(funcion sumar_10)Se procesaron correctamente 50010 elementos y su acumulador expresa el resultado correcto");
	lista_destruir_todo(lista, free);
}

size_t contador_destructor = 0;
void mi_destructor(void *dato)
{
	free(dato);
	contador_destructor++;
}
void tests_lista_destruir_todo()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1000);
	contador_destructor = 0;
	lista_destruir_todo(lista, mi_destructor);
	lista = NULL;
	pa2m_afirmar(lista == NULL, "La lista fue destruida correctamente");
	pa2m_afirmar(contador_destructor == 1000,
		     "Todos los elementos son destruidos correctamente");
}

void tests_lista_destruir()
{
	const size_t CANT = 1000;
	lista_t *lista = lista_crear();
	// Array para guardar los punteros de los elementos
	int **elementos = malloc(sizeof(int *) * CANT);

	for (size_t i = 0; i < CANT; i++) {
		elementos[i] = malloc(sizeof(int));
		*elementos[i] = i; // Asignamos valor
		lista_agregar(lista, elementos[i]);
	}

	int *primero = lista_buscar_elemento(lista, 0);

	// 1. Destruimos la lista
	lista_destruir(lista);
	lista = NULL;
	// 2. Verificaciones
	pa2m_afirmar(lista == NULL, "La lista fue destruida correctamente");
	pa2m_afirmar(*primero == 0,
		     "Los elemenotos de la lista siguen siendo accesibles");

	// 3. Prueba de estres
	bool todos_correctos = true;
	for (size_t i = 0; i < CANT; i++) {
		if (*elementos[i] != (int)i) {
			todos_correctos = false;
			break;
		}
	}
	pa2m_afirmar(
		todos_correctos,
		"Prueba de estres:Los 1000 elementos siguen siendo accesibles y correctos");

	//Liberacion de memoria del test
	for (size_t i = 0; i < CANT; i++)
		free(elementos[i]);
	free(elementos);
}

void tests_lista_iterador_crear()
{
	// 1. Crear iterador con lista NULL
	lista_iterador_t *it = lista_iterador_crear(NULL);
	pa2m_afirmar(it == NULL, "Crear iterador con lista NULL devuelve NULL");

	// 2. Crear iterador con lista vacía
	lista_t *lista = lista_crear();
	it = lista_iterador_crear(lista);
	pa2m_afirmar(it == NULL,
		     "No se puede crear un iterador de una lista vacía");

	// 3. Crear iterador con lista con elementos
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);

	pa2m_afirmar(it_2 != NULL,
		     "Se puede crear un iterador de una lista con elementos");
	pa2m_afirmar(lista_iterador_obtener_actual(it_2) ==
			     lista_buscar_elemento(lista, 0),
		     "El iterador comienza en el primer nodo");
	lista_iterador_destruir(it_2);
	// 4. Prueba de estrés

	agregando_elementos_dinamicos(lista, 100000);

	lista_iterador_t *it_3 = lista_iterador_crear(lista);

	pa2m_afirmar(
		it_3 != NULL,
		"Se puede crear un iterador de una lista de +100000 elementos");
	lista_iterador_destruir(it_3);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_hay_mas_elementos()
{
	// Caso 1: Iterador NULL
	pa2m_afirmar(lista_iterador_hay_mas_elementos(NULL) == false,
		     "Un iterador NULL devuelve false");

	// Caso 2: Iterador sobre lista con un solo elemento
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it_uno = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_hay_mas_elementos(it_uno),
		     "Iterador sobre lista con un elemento tiene elementos");
	lista_iterador_siguiente(it_uno);
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it_uno),
		     "Después de avanzar ya no hay más elementos");
	lista_iterador_destruir(it_uno);

	// Caso 3: Iterador sobre lista con varios elementos
	agregando_elementos_dinamicos(lista, 10000);
	lista_iterador_t *it_varios = lista_iterador_crear(lista);

	pa2m_afirmar(
		lista_iterador_hay_mas_elementos(it_varios),
		"El iterador sobre lista con varios elementos se crea correctamente");
	lista_iterador_siguiente(it_varios);
	pa2m_afirmar(lista_iterador_hay_mas_elementos(it_varios),
		     "El iterador aún tiene más elementos luego de avanzar");

	lista_iterador_destruir(it_varios);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_siguiente()
{
	// Caso 1: Iterador NULL
	lista_iterador_siguiente(NULL);
	pa2m_afirmar(true, "Avanzar un iterador NULL no rompe el programa");

	// Caso 2: Iterador sobre lista con un solo elemento
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it_uno = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_obtener_actual(it_uno) ==
			     lista_buscar_elemento(lista, 0),
		     "El iterador comienza en el único elemento");
	lista_iterador_siguiente(it_uno);
	pa2m_afirmar(lista_iterador_obtener_actual(it_uno) == NULL,
		     "El iterador avanza correctamente devolviendo NULL");

	lista_iterador_destruir(it_uno);

	// Caso 3: Iterador sobre lista con varios elementos
	agregando_elementos_dinamicos(lista, 5);
	lista_iterador_t *it_varios = lista_iterador_crear(lista);

	for (size_t i = 0; i < 5; i++) {
		lista_iterador_siguiente(it_varios);
	}
	pa2m_afirmar(lista_iterador_hay_mas_elementos(it_varios),
		     "El iterador avanza correctamente con varios elementos");

	lista_iterador_siguiente(it_varios);
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it_varios),
		     "Recorre correctamante todo los elementos");

	lista_iterador_destruir(it_varios);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_obtener_actual()
{
	// Caso 1: Iterador NULL
	pa2m_afirmar(lista_iterador_obtener_actual(NULL) == NULL,
		     "Un iterador NULL devuelve NULL ");

	// Caso 2: Lista con varios elementos
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it_uno = lista_iterador_crear(lista);
	int *num = lista_iterador_obtener_actual(it_uno);
	pa2m_afirmar(*num == 0,
		     "El iterador devuelve correctamante un elemento");
	lista_iterador_siguiente(it_uno);
	int *num2 = lista_iterador_obtener_actual(it_uno);
	pa2m_afirmar(
		*num2 == 1,
		"Después de avanzar, el iterador devuelve el nuevo elemento");
	lista_iterador_siguiente(it_uno);
	pa2m_afirmar(lista_iterador_obtener_actual(it_uno) == NULL,
		     "Cuando recorrio toda la lista devuelve NULL");

	lista_iterador_destruir(it_uno);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_destruir()
{
	// Caso 1: Destruir iterador NULL
	lista_iterador_destruir(NULL);
	pa2m_afirmar(true, "Destruir un iterador NULL no produce errores");

	// Caso 2: Destruir un iterador válido
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_destruir(it);
	pa2m_afirmar(true, "Se destruye correctamente un iterador válido");

	// Caso 3: La lista sigue siendo usable después de destruir el iterador
	pa2m_afirmar(lista_cantidad(lista) == 2,
		     "La lista sigue intacta tras destruir el iterador");

	// Caso 4 Prueba de estres: se puede destruir un iterador con muchos elementos
	agregando_elementos_dinamicos(lista, 100000);
	lista_iterador_t *it_2 = lista_iterador_crear(lista);

	lista_iterador_destruir(it_2);
	pa2m_afirmar(
		true,
		"Prueba de estres:Se destruye correctamente un iterador con +100000 elementos");

	lista_destruir_todo(lista, free);
}
// ------------------------------------------------------------------
void tests_pila_crear()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se puede crear una pila");
	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "La pila recién creada está vacía");

	pila_destruir(pila);
}

void tests_pila_apilar()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;
	//1
	pa2m_afirmar(pila_apilar(pila, &a) == true,
		     "Se apilan correctamente los elementos");
	pila_apilar(pila, &b);
	//2
	pa2m_afirmar(pila_cantidad(pila) == 2,
		     "La pila aumenta su tamaño al apilar");

	pila_destruir(pila);
	//3
	// Prueba de estrés con 100000 elementos en pila
	pila_t *pila_2 = pila_crear();
	for (int i = 0; i < 100000; i++) {
		int *num = malloc(sizeof(int));
		*num = i;
		pila_apilar(pila_2, num);
	}

	pa2m_afirmar(
		pila_cantidad(pila_2) == 100000,
		"Prueba de estrés: Se apilaron correctamente +100000 elementos");

	// Liberamos memoria
	while (pila_cantidad(pila_2) > 0) {
		int *elem = pila_desapilar(pila_2);
		free(elem);
	}

	pila_destruir(pila_2);
}

void tests_pila_desapilar()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;
	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	void *elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &b,
		     "Desapilar devuelve el último elemento apilado");
	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La pila reduce su tamaño al desapilar");

	pila_desapilar(pila); // queda vacía
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar en pila vacía devuelve NULL");

	pila_destruir(pila);
}

void tests_pila_ver_primero()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pa2m_afirmar(pila_ver_primero(pila) == NULL,
		     "Ver primero en pila vacía devuelve NULL");

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pa2m_afirmar(pila_ver_primero(pila) == &b,
		     "Ver primero devuelve el último apilado sin desapilar");

	pila_destruir(pila);
}

void tests_pila_cantidad()
{
	pila_t *pila = pila_crear();
	int a = 1, b = 2, c = 3;

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "Una pila recién creada tiene cantidad 0");
	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);
	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"La cantidad refleja la cantidad de elementos apilados correctamente");

	pila_destruir(pila);
}

void tests_pila_destruir()
{
	pila_t *pila = pila_crear();
	int *nums = malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; i++) {
		pila_apilar(pila, &nums[i]);
	}

	pa2m_afirmar(pila_cantidad(pila) == 100,
		     "La pila tiene 100 elementos antes de destruirse");

	pila_destruir(pila);
	free(nums);

	pa2m_afirmar(true, "La pila se destruye sin provocar errores");
}
// ------------------------------------------------------------------
void tests_cola_crear()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se crea la cola correctamente");
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "La cola recién creada está vacía");
	cola_destruir(cola);
}

void tests_cola_encolar()
{
	cola_t *cola = cola_crear();
	//1
	pa2m_afirmar(cola_encolar(cola, NULL) == true,
		     "Se puede encolar un elemento NULL");

	int *n = malloc(sizeof(int));
	*n = 42;
	//2
	pa2m_afirmar(cola_encolar(cola, n) == true,
		     "Se puede encolar un elemento dinámico");
	//3
	pa2m_afirmar(cola_cantidad(cola) == 2,
		     "Cantidad correcta después de encolar ");
	cola_destruir(cola);
	free(n);
	//4 Prueba de estrés con 100000 elementos
	cola_t *cola_2 = cola_crear();
	for (int i = 0; i < 100000; i++) {
		int *num = malloc(sizeof(int));
		*num = i;
		cola_encolar(cola_2, num);
	}

	pa2m_afirmar(
		cola_cantidad(cola_2) == 100000,
		"Prueba de estres: Se encolaron correctamente +100000 elementos");

	// Liberamos memoria
	while (cola_cantidad(cola_2) > 0) {
		int *elem = cola_desencolar(cola_2);
		free(elem);
	}

	cola_destruir(cola_2);
}

void tests_cola_desencolar()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar en cola vacía devuelve NULL");

	int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
	*n1 = 1;
	*n2 = 2;
	cola_encolar(cola, n1);
	cola_encolar(cola, n2);

	int *desencolado = cola_desencolar(cola);
	pa2m_afirmar(*desencolado == 1,
		     "Se desencola el primer elemento encolado (FIFO)");
	free(desencolado);

	desencolado = cola_desencolar(cola);
	pa2m_afirmar(*desencolado == 2,
		     "Se desencola el segundo elemento encolado (FIFO)");
	free(desencolado);

	pa2m_afirmar(
		cola_cantidad(cola) == 0,
		"La cola queda vacía después de desencolar todos los elementos");

	cola_destruir(cola);
}

void tests_cola_ver_primero()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola vacía devuelve NULL");

	int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
	*n1 = 10;
	*n2 = 20;
	cola_encolar(cola, n1);
	cola_encolar(cola, n2);

	int *primero = cola_ver_primero(cola);
	pa2m_afirmar(
		*primero == 10,
		"Ver primero devuelve correctamente el primer elemento encolado");

	cola_destruir(cola);
	free(n1);
	free(n2);
}

void tests_cola_cantidad()
{
	cola_t *cola = cola_crear();
	int a = 1, b = 2, c = 3;

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "Una cola recién creada tiene cantidad 0");
	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);
	pa2m_afirmar(
		cola_cantidad(cola) == 3,
		"La cantidad refleja correctamente los elementos encolados");

	cola_destruir(cola);
}

void tests_cola_destruir()
{
	cola_t *cola = cola_crear();
	int *nums = malloc(sizeof(int) * 100);
	for (int i = 0; i < 100; i++) {
		cola_encolar(cola, &nums[i]);
	}

	pa2m_afirmar(cola_cantidad(cola) == 100,
		     "La cola tiene 100 elementos antes de destruirse");

	cola_destruir(cola);
	free(nums);

	pa2m_afirmar(true, "La cola se destruye sin provocar errores");
}
int main()
{
	pa2m_nuevo_grupo("---------Pruebas de Lista---------");
	pa2m_nuevo_grupo("lista_crear");
	tests_lista_crear();

	pa2m_nuevo_grupo("lista_vacia");
	tests_lista_vacia();

	pa2m_nuevo_grupo("lista_cantidad");
	tests_lista_cantidad();

	pa2m_nuevo_grupo("lista_agregar");
	tests_lista_agregar();

	pa2m_nuevo_grupo("lista_insertar");
	tests_lista_insertar();

	pa2m_nuevo_grupo("lista_eliminar_elemento");
	tests_lista_eliminar_elemento();

	pa2m_nuevo_grupo("lista_buscar_posicion");
	tests_lista_lista_buscar_posicion();

	pa2m_nuevo_grupo("lista_buscar_elemento");
	tests_lista_lista_buscar_elemento();

	pa2m_nuevo_grupo("lista_con_cada_elemento");
	tests_lista_con_cada_elemento();

	pa2m_nuevo_grupo("lista_destruir_todo");
	tests_lista_destruir_todo();

	pa2m_nuevo_grupo("lista_destruir");
	tests_lista_destruir();

	pa2m_nuevo_grupo("lista_iterador_crear");
	tests_lista_iterador_crear();

	pa2m_nuevo_grupo("lista_iterador_hay_mas_elementos");
	tests_lista_iterador_hay_mas_elementos();

	pa2m_nuevo_grupo("lista_iterador_siguiente");
	tests_lista_iterador_siguiente();

	pa2m_nuevo_grupo("lista_iterador_obtener_actual");
	tests_lista_iterador_obtener_actual();

	pa2m_nuevo_grupo("lista_iterador_destruir");
	tests_lista_iterador_destruir();

	pa2m_nuevo_grupo("---------Pruebas de Pila---------");
	pa2m_nuevo_grupo("pila_crear");
	tests_pila_crear();

	pa2m_nuevo_grupo("pila_apilar");
	tests_pila_apilar();

	pa2m_nuevo_grupo("pila_desapilar");
	tests_pila_desapilar();

	pa2m_nuevo_grupo("pila_ver_primero");
	tests_pila_ver_primero();

	pa2m_nuevo_grupo("pila_cantidad");
	tests_pila_cantidad();

	pa2m_nuevo_grupo("pila_destruir");
	tests_pila_destruir();

	pa2m_nuevo_grupo("---------Pruebas de Cola---------");
	pa2m_nuevo_grupo("cola_crear");
	tests_cola_crear();

	pa2m_nuevo_grupo("cola_encolar");
	tests_cola_encolar();

	pa2m_nuevo_grupo("cola_desencolar");
	tests_cola_desencolar();

	pa2m_nuevo_grupo("cola_ver_primero");
	tests_cola_ver_primero();

	pa2m_nuevo_grupo("cola_cantidad");
	tests_cola_cantidad();

	pa2m_nuevo_grupo("cola_destruir");
	tests_cola_destruir();

	return pa2m_mostrar_reporte();
}
