#include "../pa2m.h"
#include "../src/pila.h"

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
void test_pila_crear_y_ver()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(
		pila_ver_primero(pila) == NULL,
		"Tratar de ver el primer elemento en una pila recien creada devuelve NULL");
	pila_destruir(pila);
}
void test_pila_crear_y_desapilar()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(
		pila_desapilar(pila) == NULL,
		"Tratar de desapilar en una pila recien creada devuelve NULL");
	pila_destruir(pila);
}
void test_pila_crear_y_destruir()
{
	pila_t *pila = pila_crear();
	pila_destruir(pila);
	pa2m_afirmar(true, "Se puede destruir una pila recien creada");
}

void tests_pila_crear()
{
	test_pila_crear_no_null();
	test_pila_crear_vacia();
	test_pila_crear_y_ver();
	test_pila_crear_y_desapilar();
	test_pila_crear_y_destruir();
}
//-----------------------
void test_pila_apilar_pila_null()
{
	int a = 10;

	pa2m_afirmar(pila_apilar(NULL, &a) == false,
		     "Trtar de apilar con una pila NULL devuelve false");
}
void test_pila_apilar_elemento_pila_vacia()
{
	pila_t *pila = pila_crear();
	int a = 10;

	pa2m_afirmar(
		pila_apilar(pila, &a) == true,
		"Se apilan correctamente los elementos cuando la pila esta vacia");

	pila_destruir(pila);
}
void test_pila_apilar_elemento_pila_con_elementos()
{
	pila_t *pila = pila_crear();
	int a = 10;
	int b = 20;
	pila_apilar(pila, &a);
	pa2m_afirmar(
		pila_apilar(pila, &b) == true,
		"Se apilan correctamente los elementos cuando la pila esta con elementos");

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
void test_pila_apilar_elemento_null()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_apilar(pila, NULL) == true,
		     "Se puede apilar un elemento NULL");
	pila_destruir(pila);
}

void tests_pila_apilar()
{
	test_pila_apilar_pila_null();
	test_pila_apilar_elemento_pila_vacia();
	test_pila_apilar_elemento_pila_con_elementos();
	test_pila_apilar_aumenta_cantidad();
	test_pila_apilar_elemento_null();
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
void test_pila_desapilar_en_pila_null()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_desapilar(NULL) == NULL,
		     "Desapilar en pila NULL devuelve NULL");

	pila_destruir(pila);
}
void test_pila_desapilar_prueba_estres()
{
	pila_t *pila = pila_crear();

	for (int i = 0; i < 10000; i++) {
		int *num = malloc(sizeof(int));
		*num = i;
		pila_apilar(pila, num);
	}

	// Liberamos memoria
	while (pila_cantidad(pila) > 0) {
		int *elem = pila_desapilar(pila);
		free(elem);
	}

	pa2m_afirmar(
		pila_cantidad(pila) == 0,
		"Prueba de estrés: Se desapilaron correctamente +10000 elementos");

	pila_destruir(pila);
}

void tests_pila_desapilar()
{
	test_pila_desapilar_devuelve_ultimo();
	test_pila_desapilar_reduce_cantidad();
	test_pila_desapilar_en_pila_vacia();
	test_pila_desapilar_en_pila_null();
	test_pila_desapilar_prueba_estres();
}
//-----------------------
void test_pila_ver_primero_en_pila_vacia()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_ver_primero(pila) == NULL,
		     "Ver primero en pila vacía devuelve NULL");

	pila_destruir(pila);
}
void test_pila_ver_primero_en_pila_null()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_ver_primero(NULL) == NULL,
		     "Ver primero en pila NULL devuelve NULL");

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
void test_pila_ver_primero_y_cantidad()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_ver_primero(pila);
	pa2m_afirmar(
		pila_cantidad(pila) == 2,
		"Ver primero no modifica la cantidad de elementos en la pila");

	pila_destruir(pila);
}
void test_pila_ver_primero_y_desapilar()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_desapilar(pila);

	pa2m_afirmar(
		pila_ver_primero(pila) == &a,
		"Ver primero funciona correctamente luego de desapilar sin que esta quede vacia");

	pila_destruir(pila);
}

void tests_pila_ver_primero()
{
	test_pila_ver_primero_en_pila_null();
	test_pila_ver_primero_en_pila_vacia();
	test_pila_ver_primero_y_cantidad();
	test_pila_ver_primero_devuelve_ultimo_apilado();
	test_pila_ver_primero_y_desapilar();
}
//-----------------------
void test_pila_cantidad_inicial_cero()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "Una pila recién creada tiene cantidad 0");

	pila_destruir(pila);
}
void test_pila_cantidad_null()
{
	pa2m_afirmar(pila_cantidad(NULL) == 0,
		     "Una pila NULL devuelve cantidad 0");
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
	test_pila_cantidad_null();
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

int main()
{
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

	return pa2m_mostrar_reporte();
}