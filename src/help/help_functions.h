/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 1: Complejidad Computacional
** Autor: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 03/03/2026
**
** Archivo help_functions.h: Funciones auxiliares para interacción con el usuario
**/

#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include <string>

// ================================
// AYUDA Y USO
// ================================

void ShowHelp();
void ShowUsage();
int ValidateArguments(int argc, char* argv[]);

// ================================
// MENÚS
// ================================

void ShowMainMenu();
void ShowAlgorithmMenu();

int AskExecutionMode();      // 1 = Normal | 2 = Debug
int AskAlgorithmChoice();    // 1 = MergeSort | 2 = QuickSort | 3 = Ambos
size_t AskInstanceSize();
int AskNumberOfExperiments();

// ================================
// UTILIDADES
// ================================

std::string trim(const std::string& str);
bool isInteger(const std::string& str);
std::string toUpper(const std::string& str);

#endif
