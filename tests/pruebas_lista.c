#include "../pa2m.h"
#include "../src/lista.h"

void agregando_elementos_dinamicos(lista_t *lista, size_t cantidad)
{
	for (size_t i = 0; i < cantidad; i++) {
		int *n = malloc(sizeof(int));
		*n = (int)i;
		if (!lista_agregar(lista, n)) {
			free(n);
			break;
		}
	}
}
int comparador_enteros(const void *a, const void *b)
{
	int x = *(int *)a;
	int y = *(int *)b;
	return x - y;
}

void test_lista_crear_correctamente()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se crea la lista correctamente");
	lista_destruir(lista);
}

void tests_lista_crear()
{
	test_lista_crear_correctamente();
}
//---------------------------------------------------------------------------------------
void test_lista_vacia_devuelve_true_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true,
		     "Si se le pasa una lista vacía devuelve 'true'");
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
	test_lista_vacia_devuelve_true_en_lista_nula();
}
//---------------------------------------------------------------------------------------
void test_lista_cantidad_en_lista_recien_creada()
{
	lista_t *lista = lista_crear();
	size_t cant = lista_cantidad(lista);
	pa2m_afirmar(cant == 0, "Una lista recien creada devuelve cantidad 0");
	lista_destruir(lista);
}
void test_lista_cantidad_en_lista_nula()
{
	size_t cant = lista_cantidad(NULL);
	pa2m_afirmar(cant == 0, "Una lista nula devuelve cantidad 0");
}

void test_lista_cantidad_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10000);

	size_t cant = lista_cantidad(lista);
	pa2m_afirmar(
		cant == 10000,
		"Prueba de estrés: se agregaron 10000 elementos y la cantidad es correcta");

	lista_destruir_todo(lista, free);
}

void tests_lista_cantidad()
{
	test_lista_cantidad_en_lista_recien_creada();
	test_lista_cantidad_en_lista_nula();
	test_lista_cantidad_prueba_estres();
}
//---------------------------------------------------------------------------------------
//ver de poner insertas distintos tipos de datos
void test_lista_agregar_elementos()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 1;

	pa2m_afirmar(lista_agregar(lista, n) == true,
		     "Puedo agregar un elemento en una lista vacía");
	int *n2 = malloc(sizeof(int));
	*n2 = 2;

	pa2m_afirmar(lista_agregar(lista, n2) == true,
		     "Puedo agregar un elemento en una lista con elementos");
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
void test_lista_agregar_elemento_null()
{
	lista_t *lista = lista_crear();

	lista_agregar(lista, NULL);

	pa2m_afirmar(lista_agregar(lista, NULL) == true,
		     "Se puede agregar un elemento NULL");

	lista_destruir_todo(lista, free);
}

void tests_lista_agregar()
{
	test_lista_agregar_en_lista_nula();
	test_lista_agregar_elementos();
	test_lista_agregar_elemento_null();
	test_lista_agregar_prueba_estres();
}
//---------------------------------------------------------------------------------------
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
void test_lista_insertar_elemento_null()
{
	lista_t *lista = lista_crear();

	lista_agregar(lista, NULL);

	pa2m_afirmar(lista_insertar(lista, NULL, 0) == true,
		     "Se puede insertar un elemento NULL");

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
	test_lista_insertar_elemento_null();
	test_lista_insertar_prueba_estres();
}
//---------------------------------------------------------------------------------------
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
void test_lista_eliminar_elemento_posicion_invalida()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);
	pa2m_afirmar(
		lista_eliminar_elemento(lista, 5) == NULL,
		"Tratar de eliminar de una lista una posicion invalida devuelve NULL");
	lista_destruir_todo(lista, free);
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
	test_lista_eliminar_elemento_posicion_invalida();
	test_lista_eliminar_elemento_prueba_estres();
}
//---------------------------------------------------------------------------------------
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
	agregando_elementos_dinamicos(lista, 10);

	pa2m_afirmar(
		lista_buscar_posicion(lista, &num, comparador_enteros) == 5,
		"Devuelve la posición correcta de un elemento existente de la lista");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_posicion_elemento_no_existente()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10);
	int num = 15;

	pa2m_afirmar(lista_buscar_posicion(lista, &num, comparador_enteros) ==
			     -1,
		     "Si no existe el elemento, devuelve -1");

	lista_destruir_todo(lista, free);
}

void test_lista_buscar_posicion_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10001);
	int num = 4000;

	pa2m_afirmar(
		lista_buscar_posicion(lista, &num, comparador_enteros) == 4000,
		"Prueba de estrés: Devuelve la posición correcta del elemento de una lista muy grande +10000");

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
//---------------------------------------------------------------------------------------
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
	agregando_elementos_dinamicos(lista, 100);

	int *elem = lista_buscar_elemento(lista, 56);
	pa2m_afirmar(*elem == 56, "Devuelve el elemento correctamente");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_elemento_fuera_de_rango()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100);

	pa2m_afirmar(lista_buscar_elemento(lista, 1000) == NULL,
		     "Buscar en posición fuera de rango devuelve NULL");

	lista_destruir_todo(lista, free);
}

void test_lista_buscar_elemento_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10000);

	int *elem = lista_buscar_elemento(lista, 5965);
	pa2m_afirmar(
		*elem == 5965,
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
//---------------------------------------------------------------------------------------
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

void tests_lista_con_cada_elemento()
{
	test_lista_con_cada_elemento_lista_nula();
	test_lista_con_cada_elemento_lista_vacia();
	test_lista_con_cada_elemento_funcion_true();
	test_lista_con_cada_elemento_detener_en_valor();
	
}
//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------
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
		*elementos[i] = (int)i;
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
		*elementos[i] = (int)i;
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
//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------
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

//-----------------------------------------------------Tests de Integracion
void test_lista_crear_vacia()
{
	lista_t *lista = lista_crear();
	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == true, "Una lista recién creada está vacía");
	lista_destruir(lista);
}
void test_lista_crear_cantidad_0()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "La lista recien creada tiene cantidad 0");
	lista_destruir(lista);
}
void test_lista_crear_primer_elemento()
{
	lista_t *lista = lista_crear();
	int *n = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(n == NULL,
		     "La lista recién creada no tiene primer elemento");
	lista_destruir(lista);
}
void test_lista_crear_ultimo_elemento()
{
	lista_t *lista = lista_crear();
	int *n = lista_buscar_elemento(lista, lista_cantidad(lista) - 1);
	pa2m_afirmar(n == NULL,
		     "La lista recién creada no tiene ultimo elemento");
	lista_destruir(lista);
}

void tests_de_integracion_lista_crear(){
	test_lista_crear_vacia();
	test_lista_crear_cantidad_0();
	test_lista_crear_primer_elemento();
	test_lista_crear_ultimo_elemento();
}
//---------------------------------------------------------------------------------------
void test_lista_vacia_despues_de_insertar_y_eliminar()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 3);


	bool vacia = lista_vacia(lista);
	pa2m_afirmar(vacia == false,
		     "Si se le pasa una lista con elementos devuelve 'false'");

	int *n = lista_eliminar_elemento(lista, 2);
	int *n2 = lista_eliminar_elemento(lista, 1);
	int *n3 = lista_eliminar_elemento(lista, 0);

	free(n);
	free(n2);
	free(n3);

	bool vacia2 = lista_vacia(lista);
	pa2m_afirmar(
		vacia2 == true,
		"La lista se encuentra vacia luego de agregar y eliminar todos sus elementos");
	lista_destruir(lista);
}
void test_lista_vacia_buscar_elemento()
{
	lista_t *lista = lista_crear();

	// Intentamos buscar un elemento en la lista vacía
	lista_buscar_elemento(lista, 0);

	// Verificamos condición de vacía
	pa2m_afirmar(
		lista_vacia(lista) == true,
		"Luego de buscar en una lista vacia, esta sigue estando vacia");

	int valor = 42;
	lista_agregar(lista, &valor);

	lista_buscar_elemento(lista, 0);

	pa2m_afirmar(
		lista_vacia(lista) == false,
		"Luego de buscar en una lista con elementos, la condicion de vacio es la correcta");
	lista_destruir(lista);
}

void tests_de_integracion_lista_vacia(){
	test_lista_vacia_despues_de_insertar_y_eliminar();
	test_lista_vacia_buscar_elemento();
}
//---------------------------------------------------------------------------------------
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
void test_lista_cantidad_buscar_elemento()
{
	lista_t *lista = lista_crear();
	int valor = 42;

	lista_agregar(lista, &valor);

	// Buscamos el elemento en la posición 0
	lista_buscar_elemento(lista, 0);

	pa2m_afirmar(lista_cantidad(lista) == 1,
		     "La cantidad es correcta luego de buscar un elemento");

	lista_destruir(lista);
}
void test_lista_cantidad_agregando_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	pa2m_afirmar(lista_cantidad(lista) == 1,
		     "La lista aumenta la cantidad despues de agregar");
	lista_destruir_todo(lista, free);
}
void test_lista_cantidad_eliminando_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	int *n = lista_eliminar_elemento(lista, 0);
	free(n);
	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "La lista resta la cantidad despues de eliminar");
	lista_destruir(lista);
}
void test_lista_cantidad_buscar_posicion()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);
	int num = 0;

	lista_buscar_posicion(lista, &num, comparador_enteros);
	pa2m_afirmar(
		lista_cantidad(lista) == 1,
		"La lista tiene la cantidad correcta luego de buscar la posicion de un elemento");
	lista_destruir_todo(lista, free);
}

void tests_de_integracion_lista_cantidad(){
	test_lista_cantidad_despues_de_insertar_y_eliminar();
	test_lista_cantidad_buscar_elemento();
	test_lista_cantidad_agregando_elemento();
	test_lista_cantidad_eliminando_elemento();
	test_lista_cantidad_buscar_posicion();
}
//---------------------------------------------------------------------------------------
void test_lista_agregar_en_lista_vacia_primer_elemento_correcto()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 1;
	lista_agregar(lista, n);

	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(*elem == 1, "Agregar un elemento en lista vacia lo posiciona correctamente en la primera posicion");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_vacia_no_hay_mas_elementos()
{
	lista_t *lista = lista_crear();
	int *n = malloc(sizeof(int));
	*n = 1;
	lista_agregar(lista, n);

	int *elem2 = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(
		elem2 == NULL,
		"No hay más elementos después del agregado en una lista vacía");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos_cantidad_correcta()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_agregar(lista, n2);
	int *n3 = malloc(sizeof(int));
	*n3 = 3;
	lista_agregar(lista, n3);
	int *n4 = malloc(sizeof(int));
	*n4 = 4;
	lista_agregar(lista, n4);

	pa2m_afirmar(lista_cantidad(lista) == 4,
		     "Despues de agregar 4 elementos la cantidad de la lista es 4");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos_ultimo_correcto()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_agregar(lista, n2);

	int *elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(*elem == 2, "El último elemento es el recién agregado");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_agregar(lista, n2);

	int *n3 = malloc(sizeof(int));
	*n3 = 3;

	pa2m_afirmar(lista_agregar(lista, n3) == true,
		     "Puedo agregar un elemento luego de buscar uno");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar_posicion()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_agregar(lista, n2);

	int *n4 = malloc(sizeof(int));
	*n4 = 4;

	pa2m_afirmar(
		lista_agregar(lista, n4) == true,
		"Puedo agregar un elemento luego de buscar la posición de uno");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_en_lista_con_elementos_no_hay_mas_elementos()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_agregar(lista, n2);

	int *n4 = malloc(sizeof(int));
	*n4 = 4;
	lista_agregar(lista, n4);

	int *elem2 = lista_buscar_elemento(lista, 4);

	pa2m_afirmar(
		elem2 == NULL,
		"No hay más elementos después del agregado en una lista con elementos");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_y_eliminar_un_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);

	int *n = lista_eliminar_elemento(lista, 1);
	free(n);
	int *elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(
		elem == NULL,
		"Se puede eliminar correctamente un elemento recién agregado");

	lista_destruir_todo(lista, free);
}
void test_lista_reagregar_despues_de_eliminar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 2);

	int *n = lista_eliminar_elemento(lista, 1);
	free(n);
	agregando_elementos_dinamicos(lista, 1);

	int *elem2 = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(
		*elem2 == 0,
		"Se puede agregar correctamente un elemento luego de eliminar");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_luego_de_insertar_al_inicio()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 0);

	int *n3 = malloc(sizeof(int));
	*n3 = 3;
	pa2m_afirmar(lista_agregar(lista, n3) == true,
		     "Puedo agregar un elemento luego de insertar al inicio");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_luego_de_insertar_por_la_mitad()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 0);

	int *n4 = malloc(sizeof(int));
	*n4 = 4;
	lista_insertar(lista, n4, 1);

	int *n5 = malloc(sizeof(int));
	*n5 = 5;
	pa2m_afirmar(
		lista_agregar(lista, n5) == true,
		"Puedo agregar un elemento luego de insertar por la mitad");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_luego_de_insertar_al_final()
{
	lista_t *lista = lista_crear();

	int *n1 = malloc(sizeof(int));
	*n1 = 1;
	lista_agregar(lista, n1);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 0);

	int *n6 = malloc(sizeof(int));
	*n6 = 6;
	lista_insertar(lista, n6,
		       1); // inserto al final (pos = cantidad actual)

	int *n7 = malloc(sizeof(int));
	*n7 = 7;
	pa2m_afirmar(lista_agregar(lista, n7) == true,
		     "Puedo agregar un elemento luego de insertar al final");

	lista_destruir_todo(lista, free);
}


void tests_de_integracion_lista_agregar(){
	test_lista_agregar_en_lista_vacia_primer_elemento_correcto();
	test_lista_agregar_en_lista_vacia_no_hay_mas_elementos();
	test_lista_agregar_en_lista_con_elementos_cantidad_correcta();
	test_lista_agregar_en_lista_con_elementos_ultimo_correcto();
	test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar();
	test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar_posicion();
	test_lista_agregar_en_lista_con_elementos_no_hay_mas_elementos();
	test_lista_agregar_y_eliminar_un_elemento();
	test_lista_reagregar_despues_de_eliminar();
	test_lista_agregar_luego_de_insertar_al_inicio();
	test_lista_agregar_luego_de_insertar_por_la_mitad();
	test_lista_agregar_luego_de_insertar_al_final();
}
//---------------------------------------------------------------------------------------
void test_lista_insertar_pos0_con_elementos()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);

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
	agregando_elementos_dinamicos(lista, 3);

	int *n6 = malloc(sizeof(int));
	*n6 = 5;
	pa2m_afirmar(lista_insertar(lista, n6, 1) == true,
		     "Puedo insertar en una posición intermedia válida");

	int *elem = lista_buscar_elemento(lista, 1);
	pa2m_afirmar(
		*elem == 5,
		"Se puede buscar el elemento insertado en una posicion intermedia y su valor es el correcto");

	int pos = lista_buscar_posicion(lista, elem, comparador_enteros);
	pa2m_afirmar(
		pos == 1,
		"El elemento insertado en el medio esta en la posicion correcta");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_en_posicion_final()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	int *n6 = malloc(sizeof(int));
	*n6 = 5;
	pa2m_afirmar(lista_insertar(lista, n6, 2) == true,
		     "Puedo insertar en la posicion final");

	int *elem = lista_buscar_elemento(lista, 2);
	pa2m_afirmar(
		*elem == 5,
		"Se puede buscar el elemento insertado al final y su valor es el correcto");

	int pos = lista_buscar_posicion(lista, elem, comparador_enteros);
	pa2m_afirmar(
		pos == 2,
		"El elemento insertado al final esta en la posicion correcta");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_y_eliminar_inicio()
{
	lista_t *lista = lista_crear();

	// Agrego un elemento inicial
	agregando_elementos_dinamicos(lista, 1);

	// Inserto al inicio
	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 0);

	// Destruyo el elemento recién insertado
	int *eliminado = lista_eliminar_elemento(lista, 0);
	pa2m_afirmar(
		*eliminado == 2,
		"Se puede eliminar un elemento recién insertado al inicio");
	free(eliminado);

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_y_eliminar_intermedio()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 5);

	// Inserto elemento intermedio
	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 1);

	int *eliminado = lista_eliminar_elemento(lista, 1);
	pa2m_afirmar(
		*eliminado == 2,
		"Se puede eliminar un elemento recién insertado en posición intermedia");
	free(eliminado);

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_y_eliminar_final()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 5);

	// Inserto al final
	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 4);

	int *eliminado = lista_eliminar_elemento(lista, 4);
	pa2m_afirmar(*eliminado == 2,
		     "Se puede eliminar un elemento recién insertado al final");
	free(eliminado);

	lista_destruir_todo(lista, free);
}
void test_lista_eliminar_y_luego_insertar_inicio()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 2);

	int *el = lista_eliminar_elemento(lista, 0);
	free(el);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 0);
	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(
		*elem == 2,
		"Se puede insertar un elemento luego de eliminar al inicio");

	lista_destruir_todo(lista, free);
}
void test_lista_eliminar_y_luego_insertar_intermedio()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 5);

	int *el = lista_eliminar_elemento(lista, 2);
	free(el);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 2);
	int *elem = lista_buscar_elemento(lista, 2);
	pa2m_afirmar(
		*elem == 2,
		"Se puede insertar un elemento luego de eliminar en la mitad");

	lista_destruir_todo(lista, free);
}
void test_lista_eliminar_y_luego_insertar_final()
{
	lista_t *lista = lista_crear();

	agregando_elementos_dinamicos(lista, 5);

	int *el = lista_eliminar_elemento(lista, 4);
	free(el);

	int *n2 = malloc(sizeof(int));
	*n2 = 2;
	lista_insertar(lista, n2, 3);
	int *elem = lista_buscar_elemento(lista, 3);
	pa2m_afirmar(
		*elem == 2,
		"Se puede insertar un elemento en la ultima posicion luego de eliminar el ultimo");

	lista_destruir_todo(lista, free);
}

void tests_de_integracion_lista_insertar(){
	test_lista_insertar_pos0_con_elementos();
	test_lista_insertar_en_posicion_intermedia();
	test_lista_insertar_en_posicion_final();
	test_lista_insertar_y_eliminar_inicio();
	test_lista_insertar_y_eliminar_intermedio();
	test_lista_insertar_y_eliminar_final();
	test_lista_eliminar_y_luego_insertar_inicio();
	test_lista_eliminar_y_luego_insertar_intermedio();
	test_lista_eliminar_y_luego_insertar_final();
}
//---------------------------------------------------------------------------------------
void test_lista_eliminar_elemento_varios()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	int *elem = lista_eliminar_elemento(lista, 0);
	free(elem);
	elem = lista_eliminar_elemento(lista, 1);
	free(elem);
	elem = lista_eliminar_elemento(lista, 0);
	free(elem);

	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "Se eliminan correctamente varios elementos de una lista");

	lista_destruir(lista);
}
void test_lista_eliminar_unico_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 1);

	int *elem = lista_eliminar_elemento(lista, 0);
	pa2m_afirmar(
		lista_vacia(lista) == true,
		"Si hay un solo elemento se elimina correctamente y deja la lista vacia");
	free(elem);
	lista_destruir(lista);
}
void test_lista_eliminar_ultimo_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	int *elem = lista_eliminar_elemento(lista, 2);

	pa2m_afirmar(*elem == 2 && lista_cantidad(lista) == 2,
		     "Se elimina correctamente el ultimo elemento");

	free(elem);
	lista_destruir_todo(lista, free);
}

void tests_de_integracion_lista_eliminar_elemento(){
	test_lista_eliminar_elemento_varios();
	test_lista_eliminar_unico_elemento();
	test_lista_eliminar_ultimo_elemento();
}
//---------------------------------------------------------------------------------------
void test_lista_buscar_posicion_despues_de_agregar()
{
	lista_t *lista = lista_crear();
	int *num = malloc(sizeof(int));
	*num = 10;
	lista_agregar(lista, num);

	pa2m_afirmar(
		lista_buscar_posicion(lista, num, comparador_enteros) == 0,
		"Devuelve la posición correcta de un elemento recien agregado");
	pa2m_afirmar(
		lista_buscar_posicion(lista, num, comparador_enteros) == 0,
		"Devuelve la posición correcta de una lista con solo 1 elemento");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_posicion_despues_de_insertar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10);
	int *num = malloc(sizeof(int));
	*num = 10;
	lista_insertar(lista, num, 5);

	pa2m_afirmar(
		lista_buscar_posicion(lista, num, comparador_enteros) == 5,
		"Devuelve la posición correcta de un elemento recien insertado");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_posicion_despues_de_eliminar()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);
	int num = 4;

	int *elem = lista_eliminar_elemento(lista, 4);
	free(elem);

	pa2m_afirmar(
		lista_buscar_posicion(lista, &num, comparador_enteros) == -1,
		"Devuelve -1 al buscar la posicion de un elemento recien eliminado");

	lista_destruir_todo(lista, free);
}

void tests_de_integracion_lista_buscar_posicion(){
	test_lista_buscar_posicion_despues_de_agregar();
	test_lista_buscar_posicion_despues_de_insertar();
	test_lista_buscar_posicion_despues_de_eliminar();
}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_buscar_elemento(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_destruir(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_destruir_todo(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_con_cada_elemento(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_iterador_crear(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_iterador_hay_mas_elementos(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_iterador_siguiente(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_iterador_obtener_actual(){}
//---------------------------------------------------------------------------------------
void tests_de_integracion_lista_iterador_destruir(){}

int main()
{
	pa2m_nuevo_grupo("---------Pruebas Unitarias de Lista---------");
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

	pa2m_nuevo_grupo("---------Pruebas de Integracion de Lista---------");
	pa2m_nuevo_grupo("lista_crear");
	tests_de_integracion_lista_crear();

	pa2m_nuevo_grupo("lista_vacia");
	tests_de_integracion_lista_vacia();

	pa2m_nuevo_grupo("lista_cantidad");
	tests_de_integracion_lista_cantidad();

	pa2m_nuevo_grupo("lista_agregar");
	tests_de_integracion_lista_agregar();

	pa2m_nuevo_grupo("lista_insertar");
	tests_de_integracion_lista_insertar();

	pa2m_nuevo_grupo("lista_eliminar_elemento");
	tests_de_integracion_lista_eliminar_elemento();

	pa2m_nuevo_grupo("lista_buscar_posicion");
	tests_de_integracion_lista_buscar_posicion();

	pa2m_nuevo_grupo("lista_buscar_elemento");
	tests_de_integracion_lista_buscar_elemento();

	pa2m_nuevo_grupo("lista_destruir");
	tests_de_integracion_lista_destruir();

	pa2m_nuevo_grupo("lista_destruir_todo");
	tests_de_integracion_lista_destruir_todo();

	pa2m_nuevo_grupo("lista_con_cada_elemento");
	tests_de_integracion_lista_con_cada_elemento();

	pa2m_nuevo_grupo("lista_iterador_crear");
	tests_de_integracion_lista_iterador_crear();

	pa2m_nuevo_grupo("lista_iterador_hay_mas_elementos");
	tests_de_integracion_lista_iterador_hay_mas_elementos();

	pa2m_nuevo_grupo("lista_iterador_siguiente");
	tests_de_integracion_lista_iterador_siguiente();

	pa2m_nuevo_grupo("lista_iterador_obtener_actual");
	tests_de_integracion_lista_iterador_obtener_actual();

	pa2m_nuevo_grupo("lista_iterador_destruir");
	tests_de_integracion_lista_iterador_destruir();

	return pa2m_mostrar_reporte();
}
