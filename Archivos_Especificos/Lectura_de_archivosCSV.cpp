#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>  // Incluimos vector para guardar varias "Personas"

// Definimos una estructura que representa a una Persona
struct Persona {
    std::string nombre;  // Almacena el nombre de la persona
    int edad;            // Almacena la edad de la persona
    std::string ciudad;  // Almacena la ciudad de la persona
};

int main() {
    // Abrimos el archivo CSV en modo de lectura
    std::ifstream archivo("salida.csv");
    std::vector<Persona> personas;  // Creamos un vector para guardar varias personas
    std::string linea;  // Una variable para leer cada línea del archivo

    // Leemos el archivo línea por línea
    while (std::getline(archivo, linea)) {
        Persona persona;  // Creamos una nueva persona para cada línea
        std::stringstream ss(linea);  // Utilizamos un stringstream para dividir la línea por comas

        // Leemos los datos separados por comas y los almacenamos en la persona
        std::getline(ss, persona.nombre, ',');  // Guardamos el nombre
        std::string edad;
        std::getline(ss, edad, ',');  // Leemos la edad como texto temporalmente
        persona.edad = std::stoi(edad);  // Convertimos la edad a número y la guardamos
        std::getline(ss, persona.ciudad, ',');  // Guardamos la ciudad

        personas.push_back(persona);  // Añadimos la persona al vector
    }
    archivo.close();  // Cerramos el archivo
    return 0;  // Finalizamos el programa+
}
