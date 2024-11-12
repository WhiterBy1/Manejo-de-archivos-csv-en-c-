#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Estructura para manejar los estudiantes
struct Estudiante { 
    int id;
    string nombre;
    string carrera;
    float promedio;
};

vector<Estudiante> listaEstudiantes;

// Función para cargar datos desde un archivo CSV
void cargarEstudiantesCSV() {
    ifstream archivo("estudiantes.csv");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo 'estudiantes.csv'. Creando uno nuevo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Estudiante estudiante;
        string promedio;

        getline(ss, estudiante.id, ',');
        getline(ss, estudiante.nombre, ',');
        getline(ss, estudiante.carrera, ',');
        getline(ss, promedio, ',');

        estudiante.promedio = stof(promedio);
        listaEstudiantes.push_back(estudiante);
    }

    archivo.close();
    cout << "Datos cargados exitosamente desde 'estudiantes.csv'." << endl;
}

// Función para guardar datos en un archivo CSV
void guardarEstudiantesCSV() {
    ofstream archivo("estudiantes.csv");
    for (const auto& estudiante : listaEstudiantes) {
        archivo << estudiante.id << ","
                << estudiante.nombre << ","
                << estudiante.carrera << ","
                << estudiante.promedio << endl;
    }
    archivo.close();
    cout << "Datos guardados exitosamente en 'estudiantes.csv'." << endl;
}

// Función para validar si un ID ya existe
bool existeID(int id) {
    for (const auto& estudiante : listaEstudiantes) {
        if (estudiante.id == id) {
            return true;
        }
    }
    return false;
}

// Función para insertar un nuevo estudiante
void insertarEstudiante() {
    Estudiante estudiante;
    do {
        cout << "Ingrese el ID del estudiante: ";
        cin >> estudiante.id;
        if (existeID(estudiante.id)) {
            cout << "Error: El ID ya existe. Ingrese un ID diferente." << endl;
        }
    } while (existeID(estudiante.id));

    cin.ignore();
    cout << "Ingrese el nombre del estudiante: ";
    getline(cin, estudiante.nombre);
    cout << "Ingrese la carrera del estudiante: ";
    getline(cin, estudiante.carrera);
    cout << "Ingrese el promedio del estudiante: ";
    cin >> estudiante.promedio;

    listaEstudiantes.push_back(estudiante);
    guardarEstudiantesCSV();
    cout << "Estudiante '" << estudiante.nombre << "' agregado exitosamente." << endl;
}

// Función para actualizar el promedio de un estudiante
void actualizarPromedio() {
    int id;
    cout << "Ingrese el ID del estudiante a actualizar: ";
    cin >> id;

    for (auto& estudiante : listaEstudiantes) {
        if (estudiante.id == id) {
            cout << "Estudiante encontrado: '" << estudiante.nombre << "'" << endl;
            cout << "Ingrese el nuevo promedio: ";
            cin >> estudiante.promedio;
            guardarEstudiantesCSV();
            cout << "Promedio del estudiante '" << estudiante.nombre << "' actualizado a " << estudiante.promedio << "." << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}

// Función para modificar nombre y carrera del estudiante
void modificarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a modificar: ";
    cin >> id;

    for (auto& estudiante : listaEstudiantes) {
        if (estudiante.id == id) {
            cout << "Estudiante encontrado: '" << estudiante.nombre << "'" << endl;
            cin.ignore();
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, estudiante.nombre);
            cout << "Ingrese la nueva carrera: ";
            getline(cin, estudiante.carrera);
            guardarEstudiantesCSV();
            cout << "Estudiante modificado exitosamente: '" << estudiante.nombre << "', Carrera: '" << estudiante.carrera << "'" << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}

// Función para buscar un estudiante por ID
void buscarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a buscar: ";
    cin >> id;

    for (const auto& estudiante : listaEstudiantes) {
        if (estudiante.id == id) {
            cout << "ID: " << estudiante.id
                 << ", Nombre: " << estudiante.nombre
                 << ", Carrera: " << estudiante.carrera
                 << ", Promedio: " << estudiante.promedio << endl;
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}

// Función para eliminar un estudiante por ID
void eliminarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a eliminar: ";
    cin >> id;

    for (size_t i = 0; i < listaEstudiantes.size(); ++i) {
        if (listaEstudiantes[i].id == id) {
            cout << "Estudiante eliminado: '" << listaEstudiantes[i].nombre << "'" << endl;
            listaEstudiantes.erase(listaEstudiantes.begin() + i);
            guardarEstudiantesCSV();
            return;
        }
    }
    cout << "Estudiante no encontrado." << endl;
}

// Función para mostrar la lista de estudiantes
void mostrarEstudiantes() {
    if (listaEstudiantes.empty()) {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    cout << "Lista de estudiantes:" << endl;
    for (const auto& estudiante : listaEstudiantes) {
        cout << "ID: " << estudiante.id
             << ", Nombre: " << estudiante.nombre
             << ", Carrera: " << estudiante.carrera
             << ", Promedio: " << estudiante.promedio << endl;
    }
}

// Menú principal
void menu() {
    int opcion;
    do {
        cout << "\n--- Menú de Gestión de Estudiantes ---" << endl;
        cout << "1. Insertar estudiante" << endl;
        cout << "2. Actualizar promedio" << endl;
        cout << "3. Modificar estudiante" << endl;
        cout << "4. Buscar estudiante" << endl;
        cout << "5. Eliminar estudiante" << endl;
        cout << "6. Mostrar estudiantes" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: insertarEstudiante(); break;
            case 2: actualizarPromedio(); break;
            case 3: modificarEstudiante(); break;
            case 4: buscarEstudiante(); break;
            case 5: eliminarEstudiante(); break;
            case 6: mostrarEstudiantes(); break;
            case 7: cout << "Saliendo del programa..." << endl; break;
            default: cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 7);
}

int main() {
    cargarEstudiantesCSV();
    menu();
    return 0;
}
