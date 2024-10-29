#include <iostream>     // Incluye librería para entrada y salida de datos
#include <fstream>      // Incluye librería para trabajar con archivos
#include <string>       // Incluye librería para manejar cadenas de texto

int main() {
    // Intentamos abrir un archivo llamado "datos.csv" en modo de lectura
    std::ifstream archivo("datos.csv");

    // Comprobamos si el archivo se abrió correctamente
    if (!archivo.is_open()) {  // Si no está abierto...
        std::cerr << "Error al abrir el archivo.\n";  // Mostramos un mensaje de error
        return 1;  // Finalizamos el programa con un código de error
    }

    std::cout << "Archivo CSV abierto correctamente.\n";  // Mensaje de éxito si se abrió bien
    archivo.close();  // Cerramos el archivo para liberar memoria
    return 0;  // Terminamos el programa
}
