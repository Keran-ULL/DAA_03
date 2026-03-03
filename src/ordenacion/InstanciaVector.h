/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 1/2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo InstanciaVector.h: Implementación concreta de instancia basada en vector
**/

#ifndef INSTANCIA_VECTOR_H
#define INSTANCIA_VECTOR_H

#include "../core/Instancia.h"
#include "../exceptions/exceptions.h"
#include <vector>
#include <iostream>

template <typename T>
class InstanciaVector : public Instancia {
 private:
  std::vector<T> datos_;

 public:
  explicit InstanciaVector(const std::vector<T>& datos) : datos_(datos) {
    if (datos_.empty()) {
      throw InvalidSizeException(0);
    }
  }

  const std::vector<T>& getDatos() const {
    return datos_;
  }

  size_t tamano() const {
    return datos_.size();
  }

  void mostrar(std::ostream& os) const override {
    for (const auto& e : datos_) {
      os << e << " ";
    }
  }
};

#endif
