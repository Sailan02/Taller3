Silas Vieira 25173142K
Monserratt Aravena 213417738

Implementación del algoritmo 

Inicialización:
Se inicializa dos vectores "distancia" y "predecesor" con tamaños iguales al numero de nodos, "distancia" se utiliza para almacenar las distancias mas cortas entre nodos, "predecesor" se utiliza para almacenar el nodo predecesor en el camino más corto desde el nodo de origen hasta cada nodo  en el grafo. 

Interacioens: 
Se realiza un bucle externo que itera nodos.size() - 1 veces (n-1 iteraciones), donde n es el número de nodos en el grafo. Esto es porque en el peor caso, el camino más corto entre dos nodos puede tener a lo sumo n-1 aristas.
Dentro de este bucle externo, hay un bucle anidado que recorre todos los nodos en el grafo y todas las conexiones salientes de cada nodo.
Para cada conexión, se actualiza la distancia si se encuentra un camino más corto.

Detección de ciclos negativos:
Después de las iteraciones, hay otro bucle que verifica si hay ciclos negativos en el grafo. Si encuentra un camino más corto después de las iteraciones, significa que hay un ciclo negativo en el grafo.

Impresión del camino más corto:
Si no se detectan ciclos negativos, se imprime el camino más corto desde el nodo de origen hasta el nodo de destino, así como el tiempo total necesario para recorrer ese camino.

Recuperación del camino:
Se reconstruye el camino más corto retrocediendo desde el nodo de destino hasta el nodo de origen utilizando el vector predecesor.

Impresión del resultado:
Finalmente, se imprime la ruta y el tiempo total del camino más corto.
