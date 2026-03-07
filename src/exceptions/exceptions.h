/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026

** Archivo exceptions.h: Definición de excepciones del framework
**/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @brief Clase base para todas las excepciones de la práctica
 */
class DAAException : public std::exception {
 protected:
  std::string error_message_;
 public:
  explicit DAAException(const std::string& msg) : error_message_(msg) {}
  const char* what() const noexcept override {return error_message_.c_str();}
};

/**
 * @brief Lanzada cuando una instancia es inválida
 */
class InvalidInstanceException : public DAAException {
 public:
  explicit InvalidInstanceException(const std::string& detail)
      : DAAException("Invalid instance: " + detail) {}
};

/**
 * @brief Lanzada cuando el tamaño de una instancia es incorrecto
 */
class InvalidSizeException : public DAAException {
 public:
  explicit InvalidSizeException(size_t size)
      : DAAException("Invalid size: " + std::to_string(size)) {}
};

/**
 * @brief Lanzada cuando falla la generación de instancias
 */
class InstanceGenerationException : public DAAException {
 public:
  explicit InstanceGenerationException(const std::string& detail)
      : DAAException("Instance generation error: " + detail) {}
};

/**
 * @brief Lanzada cuando un algoritmo recibe un tipo de instancia incorrecto
 */
class IncompatibleInstanceException : public DAAException {
 public:
  explicit IncompatibleInstanceException(const std::string& algorithm)
      : DAAException("Incompatible instance type for algorithm: " + algorithm) {}
};

/**
 * @brief Lanzada cuando ocurre un error durante la ejecución del algoritmo
 */
class AlgorithmExecutionException : public DAAException {
 public:
  explicit AlgorithmExecutionException(const std::string& algorithm)
      : DAAException("Execution error in algorithm: " + algorithm) {}
};

/**
 * @brief Lanzada cuando ocurre un error en la medición de tiempos
 */
class TimeMeasurementException : public DAAException {
 public:
  TimeMeasurementException()
      : DAAException("Error during time measurement") {}
};

#endif
