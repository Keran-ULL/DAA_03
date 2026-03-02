/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 2: Máquina RAM
** Autor: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 21/02/2026

** Archivo exceptions.h: Archivo de excepciones
**
** Referencias:
**      Enlaces de interes

** Historial de revisiones:
**      21/02/2026 - Creacion (primera version) del codigo
**/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @brief Base exception class for all RAM machine exceptions
 */
class Exceptions : public std::exception {
 protected:
  std::string error_message_;
 public:
  explicit Exceptions(const std::string& msg) : error_message_(msg) {}
  const char* what() const noexcept override { return error_message_.c_str(); }
};

/**
 * @brief Thrown when trying to write on the input tape
 */
class WriteOnInputTapeException : public Exceptions {
 public:
  WriteOnInputTapeException() : Exceptions("Invalid operation: cannot write on input tape") {}
};

/**
 * @brief Thrown when trying to read from the output tape
 */
class ReadOnOutputTapeException : public Exceptions {
 public:
  ReadOnOutputTapeException() : Exceptions("Invalid operation: cannot read from output tape") {}
};

/**
 * @brief Thrown when reading past the end of the input tape
 */
class OutOfTapeException : public Exceptions {
 public:
  OutOfTapeException() : Exceptions("Input tape exhausted: no more values to read") {}
};

/**
 * @brief Thrown when a scalar operation is attempted on a vector register
 */
class ScalarOperationOnVectorException : public Exceptions {
 public:
  ScalarOperationOnVectorException() : Exceptions("Invalid operation: cannot perform scalar operation on vector register") {}
};

/**
 * @brief Thrown when a vector operation is attempted on a scalar register
 */
class VectorOperationOnScalarException : public Exceptions {
 public:
  VectorOperationOnScalarException() : Exceptions("Invalid operation: cannot perform vector operation on scalar register") {}
};

/**
 * @brief Thrown when an index is out of bounds in a vector register
 */
class VectorIndexOutOfBoundsException : public Exceptions {
 public:
  explicit VectorIndexOutOfBoundsException(int index) : Exceptions("Vector register index out of bounds: " + std::to_string(index)) {}
};

/**
 * @brief Thrown when accessing a register that has never been initialized
 */
class UninitializedRegisterException : public Exceptions {
 public:
  explicit UninitializedRegisterException(int reg) : Exceptions("Access to uninitialized register R" + std::to_string(reg)) {}
};

/**
 * @brief Thrown when a write is attempted on a read-only operand 
 */
class WriteOnConstantOperandException : public Exceptions {
 public:
  WriteOnConstantOperandException() : Exceptions("Invalid operation: cannot write to a constant operand") {}
};

/**
 * @brief Thrown when an operand string cannot be parsed
 */
class InvalidOperandException : public Exceptions {
 public:
  explicit InvalidOperandException(const std::string& operand) : Exceptions("Invalid operand: '" + operand + "'") {}
};

/**
 * @brief Thrown when an unknown instruction is found
 */
class InvalidInstructionException : public Exceptions {
 public:
  explicit InvalidInstructionException(const std::string& instr, int line) : Exceptions("Invalid instruction '" + instr + "' at line " + std::to_string(line)) {}
};

/**
 * @brief Thrown when an instruction receives an incompatible operand type
 */
class IncompatibleOperandException : public Exceptions {
 public:
  explicit IncompatibleOperandException(const std::string& instr, const std::string& operand) : Exceptions("Instruction '" + instr + "' does not support operand '" + operand + "'") {}
};

/**
 * @brief Thrown when a division by zero occurs
 */
class DivisionByZeroException : public Exceptions {
 public:
  DivisionByZeroException() : Exceptions("Runtime error: division by zero") {}
};

/**
 * @brief Thrown when a JUMP/JZERO/JGTZ references an undefined label
 */
class UndefinedLabelException : public Exceptions {
 public:
  explicit UndefinedLabelException(const std::string& label) : Exceptions("Undefined label: '" + label + "'") {}
};

/**
 * @brief Thrown when READ/WRITE uses R0 as operand 
 */
class InvalidR0OperandException : public Exceptions {
 public:
  explicit InvalidR0OperandException(const std::string& instr) : Exceptions("Instruction '" + instr + "' cannot use R0 as operand") {}
};

/**
 * @brief Thrown when HALT is reached
 */
class HaltException : public Exceptions {
 public:
  HaltException() : Exceptions("HALT instruction encountered") {}
};

/**
 * @brief Thrown when a file cannot be opened
 */
class FileNotFoundException : public Exceptions {
 public:
  explicit FileNotFoundException(const std::string& filename) : Exceptions("Cannot open file: '" + filename + "'") {}
};

/**
 * @brief Thrown when a file is empty or has no valid content
 */
class EmptyFileException : public Exceptions {
 public:
  explicit EmptyFileException(const std::string& filename) : Exceptions("File is empty or has no valid content: '" + filename + "'") {}
};

/**
 * @brief Thrown when a program file has a syntax error
 */
class ProgramSyntaxException : public Exceptions {
 public:
  explicit ProgramSyntaxException(const std::string& detail, int line) : Exceptions("Syntax error at line " + std::to_string(line) + ": " + detail) {}
};

#endif