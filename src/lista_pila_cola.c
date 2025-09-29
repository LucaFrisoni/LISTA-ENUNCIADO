#include "lista.h"
#include "cola.h"
#include "pila.h"

//Si fuese doblemente enlazada tendria anterior tambien
typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *primero;
	nodo_t *ultimo;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t *actual;
};

struct pila {
	lista_t *lista;
};

struct cola {
	lista_t *lista;
};

// ------------------------------------------------------------------------------------------------------------Lista
lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if (!lista) {
		return NULL;
	}

	return lista;
}
//-----------------------------------------------
bool lista_vacia(lista_t *lista)
{
	if (!lista)
		return true;

	return (lista->primero == NULL && lista->ultimo == NULL);
}
//-----------------------------------------------
size_t lista_cantidad(lista_t *lista)
{
	if (!lista)
		return 0;
	return lista->cantidad;
}
//-----------------------------------------------
bool lista_agregar(lista_t *lista, void *dato)
{
	if (!lista)
		return false;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->elemento = dato;

	if (!lista->primero) { // lista vacía
		lista->primero = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	} else { // lista con elementos
		lista->ultimo->siguiente = nuevo_nodo;
		lista->ultimo = nuevo_nodo;
	}
	lista->cantidad++;
	return true;
}
//-----------------------------------------------
bool validando_lista_y_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista))
		return false;
	if (posicion > 0 && lista_cantidad(lista) <= posicion)
		return false;
	return true;
}

bool lista_insertar_posicion_0(lista_t *lista, void *elemento,
			       nodo_t *nuevo_nodo)
{
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = lista->primero;
	lista->primero = nuevo_nodo;

	if (lista_cantidad(lista) == 0) {
		lista->ultimo = nuevo_nodo;
	}
	lista->cantidad++;
	return true;
}

bool lista_insertar_en_medio(lista_t *lista, void *elemento, size_t posicion,
			     nodo_t *nuevo_nodo)
{
	nodo_t *nodo_previo = NULL;
	nodo_t *nodo_en_posicion = lista->primero;

	// Recorro hasta la posición
	for (size_t i = 0; i < posicion; i++) {
		nodo_previo = nodo_en_posicion;
		nodo_en_posicion = nodo_en_posicion->siguiente;
	}

	// Insierto el nuevo nodo
	nodo_previo->siguiente = nuevo_nodo;
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = nodo_en_posicion;
	lista->cantidad++;
	return true;
}

bool lista_insertar(lista_t *lista, void *elemento, size_t posicion)
{
	if (!validando_lista_y_posicion(lista, posicion))
		return false;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (!nuevo_nodo)
		return false;

	if (posicion == 0) {
		return lista_insertar_posicion_0(lista, elemento, nuevo_nodo);
	} else {
		return lista_insertar_en_medio(lista, elemento, posicion,
					       nuevo_nodo);
	}
}
//-----------------------------------------------
int lista_buscar_posicion(lista_t *lista, void *elemento,
			  int (*comparador)(const void *, const void *))
{
	if (!lista || !comparador || lista_vacia(lista))
		return -1;

	nodo_t *nodo_actual = lista->primero;
	int posicion = 0;

	while (nodo_actual) {
		if (comparador(nodo_actual->elemento, elemento) == 0) {
			return posicion; // elemento encontrado
		}
		nodo_actual = nodo_actual->siguiente;
		posicion++;
	}

	return -1; // no se encontró
}
//-----------------------------------------------
void *lista_buscar_elemento(lista_t *lista, size_t posicion)
{
	if (!validando_lista_y_posicion(lista, posicion))
		return NULL;

	nodo_t *nodo_actual = lista->primero;

	for (size_t i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente;
	}

	return nodo_actual->elemento;
}
//-----------------------------------------------
size_t lista_con_cada_elemento(lista_t *lista, bool (*f)(void *, void *),
			       void *extra)
{
	if (!lista || !f || lista_vacia(lista))
		return 0; // no se procesó ningún elemento

	nodo_t *nodo_actual = lista->primero;
	size_t contador = 0;

	while (nodo_actual) {
		bool continuar = f(nodo_actual->elemento, extra);
		contador++;

		if (!continuar)
			break; // la función pidió parar

		nodo_actual = nodo_actual->siguiente;
	}

	return contador;
}
//-----------------------------------------------
void *lista_eliminar_elemento(lista_t *lista, size_t posicion)
{
	if (!validando_lista_y_posicion(lista, posicion))
		return NULL;

	nodo_t *nodo_actual = lista->primero;
	nodo_t *nodo_previo = NULL;

	// Recorro hasta la posición - si posicion es 0 no recorre
	for (size_t i = 0; i < posicion; i++) {
		nodo_previo = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
	}

	void *valor_aux = nodo_actual->elemento;

	if (nodo_previo) {
		// caso general: no es el primero
		nodo_previo->siguiente = nodo_actual->siguiente;
	} else {
		// caso especial: eliminamos el primero
		lista->primero = nodo_actual->siguiente;
	}

	// //Caso que eliminamos el ultimo unico nodo
	if (!nodo_actual->siguiente)
		lista->ultimo = nodo_previo; //Es NULL

	free(nodo_actual);
	lista->cantidad--;
	return valor_aux;
}
//-----------------------------------------------
void lista_destruir_todo(lista_t *lista, void (*destructor)(void *))
{
	if (!lista || lista_vacia(lista))
		return;

	nodo_t *nodo_actual = lista->primero;
	while (nodo_actual != NULL) {
		nodo_t *nodo_prox = nodo_actual->siguiente;
		if (destructor) {
			destructor(nodo_actual->elemento);
		}

		free(nodo_actual);
		nodo_actual = nodo_prox;
	}
	free(lista);
}
//-----------------------------------------------
//Sirve para cuando queres destruir la lista pero no los datos de los Nodos
void lista_destruir(lista_t *lista)
{
	if (!lista) {
		return;
	}

	nodo_t *nodo_actual = lista->primero;
	while (nodo_actual != NULL) {
		nodo_t *nodo_prox = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = nodo_prox;
	}
	free(lista);
}
//----------------------------------------------- Iterador externo
lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	lista_iterador_t *it = calloc(1, sizeof(lista_iterador_t));
	if (!it)
		return NULL;

	it->actual = lista->primero;
	return it;
}

bool lista_iterador_hay_mas_elementos(lista_iterador_t *it)
{
	if (!it)
		return false;

	return it->actual != NULL;
}

void lista_iterador_siguiente(lista_iterador_t *it)
{
	if (!it || !it->actual)
		return;

	it->actual = it->actual->siguiente;
}

void *lista_iterador_obtener_actual(lista_iterador_t *it)
{
	if (!it || !it->actual)
		return NULL;

	return it->actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *it)
{
	if (!it)
		return;

	free(it);
}
// -----------------------------------------------Pila
pila_t *pila_crear()
{
	lista_t *lista = lista_crear();
	if (!lista)
		return NULL;

	pila_t *pila = calloc(1, sizeof(pila_t));
	if (!pila) {
		free(lista);
		return NULL;
	}

	pila->lista = lista;
	return pila;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila)
		return false;

	if (lista_vacia(pila->lista))
		return lista_agregar(pila->lista, elemento);

	return lista_insertar(pila->lista, elemento, 0);
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila)
		return NULL;
	return lista_eliminar_elemento(pila->lista, 0);
}

void *pila_ver_primero(pila_t *pila)
{
	if (!pila || lista_cantidad(pila->lista) == 0)
		return NULL;

	return pila->lista->primero->elemento;
}

size_t pila_cantidad(pila_t *pila)
{
	if (!pila)
		return 0;
	return lista_cantidad(pila->lista);
}

void pila_destruir(pila_t *pila)
{
	if (!pila)
		return;
	lista_destruir(pila->lista);
	free(pila);
}
// -----------------------------------------------Cola

cola_t *cola_crear()
{
	lista_t *lista = lista_crear();
	if (!lista)
		return NULL;

	cola_t *cola = calloc(1, sizeof(cola_t));
	if (!cola) {
		free(lista);
		return NULL;
	}

	cola->lista = lista;
	return cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola)
		return false;
	return lista_agregar(cola->lista, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola)
		return NULL;
	return lista_eliminar_elemento(cola->lista, 0);
}

void *cola_ver_primero(cola_t *cola)
{
	if (!cola || lista_cantidad(cola->lista) == 0)
		return NULL;

	return cola->lista->primero->elemento;
}

size_t cola_cantidad(cola_t *cola)
{
	if (!cola)
		return 0;
	return lista_cantidad(cola->lista);
}

void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;
	lista_destruir(cola->lista);
	free(cola);
}