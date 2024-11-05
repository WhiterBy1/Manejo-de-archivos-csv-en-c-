#include <iostream>
#include <fstream>
#include <string>

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

// Función para guardar los datos de una persona en un archivo
void guardarPersona(const Persona& persona, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << persona.nombre << "\n";
        archivo << persona.edad << "\n";
        archivo << persona.direccion.ciudad << "\n";
        archivo << persona.direccion.calle << "\n";
        archivo << persona.direccion.numero << "\n";
        for (const auto& trabajo : persona.trabajos) {
            archivo << trabajo << "\n";
        }
        archivo.close();
        cout << "Datos guardados en " << nombreArchivo << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

// Función para cargar los datos de una persona desde un archivo
bool cargarPersona(Persona& persona, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        getline(archivo, persona.nombre);
        archivo >> persona.edad;
        archivo.ignore();  // Ignorar el salto de línea después de la edad
        getline(archivo, persona.direccion.ciudad);
        getline(archivo, persona.direccion.calle);
        archivo >> persona.direccion.numero;
        archivo.ignore();  // Ignorar el salto de línea después del número
        for (auto& trabajo : persona.trabajos) {
            getline(archivo, trabajo);
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

    // Cargamos los datos de la persona desde el archivo
    Persona personaCargada;
    if (cargarPersona(personaCargada, nombreArchivo)) {
        // Imprimimos los datos de la persona cargada
        cout << "\nDatos cargados desde el archivo:\n";
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
