/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 1: Complejidad Computacional
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

// ================================
// AYUDA Y USO
// ================================

void ShowHelp() {
  std::cout << "ANALISIS DE ALGORITMOS - PRACTICA 1\n";
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

void ShowUsage() {
  std::cout << "Uso: ./programa [--help]\n";
  std::cout << "Ejecuta sin argumentos para modo interactivo.\n";
}

int ValidateArguments(int argc, char* argv[]) {
  if (argc == 2) {
    std::string arg = argv[1];
    if (arg == "--help" || arg == "-h") {
      ShowHelp();
      return 0;
    }
  }
  else if (argc == 1) {
    return -1;  // ejecución normal
  }

  ShowUsage();
  return 1;
}

// ================================
// MENÚS
// ================================

void ShowMainMenu() {
  std::cout << "\n===== MENU PRINCIPAL =====\n";
  std::cout << "1. Modo normal (comparacion de tiempos)\n";
  std::cout << "2. Modo debug (mostrar ejecucion)\n";
  std::cout << "0. Salir\n";
}

void ShowAlgorithmMenu() {
  std::cout << "\n===== SELECCION DE ALGORITMO =====\n";
  std::cout << "1. MergeSort\n";
  std::cout << "2. QuickSort\n";
  std::cout << "3. Ambos\n";
}

int AskExecutionMode() {
  int option;
  ShowMainMenu();
  std::cout << "Seleccione una opcion: ";
  std::cin >> option;
  return option;
}

int AskAlgorithmChoice() {
  int option;
  ShowAlgorithmMenu();
  std::cout << "Seleccione algoritmo: ";
  std::cin >> option;
  return option;
}

size_t AskInstanceSize() {
  size_t size;
  std::cout << "Tamano de la instancia: ";
  std::cin >> size;
  return size;
}

int AskNumberOfExperiments() {
  int n;
  std::cout << "Numero de experimentos: ";
  std::cin >> n;
  return n;
}

// ================================
// UTILIDADES
// ================================

std::string trim(const std::string& str) {
  const std::string whitespace = " \t\n\r\f\v";
  size_t start = str.find_first_not_of(whitespace);
  if (start == std::string::npos) return "";
  size_t end = str.find_last_not_of(whitespace);
  return str.substr(start, end - start + 1);
}

bool isInteger(const std::string& str) {
  if (str.empty()) return false;

  size_t i = 0;
  if (str[0] == '-' || str[0] == '+') {
    if (str.size() == 1) return false;
    i = 1;
  }

  for (; i < str.size(); ++i) {
    if (!std::isdigit(str[i])) return false;
  }

  return true;
}

std::string toUpper(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c){ return std::toupper(c); });
  return result;
}
