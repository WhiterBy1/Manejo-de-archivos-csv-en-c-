#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Definimos una estructura para almacenar la dirección de una persona
struct Direccion {
    string ciudad;
    string calle;
    int numero;
};

// Definimos una estructura que representa a una Persona
struct Persona {
    string nombre;
    int edad;
    Direccion direccion;  // Una persona tiene una dirección (estructura anidada)
    string trabajos[3];  // Array para almacenar hasta 3 trabajos anteriores
};

// Función para guardar los datos de una persona en un archivo CSV
void guardarPersona(const Persona& persona, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        // Escribir los datos de la persona en formato CSV
        archivo << persona.nombre << "," << persona.edad << ","
                << persona.direccion.ciudad << "," << persona.direccion.calle << ","
                << persona.direccion.numero << ",";
        
        // Escribir trabajos separados por comas
        for (int i = 0; i < 3; ++i) {
            archivo << persona.trabajos[i];
            if (i < 2) archivo << ","; // Agregar coma después de cada trabajo excepto el último
        }
        archivo << "\n";  // Nueva línea al final
        archivo.close();
        cout << "Datos guardados en " << nombreArchivo << " en formato CSV." << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

// Función para cargar los datos de una persona desde un archivo CSV
bool cargarPersona(Persona& persona, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo ios::app);
    if (archivo.is_open()) {
        string linea;
        if (getline(archivo, linea)) {  // Leer toda la línea
            stringstream ss(linea);     // Crear un stream a partir de la línea

            // Leer los datos separados por comas
            getline(ss, persona.nombre, ',');
            string edadStr;
            getline(ss, edadStr, ',');
            persona.edad = stoi(edadStr);

            getline(ss, persona.direccion.ciudad, ',');
            getline(ss, persona.direccion.calle, ',');
            string numeroStr;
            getline(ss, numeroStr, ',');
            persona.direccion.numero = stoi(numeroStr);

            // Leer los trabajos
            for (auto& trabajo : persona.trabajos) {
                getline(ss, trabajo, ',');
            }
        }
        archivo.close();
        return true;
    } else {
        cerr << "No se pudo abrir el archivo para leer." << endl;
        return false;
    }
}

int main() {
    // Creamos una persona con información completa
    Persona persona = {
        "Carlos",
        30,
        {"Ciudad de México", "Avenida Siempre Viva", 123},
        {"Desarrollador", "Ingeniero de soporte", "Administrador"}
    };

    // Guardamos los datos de la persona en un archivo
    string nombreArchivo = "datos_persona.txt";
    guardarPersona(persona, nombreArchivo);

    // Cargamos los datos de la persona desde el archivo CSV
    Persona personaCargada;
    if (cargarPersona(personaCargada, nombreArchivo)) {
        // Imprimimos los datos de la persona cargada
        cout << "\nDatos cargados desde el archivo CSV:\n";
        cout << "Nombre: " << personaCargada.nombre << "\n";
        cout << "Edad: " << personaCargada.edad << "\n";
        cout << "Direccion: " << personaCargada.direccion.ciudad << ", "
             << personaCargada.direccion.calle << ", " << personaCargada.direccion.numero << "\n";
        cout << "Trabajos anteriores:\n";
        for (const auto& trabajo : personaCargada.trabajos) {
            cout << "- " << trabajo << "\n";
        }
    }

    return 0;
}
