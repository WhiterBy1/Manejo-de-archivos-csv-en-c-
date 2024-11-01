#include <iostream>   // Biblioteca para entrada y salida de datos
#include <fstream>    // Biblioteca para el manejo de archivos
#include <sstream>    // Biblioteca para trabajar con flujos de texto (útil para procesar líneas de texto)
#include <vector>     // Biblioteca para el uso de vectores (listas de tamaño variable)

int main() {
    // Nombre del archivo CSV que queremos leer y escribir
    std::string nombreArchivo = "ejemplo.csv";

    // Crear un flujo de entrada (ifstream) para leer el archivo
    std::ifstream archivoLectura(nombreArchivo);

    // Vector para almacenar los datos leídos del archivo
    std::vector<std::vector<std::string>> datos;

    // Verificar si el archivo se abrió correctamente
    if (!archivoLectura.is_open()) {
        std::cerr << "No se pudo abrir el archivo para lectura." << std::endl;
        return 1; // Salir del programa si hay un error
    }

    // Leer el archivo línea por línea
    std::string linea;
    while (std::getline(archivoLectura, linea)) { // getline lee cada línea del archivo
        std::stringstream ss(linea); // Convertimos la línea en un flujo de texto
        std::string valor;
        std::vector<std::string> fila; // Vector para almacenar una fila de datos

        // Dividir la línea en "valores" separados por comas
        while (std::getline(ss, valor, ',')) { // Lee cada valor separado por comas
            fila.push_back(valor); // Agregar el valor al vector de la fila
        }

        // Agregar la fila al vector de datos
        datos.push_back(fila);
    }

    // Cerrar el archivo después de leerlo
    archivoLectura.close();

    // Mostrar los datos leídos
    std::cout << "Datos leídos del archivo CSV:" << std::endl;
    for (const auto& fila : datos) { // Iterar sobre cada fila en el vector de datos
        for (const auto& valor : fila) { // Iterar sobre cada valor en la fila
            std::cout << valor << " "; // Mostrar el valor separado por un espacio
        }
        std::cout << std::endl; // Salto de línea después de cada fila
    }

    // Abrir el archivo en modo de escritura (ofstream) para agregar más datos
    std::ofstream archivoEscritura(nombreArchivo, std::ios::app); // ios::app permite añadir al final del archivo

    // Verificar si el archivo se abrió correctamente para escritura
    if (!archivoEscritura.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return 1;
    }

    // Datos que vamos a añadir
    std::vector<std::string> nuevaFila = {"NuevoDato1", "NuevoDato2", "NuevoDato3"};

    // Escribir la nueva fila en el archivo, separando cada valor con una coma
    for (size_t i = 0; i < nuevaFila.size(); ++i) {
        archivoEscritura << nuevaFila[i]; // Escribir el valor

        // Agregar una coma después de cada valor, excepto el último
        if (i < nuevaFila.size() - 1) {
            archivoEscritura << ",";
        }
    }

    // Añadir un salto de línea al final de la fila
    archivoEscritura << std::endl;

    // Cerrar el archivo después de escribir
    archivoEscritura.close();

    std::cout << "Nueva fila agregada al archivo CSV." << std::endl;

    return 0; // Fin del programa
}