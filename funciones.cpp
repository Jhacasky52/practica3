#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

// Convierte cadena de '0'/'1' en bytes reales
void escribirBinario(FILE *salida, const char *bits) {
    int len = strlen(bits);
    for (int i = 0; i < len; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8 && (i + j) < len; j++) {
            byte = (byte << 1) | (bits[i + j] - '0');
        }
        fwrite(&byte, 1, 1, salida);
    }
}

// ====== MÉTODO 1 ======

void metodo1(const char *entrada, const char *salida, int n) {
    FILE *fin = fopen(entrada, "r");
    FILE *fout = fopen(salida, "wb");
    if (!fin || !fout) {
        printf("Error abriendo archivos.\n");
        return;
    }

    // Convertir todo el archivo a binario ASCII
    char *binario = malloc(8 * 1000000); // soporte hasta ~1MB texto
    binario[0] = '\0';
    char aux[9];
    int totalBits = 0;
    unsigned char c;

    while (fread(&c, 1, 1, fin)) {
        charToBin(c, aux);
        strcat(binario, aux);
        totalBits += 8;
    }

    int bloques = (totalBits + n - 1) / n;
    char codificado[totalBits + 1];
    codificado[0] = '\0';

    // Aplicar reglas
    for (int b = 0; b < bloques; b++) {
        char bloque[n + 1];
        strncpy(bloque, binario + b * n, n);
        bloque[n] = '\0';

        if (strlen(bloque) == 0) break;

        if (b == 0) {
            invertirBits(bloque, strlen(bloque));
        } else {
            // analizar bloque anterior sin codificar
            char anterior[n + 1];
            strncpy(anterior, binario + (b - 1) * n, n);
            anterior[n] = '\0';

            int unos = 0, ceros = 0;
            for (int i = 0; i < strlen(anterior); i++) {
                if (anterior[i] == '1') unos++; else ceros++;
            }

            if (unos == ceros)
                invertirBits(bloque, strlen(bloque));
            else if (ceros > unos)
                invertirCada2(bloque, strlen(bloque));
            else
                invertirCada3(bloque, strlen(bloque));
        }
        strcat(codificado, bloque);
    }

    escribirBinario(fout, codificado);

    fclose(fin);
    fclose(fout);
    free(binario);

    printf("Archivo codificado con método 1 guardado en %s\n", salida);
}

// ====== MÉTODO 2 ======

void metodo2(const char *entrada, const char *salida, int n) {
    FILE *fin = fopen(entrada, "r");
    FILE *fout = fopen(salida, "wb");
    if (!fin || !fout) {
        printf("Error abriendo archivos.\n");
        return;
    }

    // Convertir a binario
    char *binario = malloc(8 * 1000000);
    binario[0] = '\0';
    char aux[9];
    int totalBits = 0;
    unsigned char c;

    while (fread(&c, 1, 1, fin)) {
        charToBin(c, aux);
        strcat(binario, aux);
        totalBits += 8;
    }

    int bloques = (totalBits + n - 1) / n;
    char codificado[totalBits + 1];
    codificado[0] = '\0';

    for (int b = 0; b < bloques; b++) {
        char bloque[n + 1];
        strncpy(bloque, binario + b * n, n);
        bloque[n] = '\0';
        if (strlen(bloque) == 0) break;
        shiftCircularDerecha(bloque, strlen(bloque));
        strcat(codificado, bloque);
    }

    escribirBinario(fout, codificado);

    fclose(fin);
    fclose(fout);
    free(binario);

    printf("Archivo codificado con método 2 guardado en %s\n", salida);
}
