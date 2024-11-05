#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Definimos una estructura para almacenar información de una Persona
struct Persona {
    std::string nombre;
    int edad;
    std::string ciudad;
};

int main() {
    // Abrimos un archivo para leer los datos de entrada
    std::ifstream archivoEntrada("entrada.csv");
    // Verificamos si el archivo se abrió correctamente
    if (!archivoEntrada.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada.\n";
        return 1;
    }

    // Abrimos otro archivo para escribir los datos de salida
    std::ofstream archivoSalida("salida.csv");
    if (!archivoSalida.is_open()) {
        std::cerr << "No se pudo abrir el archivo de salida.\n";
        return 1;
    }

    std::vector<Persona> personas;  // Creamos un vector de personas
    std::string linea;

    // Omitimos la primera línea del archivo (los encabezados)
    std::getline(archivoEntrada, linea);

    // Leemos el archivo línea por línea
    while (std::getline(archivoEntrada, linea)) {
        Persona persona;
        std::stringstream ss(linea);

        // Leemos los campos separados por comas y los almacenamos en persona
        std::getline(ss, persona.nombre, ',');
        std::string edad;
        std::getline(ss, edad, ',');
        
        // Eliminar espacios adicionales que puedan estar presentes
        edad.erase(0, edad.find_first_not_of(" "));  // Eliminar espacios iniciales
        try {
            persona.edad = std::stoi(edad);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: edad inválida en la línea \"" << linea << "\"\n";
            continue;  // Saltar a la siguiente línea
        }
        
        std::getline(ss, persona.ciudad, ',');
        persona.ciudad.erase(0, persona.ciudad.find_first_not_of(" "));  // Eliminar espacios iniciales

        personas.push_back(persona);  // Añadimos persona al vector
    }

    // Escribimos cada persona en el archivo de salida
    for (const auto& persona : personas) {
        archivoSalida << persona.nombre << "," << persona.edad << "," << persona.ciudad << "\n";
    }

    archivoEntrada.close();  // Cerramos el archivo de entrada
    archivoSalida.close();  // Cerramos el archivo de salida
    return 0;  // Terminamos el programa
}
