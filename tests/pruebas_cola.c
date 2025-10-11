#include "../pa2m.h"
#include "../src/cola.h"
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
void test_cola_crear_y_ver()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(
		cola_ver_primero(cola) == NULL,
		"Tratar de ver el primer elemento en una cola recien creada devuelve NULL");
	cola_destruir(cola);
}
void test_cola_crear_y_desencolar()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(
		cola_desencolar(cola) == NULL,
		"Tratar de desencolar en una cola recien creada devuelve NULL");
	cola_destruir(cola);
}
void test_cola_crear_y_destruir()
{
	cola_t *cola = cola_crear();
	cola_destruir(cola);
	pa2m_afirmar(true, "Se puede destruir una cola recien creada");
}

void tests_cola_crear()
{
	test_cola_crear_1();
	test_cola_crear_2();
	test_cola_crear_y_ver();
	test_cola_crear_y_desencolar();
	test_cola_crear_y_destruir();
}
//-----------------------
void test_cola_encolar_elemento_null()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_encolar(cola, NULL) == true,
		     "Se puede encolar un elemento NULL");
	cola_destruir(cola);
}
void test_cola_encolar_null()
{
	pa2m_afirmar(cola_encolar(NULL, NULL) == false,
		     "Encolar con cola NULL devuelve false");
}
void test_cola_encolar_elemento_cola_vacia()
{
	cola_t *cola = cola_crear();
	int a = 10;

	pa2m_afirmar(
		cola_encolar(cola, &a) == true,
		"Se encolan correctamente los elementos cuando la cola esta vacia");

	cola_destruir(cola);
}
void test_cola_encolar_elemento_cola_con_elementos()
{
	cola_t *cola = cola_crear();
	int a = 10;
	int b = 20;
	cola_encolar(cola, &a);
	pa2m_afirmar(
		cola_encolar(cola, &b) == true,
		"Se encolan correctamente los elementos cuando la cola esta con elementos");

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

	pa2m_afirmar(cola_cantidad(cola) == 2, "Encolar aumenta la cantidad");

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
	test_cola_encolar_null();
	test_cola_encolar_elemento_cola_vacia();
	test_cola_encolar_elemento_cola_con_elementos();
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
void test_cola_desencolar_en_cola_null()
{
	pa2m_afirmar(cola_desencolar(NULL) == NULL,
		     "Desencolar en cola NULL devuelve NULL");
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
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "Desencolar reduce la cantidad de elementos de la cola");

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
	test_cola_desencolar_en_cola_null();
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
void test_cola_ver_primero_en_cola_null()
{
	pa2m_afirmar(cola_ver_primero(NULL) == NULL,
		     "Ver primero en cola NULL devuelve NULL");
}
void test_cola_ver_primero_y_cantidad()
{
	cola_t *cola = cola_crear();
	int a = 10, b = 20;

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_ver_primero(cola);

	pa2m_afirmar(
		cola_cantidad(cola) == 2,
		"Ver primero no modifica la cantidad de elementos en la cola");

	cola_destruir(cola);
}
void test_cola_ver_primero_y_desencolar()
{
	cola_t *cola = cola_crear();
	int a = 10, b = 20;

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);
	cola_desencolar(cola);

	pa2m_afirmar(
		cola_ver_primero(cola) == &b,
		"Ver primero funciona correctamente luego de desencolar sin que esta quede vacía");

	cola_destruir(cola);
}

void tests_cola_ver_primero()
{
	test_cola_ver_primero_en_cola_vacia();
	test_cola_ver_primero_devuelve_primer_elemento();
	test_cola_ver_primero_en_cola_null();
	test_cola_ver_primero_y_cantidad();
	test_cola_ver_primero_y_desencolar();
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
void test_cola_cantidad_null()
{
	pa2m_afirmar(cola_cantidad(NULL) == 0,
		     "Una cola NULL devuelve cantidad 0");
}

void tests_cola_cantidad()
{
	test_cola_cantidad_inicial_cero();
	test_cola_cantidad_refleja_elementos_encolados();
	test_cola_cantidad_null();
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