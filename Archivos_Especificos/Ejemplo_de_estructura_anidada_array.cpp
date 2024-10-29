#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Definimos una estructura para almacenar la dirección de una persona
struct Direccion {
    std::string ciudad;
    std::string calle;
    int numero;
};

// Definimos una estructura que representa a una Persona
struct Persona {
    std::string nombre;
    int edad;
    Direccion direccion;  // Una persona tiene una dirección (estructura anidada)
    std::string trabajos[3];  // Array para almacenar hasta 3 trabajos anteriores
};

int main() {
    // Creamos una persona con información completa
    Persona persona = {
        "Carlos",
        30,
        {"Ciudad de México", "Avenida Siempre Viva", 123},  // Dirección
        {"Desarrollador", "Ingeniero de soporte", "Administrador"}  // Trabajos anteriores
    };

    // Imprimimos los datos de la persona
    std::cout << "Nombre: " << persona.nombre << "\n";
    std::cout << "Edad: " << persona.edad << "\n";
    std::cout << "Direccion: " << persona.direccion.ciudad << ", "
              << persona.direccion.calle << ", " << persona.direccion.numero << "\n";
    std::cout << "Trabajos anteriores:\n";
    for (const auto& trabajo : persona.trabajos) {
        std::cout << "- " << trabajo << "\n";
    }

    return 0;
}
