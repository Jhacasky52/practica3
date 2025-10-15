#include <iostream>

using namespace std;

#include "funciones.h"
int main() {
    std::string nombreArchivo;
    int n, metodo;

    std::cout << "Nombre del archivo de entrada: ";
    std::cin >> nombreArchivo;

    std::cout << "Ingresa la semilla (n): ";
    std::cin >> n;

    std::cout << "Selecciona el metodo de codificacion (1): ";
    std::cin >> metodo;

    if (metodo != 1) {
        std::cerr << "Metodo no implementado." << std::endl;
        return 1;
    }

    std::vector<std::string> bloques = codificarArchivo("C:/Users/Est01/Desktop/jhacasky/practica4/practica3/ABCD.txt", n);

    if (bloques.empty()) {
        std::cerr << "Error durante la codificacion." << std::endl;
        return 1;
    }

    std::cout << "\nBloques codificados de " << n << " bits:\n";
    for (const auto& bloque : bloques) {
        std::cout << bloque << " ";
    }
    std::cout << std::endl;
    std::vector<std::string> bloquesCodificados = transformarBloques(bloques);
    std::cout << "Bloques codificados:\n";
    string bloque="1101";
    cout<<invertirBitEspecificoEnCadaGrupo(bloque,3,3)<<""<<endl;
    for (const auto& bloque : bloquesCodificados) {
        std::cout << bloque << " ";
    }
    std::cout << std::endl;
