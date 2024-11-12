#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Definimos la estructura para almacenar la temperatura de un día
struct registro_temp {
    int dia;
    double temperatura;
};

// Función para registrar temperaturas y guardarlas en el archivo CSV
void registrar_temperaturas(const string &nombre_archivo) {
    ofstream archivo(nombre_archivo, ios::app);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    for (int i = 1; i <= 7; ++i) {
        double temperatura;
        cout << "Ingrese la temperatura para el dia " << i << ": ";
        cin >> temperatura;

        archivo << i << "," << temperatura << endl;
    }

    archivo.close();
    cout << "Temperaturas registradas exitosamente." << endl;
}

// Función para leer las temperaturas del archivo CSV
vector<registro_temp> leer_temperaturas(const string &nombre_archivo) {
    vector<registro_temp> temperaturas;
    ifstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            registro_temp temp;
            char coma; // Para ignorar la coma en el CSV
            iss >> temp.dia >> coma >> temp.temperatura;
            temperaturas.push_back(temp);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
    return temperaturas;
}

// Función para calcular el promedio de temperaturas
double calcular_promedio(const vector<registro_temp> &temperaturas) {
    if (temperaturas.empty()) {
        return 0.0;
    }

    double suma = 0;
    for (const auto &temp : temperaturas) {
        suma += temp.temperatura;
    }

    return suma / temperaturas.size();
}

// Función para encontrar la temperatura máxima y mínima
pair<double, double> encontrar_temperaturas_maxima_minima(const vector<registro_temp> &temperaturas) {
    if (temperaturas.empty()) {
        return make_pair(0.0, 0.0);
    }

    double maxima = temperaturas[0].temperatura;
    double minima = temperaturas[0].temperatura;

    for (const auto &temp : temperaturas) {
        if (temp.temperatura > maxima) {
            maxima = temp.temperatura;
        }
        if (temp.temperatura < minima) {
            minima = temp.temperatura;
        }
    }

    return make_pair(maxima, minima);
}

// Función principal
int main() {
    string nombre_archivo = "temperatura.csv";

    int opcion;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Registrar temperaturas de la semana\n";
        cout << "2. Mostrar promedio de temperaturas\n";
        cout << "3. Mostrar temperatura maxima y minima\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                registrar_temperaturas(nombre_archivo);
                break;
            }
            case 2: {
                vector<registro_temp> temperaturas = leer_temperaturas(nombre_archivo);
                double promedio = calcular_promedio(temperaturas);
                cout << "El promedio de temperaturas es: " << promedio << " grados." << endl;
                break;
            }
            case 3: {
                vector<registro_temp> temperaturas = leer_temperaturas(nombre_archivo);
                auto [maxima, minima] = encontrar_temperaturas_maxima_minima(temperaturas);
                cout << "Temperatura maxima: " << maxima << " grados." << endl;
                cout << "Temperatura minima: " << minima << " grados." << endl;
                break;
            }
            case 4: {
                cout << "Saliendo del programa." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Intente nuevamente." << endl;
                break;
            }
        }
    } while (opcion != 4);

    return 0;
}
