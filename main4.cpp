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

    Nodo(int _id, const string &_nombre, const string &_tipo)
        : id(_id), nombre(_nombre), tipo(_tipo) {}
};

class Arista
{
public:
    int idCliente;
    int idServidor;
    int velocidad;
    int distancia;

    Arista(int _idCliente, int _idServidor, int _velocidad, int _distancia)
        : idCliente(_idCliente), idServidor(_idServidor), velocidad(_velocidad), distancia(_distancia) {}
};

class Grafo
{
public:
    vector<Nodo> nodos;
    vector<Arista> aristas;

    void agregarNodo(int id, const string &nombre, const string &tipo)
    {
        nodos.push_back(Nodo(id, nombre, tipo));
    }

    void agregarArista(int idCliente, int idServidor, int velocidad, int distancia)
    {
        aristas.push_back(Arista(idCliente, idServidor, velocidad, distancia));
    }

    void imprimirGrafo()
    {
        cout << "Nodos:" << endl;
        for (const auto &nodo : nodos)
        {
            cout << "ID: " << nodo.id << ", Nombre: " << nodo.nombre << ", Tipo: " << nodo.tipo << endl;
        }

        cout << "\nAristas:" << endl;
        for (const auto &arista : aristas)
        {
            cout << "ID Cliente: " << arista.idCliente << ", ID Servidor: " << arista.idServidor
                 << ", Velocidad: " << arista.velocidad << ", Distancia: " << arista.distancia << endl;
        }
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
            grafo.agregarArista(stoi(datos[0]), stoi(datos[1]), stoi(datos[2]), stoi(datos[3]));
            grafo.agregarArista(stoi(datos[1]), stoi(datos[0]), stoi(datos[2]), stoi(datos[3])); // Añadir arista inversa para grafos no dirigidos
        }
    }

    archivo.close();
}

void bellmanFord(Grafo &grafo, int origen, int destino)
{
    vector<int> distancia(grafo.nodos.size(), INT_MAX);
    vector<int> predecesor(grafo.nodos.size(), -1);

    distancia[origen] = 0;

    for (std::vector<Nodo>::size_type i = 0; i < grafo.nodos.size() - 1; ++i)
    {
        for (const auto &arista : grafo.aristas)
        {
            if (distancia[arista.idCliente] != INT_MAX &&
                distancia[arista.idCliente] + arista.distancia < distancia[arista.idServidor])
            {
                distancia[arista.idServidor] = distancia[arista.idCliente] + arista.distancia;
                predecesor[arista.idServidor] = arista.idCliente;
            }
        }
    }

    for (const auto &arista : grafo.aristas)
    {
        if (distancia[arista.idCliente] != INT_MAX &&
            distancia[arista.idCliente] + arista.distancia < distancia[arista.idServidor])
        {
            cerr << "El grafo contiene ciclos negativos." << endl;
            exit(EXIT_FAILURE);
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
    for (int i = 0; i < static_cast<int>(camino.size()); ++i)
    {
        cout << camino[i];
        if (i < static_cast<int>(camino.size() - 1))
        {
            cout << " -> ";
        }
    }

    cout << "\nTiempo total: " << distancia[destino] << " segundos" << endl;
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
            bellmanFord(grafo, origen, destino);
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



