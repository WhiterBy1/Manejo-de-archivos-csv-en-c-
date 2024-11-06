#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>  // Incluimos vector para guardar varias "Personas"

// Definimos una estructura que representa a una Persona
struct Persona {
    string nombre;  // Almacena el nombre de la persona
    int edad;            // Almacena la edad de la persona
    string ciudad;  // Almacena la ciudad de la persona
};


using namespace std;
int main() {
    // Abrimos el archivo CSV en modo de lectura
    ifstream archivo("salida.csv");
    vector<Persona> personas;  // Creamos un vector para guardar varias personas
    string linea;  // Una variable para leer cada línea del Varia
    // Leemos el archivo línea por línea
    while (getline(archivo, linea)) {
        Persona Variable_persona;  // Creamos una nueva persona para cada línea
        stringstream ss(linea);  // Utilizamos un stringstream para dividir la línea por comas
        // Leemos los datos separados por comas y los almacenamos en la persona
        getline(ss, Variable_persona.nombre, ',');  // Guardamos el nombre
        string edad;
        getline(ss, edad, ',');  // Leemos la edad como texto temporalmente
        Variable_persona.edad = stoi(edad);  // Convertimos la edad a número y la guardamos
        getline(ss, Variable_persona.ciudad, ',');  // Guardamos la ciudad

        personas.push_back(Variable_persona);  // Añadimos la persona al vector
    }
    archivo.close();  // Cerramos el archivo
    return 0;  // Finalizamos el programa+
}
