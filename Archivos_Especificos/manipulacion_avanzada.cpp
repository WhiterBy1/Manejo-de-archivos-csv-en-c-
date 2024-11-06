#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Función para cargar el archivo CSV en una matriz de datos
vector<vector<string>> cargarCSV(const string& nombreArchivo) {
    vector<vector<string>> datos;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dato;
        vector<string> fila;

        while (getline(ss, dato, ',')) {
            fila.push_back(dato);
        }
        datos.push_back(fila);
    }

    archivo.close();
    return datos;
}

// Función para guardar la matriz de datos en el archivo CSV
void guardarCSV(const vector<vector<string>>& datos, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size(); ++i) {
            archivo << fila[i];
            if (i < fila.size() - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

// Función para eliminar una fila específica
void eliminarFila(vector<vector<string>>& datos, int fila) {
    if (fila >= 0 && fila < datos.size()) {
        datos.erase(datos.begin() + fila);
    } else {
        cerr << "Número de fila inválido." << endl;
    }
}

// Función para eliminar una columna específica
void eliminarColumna(vector<vector<string>>& datos, int columna) {
    for (auto& fila : datos) {
        if (columna >= 0 && columna < fila.size()) {
            fila.erase(fila.begin() + columna);
        }
    }
}

// Función para editar un dato específico en la matriz de datos
void editarDato(vector<vector<string>>& datos, int fila, int columna, const string& nuevoValor) {
    if (fila >= 0 && fila < datos.size() && columna >= 0 && columna < datos[fila].size()) {
        datos[fila][columna] = nuevoValor;
    } else {
        cerr << "Coordenadas de fila o columna inválidas." << endl;
    }
}

// Función para convertir una columna a enteros y mostrar promedio, mínimo y máximo
void analizarColumnaEntero(const vector<vector<string>>& datos, int columna) {
    vector<int> numeros;
    for (size_t i = 1; i < datos.size(); ++i) {  // Empezamos desde la segunda fila (evitar encabezados)
        try {
            int numero = stoi(datos[i][columna]);
            numeros.push_back(numero);
        } catch (...) {
            cerr << "Error al convertir el dato en la fila " << i + 1 << " a entero." << endl;
        }
    }

    if (!numeros.empty()) {
        int suma = 0, min = numeros[0], max = numeros[0];
        for (int num : numeros) {
            suma += num;
            if (num < min) min = num;
            if (num > max) max = num;
        }
        cout << "Promedio: " << (suma / numeros.size()) << endl;
        cout << "Minimo: " << min << endl;
        cout << "Maximo: " << max << endl;
    } else {
        cerr << "No hay datos enteros en esta columna." << endl;
    }
}

// Función para ordenar una columna específica usando el método de burbuja
void ordenarColumnaBurbuja(vector<vector<string>>& datos, int columna) {
    // Convertir los datos a enteros solo para la columna especificada
    vector<int> numeros;
    for (size_t i = 1; i < datos.size(); ++i) {
        try {
            int numero = stoi(datos[i][columna]);
            numeros.push_back(numero);
        } catch (...) {
            cerr << "Error: dato no convertible en la fila " << i + 1 << endl;
        }
    }

    // Ordenar usando el método de burbuja
    for (size_t i = 0; i < numeros.size() - 1; ++i) {
        for (size_t j = 0; j < numeros.size() - i - 1; ++j) {
            if (numeros[j] > numeros[j + 1]) {
                swap(numeros[j], numeros[j + 1]);

                // Intercambiamos filas en la matriz original para reflejar el orden
                swap(datos[j + 1], datos[j + 2]);  // +1 y +2 porque empezamos en la fila 1
            }
        }
    }

    cout << "Datos ordenados en la columna especificada." << endl;
}

// Menú principal
int main() {
    string nombreArchivo = "datos_personas.csv";
    vector<vector<string>> datos = cargarCSV(nombreArchivo);
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Eliminar fila\n";
        cout << "2. Eliminar columna\n";
        cout << "3. Editar dato\n";
        cout << "4. Analizar columna (promedio, minimo, maximo)\n";
        cout << "5. Ordenar columna (burbuja)\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int fila;
                cout << "Ingrese el número de fila a eliminar: ";
                cin >> fila;
                eliminarFila(datos, fila - 1);  // Convertir a índice (0-based)
                guardarCSV(datos, nombreArchivo);
                break;
            }
            case 2: {
                int columna;
                cout << "Ingrese el número de columna a eliminar: ";
                cin >> columna;
                eliminarColumna(datos, columna - 1);  // Convertir a índice (0-based)
                guardarCSV(datos, nombreArchivo);
                break;
            }
            case 3: {
                int fila, columna;
                string nuevoValor;
                cout << "Ingrese el número de fila: ";
                cin >> fila;
                cout << "Ingrese el número de columna: ";
                cin >> columna;
                cin.ignore();
                cout << "Ingrese el nuevo valor: ";
                getline(cin, nuevoValor);
                editarDato(datos, fila - 1, columna - 1, nuevoValor);  // Convertir a índice (0-based)
                guardarCSV(datos, nombreArchivo);
                break;
            }
            case 4: {
                int columna;
                cout << "Ingrese el número de columna a analizar: ";
                cin >> columna;
                analizarColumnaEntero(datos, columna - 1);  // Convertir a índice (0-based)
                break;
            }
            case 5: {
                int columna;
                cout << "Ingrese el número de columna a ordenar: ";
                cin >> columna;
                ordenarColumnaBurbuja(datos, columna - 1);  // Convertir a índice (0-based)
                guardarCSV(datos, nombreArchivo);
                break;
            }
            case 6:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 6);

    return 0;
}
