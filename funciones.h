#ifndef FUNCIONES_H
#define FUNCIONES_H
void charToBin(unsigned char c, char *bin);
void invertirBits(char *bits, int n);

void invertirCada2(char *bits, int n);

void invertirCada3(char *bits, int n);
void shiftCircularDerecha(char *bits, int n);

// Convierte cadena de '0'/'1' en bytes reales
void escribirBinario(FILE *salida, const char *bits);

// ====== MÉTODO 1 ======

void metodo1(const char *entrada, const char *salida, int n);
void metodo2(const char *entrada, const char *salida, int n);
#endif // FUNCIONES_H
