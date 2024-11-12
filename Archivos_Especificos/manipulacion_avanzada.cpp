#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

// Función para eliminar espacios en blanco al inicio y al final del string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return str.substr(first, (last - first + 1));
}

// Función para convertir string a entero con validación mejorada
int convertirAEntero(const string* str) {
    if (str == nullptr) {
        cout << "Advertencia: El puntero al string es nulo.\n";
        return -1;
    }
    if (str->empty()) {
        cout << "Advertencia: El valor está vacío.\n";
        return -1;
    }

    string trimmedStr = trim(*str);
    if (trimmedStr.empty()) {
        cout << "Advertencia: El valor contiene solo espacios en blanco.\n";
        return -1;
    }

    for (size_t i = 0; i < trimmedStr.size(); i++) {
        if (!isdigit(trimmedStr[i]) && !(i == 0 && trimmedStr[i] == '-')) {
            cout << "Advertencia: El valor no es numérico: " << trimmedStr << "\n";
            return -1;
        }
    }

    try {
        return stoi(trimmedStr);
    } catch (const exception& e) {
        cout << "Error de conversión: " << e.what() << " para el valor: " << trimmedStr << "\n";
        return -1;
    }
}

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

// Función para guardar los datos en el archivo CSV
void guardarCSV(const vector<vector<string>>& datos, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size(); i++) {
            archivo << fila[i];
            if (i < fila.size() - 1) archivo << ",";
        }
        archivo << "\n";
    }

    archivo.close();
    cout << "Datos guardados correctamente.\n";
}

// Función para mostrar el contenido del CSV
void mostrarCSV(const vector<vector<string>>& datos) {
    cout << "\nContenido del CSV:\n";
    for (const auto& fila : datos) {
        for (const auto& dato : fila) {
            cout << dato << " ";
        }
        cout << "\n";
    }
}

// Función para eliminar una fila
void eliminarFila(vector<vector<string>>& datos, int fila) {
    if (fila >= 1 && fila < datos.size()) {
        datos.erase(datos.begin() + fila);
        cout << "Fila eliminada.\n";
    } else {
        cout << "Número de fila inválido.\n";
    }
}

// Función para eliminar una columna
void eliminarColumna(vector<vector<string>>& datos, int columna) {
    if (columna >= 0 && columna < datos[0].size()) {
        for (auto& fila : datos) {
            if (columna < fila.size()) {
                fila.erase(fila.begin() + columna);
            }
        }
        cout << "Columna eliminada.\n";
    } else {
        cout << "Número de columna inválido.\n";
    }
}

// Función para editar un dato específico
void editarDato(vector<vector<string>>& datos, int fila, int columna, const string& nuevoValor) {
    if (fila >= 1 && fila < datos.size() && columna >= 0 && columna < datos[fila].size()) {
        datos[fila][columna] = nuevoValor;
        cout << "Dato editado.\n";
    } else {
        cout << "Coordenadas inválidas.\n";
    }
}

// Función para ordenar los datos por una columna numérica
void ordenarPorColumnaNumerica(vector<vector<string>>& datos, int columna) {
    vector<pair<int, size_t>> valores;

    for (size_t i = 1; i < datos.size(); i++) {
        if (columna < datos[i].size()) {
            int valor = convertirAEntero(&datos[i][columna]);
            valores.push_back({valor, i});
        } else {
            cout << "Advertencia: Índice de columna fuera de los límites para la fila " << i + 1 << ".\n";
        }
    }

    sort(valores.begin(), valores.end(), [](const pair<int, size_t>& a, const pair<int, size_t>& b) {
        return a.first < b.first;
    });

    vector<vector<string>> datosOrdenados;
    datosOrdenados.push_back(datos[0]);

    for (const auto& [valor, indice] : valores) {
        datosOrdenados.push_back(datos[indice]);
    }

    datos = datosOrdenados;
    cout << "Datos ordenados.\n";
}

// Menú principal
int main() {
    string nombreArchivo = "datos_persona.csv";
    vector<vector<string>> datos = cargarCSV(nombreArchivo);
    int opcion;

    do {
        cout << "\nMenú:\n";
        cout << "1. Mostrar CSV\n";
        cout << "2. Eliminar fila\n";
        cout << "3. Eliminar columna\n";
        cout << "4. Editar dato\n";
        cout << "5. Ordenar por edad\n";
        cout << "6. Ordenar por número de dirección\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            mostrarCSV(datos);
        } else if (opcion == 2) {
            int fila;
            cout << "Número de fila a eliminar: ";
            cin >> fila;
            eliminarFila(datos, fila - 1);
            guardarCSV(datos, nombreArchivo);
        } else if (opcion == 3) {
            int columna;
            cout << "Número de columna a eliminar: ";
            cin >> columna;
            eliminarColumna(datos, columna - 1);
            guardarCSV(datos, nombreArchivo);
        } else if (opcion == 4) {
            int fila, columna;
            string nuevoValor;
            cout << "Número de fila: ";
            cin >> fila;
            cout << "Número de columna: ";
            cin >> columna;
            cin.ignore();
            cout << "Nuevo valor: ";
            getline(cin, nuevoValor);
            editarDato(datos, fila - 1, columna - 1, nuevoValor);
            guardarCSV(datos, nombreArchivo);
        } else if (opcion == 5) {
            ordenarPorColumnaNumerica(datos, 1);
            mostrarCSV(datos);
            guardarCSV(datos, nombreArchivo);
        } else if (opcion == 6) {
            ordenarPorColumnaNumerica(datos, 4);
            mostrarCSV(datos);
            guardarCSV(datos, nombreArchivo);
        } else if (opcion == 7) {
            cout << "Saliendo del programa.\n";
        } else {
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
