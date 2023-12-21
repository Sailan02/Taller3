#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <iomanip>

using namespace std;

class Nodo
{
public:
    int id;
    string nombre;
    string tipo;
    vector<pair<Nodo*, pair<int, int>>> conexiones;

    Nodo(int _id, const string &_nombre, const string &_tipo)
        : id(_id), nombre(_nombre), tipo(_tipo) {}
};

class Grafo
{
public:
    vector<Nodo> nodos;

    void agregarNodo(int id, const string &nombre, const string &tipo)
    {
        nodos.push_back(Nodo(id, nombre, tipo));
    }

    void agregarConexion(int idNodo1, int idNodo2, int velocidad, int distancia)
    {
        Nodo* nodo1 = &nodos[idNodo1];
        Nodo* nodo2 = &nodos[idNodo2];

        nodo1->conexiones.push_back(make_pair(nodo2, make_pair(velocidad, distancia)));
        nodo2->conexiones.push_back(make_pair(nodo1, make_pair(velocidad, distancia)));
    }

    void imprimirGrafo()
{
    cout << "Nodos:" << endl;
    for (const auto &nodo : nodos)
    {
        cout << "ID: " << nodo.id << ", Nombre: " << nodo.nombre << ", Tipo: " << nodo.tipo << endl;

        cout << "Conexiones:" << endl;
        for (const auto &conexion : nodo.conexiones)
        {
            cout << "  Conectado a ID: " << conexion.first->id
                 << ", Nombre: " << conexion.first->nombre
                 << ", Velocidad: " << conexion.second.first
                 << ", Distancia: " << conexion.second.second << endl;
        }
    }
}

    void bellmanFord(int origen, int destino)
    {
        vector<int> distancia(nodos.size(), INT_MAX);
        vector<int> predecesor(nodos.size(), -1);

        distancia[origen] = 0;

        for (size_t i = 0; i < nodos.size() - 1; ++i)
        {
            for (const auto &nodo : nodos)
            {
                for (const auto &conexion : nodo.conexiones)
                {
                    int idNodoCliente = nodo.id;
                    int idNodoServidor = conexion.first->id;
                    int peso = conexion.second.second; // Distancia como peso

                    if (distancia[idNodoCliente] != INT_MAX &&
                        distancia[idNodoCliente] + peso < distancia[idNodoServidor])
                    {
                        distancia[idNodoServidor] = distancia[idNodoCliente] + peso;
                        predecesor[idNodoServidor] = idNodoCliente;
                    }
                }
            }
        }

        for (const auto &nodo : nodos)
        {
            for (const auto &conexion : nodo.conexiones)
            {
                int idNodoCliente = nodo.id;
                int idNodoServidor = conexion.first->id;
                int peso = conexion.second.second; // Distancia como peso

                if (distancia[idNodoCliente] != INT_MAX &&
                    distancia[idNodoCliente] + peso < distancia[idNodoServidor])
                {
                    cerr << "El grafo contiene ciclos negativos." << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        cout << "Camino más corto desde el nodo " << origen << " hasta el nodo " << destino << ":" << endl;

        int actual = destino;
        vector<int> camino;
        while (actual != -1)
        {
            camino.push_back(actual);
            actual = predecesor[actual];
        }

        reverse(camino.begin(), camino.end());

        cout << "Ruta: ";
        for (size_t i = 0; i < camino.size(); ++i)
        {
            cout << camino[i];
            if (i < camino.size() - 1)
            {
                cout << " -> ";
            }
        }

        cout << "\nTiempo total: " << distancia[destino] << " segundos" << endl;
    }
};

void cargarDesdeCSV(Grafo &grafo, const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        exit(EXIT_FAILURE);
    }

    string linea;
    getline(archivo, linea); // Ignorar la primera línea (encabezado)

    while (getline(archivo, linea))
    {
        istringstream ss(linea);
        string token;

        vector<string> datos;
        while (getline(ss, token, ','))
        {
            datos.push_back(token);
        }

        if (datos.size() == 3)
        {
            grafo.agregarNodo(stoi(datos[0]), datos[1], datos[2]);
        }
        else if (datos.size() == 4)
        {
            grafo.agregarConexion(stoi(datos[0]), stoi(datos[1]), stoi(datos[2]), stoi(datos[3]));
        }
    }

    archivo.close();
}

int main()
{
    Grafo grafo;

    cargarDesdeCSV(grafo, "servidores.csv");
    cargarDesdeCSV(grafo, "conexiones.csv");

    int opcion;
    do
    {
        cout << "\nMenu:" << endl;
        cout << "1. Imprimir informacion del grafo" << endl;
        cout << "2. Encontrar el camino mas corto entre nodos" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese la opción deseada: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            grafo.imprimirGrafo();
            break;
        case 2:
            int origen, destino;
            cout << "Ingrese el nodo de origen: ";
            cin >> origen;
            cout << "Ingrese el nodo de destino: ";
            cin >> destino;
            grafo.bellmanFord(origen, destino);
            break;
        case 3:
            cout << "Saliendo del programa. Hasta luego." << endl;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 3);

    return 0;
}



