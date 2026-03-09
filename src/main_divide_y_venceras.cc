/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Vencerás
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo main.cpp: Programa principal
**/
/**
** Archivo main.cpp
**/

#include <iostream>

#include "help/help_functions.h"
#include "execution/execution_funcions.h"
#include "exceptions/exceptions.h"

/**
 * @brief Función principal del programa.
 * @param argc Número de argumentos
 * @param argv Vector de argumentos
 * @returns Código de salida
 */
int main(int argc, char* argv[]) {
  int argStatus = ValidateArguments(argc, argv);
  if (argStatus != -1) return argStatus;
  while (true) {
    int opcion = AskMainOption();
    if (opcion == 0) {
      std::cout << "Saliendo...\n";
      break;
    }
    if (opcion == 1) {
      RunSortingMenu();
    }
    if (opcion == 2) {
      RunSchedulingMenu();
    }
  }
  return 0;
}
