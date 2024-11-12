#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Persona {
    std::string nombre;
    int edad;
    std::string ciudad;
};

int main() {
    // Abrimos el archivo en modo de lectura
    std::ifstream archivoEntrada("datos_persona.csv");
    std::vector<Persona> personas;
    std::string linea;

    // Leemos cada línea del archivo
    while (std::getline(archivoEntrada, linea)) {
        Persona persona;
        std::stringstream ss(linea);

        // Dividimos la línea en nombre, edad y ciudad
        std::getline(ss, persona.nombre, ',');
        std::string edad;
        std::getline(ss, edad, ',');
        persona.edad = std::stoi(edad);
        std::getline(ss, persona.ciudad, ',');

        // Si la persona se llama "Juan", le aumentamos la edad en 1
        if (persona.nombre == "Juan") {
            persona.edad += 1;
        }

        personas.push_back(persona);  // Guardamos la persona en el vector
    }
    archivoEntrada.close();  // Cerramos el archivo de lectura

    // Abrimos el archivo en modo de escritura para guardar los cambios
    std::ofstream archivoSalida("personas.csv");
    for (const auto& persona : personas) {
        archivoSalida << persona.nombre << "," << persona.edad << "," << persona.ciudad << "\n";
    }
    archivoSalida.close();  // Cerramos el archivo de escritura
    return 0;  // Terminamos el programa
}
