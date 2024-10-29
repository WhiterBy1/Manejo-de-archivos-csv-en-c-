#include <iostream>
#include <fstream>

int main() {
    std::ifstream archivo("noexiste.csv");  // Intentamos abrir un archivo que no existe

    // Comprobamos si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo.\n";
        return 1;  // Finalizamos el programa si el archivo no existe
    }

    std::string linea;
    while (std::getline(archivo, linea)) {  // Leemos cada línea del archivo
        if (linea.empty()) {  // Si la línea está vacía...
            std::cerr << "Advertencia: Línea vacía encontrada.\n";
            continue;  // Saltamos a la siguiente línea sin procesar esta
        }
        std::cout << "Línea leída: " << linea << "\n";
    }

    archivo.close();  // Cerramos el archivo después de terminar
    return 0;
}