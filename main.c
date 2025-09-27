#include "src/lista.h"
#include "src/tp1.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// ----------------------- Validaciones -----------------------
bool validando_formato_csv(const char *archivo)
{
	if (!archivo)
		return false;

	const char *ext = strrchr(archivo, '.');
	if (!ext || strcmp(ext, ".csv") != 0)
		return false;

	return true;
}

bool validando_params(int argc, char *argv[])
{
	if (argc < 5) {
		printf("Se deben de pasar los 5 parametros permitidos <ejecutable> <archivo_pokemones.csv> buscar nombre|id <valor>\n");
		return false;
	}
	if (argc > 5) {
		printf("Solo 5 parametros permitidos <ejecutable> <archivo_pokemones.csv> buscar nombre|id <valor>\n");
		return false;
	}
	if (!validando_formato_csv(argv[1])) {
		printf("El archivo pasado debe de estar en formato 'csv'\n");
		return false;
	}
	if (strcmp(argv[2], "buscar") != 0) {
		printf("El tercer argumento debe ser 'buscar'\n");
		return false;
	}
	if (strcmp(argv[3], "nombre") != 0 && strcmp(argv[3], "id") != 0) {
		printf("El cuarto argumento para buscar debe ser 'nombre' o 'id'\n");
		return false;
	}
	return true;
}
// ----------------------- Callback para guardar en lista -----------------------
bool guardar_en_lista(struct pokemon *poke, void *extra)
{
	lista_t *lista = extra;
	return lista_agregar(lista, poke);
}
// ----------------------- Comparadores -----------------------
int buscando_por_nombre_lista(const void *a, const void *b)
{
	const struct pokemon *p = a;
	const char *nombre = b;

	if (!p || !nombre)
		return -1;

	return strcmp(p->nombre, nombre) == 0 ? 0 : -1;
}

int buscando_por_id_lista(const void *a, const void *b)
{
	const struct pokemon *p = a;
	const int *id = b;

	if (!p || !id)
		return -1;

	return (p->id == *id) ? 0 : -1;
}
// ----------------------- Mostrar -----------------------
const char *convert_tipo_a_string(enum tipo_pokemon tipo)
{
	switch (tipo) {
	case TIPO_ELEC:
		return "ELEC";
	case TIPO_FUEG:
		return "FUEG";
	case TIPO_PLAN:
		return "PLAN";
	case TIPO_AGUA:
		return "AGUA";
	case TIPO_NORM:
		return "NORM";
	case TIPO_FANT:
		return "FANT";
	case TIPO_PSI:
		return "PSI";
	case TIPO_LUCH:
		return "LUCH";
	default:
		return "DESCONOCIDO";
	}
}

void mostrar_pokemon(struct pokemon *p)
{
	if (!p)
		return;
	printf("Id: %d\n", p->id);
	printf("Nombre: %s\n", p->nombre);
	printf("Tipo: %s\n", convert_tipo_a_string(p->tipo));
	printf("Ataque: %d\n", p->ataque);
	printf("Defensa: %d\n", p->defensa);
	printf("Velocidad: %d\n\n", p->velocidad);
}
// ----------------------- Búsqueda con iterador -----------------------
struct pokemon *buscar_pokemon_iterador(lista_t *lista, void *criterio,
					int (*comparador)(const void *,
							  const void *))
{
	lista_iterador_t *it = lista_iterador_crear(lista);
	if (!it)
		return NULL;

	struct pokemon *resultado = NULL;
	while (lista_iterador_hay_mas_elementos(it)) {
		struct pokemon *p = lista_iterador_obtener_actual(it);
		if (comparador(p, criterio) == 0) {
			resultado = p;
			break;
		}
		lista_iterador_siguiente(it);
	}
	lista_iterador_destruir(it);
	return resultado;
}

int main(int argc, char *argv[])
{
	if (!validando_params(argc, argv))
		return 0;

	struct pokemon *p = NULL;
	tp1_t *tp1 = tp1_leer_archivo(argv[1]);
	lista_t *lista_pokemones = lista_crear();
	if (!tp1 || !lista_pokemones)
		return 0;

	tp1_con_cada_pokemon(tp1, guardar_en_lista, lista_pokemones);

	// Buscar por nombre
	if (strcmp(argv[3], "nombre") == 0)
		p = buscar_pokemon_iterador(lista_pokemones, argv[4],
					    buscando_por_nombre_lista);

	// Buscar por id
	if (strcmp(argv[3], "id") == 0) {
		int id = atoi(argv[4]);
		p = buscar_pokemon_iterador(lista_pokemones, &id,
					    buscando_por_id_lista);
	}

	if (p)
		mostrar_pokemon(p);
	else
		printf("No se encontró el pokemon\n");

	lista_destruir(lista_pokemones);
	tp1_destruir(tp1);
	return 0;
}
