#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador)
		return NULL;
	abb_t *nuevo_abb = calloc(1,sizeof(struct abb));
	if(!nuevo_abb)
		return NULL;
	nuevo_abb->comparador = comparador;
	return nuevo_abb;
}

nodo_abb_t *abb_insertar_rec(nodo_abb_t *nodo_raiz,void *elemento,int (*comparador)(void *,void*), int *flag)
{
	if(nodo_raiz == NULL){
		nodo_abb_t *nueva_hoja = calloc(1,sizeof(nodo_abb_t));
		if(!nueva_hoja){
			*flag = 1;
			return NULL;
		}
		nueva_hoja->elemento = elemento;
		nueva_hoja->izquierda = NULL;
		nueva_hoja->derecha = NULL;
		return nueva_hoja;
	}

	int comparacion = comparador(elemento,nodo_raiz->elemento);

	if(comparacion <= 0)
		nodo_raiz->izquierda = abb_insertar_rec(nodo_raiz->izquierda, elemento, comparador, flag);
	else
		nodo_raiz->derecha = abb_insertar_rec(nodo_raiz->derecha, elemento, comparador, flag);

	return nodo_raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{	
	if(arbol == NULL)
		return NULL;
	int flag = 0;
	arbol->nodo_raiz = abb_insertar_rec(arbol->nodo_raiz,elemento,arbol->comparador, &flag);

	if(flag != 0)
		return NULL;
		
	arbol->tamanio += 1;
	return arbol;
}

nodo_abb_t *extraer_mas_derecho(nodo_abb_t *nodo, nodo_abb_t **extraido)
{
	if(nodo->derecha == NULL){
		*extraido = nodo;
		return nodo->izquierda;
	}
	nodo->derecha = extraer_mas_derecho(nodo->derecha, extraido);
	return nodo;
}

nodo_abb_t *abb_quitar_rec(nodo_abb_t *nodo_raiz, void *elemento, int (*comparador)(void *,void*),
void **el_extraido, int *comparacion)
{
	if(nodo_raiz == NULL)
	 	return NULL;

	*comparacion = comparador(elemento,nodo_raiz->elemento);
	if(*comparacion == 0){
		*el_extraido = nodo_raiz->elemento;
		nodo_abb_t *der = nodo_raiz->derecha;
		nodo_abb_t *izq = nodo_raiz->izquierda;

		if(der && izq){
			nodo_abb_t *extraido = NULL;
			nodo_raiz->izquierda = extraer_mas_derecho(nodo_raiz->izquierda, &extraido);
			nodo_raiz->elemento = extraido->elemento;
			free(extraido);
			return nodo_raiz;
		}

		free(nodo_raiz);
		if(izq)
			return izq;
		return der;
	}

	if(*comparacion < 0)
		nodo_raiz->izquierda = abb_quitar_rec(nodo_raiz->izquierda, elemento, comparador,
		 el_extraido, comparacion);
	else
		nodo_raiz->derecha = abb_quitar_rec(nodo_raiz->derecha, elemento, comparador,
		 el_extraido, comparacion);

	return nodo_raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if(abb_vacio(arbol))
		return NULL;

	void *el_extraido = NULL;
	int comparacion = 1;
	arbol->nodo_raiz = abb_quitar_rec(arbol->nodo_raiz, elemento, arbol->comparador, 
	&el_extraido, &comparacion);

	if(comparacion == 0)
		arbol->tamanio -= 1;
	return el_extraido;
}

void abb_buscar_rec(nodo_abb_t *nodo, void *elemento, int (*comparador)(void *,void*), void **el_buscado)
{
	if(nodo == NULL)
		return;

	int comparacion = comparador(elemento,nodo->elemento);

	if(comparacion == 0){
		*el_buscado = nodo->elemento;
		return;
	}

	if(comparacion < 0)
		abb_buscar_rec(nodo->izquierda, elemento, comparador, el_buscado);
	else 
		abb_buscar_rec(nodo->derecha, elemento, comparador, el_buscado);

	return;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(abb_vacio(arbol) || elemento == NULL)
		return NULL;
	void *el_buscado = NULL;
	abb_buscar_rec(arbol->nodo_raiz, elemento, arbol->comparador, &el_buscado);
	return el_buscado;
}

bool abb_vacio(abb_t *arbol)
{
	return (bool)(arbol == NULL || arbol->tamanio == 0);
}

size_t abb_tamanio(abb_t *arbol)
{
	if(abb_vacio(arbol))
		return 0;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	abb_destruir_todo(arbol,NULL);
}

void abb_destruir_todo_rec(nodo_abb_t *nodo, void (*destructor)(void *) )
{
	if(nodo == NULL)
		return;
	abb_destruir_todo_rec(nodo->izquierda,destructor);
	abb_destruir_todo_rec(nodo->derecha,destructor);
	if(destructor)
		destructor(nodo->elemento);
	
	free(nodo);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(arbol == NULL)
		return;

	abb_destruir_todo_rec(arbol->nodo_raiz, destructor);

	free(arbol);
}

void con_cada_inorden_rec(nodo_abb_t *nodo,bool (*funcion)(void *, void *), void *aux, 
size_t *invocaciones, bool *seguir)
{
	if(!nodo)
		return;

	con_cada_inorden_rec(nodo->izquierda, funcion, aux, invocaciones, seguir);
	
	if(*seguir){		
		*invocaciones += 1;
		if(funcion(nodo->elemento,aux) == false)
			*seguir = false;
		else
			con_cada_inorden_rec(nodo->derecha, funcion, aux, invocaciones, seguir);
	}
}

void con_cada_preorden_rec(nodo_abb_t *nodo,bool (*funcion)(void *, void *), void *aux, 
size_t *invocaciones, bool *seguir)
{
	if(!nodo)
		return;
	
	if(*seguir){		
		*invocaciones += 1;
		if(funcion(nodo->elemento,aux) == false){
			*seguir = false;
		}else{
			con_cada_preorden_rec(nodo->izquierda, funcion, aux, invocaciones, seguir);
			con_cada_preorden_rec(nodo->derecha, funcion, aux, invocaciones, seguir);
		}
	}
}

void con_cada_postorder_rec(nodo_abb_t *nodo,bool (*funcion)(void *, void *), void *aux, 
size_t *invocaciones, bool *seguir)
{
	if(!nodo)
		return;

	con_cada_postorder_rec(nodo->izquierda, funcion, aux, invocaciones, seguir);
	
	if(*seguir)	
		con_cada_postorder_rec(nodo->derecha, funcion, aux, invocaciones, seguir);
	if(*seguir){
		*invocaciones += 1;
		if(funcion(nodo->elemento,aux) == false)
			*seguir = false;			
	}
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if(funcion == NULL)
		return 0;
	if(abb_vacio(arbol))
		return 0;

	size_t invocaciones = 0;
	bool seguir = true;

	switch (recorrido){
	case INORDEN:
		con_cada_inorden_rec(arbol->nodo_raiz, funcion, aux, &invocaciones, &seguir);
		break;
	case PREORDEN:
		con_cada_preorden_rec(arbol->nodo_raiz, funcion, aux, &invocaciones, &seguir);
		break;
	case POSTORDEN:
		con_cada_postorder_rec(arbol->nodo_raiz, funcion, aux, &invocaciones, &seguir);
		break;
	default:
		return 0;
	}
	return invocaciones;
}

void recorrer_inorden_rec(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *recorridos)
{
	if(!nodo)
		return;

	recorrer_inorden_rec(nodo->izquierda, array, tamanio_array, recorridos);

	if(*recorridos < tamanio_array){
		array[*recorridos] = nodo->elemento;
		*recorridos += 1;
		recorrer_inorden_rec(nodo->derecha, array, tamanio_array, recorridos);
	}

}

void recorrer_preorden_rec(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *recorridos)
{
	if(!nodo)
		return;


	if(*recorridos < tamanio_array){
		array[*recorridos] = nodo->elemento;
		*recorridos += 1;
		recorrer_preorden_rec(nodo->izquierda, array, tamanio_array, recorridos);
	}

	if(*recorridos < tamanio_array)
		recorrer_preorden_rec(nodo->derecha, array, tamanio_array, recorridos);
}

void recorrer_postorder_rec(nodo_abb_t *nodo, void **array, size_t tamanio_array, size_t *recorridos)
{
	if(!nodo)
		return;

	recorrer_postorder_rec(nodo->izquierda, array, tamanio_array, recorridos);
	
	if(*recorridos < tamanio_array)
		recorrer_postorder_rec(nodo->derecha, array, tamanio_array, recorridos);

	if(*recorridos < tamanio_array){
		array[*recorridos] = nodo->elemento;
		*recorridos += 1;
	}

}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if(!arbol || !array || tamanio_array == 0)
		return 0;
	size_t el_recorridos = 0;
	
	switch (recorrido){
	case INORDEN:
		recorrer_inorden_rec(arbol->nodo_raiz, array, tamanio_array, &el_recorridos);
		break;
	case PREORDEN:
		recorrer_preorden_rec(arbol->nodo_raiz, array, tamanio_array, &el_recorridos);
		break;
	case POSTORDEN:
		recorrer_postorder_rec(arbol->nodo_raiz, array, tamanio_array, &el_recorridos);
		break;
	default:
		return 0;
	}
	return el_recorridos;
}
