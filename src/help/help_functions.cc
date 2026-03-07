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
#include <sstream>
#include <algorithm>
#include <cctype>

/**
 * @brief Muestra la ayuda completa del programa.
 */
void ShowHelp() {
  std::cout << "ANALISIS DE ALGORITMOS - PRACTICA 2\n";
  std::cout << "Comparador de algoritmos Divide y Venceras\n\n";

  std::cout << "Uso:\n";
  std::cout << "  ./programa [--help]\n\n";

  std::cout << "Modos de ejecucion:\n";
  std::cout << "  1. Modo normal  -> Comparacion de tiempos\n";
  std::cout << "  2. Modo debug   -> Muestra instancia y solucion\n\n";

  std::cout << "Algoritmos disponibles:\n";
  std::cout << "  - MergeSort\n";
  std::cout << "  - QuickSort\n\n";
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
 * @param argc Número de argumentos
 * @param argv Vector de argumentos
 * @returns 0 si mostró help, -1 si ejecución normal, 1 si argumentos inválidos
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
 * @brief Muestra el menú principal del programa.
 */
void ShowMainMenu() {
  std::cout << "\n===== MENU PRINCIPAL =====\n";
  std::cout << "1. Modo normal (comparacion de tiempos)\n";
  std::cout << "2. Modo debug (mostrar ejecucion)\n";
  std::cout << "0. Salir\n";
}

/**
 * @brief Muestra el menú de selección de algoritmo.
 */
void ShowAlgorithmMenu() {
  std::cout << "\n===== SELECCION DE ALGORITMO =====\n";
  std::cout << "1. MergeSort\n";
  std::cout << "2. QuickSort\n";
  std::cout << "3. Ambos\n";
}

/**
 * @brief Solicita al usuario seleccionar el modo de ejecución.
 * @returns Opción seleccionada
 */
int AskExecutionMode() {
  int option;
  ShowMainMenu();
  std::cout << "Seleccione una opcion: ";
  std::cin >> option;
  return option;
}

/**
 * @brief Solicita al usuario seleccionar el algoritmo a ejecutar.
 * @returns Opción seleccionada
 */
int AskAlgorithmChoice() {
  int option;
  ShowAlgorithmMenu();
  std::cout << "Seleccione algoritmo: ";
  std::cin >> option;
  return option;
}

/**
 * @brief Solicita al usuario el tamaño de la instancia.
 * @returns Tamaño introducido
 */
size_t AskInstanceSize() {
  size_t size;
  std::cout << "Tamano de la instancia: ";
  std::cin >> size;
  return size;
}

/**
 * @brief Solicita al usuario el número de experimentos a realizar.
 * @returns Número de experimentos
 */
int AskNumberOfExperiments() {
  int n;
  std::cout << "Numero de experimentos: ";
  std::cin >> n;
  return n;
}