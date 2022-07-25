#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


// AUXILIARES
int comparar_int(void* _i1, void* _i2)
{
  	int* i1=_i1;
  	int* i2=_i2;
	if(_i1 == NULL && _i2 == NULL)
  		return 0;
	else if(_i1 == NULL)
		return -1;
	return *i1-*i2;
}

void modificador_de_variables_estaticas_int_a_1(void *elemento_a_modificar)
{
	*(int *)elemento_a_modificar = 1;
}

int comparador_de_arrays(void **array, int **array_esperado, size_t tamanio)
{
	for (size_t i = 0; i < tamanio; i++){
		if(*(int *)array[i] != *array_esperado[i] )
			return -1;
	}
	return 0;
}

bool mostrar_hasta_encontrar_un_numero_referencia(void *a_comparar, void *numero_referencia)
{
	printf("%d ",*(int *)a_comparar);
	if(*(int *)a_comparar == *(int *)numero_referencia){
		printf("\n");
		return false;
	}
	return true;
}

// PRUEBAS
void pruebas_de_crear_un_arbol()
{
	pa2m_afirmar(abb_crear(NULL) == NULL, "No se puede crear un arbol sin comparador");
	abb_t *arbol = abb_crear(comparar_int);
	// CAJA BLANCA
	pa2m_afirmar(arbol != NULL && arbol->tamanio == 0 && arbol->comparador != NULL && arbol->nodo_raiz == NULL,
	"El arbol se crea correctamente según las especificaciones requeridas.");

	abb_destruir(arbol);
}

void pruebas_de_insertar_elementos_en_un_arbol()
{
	abb_t *arbol = abb_crear(comparar_int);
	int a = 60, b = 30, c = 120;

	pa2m_afirmar(abb_insertar(NULL,&a) == NULL, "No se puede insertar un elemento con arbol NULL.");

	// PRUEBAS DE CAJA BLANCA.
	pa2m_afirmar(abb_insertar(arbol,&a) != NULL && *(int *)arbol->nodo_raiz->elemento == a, 
	"Se inserto el primer elemento en el arbol y es el correcto.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL && arbol->nodo_raiz->derecha == NULL ,
	"Izquierda y Derecha del primer nodo ingresado son NULL.");

	pa2m_afirmar(abb_insertar(arbol,&b) != NULL && *(int *)arbol->nodo_raiz->izquierda->elemento == b, 
	"Se inserto un segundo elemento ,menor, y se encuentra a la izquierda.");

	pa2m_afirmar(abb_insertar(arbol,&c) != NULL && *(int *)arbol->nodo_raiz->derecha->elemento == c, 
	"Se inserto un tercer elemento ,mayor, y se encuentra a la derecha.");

	pa2m_afirmar(abb_insertar(arbol,NULL) != NULL, "Se puede insertar un elemento NULL en el arbol.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda->izquierda->elemento == NULL, 
	"El elemento NULL esta en el nodo mas izquierdo, con un arbol de elementos no nulos");

	pa2m_afirmar(abb_insertar(arbol,NULL) != NULL && arbol->nodo_raiz->izquierda->izquierda->izquierda->elemento == NULL, 
	"Al insertar otro elemento NULL se encuentra a la izquierda del nodo anterior.");


	abb_destruir(arbol);
	return;
}

void pruebas_de_quitar_elementos_de_un_arbol()
{
	abb_t *arbol = abb_crear(comparar_int);
	int a = 60;
	
	abb_insertar(arbol,&a);
	void *elemento_quitado = abb_quitar(arbol, &a);
	pa2m_afirmar(elemento_quitado != NULL, "Quitar el unico el.(no nulo) del arbol no devuelve NULL.");
	pa2m_afirmar(*(int *)elemento_quitado == a, "Quitar el unico el. del arbol devuelve ese elemento.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "Ahora el tamanio del arbol es 0.");
	pa2m_afirmar(abb_quitar(arbol,&a) == NULL,"No se puede quitar un elemento de un arbol vacío.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El tamanio del arbol sigue siendo 0.");

	int b = 40, c = 50, d = 30, e = 70, f = 35, g = 39;
	abb_insertar(arbol,&b);
	abb_insertar(arbol,&c);
	abb_insertar(arbol,&d);
	abb_insertar(arbol,&e);
	abb_insertar(arbol,&f);
	abb_insertar(arbol,&g);

	pa2m_afirmar(abb_tamanio(arbol) == 6, "El tamanio ahora es 6.");

	abb_insertar(arbol,NULL);
	pa2m_afirmar(abb_quitar(arbol,NULL) == NULL,
	"Se insertó un elemento null. Se busca quitarlo con abb_quitar y el resultado es NULL.");
	pa2m_afirmar(abb_tamanio(arbol) == 6, "El tamanio sigue siendo 6.");

	abb_insertar(arbol,NULL);
	abb_insertar(arbol,NULL);
	pa2m_afirmar(abb_quitar(arbol,NULL) == NULL && abb_quitar(arbol,NULL) == NULL,
	"Se insertaron DOS elementos null. Se busca quitarlos con abb_quitar y el resultado es NULL.");
	pa2m_afirmar(abb_tamanio(arbol) == 6, "El tamanio sigue siendo 6.");
	
	// PRUEBAS DE CAJA BLANCA.
	pa2m_afirmar(*(int *)abb_quitar(arbol,&b) == b,  
	"Se quita el nodo de la raiz principal y el elemento es el esperado.");
	pa2m_afirmar(*(int *)arbol->nodo_raiz->elemento == g, 
	"El elemento reemplazante es el predecesor inorden.");
	pa2m_afirmar(arbol->tamanio == 5, 
	"Eran 6, ahora la cantidad de elementos del arbol es 5.");


	abb_destruir(arbol);
}

void pruebas_de_comparar_cada_elemento_del_arbol_con_una_funcion_de_comparacion_del_usuario_con_diferentes_recorridos()
{
	abb_t *arbol = abb_crear(comparar_int);
	int a = 60, b= 40, c = 50, d = 30, e = 70;
	
	pa2m_afirmar(abb_con_cada_elemento(NULL,INORDEN,&mostrar_hasta_encontrar_un_numero_referencia,&e) == 0,
	"Con un arbol NULL se llama la función 0 veces.");

	pa2m_afirmar(abb_con_cada_elemento(arbol,INORDEN,&mostrar_hasta_encontrar_un_numero_referencia,&e) == 0,
	"Con un arbol vacío se llama la función 0 veces.");

	abb_insertar(arbol,&a);
	abb_insertar(arbol,&b);
	abb_insertar(arbol,&c);
	abb_insertar(arbol,&d);
	abb_insertar(arbol,&e);

	// PRUEBAS DE INORDEN
	int aux = 30;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 1,
	"Recorrido INORDEN. la cantidad de invocaciones es la esperada.(1)");

	aux = 50;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 3,
	"Recorrido INORDEN. la cantidad de invocaciones es la esperada.(3)");

	aux = 70;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 5,
	"Recorrido INORDEN. la cantidad de invocaciones es la esperada.(5)");

	// PRUEBAS DE PREORDEN
	pa2m_nuevo_grupo("                   ");
	aux = 30;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 3,
	"Recorrido PREORDEN. la cantidad de invocaciones es la esperada.(3)");
	
	aux = 50;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 4,
	"Recorrido PREORDEN. la cantidad de invocaciones es la esperada.(4)");

	aux = 70;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 5,
	"Recorrido PREORDEN. la cantidad de invocaciones es la esperada.(5)");

	// PRUEBAS DE POSTORDEN
	pa2m_nuevo_grupo("                   ");
	aux = 30;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 1,
	"Recorrido POSTORDEN. la cantidad de invocaciones es la esperada.(1)");
	
	aux = 50;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 2,
	"Recorrido POSTORDEN. la cantidad de invocaciones es la esperada.(2)");

	aux = 70;
	printf("Los numeros comparados fueron: ");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, &mostrar_hasta_encontrar_un_numero_referencia, &aux) == 4,
	"Recorrido POSTORDEN. la cantidad de invocaciones es la esperada.(4)");


	abb_destruir(arbol);
}

void pruebas_de_recorrer_el_arbol_con_tres_tipos_de_rec_diferentes_guardando_los_elementos_en_un_array()
{
	abb_t *arbol = abb_crear(comparar_int);
	int a = 60, b= 40, c = 50, d = 30, e = 70;
	
	abb_insertar(arbol,&a);    		
	abb_insertar(arbol,&b);
	abb_insertar(arbol,&c);
	abb_insertar(arbol,&d);
	abb_insertar(arbol,&e);

	// PRUEBAS INORDEN
	size_t tamanio_array = 5;
	void *array[tamanio_array];
	int *array_esperado[5] = {&d,&b,&c,&a,&e};

	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, tamanio_array) == 5,
	"Con recorrido INORDEN y tamanio de array 5 se recorrieron todos los 5 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado, tamanio_array) == 0,
	 "El array resultante es el esperado.");
	
	tamanio_array = 3;
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, tamanio_array) == 3,
	"Con recorrido INORDEN y tamanio de array 3 se recorrieron solo 3 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado, tamanio_array) == 0,
	 "El array resultante es el esperado.");
	
	// PRUEBAS PREORDEN
	int *array_esperado2[5] = {&a,&b,&d,&c,&e};
	tamanio_array = 5;
	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, array, tamanio_array) == 5,
	"Con recorrido PREORDEN y tamanio de array 5 se recorrieron todos los 5 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado2, tamanio_array) == 0,
	"El array resultante es el esperado.");
	
	tamanio_array = 3;
	pa2m_afirmar(abb_recorrer(arbol, PREORDEN, array, tamanio_array) == 3,
	"Con recorrido PREORDEN y tamanio de array 3 se recorrieron solo 3 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado2, tamanio_array) == 0,
	 "El array resultante es el esperado.");
	
	// PRUEBAS POSTORDEN
	int *array_esperado3[5] = {&d,&c,&b,&e,&a};
	tamanio_array = 5;
	pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, array, tamanio_array) == 5,
	"Con recorrido POSTORDEN y tamanio de array 5 se recorrieron todos los 5 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado3, tamanio_array) == 0,
	 "El array resultante es el esperado.");
	
	tamanio_array = 3;
	pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, array, tamanio_array) == 3,
	"Con recorrido POSTORDEN y tamanio de array 3 se recorrieron solo 3 elementos.");
	pa2m_afirmar(comparador_de_arrays(array, array_esperado3, tamanio_array) == 0,
	 "El array resultante es el esperado.");
	

	abb_destruir(arbol);
}

void pruebas_de_destruir_un_arbol_con_elementos_sin_perdida_de_memoria_modificando_los_elementos()
{
	abb_t *arbol = abb_crear(comparar_int);
	int a = 60, b= 40, c = 50, d = 30, e = 70;
	
	abb_insertar(arbol,&a);    		
	abb_insertar(arbol,&b);
	abb_insertar(arbol,&c);
	abb_insertar(arbol,&d);
	abb_insertar(arbol,&e);

	abb_destruir_todo(arbol, &modificador_de_variables_estaticas_int_a_1);
	pa2m_afirmar(a == 1 && b == 1 && c == 1 && d == 1 && e == 1,
	 "Invocando abb_destruir_todo en un arbol con elementos tiene el resultado esperado.");
}

void pruebas_de_buscar_elementos_en_un_arbol_con_busqueda_binaria()
{
	int a = 60, b= 40, c = 50, d = 30, e = 70;
	pa2m_afirmar(abb_buscar(NULL,&d) == NULL, "No se puede buscar en un arbol nulo.");

	abb_t *arbol = abb_crear(comparar_int);
	pa2m_afirmar(abb_buscar(arbol,&d) == NULL, "No se puede buscar en un arbol vacio.");

	abb_insertar(arbol,&a);    		
	abb_insertar(arbol,&b);
	abb_insertar(arbol,&c);
	abb_insertar(arbol,&d);
	abb_insertar(arbol,&e);

	pa2m_afirmar(*(int *)abb_buscar(arbol,&d) == d, "Se busca un elemento del arbol y se encuentra.");
	pa2m_afirmar(*(int *)abb_buscar(arbol,&e) == e, "Se busca otro elemento del arbol y se encuentra.");
	abb_quitar(arbol,&b);
	pa2m_afirmar(abb_buscar(arbol,&b) == NULL, 
	"Se busca un elemento que NO esta en el arbol y devuelve NULL.");

	abb_insertar(arbol,NULL);
	pa2m_afirmar(abb_buscar(arbol,NULL) == NULL,
	"Se inserto un elemento NULL. Se lo busca y el resultado es NULL.");

	abb_destruir(arbol);
}

int main()
{
  	pa2m_nuevo_grupo("___________________________ Pruebas de ABB ___________________________");

	pa2m_nuevo_grupo("Pruebas de crear arbol.");
	pruebas_de_crear_un_arbol();

  	pa2m_nuevo_grupo("Pruebas de insertar elementos.");
  	pruebas_de_insertar_elementos_en_un_arbol();

	pa2m_nuevo_grupo("Pruebas de quitar elementos.");
	pruebas_de_quitar_elementos_de_un_arbol();

	pa2m_nuevo_grupo("Pruebas de con_cada_elemento().");
	pruebas_de_comparar_cada_elemento_del_arbol_con_una_funcion_de_comparacion_del_usuario_con_diferentes_recorridos();

	pa2m_nuevo_grupo("Pruebas de recorrer el arbol.");
	pruebas_de_recorrer_el_arbol_con_tres_tipos_de_rec_diferentes_guardando_los_elementos_en_un_array();

	pa2m_nuevo_grupo("Pruebas del destructor total.");
	pruebas_de_destruir_un_arbol_con_elementos_sin_perdida_de_memoria_modificando_los_elementos();

	pa2m_nuevo_grupo("Pruebas de buscar elementos.");
	pruebas_de_buscar_elementos_en_un_arbol_con_busqueda_binaria();


  	return pa2m_mostrar_reporte();
}
