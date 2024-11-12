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
    cout << "Archivo guardado con éxito.\n";
}

// Función para mostrar el contenido completo del CSV
void mostrarCSV(const vector<vector<string>>& datos) {
    cout << "\n--- Contenido del CSV ---\n";
    for (const auto& fila : datos) {
        for (const auto& dato : fila) {
            cout << dato << " ";
        }
        cout << "\n";
    }
    cout << "-------------------------\n";
}

// Función para ordenar los datos según una columna específica
void ordenarPorColumna(vector<vector<string>>& datos, int columna) {
    if (columna >= 0 && columna < datos[0].size()) {
        // Usamos sort con una lambda que compara las filas por el valor de la columna
        sort(datos.begin() + 1, datos.end(), [columna](const vector<string>& a, const vector<string>& b) {
            return a[columna] < b[columna];
        });
        cout << "Datos ordenados según la columna " << columna + 1 << ".\n";
    } else {
        cerr << "Número de columna inválido.\n";
    }
}

// Función para eliminar una fila específica (no permite eliminar encabezados)
void eliminarFila(vector<vector<string>>& datos, int fila) {
    if (fila >= 1 && fila < datos.size()) {
        cout << "Eliminando fila: ";
        for (const auto& dato : datos[fila]) {
            cout << dato << " ";
        }
        cout << "\n";
        datos.erase(datos.begin() + fila);
    } else {
        cerr << "Número de fila inválido (no se puede eliminar la fila de encabezados).\n";
    }
}

// Función para eliminar una columna específica
void eliminarColumna(vector<vector<string>>& datos, int columna) {
    cout << "Eliminando columna: ";
    if (columna >= 0 && columna < datos[0].size()) {
        for (size_t i = 0; i < datos.size(); ++i) {
            cout << datos[i][columna] << " ";
            datos[i].erase(datos[i].begin() + columna);
        }
        cout << "\n";
    } else {
        cerr << "Número de columna inválido.\n";
    }
}

// Función para editar un dato específico (no permite editar encabezados)
void editarDato(vector<vector<string>>& datos, int fila, int columna, const string& nuevoValor) {
    if (fila >= 1 && fila < datos.size() && columna >= 0 && columna < datos[fila].size()) {
        cout << "Editando dato [" << fila + 1 << ", " << columna + 1 << "] de '"
             << datos[fila][columna] << "' a '" << nuevoValor << "'\n";
        datos[fila][columna] = nuevoValor;
    } else {
        cerr << "Coordenadas de fila o columna inválidas (no se pueden editar los encabezados).\n";
    }
}

// Función para analizar una columna de enteros (omitiendo encabezados)
void analizarColumnaEntero(const vector<vector<string>>& datos, int columna) {
    if (columna >= 0 && columna < datos[0].size()) {
        vector<int> numeros;
        for (size_t i = 1; i < datos.size(); ++i) {
            try {
                int numero = stoi(datos[i][columna]);
                numeros.push_back(numero);
            } catch (...) {
                cerr << "Error al convertir el dato en la fila " << i + 1 << " a entero.\n";
            }
        }

        if (!numeros.empty()) {
            int suma = 0, min = numeros[0], max = numeros[0];
            for (int num : numeros) {
                suma += num;
                if (num < min) min = num;
                if (num > max) max = num;
            }
            cout << "Promedio: " << (suma / numeros.size()) << "\n";
            cout << "Mínimo: " << min << "\n";
            cout << "Máximo: " << max << "\n";
        } else {
            cerr << "No hay datos enteros en esta columna.\n";
        }
    } else {
        cerr << "Número de columna inválido.\n";
    }
}

// Menú principal
int main() {
    string nombreArchivo = "datos_persona.csv";
    vector<vector<string>> datos = cargarCSV(nombreArchivo);
    int opcion;

    do {
        cout << "\n--- MENÚ ---\n";
        cout << "1. Mostrar CSV\n";
        cout << "2. Eliminar fila\n";
        cout << "3. Eliminar columna\n";
        cout << "4. Editar dato\n";
        cout << "5. Analizar columna (promedio, mínimo, máximo)\n";
        cout << "6. Ordenar datos por columna\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarCSV(datos);
                break;
            case 2: {
                int fila;
                cout << "Ingrese el número de fila a eliminar (no se permite eliminar encabezados): ";
                cin >> fila;
                eliminarFila(datos, fila - 1);
                guardarCSV(datos, nombreArchivo);
                mostrarCSV(datos);
                break;
            }
            case 3: {
                int columna;
                cout << "Ingrese el número de columna a eliminar: ";
                cin >> columna;
                eliminarColumna(datos, columna - 1);
                guardarCSV(datos, nombreArchivo);
                mostrarCSV(datos);
                break;
            }
            case 4: {
                int fila, columna;
                string nuevoValor;
                cout << "Ingrese el número de fila: ";
                cin >> fila;
                cout << "Ingrese el número de columna: ";
                cin >> columna;
                cin.ignore();
                cout << "Ingrese el nuevo valor: ";
                getline(cin, nuevoValor);
                editarDato(datos, fila - 1, columna - 1, nuevoValor);
                guardarCSV(datos, nombreArchivo);
                mostrarCSV(datos);
                break;
            }
            case 5: {
                int columna;
                cout << "Ingrese el número de columna a analizar: ";
                cin >> columna;
                analizarColumnaEntero(datos, columna - 1);
                break;
            }
            case 6: {
                int columna;
                cout << "Ingrese el número de columna para ordenar los datos: ";
                cin >> columna;
                ordenarPorColumna(datos, columna - 1);
                guardarCSV(datos, nombreArchivo);
                mostrarCSV(datos);
                break;
            }
            case 7:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 7);

    return 0;
}
