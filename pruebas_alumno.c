#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

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
	if (a == NULL && b == NULL)
		return 0; // ambos NULL → iguales
	if (a == NULL || b == NULL)
		return 1; // uno NULL → distintos
	return (*(int *)a - *(int *)b);
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

void tests_lista_cantidad()
{
	test_lista_cantidad_en_lista_recien_creada();
	test_lista_cantidad_en_lista_nula();
}
//---------------------------------------------------------------------------------------
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
void test_lista_agregar_elemento_null()
{
	lista_t *lista = lista_crear();

	lista_agregar(lista, NULL);

	pa2m_afirmar(lista_agregar(lista, NULL) == true,
		     "Se puede agregar un elemento NULL");

	lista_destruir_todo(lista, free);
}
void test_lista_agregar_acepta_diferentes_tipos_de_datos()
{
	lista_t *lista = lista_crear();

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	pa2m_afirmar(lista_agregar(lista, &entero) == true,
		     "lista_agregar permite agregar un entero");
	pa2m_afirmar(lista_agregar(lista, texto) == true,
		     "lista_agregar permite agregar un string");
	pa2m_afirmar(lista_agregar(lista, &decimal) == true,
		     "lista_agregar permite agregar un double");
	pa2m_afirmar(lista_agregar(lista, vector) == true,
		     "lista_agregar permite agregar un vector");
	pa2m_afirmar(lista_agregar(lista, &p) == true,
		     "lista_agregar permite agregar un struct");

	lista_destruir_todo(lista, NULL);
}
void test_lista_agregar_permite_agregar_el_mismo_dato_dos_veces()
{
	lista_t *lista = lista_crear();

	int valor = 42;

	bool resultado1 = lista_agregar(lista, &valor);
	bool resultado2 = lista_agregar(lista, &valor);

	pa2m_afirmar(resultado1 == true && resultado2 == true,
		     "lista_agregar permite agregar dos veces el mismo dato");

	lista_destruir_todo(lista, NULL);
}

void tests_lista_agregar()
{
	test_lista_agregar_en_lista_nula();
	test_lista_agregar_elementos();
	test_lista_agregar_elemento_null();
	test_lista_agregar_acepta_diferentes_tipos_de_datos();
	test_lista_agregar_permite_agregar_el_mismo_dato_dos_veces();
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

void tests_lista_insertar()
{
	test_lista_insertar_en_lista_nula();
	test_lista_insertar_en_lista_vacia_pos0();
	test_lista_insertar_posicion_invalida();
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

void tests_lista_eliminar_elemento()
{
	test_lista_eliminar_elemento_lista_nula();
	test_lista_eliminar_elemento_lista_vacia();
	test_lista_eliminar_elemento_posicion_invalida();
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

void tests_lista_buscar_posicion()
{
	test_lista_buscar_posicion_lista_nula();
	test_lista_buscar_posicion_lista_vacia();
	test_lista_buscar_posicion_sin_comparador();
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

void tests_lista_buscar_elemento()
{
	test_lista_buscar_elemento_lista_nula();
	test_lista_buscar_elemento_lista_vacia();
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

void tests_lista_con_cada_elemento()
{
	test_lista_con_cada_elemento_lista_nula();
	test_lista_con_cada_elemento_lista_vacia();
}
//---------------------------------------------------------------------------------------
size_t contador_destructor = 0;
void mi_destructor(void *dato)
{
	free(dato);
	contador_destructor++;
}

void test_lista_destruir_todo_abb_null()
{
	lista_destruir_todo(NULL, mi_destructor);
	pa2m_afirmar(true, "Pasarle abb NULL no genera crush");
}
void test_lista_destruir_todo_comparador_null()
{
	lista_t *lista = lista_crear();

	lista_destruir_todo(lista, NULL);
	pa2m_afirmar(true, "Pasarle comparador NULL no genera crush");
}

void tests_lista_destruir_todo()
{
	test_lista_destruir_todo_abb_null();
	test_lista_destruir_todo_comparador_null();
}
//---------------------------------------------------------------------------------------
void test_lista_destruir_abb_null()
{
	lista_destruir(NULL);
	pa2m_afirmar(true, "Pasarle abb NULL no genera crush");
}
void test_lista_destruir_abb_correctamente()
{
	lista_t *lista = lista_crear();
	lista_destruir(lista);
	pa2m_afirmar(true, "Destruye correctamente un abb vacio");
}

void tests_lista_destruir()
{
	test_lista_destruir_abb_null();
	test_lista_destruir_abb_correctamente();
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

void tests_lista_iterador_crear()
{
	test_iterador_crear_lista_nula();
	test_iterador_crear_lista_vacia();
}
//---------------------------------------------------------------------------------------
void test_iterador_hay_mas_elementos_iterador_nulo()
{
	pa2m_afirmar(lista_iterador_hay_mas_elementos(NULL) == false,
		     "Un iterador NULL devuelve false");
}

void tests_lista_iterador_hay_mas_elementos()
{
	test_iterador_hay_mas_elementos_iterador_nulo();
}
//---------------------------------------------------------------------------------------
void test_iterador_siguiente_iterador_nulo()
{
	lista_iterador_siguiente(NULL);
	pa2m_afirmar(true, "Avanzar un iterador NULL no rompe el programa");
}

void tests_lista_iterador_siguiente()
{
	test_iterador_siguiente_iterador_nulo();
}
//---------------------------------------------------------------------------------------
void test_iterador_obtener_actual_iterador_nulo()
{
	pa2m_afirmar(lista_iterador_obtener_actual(NULL) == NULL,
		     "Un iterador NULL devuelve NULL");
}

void tests_lista_iterador_obtener_actual()
{
	test_iterador_obtener_actual_iterador_nulo();
}
//---------------------------------------------------------------------------------------
void test_iterador_destruir_nulo()
{
	lista_iterador_destruir(NULL);
	pa2m_afirmar(true, "Destruir un iterador NULL no produce errores");
}

void tests_lista_iterador_destruir()
{
	test_iterador_destruir_nulo();
}

//---------------------------------------------------------------------------------------------------Tests de Integracion
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

void tests_de_integracion_lista_crear()
{
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
		"La lista se encuentra vacia luego de eliminar todos sus elementos");
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
void test_lista_vacia_integracion_despues_de_agregar()
{
	lista_t *lista = lista_crear();
	int valor = 10;

	lista_agregar(lista, &valor);

	pa2m_afirmar(
		!lista_vacia(lista),
		"Una lista deja de estar vacía después de agregar un elemento");

	lista_destruir(lista);
}
void test_integracion_lista_buscar_posicion_y_vacia()
{
	lista_t *lista = lista_crear();

	lista_buscar_posicion(lista, NULL, comparador_enteros);

	// La lista sigue vacía después de la búsqueda
	pa2m_afirmar(
		lista_vacia(lista),
		"Lista sigue vacía después de buscar posición en lista vacía");

	// Agregar un elemento
	int valor = 42;
	lista_agregar(lista, &valor);

	// Buscar la posición 0 ahora devuelve el elemento agregado

	lista_buscar_posicion(lista, &valor, comparador_enteros);

	// La lista ya no está vacía
	pa2m_afirmar(
		!lista_vacia(lista),
		"Ver la condicion de vacio de una lista con elementos devuelve correctamante su condicion luego de buscar posicion");

	lista_destruir_todo(lista, NULL);
}

void tests_de_integracion_lista_vacia()
{
	test_lista_vacia_integracion_despues_de_agregar();
	test_lista_vacia_despues_de_insertar_y_eliminar();
	test_lista_vacia_buscar_elemento();
	test_integracion_lista_buscar_posicion_y_vacia();
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

void tests_de_integracion_lista_cantidad()
{
	test_lista_cantidad_agregando_elemento();
	test_lista_cantidad_eliminando_elemento();
	test_lista_cantidad_despues_de_insertar_y_eliminar();
	test_lista_cantidad_buscar_elemento();
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
	pa2m_afirmar(
		*elem == 1,
		"Agregar un elemento en lista vacia lo posiciona correctamente en la primera posicion");

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

	pa2m_afirmar(
		lista_cantidad(lista) == 4,
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

void tests_de_integracion_lista_agregar()
{
	test_lista_agregar_en_lista_vacia_primer_elemento_correcto();
	test_lista_agregar_en_lista_vacia_no_hay_mas_elementos();
	test_lista_agregar_en_lista_con_elementos_cantidad_correcta();
	test_lista_agregar_en_lista_con_elementos_ultimo_correcto();
	test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar();
	test_lista_agregar_en_lista_con_elementos_agregar_luego_de_buscar_posicion();
	test_lista_agregar_en_lista_con_elementos_no_hay_mas_elementos();
	test_lista_reagregar_despues_de_eliminar();
	test_lista_agregar_luego_de_insertar_al_inicio();
	test_lista_agregar_luego_de_insertar_por_la_mitad();
	test_lista_agregar_luego_de_insertar_al_final();
}
//---------------------------------------------------------------------------------------
void test_lista_insertar_elemento_null()
{
	lista_t *lista = lista_crear();

	lista_agregar(lista, NULL);

	pa2m_afirmar(lista_insertar(lista, NULL, 0) == true,
		     "Se puede insertar un elemento NULL");

	lista_destruir_todo(lista, free);
}
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
	*n2 = 6;
	lista_insertar(lista, n2, 3);
	int *elem = lista_buscar_elemento(lista, 3);
	pa2m_afirmar(
		*elem == 6,
		"Se puede insertar un elemento en la ultima posicion luego de eliminar el ultimo");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_posicion_inicio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	lista_buscar_posicion(lista, lista_buscar_elemento(lista, 0),
			      comparador_enteros);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 100;
	lista_insertar(lista, nuevo, 0);

	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(
		*elem == 100,
		"Se puede insertar un elemento al inicio luego de buscar la posición de un elemento");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_posicion_intermedio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);

	lista_buscar_posicion(lista, lista_buscar_elemento(lista, 2),
			      comparador_enteros);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 200;
	lista_insertar(lista, nuevo, 2);

	int *elem = lista_buscar_elemento(lista, 2);
	pa2m_afirmar(
		*elem == 200,
		"Se puede insertar un elemento en el medio luego de buscar la posición de un elemento");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_posicion_final()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);

	lista_buscar_posicion(lista, lista_buscar_elemento(lista, 4),
			      comparador_enteros);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 300;

	lista_insertar(lista, nuevo, 4);

	int *elem = lista_buscar_elemento(lista, 4);

	pa2m_afirmar(
		*elem == 300,
		"Se puede insertar un elemento al final luego de buscar la posición de un elemento");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_elemento_inicio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 3);

	lista_buscar_elemento(lista, 0);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 101;
	lista_insertar(lista, nuevo, 0);

	int *elem = lista_buscar_elemento(lista, 0);
	pa2m_afirmar(
		*elem == 101,
		"Se puede insertar un elemento al inicio luego de buscar un elemento");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_elemento_intermedio()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);

	lista_buscar_elemento(lista, 2);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 201;
	lista_insertar(lista, nuevo, 2);

	int *elem = lista_buscar_elemento(lista, 2);
	pa2m_afirmar(
		*elem == 201,
		"Se puede insertar un elemento en el medio luego de buscar un elemento");

	lista_destruir_todo(lista, free);
}
void test_insertar_despues_de_buscar_elemento_final()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5);

	lista_buscar_elemento(lista, 4);

	int *nuevo = malloc(sizeof(int));
	*nuevo = 301;
	lista_insertar(lista, nuevo, 4);

	int *elem = lista_buscar_elemento(lista, 4);
	pa2m_afirmar(
		*elem == 301,
		"Se puede insertar un elemento al final luego de buscar un elemento");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_dos_veces_mismo_dato()
{
	lista_t *lista = lista_crear();

	int *elem1 = malloc(sizeof(int));
	*elem1 = 50;
	int *elem2 = malloc(sizeof(int));
	*elem2 = 50;

	agregando_elementos_dinamicos(lista, 2);
	lista_insertar(lista, elem1, 0);
	lista_insertar(lista, elem2, 1); // insertar el mismo puntero otra vez

	int *resultado1 = lista_buscar_elemento(lista, 0);
	int *resultado2 = lista_buscar_elemento(lista, 1);

	pa2m_afirmar(*resultado1 == 50 && *resultado2 == 50,
		     "Se puede insertar dos veces el mismo elemento");

	lista_destruir_todo(lista, free);
}
void test_lista_insertar_acepta_diferentes_tipos_de_datos()
{
	lista_t *lista = lista_crear();

	// Primero agregamos un elemento base (ya que insertar requiere que exista la lista)
	int base = 0;
	lista_agregar(lista, &base);

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	pa2m_afirmar(lista_insertar(lista, &entero, 0) == true,
		     "Se permite insertar un entero");
	pa2m_afirmar(lista_insertar(lista, texto, 1) == true,
		     "Se permite insertar un string");
	pa2m_afirmar(lista_insertar(lista, &decimal, 2) == true,
		     "Se permite insertar un double");
	pa2m_afirmar(lista_insertar(lista, vector, 3) == true,
		     "Se permite insertar un vector");
	pa2m_afirmar(lista_insertar(lista, &p, 4) == true,
		     "Se permite insertar un struct");

	lista_destruir_todo(lista, NULL);
}

void tests_de_integracion_lista_insertar()
{
	test_lista_insertar_elemento_null();
	test_lista_insertar_pos0_con_elementos();
	test_lista_insertar_en_posicion_intermedia();
	test_lista_insertar_en_posicion_final();
	test_lista_insertar_y_eliminar_inicio();
	test_lista_insertar_y_eliminar_intermedio();
	test_lista_insertar_y_eliminar_final();
	test_lista_eliminar_y_luego_insertar_inicio();
	test_lista_eliminar_y_luego_insertar_intermedio();
	test_lista_eliminar_y_luego_insertar_final();
	test_insertar_despues_de_buscar_posicion_inicio();
	test_insertar_despues_de_buscar_posicion_intermedio();
	test_insertar_despues_de_buscar_posicion_final();
	test_insertar_despues_de_buscar_elemento_inicio();
	test_insertar_despues_de_buscar_elemento_intermedio();
	test_insertar_despues_de_buscar_elemento_final();
	test_lista_insertar_dos_veces_mismo_dato();
	test_lista_insertar_acepta_diferentes_tipos_de_datos();
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
void test_lista_eliminar_elimina_diferentes_tipos_de_datos()
{
	lista_t *lista = lista_crear();

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	lista_agregar(lista, &entero);
	lista_agregar(lista, texto);
	lista_agregar(lista, &decimal);
	lista_agregar(lista, vector);
	lista_agregar(lista, &p);

	void *eliminado1 = lista_eliminar_elemento(lista, 0);
	void *eliminado2 = lista_eliminar_elemento(lista, 0);
	void *eliminado3 = lista_eliminar_elemento(lista, 0);
	void *eliminado4 = lista_eliminar_elemento(lista, 0);
	void *eliminado5 = lista_eliminar_elemento(lista, 0);

	pa2m_afirmar(eliminado1 == &entero,
		     "Devuelve y elimina correctamente un entero");
	pa2m_afirmar(eliminado2 == texto,
		     "Devuelve y elimina correctamente un string");
	pa2m_afirmar(eliminado3 == &decimal,
		     "Devuelve y elimina correctamente un double");
	pa2m_afirmar(eliminado4 == vector,
		     "Devuelve y elimina correctamente un vector");
	pa2m_afirmar(eliminado5 == &p,
		     "Devuelve y elimina correctamente un struct");

	lista_destruir_todo(lista, NULL);
}
void test_lista_eliminar_elemento_null()
{
	lista_t *lista = lista_crear();

	int *a = malloc(sizeof(int));
	*a = 10;

	lista_agregar(lista, a);
	lista_agregar(lista, NULL);

	void *eliminado = lista_eliminar_elemento(lista, 1);

	pa2m_afirmar(eliminado == NULL,
		     "Se puede eliminar correctamente un elemento NULL");

	lista_destruir_todo(lista, free);
}
void test_lista_eliminar_elemento_repetido()
{
	lista_t *lista = lista_crear();

	int *x1 = malloc(sizeof(int));
	int *x2 = malloc(sizeof(int));
	int *y = malloc(sizeof(int));
	*x1 = 42;
	*x2 = 42;
	*y = 99;

	lista_agregar(lista, x1);
	lista_agregar(lista, x2);
	lista_agregar(lista, y);

	void *eliminado1 = lista_eliminar_elemento(lista, 0);
	void *eliminado2 = lista_eliminar_elemento(lista, 0);

	pa2m_afirmar(*(int *)eliminado1 == 42 && *(int *)eliminado2 == 42,
		     "Elimina correctamente elementos con valores repetidos");

	free(eliminado1);
	free(eliminado2);
	lista_destruir_todo(lista, free);
}
void test_lista_eliminar_funciona_despues_de_buscar_por_elemento_y_pos()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;

	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	lista_buscar_elemento(lista, 2);

	size_t pos_c = lista_buscar_posicion(lista, &c, comparador_enteros);
	pa2m_afirmar(
		*(int *)lista_eliminar_elemento(lista, pos_c) == 30,
		"Se puede eliminar correctamente después de buscar por elemento y por posicion");

	lista_destruir_todo(lista, NULL);
}
void test_lista_eliminar_funciona_despues_de_insertar()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30, nuevo = 99;

	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	lista_insertar(lista, &nuevo, 0);
	pa2m_afirmar(
		*(int *)lista_eliminar_elemento(lista, 0) == 99,
		"Se puede eliminar correctamente después de insertar un nuevo elemento");

	lista_destruir_todo(lista, NULL);
}

void tests_de_integracion_lista_eliminar_elemento()
{
	test_lista_eliminar_elemento_varios();
	test_lista_eliminar_unico_elemento();
	test_lista_eliminar_ultimo_elemento();
	test_lista_agregar_y_eliminar_un_elemento();
	test_lista_eliminar_elimina_diferentes_tipos_de_datos();
	test_lista_eliminar_elemento_null();
	test_lista_eliminar_elemento_repetido();
	test_lista_eliminar_funciona_despues_de_buscar_por_elemento_y_pos();
	test_lista_eliminar_funciona_despues_de_insertar();
}
//---------------------------------------------------------------------------------------
void test_lista_buscar_posicion_despues_de_agregar()
{
	lista_t *lista = lista_crear();

	int *num = malloc(sizeof(int));
	*num = 10;

	lista_agregar(lista, num);
	int pos = lista_buscar_posicion(lista, num, comparador_enteros);

	pa2m_afirmar(
		pos == 0,
		"Devuelve la posición correcta de un elemento recien agregado");
	pa2m_afirmar(
		pos == 0,
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
	int pos = lista_buscar_posicion(lista, num, comparador_enteros);
	pa2m_afirmar(
		pos == 5,
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
void test_lista_buscar_posicion_elemento_null_en_lista()
{
	lista_t *lista = lista_crear();

	int a = 10;
	int b = 20;

	lista_agregar(lista, &a);
	lista_agregar(lista, NULL);
	lista_agregar(lista, &b);

	int pos = lista_buscar_posicion(lista, NULL, comparador_enteros);

	pa2m_afirmar(
		pos == 1,
		"Se puede buscar y encontrar correctamente un elemento NULL en la lista");

	lista_destruir(lista);
}

void tests_de_integracion_lista_buscar_posicion()
{
	test_lista_buscar_posicion_despues_de_agregar();
	test_lista_buscar_posicion_despues_de_insertar();
	test_lista_buscar_posicion_despues_de_eliminar();
	test_lista_buscar_posicion_elemento_existente();
	test_lista_buscar_posicion_elemento_no_existente();
	test_lista_buscar_posicion_elemento_null_en_lista();
}
//---------------------------------------------------------------------------------------
void test_lista_buscar_elemento_agregado()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100);

	int *elem = lista_buscar_elemento(lista, 56);
	pa2m_afirmar(
		*elem == 56,
		"Buscar un elemento recien agregado lo devuelve correctamente");
	pa2m_afirmar(
		*elem == 56,
		"Busca correctamente un elemento en una lista con varios elementos");
	lista_destruir_todo(lista, free);
}
void test_lista_buscar_elemento_fuera_de_rango()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100);

	pa2m_afirmar(lista_buscar_elemento(lista, 1000) == NULL,
		     "Buscar en un posición fuera de rango devuelve NULL");

	lista_destruir_todo(lista, free);
}
void test_lista_buscar_elemento_null()
{
	lista_t *lista = lista_crear();

	int a = 10;
	lista_agregar(lista, &a);
	lista_agregar(lista, NULL);
	int b = 20;
	lista_agregar(lista, &b);

	void *elem = lista_buscar_elemento(lista, 1);

	pa2m_afirmar(
		elem == NULL,
		"Se puede buscar y encontrar correctamente un elemento NULL en la lista");

	lista_destruir(lista);
}
void test_lista_buscar_elemento_repetido()
{
	lista_t *lista = lista_crear();

	int x1 = 42;
	int x2 = 42;

	lista_agregar(lista, &x1);
	lista_agregar(lista, &x2);

	void *elem1 = lista_buscar_elemento(lista, 0);
	void *elem2 = lista_buscar_elemento(lista, 1);

	pa2m_afirmar(
		elem1 == &x1 && elem2 == &x2,
		"Se puede buscar correctamente dos elementos con el mismo valor");

	lista_destruir(lista);
}
void test_lista_buscar_elemento_recien_insertado()
{
	lista_t *lista = lista_crear();
	int a = 10;
	lista_agregar(lista, &a);

	int nuevo = 99;
	lista_insertar(lista, &nuevo, 0);

	void *elem = lista_buscar_elemento(lista, 0);

	pa2m_afirmar(
		elem == &nuevo,
		"Se puede buscar un elemento recién insertado correctamente");

	lista_destruir(lista);
}
void test_lista_buscar_elemento_usando_posicion()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;

	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	size_t pos_b = lista_buscar_posicion(lista, &b, comparador_enteros);
	void *elem = lista_buscar_elemento(lista, pos_b);

	pa2m_afirmar(
		elem == &b,
		"Se puede encontrar un elemento correctamente pasándole su posición con lista_buscar_posicion");

	lista_destruir(lista);
}
void test_lista_buscar_elemento_varios_tipos()
{
	lista_t *lista = lista_crear();

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	// Agrego todos los elementos
	lista_agregar(lista, &entero);
	lista_agregar(lista, texto);
	lista_agregar(lista, &decimal);
	lista_agregar(lista, vector);
	lista_agregar(lista, &p);
	lista_agregar(lista, NULL);

	// Busco cada elemento por posición y comparo puntero
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == &entero,
		     "Se puede buscar un int");
	pa2m_afirmar(lista_buscar_elemento(lista, 1) == texto,
		     "Se puede buscar un string");
	pa2m_afirmar(lista_buscar_elemento(lista, 2) == &decimal,
		     "Se puede buscar un double");
	pa2m_afirmar(lista_buscar_elemento(lista, 3) == vector,
		     "Se puede buscar un vector");
	pa2m_afirmar(lista_buscar_elemento(lista, 4) == &p,
		     "Se puede buscar un struct");
	pa2m_afirmar(lista_buscar_elemento(lista, 5) == NULL,
		     "Se puede buscar un elemento NULL");

	lista_destruir(lista);
}

void tests_de_integracion_lista_buscar_elemento()
{
	test_lista_buscar_elemento_agregado();
	test_lista_buscar_elemento_fuera_de_rango();
	test_lista_buscar_elemento_null();
	test_lista_buscar_elemento_repetido();
	test_lista_buscar_elemento_recien_insertado();
	test_lista_buscar_elemento_usando_posicion();
	test_lista_buscar_elemento_varios_tipos();
}
//---------------------------------------------------------------------------------------
void test_lista_destruir_elementos_dinamicos_accesibles()
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

	pa2m_afirmar(
		*primero == 0,
		"Al destruir los elementos dinamicos de la lista siguen siendo accesibles");

	for (size_t i = 0; i < CANT; i++)
		free(elementos[i]);
	free(elementos);
}
void test_lista_destruir_verificar_destruccion_con_elementos()
{
	lista_t *lista = lista_crear();
	int *elem = malloc(sizeof(int));
	*elem = 42;
	lista_agregar(lista, elem);

	lista_destruir(lista);
	lista = NULL;

	pa2m_afirmar(lista == NULL,
		     "La lista con elementos fue destruida correctamente");

	free(elem);
}

void tests_de_integracion_lista_destruir()
{
	test_lista_destruir_elementos_dinamicos_accesibles();
	test_lista_destruir_verificar_destruccion_con_elementos();
}
//---------------------------------------------------------------------------------------
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

void tests_de_integracion_lista_destruir_todo()
{
	test_lista_destruir_todo_lista_con_elementos();
}
//---------------------------------------------------------------------------------------
void test_lista_con_cada_elemento_funcion_true()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 10);

	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(lista, sumar_10, &acumulador);

	pa2m_afirmar(
		procesados == 10,
		"Se devuelve correctamente la cantidad de elementos procesados cuando la funcion devuelve siempre true");
	pa2m_afirmar(
		procesados == 10,
		"Iterador interno recorre correctamente despues de agregar");
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
		"Funcion detener_en_5:La iteración se detiene correctamente al momento que la funcion devuelve false");

	lista_destruir_todo(lista, free);
}
void test_lista_con_cada_elemento_funcion_nula()
{
	lista_t *lista = lista_crear();
	long long int acumulador = 0;
	agregando_elementos_dinamicos(lista, 2);

	size_t procesados = lista_con_cada_elemento(lista, NULL, &acumulador);
	pa2m_afirmar(procesados == 0,
		     "Si se le pasa funcion NULL, no procesa elementos");

	lista_destruir_todo(lista, free);
}
void test_iterador_interno_despues_de_eliminar()
{
	lista_t *lista = lista_crear();
	int nums[5] = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < 5; i++)
		lista_agregar(lista, &nums[i]);

	lista_eliminar_elemento(lista, 0);
	lista_eliminar_elemento(lista, 1);
	lista_eliminar_elemento(lista, 2);

	long long int suma = 0;
	lista_con_cada_elemento(lista, sumar_10, &suma);

	// Deben quedar 2 y 4
	pa2m_afirmar(
		suma == 6,
		"Iterador interno recorre correctamente los elementos restantes después de eliminar");

	lista_destruir(lista);
}
void test_iterador_interno_despues_de_insertar()
{
	lista_t *lista = lista_crear();
	int nums[3] = { 1, 2, 3 };
	int a = 10, b = 20;

	for (int i = 0; i < 3; i++)
		lista_agregar(lista, &nums[i]);

	// Inserciones en distintas posiciones
	lista_insertar(lista, &a, 0); // inicio
	lista_insertar(lista, &b, 2); // medio

	long long int suma = 0;
	lista_con_cada_elemento(lista, sumar_10, &suma);

	// Elementos en orden: 10,1,20,2,3
	pa2m_afirmar(
		suma == 36,
		"Iterador interno recorre correctamente después de insertar elementos");

	lista_destruir(lista);
}

void tests_de_integracion_lista_con_cada_elemento()
{
	test_lista_con_cada_elemento_funcion_true();
	test_lista_con_cada_elemento_detener_en_valor();
	test_lista_con_cada_elemento_funcion_nula();
	test_iterador_interno_despues_de_eliminar();
	test_iterador_interno_despues_de_insertar();
}
//---------------------------------------------------------------------------------------
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

void tests_de_integracion_lista_iterador_crear()
{
	test_iterador_crear_lista_con_elementos_no_null();
	test_iterador_crear_lista_con_elementos_posicion_inicial();
}
//---------------------------------------------------------------------------------------
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

void tests_de_integracion_lista_iterador_hay_mas_elementos()
{
	test_iterador_hay_mas_elementos_un_elemento_inicio();
	test_iterador_hay_mas_elementos_un_elemento_despues_avanzar();
	test_iterador_hay_mas_elementos_varios_elementos_inicio();
	test_iterador_hay_mas_elementos_varios_elementos_despues_avanzar();
}
//---------------------------------------------------------------------------------------
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
	pa2m_afirmar(
		lista_iterador_obtener_actual(it) == NULL,
		"El iterador avanza correctamente devolviendo NULL cuando se queda sin elementos");

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

void tests_de_integracion_lista_iterador_siguiente()
{
	test_iterador_siguiente_un_elemento_inicio();
	test_iterador_siguiente_un_elemento_despues_avanzar();
	test_iterador_siguiente_varios_elementos_avanzar();
	test_iterador_siguiente_varios_elementos_final();
}
//---------------------------------------------------------------------------------------
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

void tests_de_integracion_lista_iterador_obtener_actual()
{
	test_iterador_obtener_actual_primer_elemento();
	test_iterador_obtener_actual_despues_avanzar();
	test_iterador_obtener_actual_final();
}
//---------------------------------------------------------------------------------------
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

void tests_de_integracion_lista_iterador_destruir()
{
	test_iterador_destruir_valido();
	test_iterador_lista_intacta_despues_destruir();
}
//-------------------------------------------------------------------------------------------------------Tests de estres
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

void tests_de_estres_lista_cantidad()
{
	test_lista_cantidad_prueba_estres();
}
//---------------------------------------------------------------------------------------
void test_lista_agregar_prueba_estres()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 100000);

	pa2m_afirmar(lista_cantidad(lista) == 100000,
		     "Prueba de estrés: Se pudieron agregar +100000 elementos");

	lista_destruir_todo(lista, free);
}

void tests_de_estres_lista_agregar()
{
	test_lista_agregar_prueba_estres();
}
//---------------------------------------------------------------------------------------
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

void tests_de_estres_lista_insertar()
{
	test_lista_insertar_prueba_estres();
}
//---------------------------------------------------------------------------------------
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

void tests_de_estres_lista_eliminar()
{
	test_lista_eliminar_elemento_prueba_estres();
}
//---------------------------------------------------------------------------------------
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

void tests_de_estres_lista_buscar_posicion()
{
	test_lista_buscar_posicion_prueba_estres();
}
//---------------------------------------------------------------------------------------
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

void tests_de_estres_lista_buscar_elemento()
{
	test_lista_eliminar_elemento_prueba_estres();
}
//---------------------------------------------------------------------------------------
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

void tests_de_estres_lista_destruir_elemento()
{
	test_lista_destruir_prueba_estres();
}
//---------------------------------------------------------------------------------------
void test_de_estres_lista_con_cada_elemento()
{
	lista_t *lista = lista_crear();
	agregando_elementos_dinamicos(lista, 5000);

	long long int acumulador = 0;
	size_t procesados =
		lista_con_cada_elemento(lista, sumar_10, &acumulador);

	pa2m_afirmar(
		procesados == 5000,
		"Prueba estres:Se devuelve correctamente la cantidad de elementos procesados cuando la funcion devuelve siempre true (+5000 elementos)");

	size_t procesados2 = lista_con_cada_elemento(lista, detener_en_5, NULL);
	pa2m_afirmar(
		procesados2 == 6,
		"Prueba estres:La iteración se detiene correctamente al momento que la funcion devuelve false (+5000 elementos)");

	lista_destruir_todo(lista, free);
}

void tests_de_estres_lista_con_cada_elemento()
{
	test_de_estres_lista_con_cada_elemento();
}
//---------------------------------------------------------------------------------------

void pruebas_lista()
{
	pa2m_nuevo_grupo("---------Pruebas Unitarias Lista---------");
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

	pa2m_nuevo_grupo("---------Pruebas de Integracion Lista---------");
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

	pa2m_nuevo_grupo("---------Pruebas de Estres Lista---------");
	pa2m_nuevo_grupo("lista_cantidad");
	tests_de_estres_lista_cantidad();

	pa2m_nuevo_grupo("lista_agregar");
	tests_de_estres_lista_agregar();

	pa2m_nuevo_grupo("lista_insertar");
	tests_de_estres_lista_insertar();

	pa2m_nuevo_grupo("lista_eliminar");
	tests_de_estres_lista_eliminar();

	pa2m_nuevo_grupo("lista_buscar_posicion");
	tests_de_estres_lista_buscar_posicion();

	pa2m_nuevo_grupo("lista_buscar_elemento");
	tests_de_estres_lista_buscar_elemento();

	pa2m_nuevo_grupo("lista_con_cada_elemento");
	tests_de_estres_lista_con_cada_elemento();

	pa2m_nuevo_grupo("lista_destruir_elemento");
	tests_de_estres_lista_destruir_elemento();
}

//-------------------------------------------------------------TEST PILA---------------------------------------------------------------------------
void test_pila_crear_correctamente()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "Se crea la pila correctamente");
	pila_destruir(pila);
}

void tests_pila_crear()
{
	test_pila_crear_correctamente();
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
void test_pila_apilar_elemento_null()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_apilar(pila, NULL) == true,
		     "Se puede apilar un elemento NULL");
	pila_destruir(pila);
}
void test_pila_apilar_elemento_dinamico()
{
	pila_t *pila = pila_crear();
	int *a = malloc(sizeof(int));
	*a = 42;

	pa2m_afirmar(pila_apilar(pila, a) == true,
		     "Se puede apilar un elemento dinámico correctamente");

	pila_destruir(pila);
	free(a);
}
void test_pila_apilar_diferentes_tipos()
{
	pila_t *pila = pila_crear();

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	pa2m_afirmar(pila_apilar(pila, &entero) == true,
		     "Se puede apilar un entero");
	pa2m_afirmar(pila_apilar(pila, texto) == true,
		     "Se puede apilar un string");
	pa2m_afirmar(pila_apilar(pila, &decimal) == true,
		     "Se puede apilar un double");
	pa2m_afirmar(pila_apilar(pila, vector) == true,
		     "Se puede apilar un vector");
	pa2m_afirmar(pila_apilar(pila, &p) == true,
		     "Se puede apilar un struct");

	pila_destruir(pila);
}

void tests_pila_apilar()
{
	test_pila_apilar_pila_null();
	test_pila_apilar_elemento_pila_vacia();
	test_pila_apilar_elemento_pila_con_elementos();
	test_pila_apilar_elemento_null();
	test_pila_apilar_elemento_dinamico();
	test_pila_apilar_diferentes_tipos();
}
//-----------------------

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

void tests_pila_desapilar()
{
	test_pila_desapilar_en_pila_vacia();
	test_pila_desapilar_en_pila_null();
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

void tests_pila_ver_primero()
{
	test_pila_ver_primero_en_pila_null();
	test_pila_ver_primero_en_pila_vacia();
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

void tests_pila_cantidad()
{
	test_pila_cantidad_inicial_cero();
	test_pila_cantidad_null();
}
//-----------------------
void test_pila_destruir_sin_errores()
{
	pila_t *pila = pila_crear();
	pila_destruir(pila); // corregido: pila_destruir
	pa2m_afirmar(true, "La pila se destruye sin provocar errores");
}

void tests_pila_destruir()
{
	test_pila_destruir_sin_errores();
}

// ----------------------------------------------------------Test de Integracion---------------------------
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

void tests_de_integracion_pila_crear()
{
	test_pila_crear_vacia();
	test_pila_crear_y_ver();
	test_pila_crear_y_desapilar();
	test_pila_crear_y_destruir();
}
// -----------------------------------
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
void test_pila_apilar_y_ver_primero()
{
	pila_t *pila = pila_crear();
	int a = 10;
	int b = 20;

	pila_apilar(pila, &a);
	pa2m_afirmar(*((int *)pila_ver_primero(pila)) == 10,
		     "Se apila el primer elemento correctamente");

	pila_apilar(pila, &b);
	pa2m_afirmar(
		*((int *)pila_ver_primero(pila)) == 20,
		"Se apila el segundo elemento correctamente y es el primero");

	pila_destruir(pila);
}
void test_pila_apilar_desapilar_y_volver_apilar()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20, c = 30;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	pila_desapilar(pila);

	pila_apilar(pila, &c);
	pa2m_afirmar(*((int *)pila_ver_primero(pila)) == 30,
		     "Se puede apilar nuevamente después de desapilar");

	pila_destruir(pila);
}
void test_pila_apilar_destruir_con_elementos()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20, c = 30;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);

	pila_destruir(pila);
	pa2m_afirmar(
		true,
		"Se puede destruir la pila con elementos apilados sin problemas");
}

void tests_de_integracion_pila_apilar()
{
	test_pila_apilar_aumenta_cantidad();
	test_pila_apilar_y_ver_primero();
	test_pila_apilar_desapilar_y_volver_apilar();
	test_pila_apilar_prueba_estres();
	test_pila_apilar_destruir_con_elementos();
}
// -----------------------------------
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
void test_pila_desapilar_un_elemento()
{
	pila_t *pila = pila_crear();
	int a = 10;

	pila_apilar(pila, &a);
	int *desapilado = pila_desapilar(pila);

	pa2m_afirmar(*desapilado == 10,
		     "Se puede desapilar correctamente un único elemento");
	pa2m_afirmar(
		pila_cantidad(pila) == 0,
		"La pila queda vacía después de desapilar el único elemento");

	pila_destruir(pila);
}
void test_pila_desapilar_varios_elementos()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20, c = 30;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);
	pila_apilar(pila, &c);

	int *des1 = pila_desapilar(pila);
	int *des2 = pila_desapilar(pila);
	int *des3 = pila_desapilar(pila);

	pa2m_afirmar(
		*des1 == 30 && *des2 == 20 && *des3 == 10,
		"Se desapilan correctamente varios elementos en orden LIFO");
	pa2m_afirmar(
		pila_cantidad(pila) == 0,
		"La pila queda vacía después de desapilar todos los elementos");

	pila_destruir(pila);
}
void test_pila_desapilar_diferentes_tipos()
{
	pila_t *pila = pila_crear();

	int entero = 5;
	char *texto = "Hola";
	double decimal = 3.14;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	pila_apilar(pila, &entero);
	pila_apilar(pila, texto);
	pila_apilar(pila, &decimal);
	pila_apilar(pila, vector);
	pila_apilar(pila, &p);

	pa2m_afirmar(pila_desapilar(pila) == &p,
		     "Se desapila un struct correctamente");
	pa2m_afirmar(pila_desapilar(pila) == vector,
		     "Se desapila un vector correctamente");
	pa2m_afirmar(pila_desapilar(pila) == &decimal,
		     "Se desapila un double correctamente");
	pa2m_afirmar(pila_desapilar(pila) == texto,
		     "Se desapila un string correctamente");
	pa2m_afirmar(pila_desapilar(pila) == &entero,
		     "Se desapila un entero correctamente");

	pila_destruir(pila);
}
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

void tests_de_integracion_pila_desapilar()
{
	test_pila_desapilar_un_elemento();
	test_pila_desapilar_varios_elementos();
	test_pila_desapilar_devuelve_ultimo();
	test_pila_desapilar_diferentes_tipos();
	test_pila_desapilar_reduce_cantidad();
	test_pila_desapilar_prueba_estres();
}
// -----------------------------------
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

void tests_de_integracion_pila_ver_primero()
{
	test_pila_ver_primero_y_cantidad();
	test_pila_ver_primero_devuelve_ultimo_apilado();
	test_pila_ver_primero_y_desapilar();
}
// -----------------------------------
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

void tests_de_integracion_pila_cantidad()
{
	test_pila_cantidad_refleja_elementos_apilados();
}
// -----------------------------------
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

void tests_de_integracion_pila_destruir()
{
	test_pila_destruir_con_elementos();
}

void pruebas_pila()
{
	pa2m_nuevo_grupo("---------Pruebas Unitarias Pila---------");
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

	pa2m_nuevo_grupo("---------Pruebas de Integracion Pila---------");
	pa2m_nuevo_grupo("pila_crear");
	tests_de_integracion_pila_crear();

	pa2m_nuevo_grupo("pila_apilar");
	tests_de_integracion_pila_apilar();

	pa2m_nuevo_grupo("pila_desapilar");
	tests_de_integracion_pila_desapilar();

	pa2m_nuevo_grupo("pila_ver_primero");
	tests_de_integracion_pila_ver_primero();

	pa2m_nuevo_grupo("pila_cantidad");
	tests_de_integracion_pila_cantidad();

	pa2m_nuevo_grupo("pila_destruir");
	tests_de_integracion_pila_destruir();
}

//-------------------------------------------------------------TEST COLA---------------------------------------------------------------------------

void test_cola_crear_correctamente()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Se crea la cola correctamente");
	cola_destruir(cola);
}

void tests_cola_crear()
{
	test_cola_crear_correctamente();
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
void test_cola_encolar_diferentes_tipos_de_datos()
{
	cola_t *cola = cola_crear();

	int entero = 42;
	char *texto = "Hola";
	double decimal = 3.1416;
	int vector[3] = { 1, 2, 3 };
	struct persona {
		char nombre[10];
		int edad;
	} p = { "Luca", 23 };

	pa2m_afirmar(cola_encolar(cola, &entero),
		     "cola_encolar permite encolar un entero");
	pa2m_afirmar(cola_encolar(cola, texto),
		     "cola_encolar permite encolar un string");
	pa2m_afirmar(cola_encolar(cola, &decimal),
		     "cola_encolar permite encolar un double");
	pa2m_afirmar(cola_encolar(cola, vector),
		     "cola_encolar permite encolar un vector");
	pa2m_afirmar(cola_encolar(cola, &p),
		     "cola_encolar permite encolar un struct");

	pa2m_afirmar(
		cola_cantidad(cola) == 5,
		"La cantidad total es correcta después de encolar distintos tipos");

	cola_destruir(cola);
}

void tests_cola_encolar()
{
	test_cola_encolar_elemento_null();
	test_cola_encolar_null();
	test_cola_encolar_elemento_cola_vacia();
	test_cola_encolar_elemento_cola_con_elementos();
	test_cola_encolar_elemento_dinamico();
	test_cola_encolar_diferentes_tipos_de_datos();
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

void tests_cola_desencolar()
{
	test_cola_desencolar_en_cola_vacia();
	test_cola_desencolar_en_cola_null();
}
//-----------------------
void test_cola_ver_primero_en_cola_vacia()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola vacía devuelve NULL");

	cola_destruir(cola);
}
void test_cola_ver_primero_en_cola_null()
{
	pa2m_afirmar(cola_ver_primero(NULL) == NULL,
		     "Ver primero en cola NULL devuelve NULL");
}

void tests_cola_ver_primero()
{
	test_cola_ver_primero_en_cola_vacia();
	test_cola_ver_primero_en_cola_null();
}
//-----------------------
void test_cola_cantidad_inicial_cero()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "Una cola recién creada tiene cantidad 0");

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
	test_cola_cantidad_null();
}
//-----------------------

void test_cola_destruir_sin_errores()
{
	cola_t *cola = cola_crear();
	cola_destruir(cola);

	pa2m_afirmar(true, "La cola se destruye sin provocar errores");
}

void tests_cola_destruir()
{
	test_cola_destruir_sin_errores();
}

// ----------------------------------------------------------Test de Integracion---------------------------
void test_cola_crear_esta_vacia()
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

void tests_de_integracion_cola_crear()
{
	test_cola_crear_esta_vacia();
	test_cola_crear_y_ver();
	test_cola_crear_y_desencolar();
	test_cola_crear_y_destruir();
}
// -----------------------------------
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
void test_cola_encolar_y_ver_primero()
{
	cola_t *cola = cola_crear();
	int valor = 10;

	cola_encolar(cola, &valor);

	pa2m_afirmar(cola_ver_primero(cola) == &valor,
		     "El primer elemento es el encolado");

	cola_destruir(cola);
}
void test_cola_encolar_desencolar_y_volver_a_encolar()
{
	cola_t *cola = cola_crear();
	int a = 1, b = 2;

	cola_encolar(cola, &a);
	cola_desencolar(cola);

	cola_encolar(cola, &b);

	pa2m_afirmar(cola_ver_primero(cola) == &b,
		     "Se puede volver a encolar después de desencolar");

	cola_destruir(cola);
}
void test_cola_destruir_con_elementos_encolados()
{
	cola_t *cola = cola_crear();
	int x = 100, y = 200;

	cola_encolar(cola, &x);
	cola_encolar(cola, &y);

	pa2m_afirmar(cola_cantidad(cola) == 2,
		     "La cola tiene elementos antes de destruirla");

	cola_destruir(cola);

	pa2m_afirmar(
		true,
		"La cola se destruye correctamente con elementos encolados");
}

void tests_de_integracion_cola_encolar()
{
	test_cola_cantidad_correcta_despues_de_encolar();
	test_cola_encolar_y_ver_primero();
	test_cola_encolar_desencolar_y_volver_a_encolar();
	test_cola_destruir_con_elementos_encolados();
	test_cola_prueba_de_estres();
}
// -----------------------------------
void test_cola_desencolar_un_elemento()
{
	cola_t *cola = cola_crear();
	int valor = 42;

	cola_encolar(cola, &valor);

	int *desencolado = cola_desencolar(cola);

	pa2m_afirmar(desencolado == &valor,
		     "Desencolar devuelve el único elemento");

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
void test_cola_desencolar_diferentes_tipos()
{
	cola_t *cola = cola_crear();

	int entero = 10;
	double decimal = 3.14;
	char *texto = "Hola";

	cola_encolar(cola, &entero);
	cola_encolar(cola, &decimal);
	cola_encolar(cola, texto);

	pa2m_afirmar(cola_desencolar(cola) == &entero, "Se desencolan enteros");
	pa2m_afirmar(cola_desencolar(cola) == &decimal,
		     "Se desencolan doubles");
	pa2m_afirmar(cola_desencolar(cola) == texto, "Se desencolan strings");

	cola_destruir(cola);
}
void test_cola_desencolar_prueba_de_estres_simple()
{
	cola_t *cola = cola_crear();
	const int N = 5000;
	int valores[N];

	// Encolamos N elementos
	for (int i = 0; i < N; i++) {
		valores[i] = i;
		cola_encolar(cola, &valores[i]);
	}

	// Desencolamos y comprobamos FIFO
	bool correcto = true;
	for (int i = 0; i < N; i++) {
		int *elem = cola_desencolar(cola);
		if (*elem != i) {
			correcto = false;
			break;
		}
	}

	pa2m_afirmar(
		correcto,
		"Prueba de estrés: se desencolan correctamente más de 5.000 elementos");

	cola_destruir(cola);
}

void tests_de_integracion_cola_desencolar()
{
	test_cola_desencolar_un_elemento();
	test_cola_desencolar_primer_elemento();
	test_cola_desencolar_segundo_elemento();
	test_cola_desencolar_y_quedar_vacia();
	test_cola_desencolar_diferentes_tipos();
	test_cola_desencolar_prueba_de_estres_simple();
}
// -----------------------------------
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

void tests_de_integracion_cola_ver_primero()
{
	test_cola_ver_primero_devuelve_primer_elemento();
	test_cola_ver_primero_y_cantidad();
	test_cola_ver_primero_y_desencolar();
}
// -----------------------------------
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

void tests_de_integracion_cola_cantidad()
{
	test_cola_cantidad_refleja_elementos_encolados();
}
// -----------------------------------
void test_cola_destruir_con_elementos()
{
	cola_t *cola = cola_crear();
	int *nums = malloc(sizeof(int) * 100);

	for (int i = 0; i < 100; i++) {
		cola_encolar(cola, &nums[i]);
	}

	pa2m_afirmar(cola_cantidad(cola) == 100,
		     "Se destruye correctamente la cola con elementos");
	cola_destruir(cola);
	free(nums);
}

void tests_de_integracion_cola_destruir()
{
	test_cola_destruir_con_elementos();
}

void pruebas_cola()
{
	pa2m_nuevo_grupo("---------Pruebas Unitarias Cola---------");
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

	pa2m_nuevo_grupo("---------Pruebas de Integriacion Cola---------");
	pa2m_nuevo_grupo("cola_crear");
	tests_de_integracion_cola_crear();

	pa2m_nuevo_grupo("cola_encolar");
	tests_de_integracion_cola_encolar();

	pa2m_nuevo_grupo("cola_desencolar");
	tests_de_integracion_cola_desencolar();

	pa2m_nuevo_grupo("cola_ver_primero");
	tests_de_integracion_cola_ver_primero();

	pa2m_nuevo_grupo("cola_cantidad");
	tests_de_integracion_cola_cantidad();

	pa2m_nuevo_grupo("cola_destruir");
	tests_de_integracion_cola_destruir();
}

int main()
{
	pruebas_lista();
	pruebas_pila();
	pruebas_cola();
	return pa2m_mostrar_reporte();
}