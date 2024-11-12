# Manejo-de-archivos-csv-en-c++
Ejemplos en C++ para el manejo de archivos CSV, desde lo básico hasta técnicas avanzadas. Incluye lectura, escritura y actualización de CSV utilizando `structs`, arreglos y estructuras anidadas. Cada archivo está bien documentado, abordando manejo de errores y modificación de datos. Ideal para aprender procesamiento de CSV en C++.



# Gestión de Estudiantes en C++ con Archivos CSV

Este proyecto en C++ permite gestionar una lista de estudiantes, utilizando un archivo CSV para almacenar y cargar los datos. Las funcionalidades incluyen insertar, modificar, eliminar, buscar y mostrar estudiantes, con un enfoque en el manejo de archivos.

## **Estructura del Proyecto**
El programa utiliza las siguientes bibliotecas:
- `<iostream>`: Para la entrada y salida de datos.
- `<vector>`: Para almacenar los estudiantes en un contenedor dinámico.
- `<string>`: Para manejar cadenas de texto.
- `<fstream>`: Para el manejo de archivos (lectura y escritura).
- `<sstream>`: Para procesar datos de texto y convertirlos a otros tipos.

### **Estructura `Estudiante`**
```
struct Estudiante {
    int id;
    string nombre;
    string carrera;
    float promedio;
};
```
Define la estructura de un estudiante con los siguientes campos:
- `id`: Identificador único del estudiante.
- `nombre`: Nombre completo del estudiante.
- `carrera`: Carrera del estudiante.
- `promedio`: Promedio de calificaciones.

### **Vector de Estudiantes**
```
vector<Estudiante> listaEstudiantes;
```
Utiliza un vector para almacenar todos los estudiantes.

## **Funciones del Programa**

### **1. `cargarEstudiantesCSV()`**
```
void cargarEstudiantesCSV() { ... }
```
- Lee los datos desde el archivo `estudiantes.csv`.
- Utiliza `ifstream` para abrir el archivo.
- Procesa cada línea con `stringstream` para separar los campos y crea un objeto `Estudiante`.
- Si el archivo no existe, muestra un mensaje y continúa.

### **2. `guardarEstudiantesCSV()`**
```
void guardarEstudiantesCSV() { ... }
```
- Guarda la lista de estudiantes en el archivo `estudiantes.csv`.
- Utiliza `ofstream` para escribir en el archivo.
- Recorre el vector `listaEstudiantes` y escribe cada estudiante como una línea en el archivo CSV.

### **3. `existeID(int id)`**
```
bool existeID(int id) { ... }
```
- Verifica si un ID de estudiante ya existe en el vector.
- Devuelve `true` si el ID existe, y `false` si no.

### **4. `insertarEstudiante()`**
```
void insertarEstudiante() { ... }
```
- Solicita al usuario los datos del nuevo estudiante.
- Verifica que el ID no exista utilizando `existeID()`.
- Agrega el nuevo estudiante al vector `listaEstudiantes` y guarda los cambios en el archivo CSV.
- Muestra un mensaje de confirmación.

### **5. `actualizarPromedio()`**
```
void actualizarPromedio() { ... }
```
- Solicita el ID del estudiante a actualizar.
- Busca el estudiante por ID en el vector.
- Solicita el nuevo promedio y actualiza el campo `promedio`.
- Guarda los cambios en el archivo CSV y muestra un mensaje de confirmación.

### **6. `modificarEstudiante()`**
```
void modificarEstudiante() { ... }
```
- Solicita el ID del estudiante a modificar.
- Permite cambiar el nombre y la carrera del estudiante.
- Guarda los cambios en el archivo CSV y muestra un mensaje de confirmación.

### **7. `buscarEstudiante()`**
```
void buscarEstudiante() { ... }
```
- Solicita el ID del estudiante a buscar.
- Busca el estudiante por ID y muestra sus datos si lo encuentra.
- Si no lo encuentra, muestra un mensaje indicando que el estudiante no existe.

### **8. `eliminarEstudiante()`**
```
void eliminarEstudiante() { ... }
```
- Solicita el ID del estudiante a eliminar.
- Busca el estudiante en el vector y lo elimina si lo encuentra.
- Guarda los cambios en el archivo CSV y muestra un mensaje de confirmación.

### **9. `mostrarEstudiantes()`**
```
void mostrarEstudiantes() { ... }
```
- Muestra la lista completa de estudiantes almacenados en el vector.
- Si la lista está vacía, muestra un mensaje indicando que no hay estudiantes registrados.

## **Función `menu()`**
```
void menu() { ... }
```
- Muestra un menú interactivo con las opciones disponibles.
- Utiliza un bucle `do-while` para permitir al usuario seleccionar opciones hasta que decida salir.
- Llama a las funciones correspondientes según la opción elegida.

## **Función `main()`**
```
int main() {
    cargarEstudiantesCSV();
    menu();
    return 0;
}
```
- Llama a `cargarEstudiantesCSV()` para cargar los datos desde el archivo al iniciar.
- Ejecuta el menú interactivo.
- Al finalizar, termina el programa.

## **Archivo CSV: `estudiantes.csv`**
El archivo CSV tiene el siguiente formato:
```
ID,Nombre,Carrera,Promedio
1,Juan Perez,Ingeniería,4.5
2,Maria Lopez,Medicina,4.8
3,Carlos Sanchez,Arquitectura,4.2
```
- Cada línea representa un estudiante.
- Los campos están separados por comas: `ID, Nombre, Carrera, Promedio`.

## **Consideraciones**
- El programa guarda automáticamente los cambios en el archivo CSV después de cada operación (insertar, modificar, eliminar).
- El archivo CSV se carga automáticamente al iniciar el programa, permitiendo continuar con los datos previos.
- Si el archivo `estudiantes.csv` no existe, el programa lo crea automáticamente.

## **Ejemplo de Uso**
```
--- Menú de Gestión de Estudiantes ---
1. Insertar estudiante
2. Actualizar promedio
3. Modificar estudiante
4. Buscar estudiante
5. Eliminar estudiante
6. Mostrar estudiantes
7. Salir
Seleccione una opción: 1
Ingrese el ID del estudiante: 4
Ingrese el nombre del estudiante: Ana Torres
Ingrese la carrera del estudiante: Derecho
Ingrese el promedio del estudiante: 4.7
Estudiante 'Ana Torres' agregado exitosamente.
```

## **Conclusión**
Este programa permite gestionar una lista de estudiantes de manera eficiente, utilizando archivos CSV para persistir los datos. Es fácil de usar y muestra mensajes claros para cada operación, asegurando una buena experiencia de usuario.
