/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 2: Divide y Venceras
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

/**
 * @brief Representa una instancia concreta basada en un vector
 * @tparam T Tipo de los elementos
 */
template <typename T> class InstanciaVector : public Instancia {
 private:
  std::vector<T> datos_;

 public:
  /**
   * @brief Constructor a partir de un vector
   * @param datos Vector con los elementos de la instancia
   */
  explicit InstanciaVector(const std::vector<T>& datos) : datos_(datos) {}

  /**
   * @brief Devuelve los datos de la instancia
   * @returns referencia constante al vector interno
   */
  const std::vector<T>& getDatos() const {
    return datos_;
  }

  /**
   * @brief Devuelve el tamaño de la instancia
   * @returns tamaño del vector interno
   */
  size_t size() const {
    return datos_.size();
  }

  /**
   * @brief Muestra la instancia por pantalla
   * @param os flujo de salida
   */
  void mostrar(std::ostream& os) const override {
    for (const auto& data : datos_) {
      os << data << " ";
    }
  }
};

#endif