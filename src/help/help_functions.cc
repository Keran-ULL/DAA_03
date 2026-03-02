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

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include "help_functions.h"

/**
 * @brief Prints Help to the user
 */
void Help() {
  std::cout << "RAM MACHINE SIMULATOR" << std::endl;
  std::cout << "Simulates the execution of a RAM program with input and output tapes.\n" << std::endl;

  std::cout << "Usage:" << std::endl;
  std::cout << "  ./ram_simulator <program.ram> <input.tape> <output.tape>" << std::endl;
  std::cout << std::endl;

  std::cout << "Arguments:" << std::endl;
  std::cout << "  <program.ram>   : File containing the RAM program (instructions and labels)." << std::endl;
  std::cout << "  <input.tape>    : File with input data (one integer per line)." << std::endl;
  std::cout << "  <output.tape>   : File where the output tape will be written after execution." << std::endl;
  std::cout << std::endl;

  std::cout << "Program format:" << std::endl;
  std::cout << "  - Instructions: LOAD, STORE, ADD, SUB, MUL, DIV, READ, WRITE, JUMP, JZERO, JGTZ, HALT." << std::endl;
  std::cout << "  - Operands: =value (constant), register (direct), *register (indirect)." << std::endl;
  std::cout << "  - Labels: alphanumeric string followed by ':' at the beginning of a line." << std::endl;
  std::cout << "  - Comments: start with '#' (ignored)." << std::endl;
  std::cout << std::endl;

  std::cout << "Extended version (vector support):" << std::endl;
  std::cout << "  - Vector access: Rbase[index], where index can be any operand type." << std::endl;
  std::cout << "  - Example: LOAD R1[R2]  loads from R1 at position given by R2." << std::endl;
  std::cout << std::endl;

  std::cout << "Options:" << std::endl;
  std::cout << "  --help        Show this help message and exit." << std::endl;
}


/**
 * @brief Prints how to use the program
 */
void Usage() {
  std::cout << "Usage: ./ram_simulator <program.ram> <input.tape> <output.tape>" << std::endl;
  std::cout << "Try './ram_simulator --help' for more information." << std::endl;
}


/**
 * @brief Validates if a file has a valid extension (.ram for RAM files, .txt for input/output files)
 * @param name The name of the file to validate
 * @return true if the file has a valid extension, false otherwise
 */
bool ValidateRAMFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(ram)$)");
  return std::regex_match(name, pattern);
}


/**
 * @brief Validates if a file has a valid extension (.ram for RAM files, .txt for input/output files)
 * @param name The name of the file to validate
 * @return true if the file has a valid extension, false otherwise
 */
bool ValidateInputOutputFile (const std::string& name) {
  if (name.find('.') == std::string::npos) {
    return false;  
  }
  std::regex pattern (R"((.*)\.(txt)$)");
  return std::regex_match(name, pattern);
}


/**
 * @brief Validates arguments given in CLI
 * @param argc
 * @param argv
 */
int ValidateArguments(int argc, char* argv[]) {
  if (argc == 2) {
    std::string arg1 = argv[1];
    if (arg1 == "--help" || arg1 == "-h") {
      Help();
      return 0;
    } 
  } else if (argc == 4) {
    if (ValidateRAMFile(argv[1]) && ValidateInputOutputFile(argv[2]) && ValidateInputOutputFile(argv[3])) {
      return -1;
    } 
  } 

  Usage();
  return 1;
}


/**
 * @brief Elimina espacios en blanco al inicio y final de una cadena.
 */
std::string trim(const std::string& string) {
  const std::string whitespace = " \t\n\r\f\v";
  size_t start = string.find_first_not_of(whitespace);
  if (start == std::string::npos) return "";
  size_t end = string.find_last_not_of(whitespace);
  return string.substr(start, end - start + 1);
}

/**
 * @brief Checks if a string represents a valid integer 
 * @param string The string to check
 * @return true if the string is a valid integer, false otherwise
 */
bool isInteger(const std::string& string) {
  if (string.empty()) return false;

  size_t i = 0;
  if (string[0] == '-' || string[0] == '+') {
    if (string.length() == 1) return false;
    i = 1;
  }

  for (; i < string.length(); ++i) {
    if (!std::isdigit(string[i])) return false;
  }

  return true;
}


/**
 * @brief Divide una línea en tokens separados por espacios.
 */
std::vector<std::string> tokenize(const std::string& line) {
  std::vector<std::string> tokens;
  std::istringstream iss(line);
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

/**
 * @brief Convierte un string a mayúsculas.
 */
std::string toUpper(const std::string& string) {
  std::string result = string;
  std::transform(result.begin(), result.end(), result.begin(),
                [](unsigned char c){ return std::toupper(c); });
  return result;
}

/**
 * @brief Comprueba si un opcode es de salto.
 */
bool isJumpOpcode(const std::string& op) {
  std::string uop = toUpper(op);
  return uop == "JUMP" || uop == "JZERO" || uop == "JGTZ";
}