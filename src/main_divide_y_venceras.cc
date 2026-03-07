/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 1: Complejidad Computacional
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo main.cpp: Programa principal
**/

#include <iostream>
#include <memory>
#include <string>

#include "help/help_functions.h"
#include "execution/execution_funcions.h"

#include "exceptions/exceptions.h"

#include "generators/GeneradorVectores.h"
#include "analysis/MedidorTiempos.h"
#include "analysis/TablaResultados.h"

#include "ordenacion/mergeSort.h"
#include "ordenacion/quickSort.h"

#include "scheduling/InstanciaScheduling.hpp"
#include "scheduling/SolucionSchedulling.hpp"
#include "scheduling/SchedulingParser.hpp"
#include "scheduling/SchedulingDyV.hpp"

using namespace std;

/**
 * @brief Función principal del programa.
 *
 * Permite seleccionar modo de ejecución, algoritmo, tamaño de instancia
 * y número de experimentos. Soporta tanto ordenación como Scheduling.
 */
int main(int argc, char* argv[]) {
  // Validar argumentos de línea de comandos
  int argStatus = ValidateArguments(argc, argv);
  if (argStatus != -1) return argStatus;

  while (true) {
    int modo = AskExecutionMode();

    if (modo == 0) {
      std::cout << "Saliendo...\n";
      break;
    }

    if (modo != 1 && modo != 2) {
      std::cout << "Opción inválida, intente de nuevo.\n";
      continue;
    }

    int algoritmo = AskAlgorithmChoice();
    if (algoritmo < 1 || algoritmo > 3) {
      std::cout << "Opción de algoritmo inválida.\n";
      continue;
    }

    size_t size = AskInstanceSize();
    int experimentos = 1;
    if (modo == 1) { 
      experimentos = AskNumberOfExperiments();
    }

    if (modo == 2) {  
      EjecutarDebugOrdenacion(algoritmo, size);
    } else { 
      EjecutarNormalOrdenacion(algoritmo, size, experimentos);
    }

    std::cout << "\n=== EJECUCIÓN DE SCHEDULING ===\n";
    std::string archivo;
    std::cout << "Ingrese ruta del archivo JSON de Scheduling: ";
    std::cin >> archivo;

    try {
      if (modo == 2) {
        EjecutarDebugScheduling(archivo);
      } else {
        EjecutarNormalScheduling(archivo);
      }
    } catch (const std::exception& e) {
      std::cout << "Error al ejecutar Scheduling: " << e.what() << std::endl;
    }
    std::cout << "\nEjecución completa.\n";
  }
  return 0;
}