/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Venceras
** Autor: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo help_functions.cc: Implementación de funciones auxiliares
**/

#include "help_functions.h"
#include <iostream>
#include <string>
#include "../execution/execution_funcions.h"

/**
 * @brief Muestra la ayuda completa del programa.
 */
void ShowHelp() {
  std::cout << "ANALISIS DE ALGORITMOS - PRACTICA 3\n";
  std::cout << "Comparador de algoritmos Divide y Venceras\n\n";
  std::cout << "Uso:\n";
  std::cout << "  ./programa [--help]\n\n";
  std::cout << "Modos de ejecucion:\n";
  std::cout << "  1. Modo normal  -> Comparacion de tiempos\n";
  std::cout << "  2. Modo debug   -> Muestra instancia y solucion\n\n";
  std::cout << "Algoritmos disponibles:\n";
  std::cout << "  - MergeSort\n";
  std::cout << "  - QuickSort\n\n";
  std::cout << "Tambien permite ejecutar el algoritmo de Scheduling.\n";
}


/**
 * @brief Muestra el uso básico del programa.
 */
void ShowUsage() {
  std::cout << "Uso: ./programa [--help]\n";
  std::cout << "Ejecuta sin argumentos para modo interactivo.\n";
}


/**
 * @brief Valida los argumentos de entrada del programa.
 */
int ValidateArguments(int argc, char* argv[]) {
  if (argc == 2) {
    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h") {
      ShowHelp();
      return 0;
    }
  }
  else if (argc == 1) {
    return -1;
  }
  ShowUsage();
  return 1;
}


/**
 * @brief Muestra el menú principal
 */
int AskMainOption() {
  int option;
  std::cout << "\n===== MENU PRINCIPAL =====\n";
  std::cout << "1. Ejecutar algoritmos de ordenacion\n";
  std::cout << "2. Ejecutar Scheduling\n";
  std::cout << "0. Salir\n";
  std::cout << "Seleccione una opcion: ";
  std::cin >> option;
  return option;
}


/**
 * @brief Muestra el menú de selección de algoritmo
 */
int AskAlgorithmChoice() {
  int option;
  std::cout << "\n===== SELECCION DE ALGORITMO =====\n";
  std::cout << "1. MergeSort\n";
  std::cout << "2. QuickSort\n";
  std::cout << "3. Ambos\n";
  std::cout << "Seleccione algoritmo: ";
  std::cin >> option;
  return option;
}


/**
 * @brief Solicita modo de ejecución
 */
int AskExecutionMode() {
  int option;
  std::cout << "\n===== MODO DE EJECUCION =====\n";
  std::cout << "1. Modo normal (comparacion de tiempos)\n";
  std::cout << "2. Modo debug (mostrar ejecucion)\n";
  std::cout << "Seleccione modo: ";
  std::cin >> option;
  return option;
}


/**
 * @brief Solicita tamaño de instancia
 */
size_t AskInstanceSize() {
  size_t size;
  std::cout << "Tamano de la instancia: ";
  std::cin >> size;
  return size;
}


/**
 * @brief Solicita número de experimentos
 */
int AskNumberOfExperiments() {
  int n;
  std::cout << "Numero de experimentos: ";
  std::cin >> n;
  return n;
}


/**
 * @brief Ejecuta el submenu completo de ordenación
 */
void RunSortingMenu() {
  int algoritmo = AskAlgorithmChoice();
  int modo = AskExecutionMode();
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
}

/**
 * @brief Ejecuta el submenu de Scheduling
 */
void RunSchedulingMenu() {
  int modo = AskExecutionMode();
  std::string archivo;
  std::cout << "Ingrese ruta del archivo JSON: ";
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
}
