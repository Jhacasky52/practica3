#include "funciones.h"


// Función para convertir un char a una cadena binaria de 8 bits
std::string charToBinary(unsigned char c) {
    return std::bitset<8>(c).to_string();
}

// Función para dividir una cadena binaria en bloques de n bits
std::vector<std::string> dividirEnBloques(const std::string& binarios, int n) {
    std::vector<std::string> bloques;
    for (size_t i = 0; i < binarios.size(); i += n) {
        std::string bloque = binarios.substr(i, n);
        if (bloque.size() < n) {
            bloque.append(n - bloque.size(), '0'); // rellenar con ceros
        }
        bloques.push_back(bloque);
    }
    return bloques;
}

std::vector<std::string> codificarArchivo(const std::string& rutaArchivo, int n){
    std::ifstream archivo(rutaArchivo);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return {};
    }

    std::string binarioTotal;
    char c;
    while (archivo.get(c)) {
        binarioTotal += charToBinary(static_cast<unsigned char>(c));
    }

    archivo.close();

    return dividirEnBloques(binarioTotal, n);
}
void charToBin(unsigned char c, char *bin) {
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = (c & (1 << i)) ? '1' : '0';
    }
    bin[8] = '\0';
}

void invertirBits(char *bits, int n) {
    for (int i = 0; i < n; i++) {
        bits[i] = (bits[i] == '0') ? '1' : '0';
    }
}

void invertirCada2(char *bits, int n) {
    for (int i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            char t1 = bits[i], t2 = bits[i + 1];
            bits[i] = (t1 == '0') ? '1' : '0';
            bits[i + 1] = (t2 == '0') ? '1' : '0';
        }
    }
}

void invertirCada3(char *bits, int n) {
    for (int i = 0; i < n; i += 3) {
        for (int j = 0; j < 3 && (i + j) < n; j++) {
            bits[i + j] = (bits[i + j] == '0') ? '1' : '0';
        }
    }
}

void shiftCircularDerecha(char *bits, int n) {
    char ultimo = bits[n - 1];
    for (int i = n - 1; i > 0; i--) {
        bits[i] = bits[i - 1];
    }
    bits[0] = ultimo;
}


// Cuenta cuántas veces aparece un carácter en una cadena
int contarCaracter(const std::string& s, char c) {
    return std::count(s.begin(), s.end(), c);
}

// Invierte cada bit ('1' -> '0', '0' -> '1')
std::string invertirBits(const std::string& bloque) {
    std::string resultado = bloque;
    for (char& bit : resultado) {
        bit = (bit == '1') ? '0' : '1';
    }
    return resultado;
}

// Invierte cada grupo de n bits
std::string invertirBitEspecificoEnCadaGrupo(const std::string& bloque, int n, int posBit) {
    std::string resultado = bloque;

    for (size_t i = 0; i < bloque.size(); i += n) {
        size_t index = i + posBit-1;
        if (index < bloque.size()) {
            resultado[index] = (bloque[index] == '1') ? '0' : '1';
        }
    }

    return resultado;
}

// Aplica la codificación a los bloques según las reglas
std::vector<std::string> transformarBloques(const std::vector<std::string>& bloquesOriginales) {
    std::vector<std::string> bloquesCodificados;

    if (bloquesOriginales.empty()) return bloquesCodificados;

    // Primer bloque: invertir todos los bits
    bloquesCodificados.push_back(invertirBits(bloquesOriginales[0]));

    // Procesar los siguientes bloques
    for (size_t i = 1; i < bloquesOriginales.size(); ++i) {
        const std::string& bloqueAnterior = bloquesOriginales[i - 1]; // sin codificar
        const std::string& bloqueActual  = bloquesOriginales[i];     // sin codificar

        int unos = contarCaracter(bloqueAnterior, '1');
        int ceros = contarCaracter(bloqueAnterior, '0');

        std::string bloqueTransformado;

        if (unos == ceros) {
            bloqueTransformado = invertirBits(bloqueActual);
        } else if (ceros > unos) {
            bloqueTransformado = invertirBitEspecificoEnCadaGrupo(bloqueActual,2, 2);
        } else {
            bloqueTransformado = invertirBitEspecificoEnCadaGrupo(bloqueActual,3, 3);
        }

        bloquesCodificados.push_back(bloqueTransformado);
    }

    return bloquesCodificados;
}


