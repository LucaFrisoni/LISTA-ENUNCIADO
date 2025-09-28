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

void test_lista_crear_no_null()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se crea la lista correctamente");
	lista_destruir(lista);
}
void test_lista_crear_vacia()
{
	lista_t *lista = lista_crear();
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true, "Una lista recién creada está vacía");
	lista_destruir(lista);
}

void tests_lista_crear()
{
	test_lista_crear_no_null();
	test_lista_crear_vacia();
}
//-----------------------
void test_lista_vacia_devuelve_true_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true,
		     "Si se le pasa una lista vacía devuelve 'true'");
	lista_destruir(lista);
}
void test_lista_vacia_devuelve_false_en_lista_con_elementos()
{
	lista_t *lista = lista_crear();
	int n = 20;
	lista_agregar(lista, &n);
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == false,
		     "Si se le pasa una lista con elementos devuelve 'false'");
	lista_destruir(lista);
}
void test_lista_vacia_devuelve_true_en_lista_nula()
{
	bool vacia = lista_vacia(NULL);
	pa2m_afirmar(vacia == true, "Una lista nula se considera vacía");
}

void tests_lista_vacia()
{
	test_lista_vacia_devuelve_true_en_lista_vacia();
	test_lista_vacia_devuelve_false_en_lista_con_elementos();
	test_lista_vacia_devuelve_true_en_lista_nula();
}
//-----------------------
void test_lista_cantidad_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	size_t cant = lista_cantidad(lista);
	pa2m_afirmar(cant == 0, "Una lista vacía devuelve cantidad 0");
	lista_destruir(lista);
}
void test_lista_cantidad_en_lista_nula()
{
	size_t cant = lista_cantidad(NULL);
	pa2m_afirmar(cant == 0, "Una lista nula devuelve cantidad 0");
}
void test_lista_cantidad_despues_de_insertar_y_eliminar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	size_t cant = lista_cantidad(lista);
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

	lista_destruir(lista);
}
void test_lista_cantidad_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 20000);

	size_t cant = lista_cantidad(lista);
	pa2m_afirmar(
		cant == 20000,
		"Prueba de estrés: se agregaron 20000 elementos y la cantidad es correcta");

	lista_destruir_todo(lista, free);
}

void tests_lista_cantidad()
{
	test_lista_cantidad_en_lista_vacia();
	test_lista_cantidad_en_lista_nula();
	test_lista_cantidad_despues_de_insertar_y_eliminar();
	test_lista_cantidad_prueba_estres();
}
//-----------------------
void test_lista_agregar_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 1;

	pa2m_afirmar(lista_agregar(lista, n) == true,
		     "Puedo agregar un elemento en una lista vacía");
	pa2m_afirmar(lista_cantidad(lista) == 1,
		     "La lista tiene la cantidad correcta después de agregar");

	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(*elem == 1, "El primer elemento es el agregado");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	pa2m_afirmar(lista_agregar(lista, n2) == true,
		     "Puedo agregar un elemento en una lista con elementos");
	pa2m_afirmar(lista_cantidad(lista) == 2,
		     "La lista ahora tiene la cantidad correcta");

	int *elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(*elem == 2, "El último elemento es el recién agregado");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_nula()
{
	int *n = malloc(sizeof(int));
	*n = 0;

	pa2m_afirmar(lista_agregar(NULL, n) == false,
		     "No se puede agregar en una lista NULL");

	free(n); // libero directamente porque no se insertó en lista
}
void test_lista_agregar_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	pa2m_afirmar(lista_cantidad(lista) == 100000,
		     "Prueba de estrés: Se pudieron agregar +100000 elementos");

	lista_destruir_todo(lista, free);
}

void tests_lista_agregar()
{
	test_lista_agregar_en_lista_vacia();
	test_lista_agregar_en_lista_con_elementos();
	test_lista_agregar_en_lista_nula();
	test_lista_agregar_prueba_estres();
}
//-----------------------
void test_lista_insertar_en_lista_nula()
{
	int *n = malloc(sizeof(int));
	*n = 0;

	pa2m_afirmar(lista_insertar(NULL, n, 0) == false,
		     "No se puede insertar en lista NULL");

	free(n);
}
void test_lista_insertar_en_lista_vacia_pos0()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 1;

	pa2m_afirmar(lista_insertar(lista, n, 0) == false,
		     "No se puede insertar en una lista vacía");

	free(n);
	lista_destruir(lista);
}
void test_lista_insertar_posicion_invalida()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 2;

	pa2m_afirmar(lista_insertar(lista, n, 5) == false,
		     "No puedo insertar en una posición inválida");

	free(n);
	lista_destruir(lista);
}
void test_lista_insertar_pos0_con_elementos()
{
	lista_t *lista = lista_crear();
	int *n3 = malloc(sizeof(int));
	*n3 = 2;
	lista_agregar(lista, n3);

	int *n4 = malloc(sizeof(int));
	*n4 = 3;
	pa2m_afirmar(lista_insertar(lista, n4, 0) == true,
		     "Puedo insertar en posición 0 cuando ya hay elementos");

	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(*elem == 3,
		     "El nuevo primer elemento es el recién insertado");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_en_posicion_intermedia()
{
	lista_t *lista = lista_crear();
	int *n3 = malloc(sizeof(int));
	*n3 = 2;
	lista_agregar(lista, n3);

	int *n4 = malloc(sizeof(int));
	*n4 = 4;
	lista_agregar(lista, n4);

	int *n5 = malloc(sizeof(int));
	*n5 = 6;
	lista_agregar(lista, n5);

	int *n6 = malloc(sizeof(int));
	*n6 = 5;
	pa2m_afirmar(lista_insertar(lista, n6, 1) == true,
		     "Puedo insertar en una posición intermedia válida");

	int *elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(*elem == 5,
		     "El elemento en la posición intermedia es el insertado");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	int *n7 = malloc(sizeof(int));
	*n7 = 42;
	pa2m_afirmar(
		lista_insertar(lista, n7, 896) == true,
		"Prueba de estrés: puedo insertar correctamente en una lista muy grande");

	int *elem = lista_buscar_elemento(lista, 896);
	pa2m_afirmar(
		*elem == 42,
		"Prueba de estrés: el elemento insertado está en la posición correcta");

	lista_destruir_todo(lista, free);
}

void tests_lista_insertar()
{
	test_lista_insertar_en_lista_nula();
	test_lista_insertar_en_lista_vacia_pos0();
	test_lista_insertar_posicion_invalida();
	test_lista_insertar_pos0_con_elementos();
	test_lista_insertar_en_posicion_intermedia();
	test_lista_insertar_prueba_estres();
}
//-----------------------
void test_lista_eliminar_elemento_lista_nula()
{
	pa2m_afirmar(lista_eliminar_elemento(NULL, 0) == NULL,
		     "Tratar de eliminar de una lista NULL devuelve NULL");
}
void test_lista_eliminar_elemento_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_eliminar_elemento(lista, 0) == NULL,
		     "Tratar de eliminar de una lista vacía devuelve NULL");
	lista_destruir(lista);
}
void test_lista_eliminar_elemento_varios()
{
	lista_t *lista = lista_crear();
	int *n1 = malloc(sizeof(int));
	*n1 = 10;
	int *n2 = malloc(sizeof(int));
	*n2 = 20;
	int *n3 = malloc(sizeof(int));
	*n3 = 30;

	lista_agregar(lista, n1);
	lista_agregar(lista, n2);
	lista_agregar(lista, n3);

	int *elem = lista_eliminar_elemento(lista, 0);
	free(elem);
	elem = lista_eliminar_elemento(lista, 1);
	free(elem);
	elem = lista_eliminar_elemento(lista, 0);
	free(elem);

	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "Se eliminan correctamente los elementos");

	lista_destruir(lista);
}
void test_lista_eliminar_elemento_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	int *elem;
	for (size_t i = 0; i < 50000; i++) {
		elem = lista_eliminar_elemento(lista, 0);
		free(elem);
	}

	pa2m_afirmar(
		lista_cantidad(lista) == 50000,
		"Prueba de estrés: Se eliminaron 50000 elementos correctamente");

	lista_destruir_todo(lista, free);
}

void tests_lista_eliminar_elemento()
{
	test_lista_eliminar_elemento_lista_nula();
	test_lista_eliminar_elemento_lista_vacia();
	test_lista_eliminar_elemento_varios();
	test_lista_eliminar_elemento_prueba_estres();
}
//-----------------------
int comparador_enteros(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;
	return x - y;
}
void test_lista_buscar_posicion_lista_nula()
{
	pa2m_afirmar(lista_buscar_posicion(NULL, NULL, comparador_enteros) ==
			     -1,
		     "Buscar en lista NULL devuelve -1");
}
void test_lista_buscar_posicion_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_buscar_posicion(lista, NULL, comparador_enteros) ==
			     -1,
		     "Buscar en lista vacía devuelve -1");
	lista_destruir(lista);
}
void test_lista_buscar_posicion_sin_comparador()
{
	lista_t *lista = lista_crear();
	int num = 5;
	pa2m_afirmar(lista_buscar_posicion(lista, &num, NULL) == -1,
		     "No pasarle comparador devuelve -1");
	lista_destruir(lista);
}
void test_lista_buscar_posicion_elemento_existente()
{
	lista_t *lista = lista_crear();
	int num = 5;
	agregando_elementos_dinamicos(lista, 100000);

	pa2m_afirmar(lista_buscar_posicion(lista, &num, comparador_enteros) ==
			     5,
		     "Devuelve la posición correcta del elemento de la lista");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_posicion_elemento_no_existente()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);
	int num = 100056;

	pa2m_afirmar(lista_buscar_posicion(lista, &num, comparador_enteros) ==
			     -1,
		     "Si no existe el elemento, devuelve -1");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_posicion_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);
	int num = 89632;

	pa2m_afirmar(
		lista_buscar_posicion(lista, &num, comparador_enteros) == 89632,
		"Prueba de estrés: Devuelve la posición correcta del elemento de una lista muy grande");

	lista_destruir_todo(lista, free);
}

void tests_lista_buscar_posicion()
{
	test_lista_buscar_posicion_lista_nula();
	test_lista_buscar_posicion_lista_vacia();
	test_lista_buscar_posicion_sin_comparador();
	test_lista_buscar_posicion_elemento_existente();
	test_lista_buscar_posicion_elemento_no_existente();
	test_lista_buscar_posicion_prueba_estres();
}
//-----------------------
void test_lista_buscar_elemento_lista_nula()
{
	pa2m_afirmar(lista_buscar_elemento(NULL, 0) == NULL,
		     "Buscar en lista NULL devuelve NULL");
}
void test_lista_buscar_elemento_lista_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == NULL,
		     "Buscar en lista vacía devuelve NULL");
	lista_destruir(lista);
}
void test_lista_buscar_elemento_valido()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	int *elem = lista_buscar_elemento(lista, 56);
	pa2m_afirmar(*elem == 56, "Devuelve el elemento correctamente");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_elemento_fuera_de_rango()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	pa2m_afirmar(lista_buscar_elemento(lista, 100001) == NULL,
		     "Buscar en posición fuera de rango devuelve NULL");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_elemento_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	int *elem = lista_buscar_elemento(lista, 59654);
	pa2m_afirmar(
		*elem == 59654,
		"Prueba de estrés: Encuentra el elemento en una lista muy grande (posición 59654)");

	lista_destruir_todo(lista, free);
}

void tests_lista_buscar_elemento()
{
	test_lista_buscar_elemento_lista_nula();
	test_lista_buscar_elemento_lista_vacia();
	test_lista_buscar_elemento_valido();
	test_lista_buscar_elemento_fuera_de_rango();
	test_lista_buscar_elemento_prueba_estres();
}
//-----------------------
bool sumar_10(void *dato, void *extra)
{
	int *num = dato;
	long long int *acumulador = extra;
	*acumulador += *num;
	return true; // siempre continuar
}
bool detener_en_5(void *dato, void *extra)
{
	(void)extra; //para el warning
	int *num = dato;
	return (*num != 5); // parar si el valor es 5
}

void test_lista_con_cada_elemento_lista_nula()
{
	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(NULL, sumar_10, &acumulador);
	pa2m_afirmar(procesados == 0, "Lista NULL no procesa elementos");
}
void test_lista_con_cada_elemento_lista_vacia()
{
	lista_t *lista = lista_crear();
	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(lista, sumar_10, &acumulador);
	pa2m_afirmar(procesados == 0, "Lista vacía no procesa elementos");
	lista_destruir(lista);
}
void test_lista_con_cada_elemento_funcion_true()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10);

	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(lista, sumar_10, &acumulador);

	pa2m_afirmar(
		procesados == 10,
		"Devuelve correctamente la cantidad de elementos procesados");
	pa2m_afirmar(acumulador == 45,
		     "El parámetro extra funciona correctamente");

	lista_destruir_todo(lista, free);
}
void test_lista_con_cada_elemento_detener_en_valor()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10);

	size_t procesados = lista_con_cada_elemento(lista, detener_en_5, NULL);
	pa2m_afirmar(
		procesados == 6,
		"Funcion detener_en_5: Iteración se detuvo al encontrar el valor 5");

	lista_destruir_todo(lista, free);
}
void test_lista_con_cada_elemento_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 50000);

	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(lista, sumar_10, &acumulador);

	pa2m_afirmar(
		procesados == 50000 && acumulador == 1249975000LL,
		"Prueba de estrés: (función sumar_10) Se procesaron correctamente 50000 elementos y el acumulador es correcto");

	lista_destruir_todo(lista, free);
}

void tests_lista_con_cada_elemento()
{
	test_lista_con_cada_elemento_lista_nula();
	test_lista_con_cada_elemento_lista_vacia();
	test_lista_con_cada_elemento_funcion_true();
	test_lista_con_cada_elemento_detener_en_valor();
	test_lista_con_cada_elemento_prueba_estres();
}
//-----------------------
size_t contador_destructor = 0;
void mi_destructor(void *dato)
{
	free(dato);
	contador_destructor++;
}
void test_lista_destruir_todo_lista_con_elementos()
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

void tests_lista_destruir_todo()
{
	test_lista_destruir_todo_lista_con_elementos();
}
//-----------------------
void test_lista_destruir_verificar_lista_nula()
{
	lista_t *lista = lista_crear();
	int *elem = malloc(sizeof(int));
	*elem = 42;
	lista_agregar(lista, elem);

	lista_destruir(lista);
	lista = NULL;

	pa2m_afirmar(lista == NULL, "La lista fue destruida correctamente");

	free(elem);
}
void test_lista_destruir_elementos_accesibles()
{
	const size_t CANT = 1000;
	lista_t *lista = lista_crear();
	int **elementos = malloc(sizeof(int *) * CANT);

	for (size_t i = 0; i < CANT; i++) {
		elementos[i] = malloc(sizeof(int));
		*elementos[i] = i;
		lista_agregar(lista, elementos[i]);
	}

	int *primero = lista_buscar_elemento(lista, 0);
	lista_destruir(lista);
	lista = NULL;

	pa2m_afirmar(*primero == 0,
		     "Los elementos de la lista siguen siendo accesibles");

	for (size_t i = 0; i < CANT; i++)
		free(elementos[i]);
	free(elementos);
}
void test_lista_destruir_prueba_estres()
{
	const size_t CANT = 1000;
	lista_t *lista = lista_crear();
	int **elementos = malloc(sizeof(int *) * CANT);

	for (size_t i = 0; i < CANT; i++) {
		elementos[i] = malloc(sizeof(int));
		*elementos[i] = i;
		lista_agregar(lista, elementos[i]);
	}

	lista_destruir(lista);
	lista = NULL;

	bool todos_correctos = true;
	for (size_t i = 0; i < CANT; i++) {
		if (*elementos[i] != (int)i) {
			todos_correctos = false;
			break;
		}
	}
	pa2m_afirmar(
		todos_correctos,
		"Prueba de estrés: Los 1000 elementos siguen siendo accesibles y correctos");

	for (size_t i = 0; i < CANT; i++)
		free(elementos[i]);
	free(elementos);
}

void tests_lista_destruir()
{
	test_lista_destruir_verificar_lista_nula();
	test_lista_destruir_elementos_accesibles();
	test_lista_destruir_prueba_estres();
}
//-----------------------
void test_iterador_crear_lista_nula()
{
	lista_iterador_t *it = lista_iterador_crear(NULL);
	pa2m_afirmar(it == NULL, "Crear iterador con lista NULL devuelve NULL");
}
void test_iterador_crear_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(it == NULL,
		     "No se puede crear un iterador de una lista vacía");
	lista_destruir(lista);
}
void test_iterador_crear_lista_con_elementos_no_null()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);

	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(it != NULL,
		     "Se puede crear un iterador de una lista con elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_crear_lista_con_elementos_posicion_inicial()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);

	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador_obtener_actual(it) ==
			     lista_buscar_elemento(lista, 0),
		     "El iterador comienza en el primer nodo");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_crear_lista_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(
		it != NULL,
		"Se puede crear un iterador de una lista de +100000 elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_crear()
{
	test_iterador_crear_lista_nula();
	test_iterador_crear_lista_vacia();
	test_iterador_crear_lista_con_elementos_no_null();
	test_iterador_crear_lista_con_elementos_posicion_inicial();
	test_iterador_crear_lista_prueba_estres();
}
//-----------------------
void test_iterador_hay_mas_elementos_iterador_nulo()
{
	pa2m_afirmar(lista_iterador_hay_mas_elementos(NULL) == false,
		     "Un iterador NULL devuelve false");
}
void test_iterador_hay_mas_elementos_un_elemento_inicio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_hay_mas_elementos(it),
		     "Iterador sobre lista con un elemento tiene elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_hay_mas_elementos_un_elemento_despues_avanzar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_siguiente(it);
	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it),
		     "Después de avanzar ya no hay más elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_hay_mas_elementos_varios_elementos_inicio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10000);
	lista_iterador_t *it = lista_iterador_crear(lista);

	pa2m_afirmar(
		lista_iterador_hay_mas_elementos(it),
		"El iterador sobre lista con varios elementos se crea correctamente");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_hay_mas_elementos_varios_elementos_despues_avanzar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10000);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_siguiente(it);
	pa2m_afirmar(lista_iterador_hay_mas_elementos(it),
		     "El iterador aún tiene más elementos luego de avanzar");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_hay_mas_elementos()
{
	test_iterador_hay_mas_elementos_iterador_nulo();
	test_iterador_hay_mas_elementos_un_elemento_inicio();
	test_iterador_hay_mas_elementos_un_elemento_despues_avanzar();
	test_iterador_hay_mas_elementos_varios_elementos_inicio();
	test_iterador_hay_mas_elementos_varios_elementos_despues_avanzar();
}
//-----------------------
void test_iterador_siguiente_iterador_nulo()
{
	lista_iterador_siguiente(NULL);
	pa2m_afirmar(true, "Avanzar un iterador NULL no rompe el programa");
}
void test_iterador_siguiente_un_elemento_inicio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_obtener_actual(it) ==
			     lista_buscar_elemento(lista, 0),
		     "El iterador comienza en el único elemento");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_siguiente_un_elemento_despues_avanzar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_siguiente(it);
	pa2m_afirmar(lista_iterador_obtener_actual(it) == NULL,
		     "El iterador avanza correctamente devolviendo NULL");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_siguiente_varios_elementos_avanzar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);
	lista_iterador_t *it = lista_iterador_crear(lista);

	for (size_t i = 0; i < 4; i++) {
		lista_iterador_siguiente(it);
	}

	pa2m_afirmar(lista_iterador_hay_mas_elementos(it),
		     "El iterador avanza correctamente con varios elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_siguiente_varios_elementos_final()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);
	lista_iterador_t *it = lista_iterador_crear(lista);

	for (size_t i = 0; i < 6; i++) {
		lista_iterador_siguiente(it);
	}

	pa2m_afirmar(!lista_iterador_hay_mas_elementos(it),
		     "Recorre correctamente todos los elementos");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_siguiente()
{
	test_iterador_siguiente_iterador_nulo();
	test_iterador_siguiente_un_elemento_inicio();
	test_iterador_siguiente_un_elemento_despues_avanzar();
	test_iterador_siguiente_varios_elementos_avanzar();
	test_iterador_siguiente_varios_elementos_final();
}
//-----------------------
void test_iterador_obtener_actual_iterador_nulo()
{
	pa2m_afirmar(lista_iterador_obtener_actual(NULL) == NULL,
		     "Un iterador NULL devuelve NULL");
}
void test_iterador_obtener_actual_primer_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);

	int *num = lista_iterador_obtener_actual(it);
	pa2m_afirmar(*num == 0,
		     "El iterador devuelve correctamente el primer elemento");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_obtener_actual_despues_avanzar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_siguiente(it);
	int *num = lista_iterador_obtener_actual(it);
	pa2m_afirmar(
		*num == 1,
		"Después de avanzar, el iterador devuelve el nuevo elemento");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}
void test_iterador_obtener_actual_final()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_siguiente(it);
	lista_iterador_siguiente(it);
	pa2m_afirmar(lista_iterador_obtener_actual(it) == NULL,
		     "Cuando recorrió toda la lista, devuelve NULL");

	lista_iterador_destruir(it);
	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_obtener_actual()
{
	test_iterador_obtener_actual_iterador_nulo();
	test_iterador_obtener_actual_primer_elemento();
	test_iterador_obtener_actual_despues_avanzar();
	test_iterador_obtener_actual_final();
}
//-----------------------
void test_iterador_destruir_nulo()
{
	lista_iterador_destruir(NULL);
	pa2m_afirmar(true, "Destruir un iterador NULL no produce errores");
}
void test_iterador_destruir_valido()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_destruir(it);
	pa2m_afirmar(true, "Se destruye correctamente un iterador válido");

	lista_destruir_todo(lista, free);
}
void test_iterador_lista_intacta_despues_destruir()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);
	lista_iterador_t *it = lista_iterador_crear(lista);
	lista_iterador_destruir(it);

	pa2m_afirmar(lista_cantidad(lista) == 2,
		     "La lista sigue intacta tras destruir el iterador");

	lista_destruir_todo(lista, free);
}
void test_iterador_destruir_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);
	lista_iterador_t *it = lista_iterador_crear(lista);

	lista_iterador_destruir(it);
	pa2m_afirmar(
		true,
		"Prueba de estres: Se destruye correctamente un iterador con +100000 elementos");

	lista_destruir_todo(lista, free);
}

void tests_lista_iterador_destruir()
{
	test_iterador_destruir_nulo();
	test_iterador_destruir_valido();
	test_iterador_lista_intacta_despues_destruir();
	test_iterador_destruir_estres();
}
// --------------------------------------PILA----------------------------
void test_pila_crear_no_null()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se puede crear una pila");
	pila_destruir(pila);
}
void test_pila_crear_vacia()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "La pila recién creada está vacía");
	pila_destruir(pila);
}

void tests_pila_crear()
{
	test_pila_crear_no_null();
	test_pila_crear_vacia();
}
//-----------------------
void test_pila_apilar_elemento()
{
	pila_t *pila = pila_crear();
	int a = 10;

	pa2m_afirmar(pila_apilar(pila, &a) == true,
		     "Se apilan correctamente los elementos");

	pila_destruir(pila);
}
void test_pila_apilar_aumenta_cantidad()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	pa2m_afirmar(pila_cantidad(pila) == 2,
		     "La pila aumenta su tamaño al apilar");

	pila_destruir(pila);
}
void test_pila_apilar_prueba_estres()
{
	pila_t *pila = pila_crear();

	for (int i = 0; i < 100000; i++) {
		int *num = malloc(sizeof(int));
		*num = i;
		pila_apilar(pila, num);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 100000,
		"Prueba de estrés: Se apilaron correctamente +100000 elementos");

	// Liberamos memoria
	while (pila_cantidad(pila) > 0) {
		int *elem = pila_desapilar(pila);
		free(elem);
	}

	pila_destruir(pila);
}

void tests_pila_apilar()
{
	test_pila_apilar_elemento();
	test_pila_apilar_aumenta_cantidad();
	test_pila_apilar_prueba_estres();
}
//-----------------------
void test_pila_desapilar_devuelve_ultimo()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	void *elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &b,
		     "Desapilar devuelve el último elemento apilado");

	pila_destruir(pila);
}
void test_pila_desapilar_reduce_cantidad()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	pila_desapilar(pila); // desapila b
	pa2m_afirmar(pila_cantidad(pila) == 1,
		     "La pila reduce su tamaño al desapilar");

	pila_destruir(pila);
}
void test_pila_desapilar_en_pila_vacia()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar en pila vacía devuelve NULL");

	pila_destruir(pila);
}

void tests_pila_desapilar()
{
	test_pila_desapilar_devuelve_ultimo();
	test_pila_desapilar_reduce_cantidad();
	test_pila_desapilar_en_pila_vacia();
}
//-----------------------
void test_pila_ver_primero_en_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_ver_primero(pila) == NULL,
		     "Ver primero en pila vacía devuelve NULL");

	pila_destruir(pila);
}
void test_pila_ver_primero_devuelve_ultimo_apilado()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	pa2m_afirmar(pila_ver_primero(pila) == &b,
		     "Ver primero devuelve el último apilado sin desapilar");

	pila_destruir(pila);
}

void tests_pila_ver_primero()
{
	test_pila_ver_primero_en_pila_vacia();
	test_pila_ver_primero_devuelve_ultimo_apilado();
}
//-----------------------
void test_pila_cantidad_inicial_cero()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "Una pila recién creada tiene cantidad 0");

	pila_destruir(pila);
}
void test_pila_cantidad_refleja_elementos_apilados()
{
	pila_t *pila = pila_crear();
	int a = 1, b = 2, c = 3;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);

	pa2m_afirmar(
		pila_cantidad(pila) == 3,
		"La cantidad refleja la cantidad de elementos apilados correctamente");

	pila_destruir(pila);
}

void tests_pila_cantidad()
{
	test_pila_cantidad_inicial_cero();
	test_pila_cantidad_refleja_elementos_apilados();
}
//-----------------------
void test_pila_destruir_con_elementos()
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
}
void test_pila_destruir_sin_errores()
{
	pila_t *pila = pila_crear();
	pila_destruir(pila); // corregido: pila_destruir
	pa2m_afirmar(true, "La pila se destruye sin provocar errores");
}

void tests_pila_destruir()
{
	test_pila_destruir_con_elementos();
	test_pila_destruir_sin_errores();
}
// ---------------------------------------COLA---------------------------
void test_cola_crear_1()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se crea la cola correctamente");
	cola_destruir(cola);
}
void test_cola_crear_2()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "La cola recién creada está vacía");
	cola_destruir(cola);
}

void tests_cola_crear()
{
	test_cola_crear_1();
	test_cola_crear_2();
}
//-----------------------
void test_cola_encolar_elemento_null()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_encolar(cola, NULL) == true,
		     "Se puede encolar un elemento NULL");
	cola_destruir(cola);
}
void test_cola_encolar_elemento_dinamico()
{
	cola_t *cola = cola_crear();
	int *n = malloc(sizeof(int));
	*n = 42;

	pa2m_afirmar(cola_encolar(cola, n) == true,
		     "Se puede encolar un elemento dinámico");

	cola_destruir(cola);
	free(n);
}
void test_cola_cantidad_correcta_despues_de_encolar()
{
	cola_t *cola = cola_crear();
	cola_encolar(cola, NULL);

	int *n = malloc(sizeof(int));
	*n = 42;
	cola_encolar(cola, n);

	pa2m_afirmar(cola_cantidad(cola) == 2,
		     "Cantidad correcta después de encolar");

	cola_destruir(cola);
	free(n);
}
void test_cola_prueba_de_estres()
{
	cola_t *cola = cola_crear();

	for (int i = 0; i < 100000; i++) {
		int *num = malloc(sizeof(int));
		*num = i;
		cola_encolar(cola, num);
	}

	pa2m_afirmar(
		cola_cantidad(cola) == 100000,
		"Prueba de estrés: Se encolaron correctamente +100000 elementos");

	// Liberamos memoria
	while (cola_cantidad(cola) > 0) {
		int *elem = cola_desencolar(cola);
		free(elem);
	}

	cola_destruir(cola);
}

void tests_cola_encolar()
{
	test_cola_encolar_elemento_null();
	test_cola_encolar_elemento_dinamico();
	test_cola_cantidad_correcta_despues_de_encolar();
	test_cola_prueba_de_estres();
}
//-----------------------
void test_cola_desencolar_en_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar en cola vacía devuelve NULL");

	cola_destruir(cola);
}
void test_cola_desencolar_primer_elemento()
{
	cola_t *cola = cola_crear();
	int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
	*n1 = 1;
	*n2 = 2;

	cola_encolar(cola, n1);
	cola_encolar(cola, n2);

	int *desencolado = cola_desencolar(cola);
	pa2m_afirmar(*desencolado == 1,
		     "Se desencola el primer elemento encolado (FIFO)");

	free(desencolado);
	free(n2); // liberamos el que sigue en la cola
	cola_destruir(cola);
}
void test_cola_desencolar_segundo_elemento()
{
	cola_t *cola = cola_crear();
	int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
	*n1 = 1;
	*n2 = 2;

	cola_encolar(cola, n1);
	cola_encolar(cola, n2);

	free(cola_desencolar(cola)); // descarto primero

	int *desencolado = cola_desencolar(cola);
	pa2m_afirmar(*desencolado == 2,
		     "Se desencola el segundo elemento encolado (FIFO)");

	free(desencolado);
	cola_destruir(cola);
}
void test_cola_desencolar_y_quedar_vacia()
{
	cola_t *cola = cola_crear();
	int *n1 = malloc(sizeof(int)), *n2 = malloc(sizeof(int));
	*n1 = 1;
	*n2 = 2;

	cola_encolar(cola, n1);
	cola_encolar(cola, n2);

	free(cola_desencolar(cola));
	free(cola_desencolar(cola));

	pa2m_afirmar(
		cola_cantidad(cola) == 0,
		"La cola queda vacía después de desencolar todos los elementos");

	cola_destruir(cola);
}

void tests_cola_desencolar()
{
	test_cola_desencolar_en_cola_vacia();
	test_cola_desencolar_primer_elemento();
	test_cola_desencolar_segundo_elemento();
	test_cola_desencolar_y_quedar_vacia();
}
//-----------------------
void test_cola_ver_primero_en_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola vacía devuelve NULL");

	cola_destruir(cola);
}
void test_cola_ver_primero_devuelve_primer_elemento()
{
	cola_t *cola = cola_crear();
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

void tests_cola_ver_primero()
{
	test_cola_ver_primero_en_cola_vacia();
	test_cola_ver_primero_devuelve_primer_elemento();
}
//-----------------------
void test_cola_cantidad_inicial_cero()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "Una cola recién creada tiene cantidad 0");

	cola_destruir(cola);
}
void test_cola_cantidad_refleja_elementos_encolados()
{
	cola_t *cola = cola_crear();
	int a = 1, b = 2, c = 3;

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_encolar(cola, &c);

	pa2m_afirmar(
		cola_cantidad(cola) == 3,
		"La cantidad refleja correctamente los elementos encolados");

	cola_destruir(cola);
}

void tests_cola_cantidad()
{
	test_cola_cantidad_inicial_cero();
	test_cola_cantidad_refleja_elementos_encolados();
}
//-----------------------
void test_cola_destruir_con_elementos()
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
}
void test_cola_destruir_sin_errores()
{
	cola_t *cola = cola_crear();
	cola_destruir(cola);

	pa2m_afirmar(true, "La cola se destruye sin provocar errores");
}

void tests_cola_destruir()
{
	test_cola_destruir_con_elementos();
	test_cola_destruir_sin_errores();
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
	tests_lista_buscar_posicion();

	pa2m_nuevo_grupo("lista_buscar_elemento");
	tests_lista_buscar_elemento();

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
