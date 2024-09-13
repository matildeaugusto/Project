#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <stdio.h>

#define MAX_LINE_LENGTH 256
#define EXTENSAO_MAPS ".1maps"

int valida_extensao(const char *filename);
FILE *abre_arquivo(const char *filename, const char *mode);
int main(int argc, char *argv[]);
void task1(FILE *output_file);
void task2(FILE *output_file);
void task3(FILE *output_file);

#endif 
