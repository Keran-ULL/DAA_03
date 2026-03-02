/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 1: Complejidad Computacional
** Autor: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 01/02/2026

** Archivo help.h: Funciones de ayuda
**
** Referencias:
**      Enlaces de interés

** Historial de revisiones:
**      01/02/2026 - Creación (primera versión) del código
**/

#include <string>
#include <vector>

void Help ();
void Usage();
bool ValidateRAMFile (const std::string& name);
bool ValidateInputOutputFile (const std::string& name);
int ValidateArguments(int argc, char* argv[]);
std::string trim(const std::string& string);
bool isInteger(const std::string& string);
std::vector<std::string> tokenize(const std::string& line);
std::string toUpper(const std::string& string);
bool isJumpOpcode(const std::string& op);