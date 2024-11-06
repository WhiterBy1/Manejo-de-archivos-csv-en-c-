#include <iostream>
#include <fstream>

using namespace std;
int main() {

    // Abrir un archivo para lectura ("datos_persona.csv")
    
    ifstream Nombre_del_Archivo1("datos_persona.csv");
    ofstream Nombre_del_Archivo2("datos_persona_modificado.csv", ios::app);
    fstream Nombre_del_Archivo3("datos_persona_modificado.csv", ios::in | ios::out | ios::app);
    
    return 0;
}
