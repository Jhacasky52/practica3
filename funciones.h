#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>
#ifndef FUNCIONES_H
#define FUNCIONES_H
std::vector<std::string> codificarArchivo(const std::string& rutaArchivo, int n);
std::string invertirCadaNBITS(const std::string& bloque, int n);
std::vector<std::string> transformarBloques(const std::vector<std::string>& bloquesOriginales);
int contarCaracter(const std::string& s, char c);
std::string invertirBits(const std::string& bloque);
std::string invertirBitEspecificoEnCadaGrupo(const std::string& bloque, int n, int posBit);
#endif // FUNCIONES_H
