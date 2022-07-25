# TDA-ABB
Implementación de un árbol binario de búsqueda en C


##1 Introducción
Para este trabajo se pidió implementar un Árbol Binario de Búsqueda en lenguaje 
C, con una firma de funciones públicas definidas y dejando a discreción del alumno 
la creación de funciones privadas del TDA.
Adicionalmente se pidió implementar un iterador interno capaz de realizar
diferentes recorridos en el árbol y una función que guarda en un vector la info. 
Almacenada por el árbol.
Finalmente, se utilizó una metodología de desarrollo orientado a pruebas.


##2 Teoría

# 2.1Arboles N-arios o Generales.
Los árboles nacen de querer optimizar la búsqueda lineal de la lista, complejidad O(n), 
para ello se buscó una estructura que similar a la búsqueda binaria, permitiría el acceso a 
la información en un tiempo de O(log n).
Un árbol se puede definir como una colección de nodos. Estos nodos son los vértices del 
árbol. Esta colección puede estar vacía, o puede tener muchos elementos, en este ultimo 
caso, siempre hay una distinción al nodo raíz. Pueden existir sub-árboles cada uno con su 
nodo raíz que esta conectado a la raíz principal del árbol “grande”. De esta manera se 
definen 1, 2, 3, o múltiples nodos hijos (los nodos raíz de los sub-árboles) y un padre el 
cual precede y está conectado con los primeros(nodo raíz del árbol grande) como muestra 
la figura:
![image](https://user-images.githubusercontent.com/92110097/180874133-c0786d63-e8f0-4c71-b25f-2fff284b386b.png)

Todos los nodos que tienen el mismo padre son hermanos (siblings).
Camino: Un camino desde un nodo a otro se define como la secuencia de nodos n1, n2,
…, nk tal que ni es el padre de ni+1 para a 1 <= i <= k. La longitud es el número de aristas
en el camino, k-1. En el árbol existe un solo camino entre la raíz general y cualquier otro 
nodo, incluido si mismo (camino de longitud cero).
![image](https://user-images.githubusercontent.com/92110097/180874211-4002d56a-f212-4594-ba8b-f86ca61e9e56.png)

Profundidad: Para cualquier nodo, la profundidad es la longitud del único camino entre sí
mismo y el nodo raíz. Por ende, la longitud del nodo raíz es 0. La altura (height) de un nodo 
es la altura del camino más largo desde si mismo a una hoja. Por ende, la altura de un 
nodo hoja es 0. Si existe un camino entre n1 y n2, entonces se dice que n1 es un ancestro
de n2 y que n2 es un descendiente de n1.

# 2.2 Árboles binarios:
Un árbol binario es otro tipo de TDA que puede estar vacío, o consistir en un nodo llamado 
raíz conjuntamente con dos árboles binarios uno llamado derecha y otro llamado 
izquierda ambos hijos del nodo raíz como muestra la figura:
![image](https://user-images.githubusercontent.com/92110097/180874475-675e8f2b-f67e-42ec-a0c7-827baf13c28a.png)
Estos árboles están íntimamente relacionados a las operaciones de búsqueda, con el 
objetivo de aproximarse a la búsqueda binaria.
Una de las operaciones mas importantes que se pueden hacer con los árboles binarios es 
el recorrido. Por supuesto no existe una única forma de recorrerlos, de esta manera 
surgen tres criterios estándar:
Preorden: Primero se visita en nodo actual luego el sub-árbol izquierdo y luego el derecho.
Inorden: Primero se visita el sub-árbol izquierdo, luego el nodo actual y por último el subárbol derecho.
Postorden: Primero se visita el sub-árbol izquierdo, luego al sub-árbol derecho y por 
último al nodo actual.

# 2.3 Árboles binarios de búsqueda:
Un árbol binario de búsqueda es un tipo de árbol binario que tiene criterios de inserción 
y comparación de nodos lo que permite tener las ventajas de las listas enlazadas, pero 
también la velocidad de la búsqueda binaria mediante el aprovechamiento de la 
estructura del TDA. Puede estar vacío o contener nodos enlazados, en este caso se asocia 
a cada nodo conformante una clave o valor que satisface las siguientes condiciones:
  1. la clave en el nodo izquierdo del hijo (si existe) es menor que la clave en el nodo 
  padre.
  2. la clave en el nodo derecho del hijo (si existe) es mayor que la clave en el nodo padre.
  3. los árboles derecho e izquierdo son también arboles binarios de búsqueda.
Un claro ejemplo de este tipo de TDA es el siguiente:
![image](https://user-images.githubusercontent.com/92110097/180874650-67c871b9-2555-4627-82b4-49b429368bc7.png)

#2.4 Operaciones de los árboles:
Las operaciones posibles en los árboles son la creación del TDA, destrucción, vacío,
inserción, eliminación, búsqueda y recorrido.
Análisis de complejidad:
Para la creación y vacío la complejidad es O(1) ya que son instrucciones sencillas de 
creación o llamado de variables.
La Búsqueda de un elemento en un ABB comienza desde su raíz, la cual se compara con 
el buscado, si hay coincidencia la búsqueda se detiene, caso contrario si la clave buscada 
es mayor se reanuda la búsqueda en el sub-árbol derecho con el mismo criterio. De la 
misma manera en caso de que la clave sea menor con el sub-árbol izquierdo.
Dado que el máximo numero de nodos en un árbol binario de altura h es:

![image](https://user-images.githubusercontent.com/92110097/180874789-33b85f95-7844-42e0-a81d-b32a612d7eb6.png)

Si consideramos que la complejidad de la búsqueda depende de la altura del árbol, es decir 
O(h) nos encontramos con que la complejidad de la operación es O(log n). Pero, si el árbol 
no está equilibrado ( y esta implementación no tiene ninguna manera de hacerlo) se puede 
dar el caso en que la altura sea como esta figura: 
![image](https://user-images.githubusercontent.com/92110097/180874837-6396bacb-75e0-449c-96c5-1f7eaab1ff08.png)
esto nos lleva a que la complejidad de la búsqueda sea O(n), por 
lo que sería lo mismo que buscar en un TDA de LISTA.

La Inserción se realiza con el mismo criterio que la búsqueda, a fin de llegar a una hoja 
del árbol que tenga al menos un lugar libre a la cual le corresponda “adoptar” ( si cumple 
la condición se ser mayor o menor) el nuevo nodo como hijo. Para esto se reservará 
memoria para un nuevo nodo, se asignará el elemento a guardar en la parte del nodo 
designada y se inicializa nulos los hijos derechos e izquierdo de este nuevo nodo. La 
complejidad es igual a la búsqueda, O(log n), por lo tanto si se insertan n elementos 
resulta ser O(n log n).


La eliminación es una extensión de la operación de búsqueda ya que requiere que se 
busque al elemento para borrarlo. Al momento de borrar un nodo hay tres casos posibles:
- Que sea una hoja, caso en el cual solo hay que borrar ese nodo y asignar nulo al 
  puntero de su padre que lo señalaba
- Que tenga un único hijo. El elemento anterior se enlaza con el hijo del que queremos 
  borrar.
- Que tenga dos hijos. Se sustituye por el elemento más próximo en clave, en este caso, 
  el predecesor INORDEN, es decir, situarse en el nodo izquierdo al que queremos 
  eliminar y continuar el recorrido derecho a partir de allí hasta encontrar el nodo hoja 
  que será el reemplazante.
  
La complejidad resulta ser O(log n).
Las operaciones de recorrido y destrucción como tienen que pasar por cada elemento 
del árbol tienen una complejidad de O(n). Los recorridos se pueden realizar de las 
maneras estándar explicadas anteriormente.
Es importante la distinción de los distintos tipos de árboles ya que fueron diseñados para 
desempeñar tareas diferentes y tienen complejidades operacionales diferentes, por 
ejemplo, un árbol n-ario es mucho más útil para el sistema de archivos de un sistema 
operativo que lo que sería un árbol binario o un ABB:
![image](https://user-images.githubusercontent.com/92110097/180875017-e302489e-bfce-461b-88eb-0e8e0d548921.png)
Por otro lado, un árbol binario de búsqueda resulta mejor para la búsqueda de los 
elementos que lo componen que un árbol n-ario.

#3 Detalles de la implementación
La implementación, se planteó con metodología de desarrollo orientado a pruebas. De esta manera 
al ir incorporando las funcionalidades del ABB, se escribían pruebas que corroboraran su correcto 
desempeño. Adicionalmente se escribieron pruebas por cada bug que surgiera durante el testeo, que 
en este caso no fueron muchos.
Tanto por la temática vista durante las clases como la dinámica de un árbol binario de búsqueda la 
mayor parte de las funcionalidades está implementada de manera recursiva.
Se utilizaron estructuras de nodo (que contiene punteros hacia el elemento a almacenar, el nodo de 
siguiente nivel izq. y su homólogo derecho) y árbol (que guarda un puntero hacia el nodo raíz general,
la función comparadora y el tamaño o cantidad de nodos).
Durante el desarrollo se encontró que las firmas de las funciones reciben, en general, la estructura de 
árbol. Esto generaba un inconveniente para recorrer o avanzar por el árbol de forma recursiva. Se 
solucionó creando funciones privadas auxiliadas que realizan el trabajo recursivo y reciben como 
parámetro, en general, el nodo raíz (o cualquier otro nodo) en vez de la estructura árbol.

#3.1 Iterador Interno
Dado que se tiene la opción de recorrer el árbol de diferente manera, se creó un switch para 
cada caso y una función auxiliar acorde con el tipo de recorrido. Mayormente estas funciones 
privadas están desarrolladas con lógica y código muy similar pero en distinto orden de 
ejecución.

#3.2 Abb_recorrer()
Para esta función se colocó un switch con la misma lógica que con el iterador interno. Las 
funciones auxiliares, aunque realizan el mismo tipo de recorrido que las homólogas de el iterador 
interno realizan detalles operacionales diferentes por lo que se implementaron separadamente 
para mantener la claridad del código.

Por último, se encontraron algunas dificultades con el uso de punteros auxiliares para retener valores en 
funciones recursivas como un doble puntero para guardar la dirección del elemento buscado, o el uso de 
un doble puntero a un array para ir guardando las direcciones de los elementos en orden.

![image](https://user-images.githubusercontent.com/92110097/180875254-b084bf7f-32f6-4b5c-8f5a-7d1e816a2e97.png)

Con un poco de atención fueron implementados sin mayores dificultades.
