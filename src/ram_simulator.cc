/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 2: Máquina RAM
** Autores: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 21/02/2026

** Archivo main.cc: Programa principal que ejecuta el menú
**
** Referencias:
**      Enlaces de interés

** Historial de revisiones:
**      21/02/2026 - Creación (primera versión)
**/

#include <string>
#include <iostream>
#include "core/ram_machine.h"
#include "help/help_functions.h"

int main(int argc, char* argv[]) {
  int result = ValidateArguments(argc, argv);
  if (result >= 0) return result;
  std::string progFile = argv[1];
  std::string inputFile = argv[2];
  std::string outputFile = argv[3];

  RAMMachine machine;

  try {
    machine.loadProgram(progFile);
    machine.loadInputTape(inputFile);
    machine.setOutputFile(outputFile);
    machine.run();
  } catch (const Exceptions& error) {
    std::cerr << "Error: " << error.what() << std::endl;
    return 1;
  } catch (const std::exception& error) {
    std::cerr << "Unexpected error: " << error.what() << std::endl;
    return 1;
  }
  
  return 0;
}