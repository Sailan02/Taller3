Silas Vieira// Monserrat Aravena

Implementación del algoritmo 
Primeramente se crea un vector "distancia" para almacenar la distancias más cortas desde el nodo de origen hasta el otro nodo, el vector "predecesor" se utiliza para rastrear los predecesores en el camino más corto. El bucle principal se base en iterar las aristas varias veces, para cada arista se verifica la distancia actual al nodo cliente mas la distancia de la arista menor que la distancia actual al nodo servidor. Luego implementamos una detección de ciclos negativos, si se encuentra un camino más corto después de todas las iteraciones, hay un ciclo negativo en el grafo. Luego de eso se imprime los resultados. 
