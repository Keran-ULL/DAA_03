/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide Y Vencerás
** Autor: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 03/03/2026
**
** Archivo help_functions.h: Funciones auxiliares para interacción con el usuario
**/

#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include <string>

// Ayuda
void ShowHelp();
void ShowUsage();
int ValidateArguments(int argc, char* argv[]);

// Menus
void ShowMainMenu();
void ShowAlgorithmMenu();
int AskExecutionMode();    
int AskAlgorithmChoice();    
size_t AskInstanceSize();
int AskNumberOfExperiments();

#endif
