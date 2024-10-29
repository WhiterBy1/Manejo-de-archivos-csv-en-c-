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
    // Abrimos otro archivo para escribir los datos de salida
    std::ofstream archivoSalida("salida.csv");

    std::vector<Persona> personas;  // Creamos un vector de personas
    std::string linea;

    // Leemos el archivo línea por línea
    while (std::getline(archivoEntrada, linea)) {
        Persona persona;
        std::stringstream ss(linea);

        // Leemos los campos separados por comas y los almacenamos en persona
        std::getline(ss, persona.nombre, ',');
        std::string edad;
        std::getline(ss, edad, ',');
        persona.edad = std::stoi(edad);
        std::getline(ss, persona.ciudad, ',');

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
