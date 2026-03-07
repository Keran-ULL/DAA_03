/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo QuickSort.h: Implementación del algoritmo QuickSort
**/

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

/**
 * @brief Implementación de QuickSort usando Divide y Vencerás
 */
template <typename T> class QuickSort  : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {
 public:
  const char* name() const override {
    return "QuickSort";
  }

 protected:
  /**
   * @brief Function that determines if the base case is enough small to be solved differently
   * @param InstanciaVectorT instance to be checked
   * @returns boolean. True if it's small enough, false otherwise
   */
  bool isSmall(const InstanciaVector<T>& instancia) const override {return instancia.getDatos().size() <= 1;}

  /**
   * @brief Resuelve el caso base (instancia pequeña) directamente
   * @param instancia InstanciaVector<T> considerada pequeña
   * @returns SolucionVector<T> con los mismos elementos de la instancia
   */
  SolucionVector<T> solveSmall(const InstanciaVector<T>& instancia) const override {return SolucionVector<T>(instancia.getDatos());}

  /**
   * @brief Divide la instancia en dos subproblemas según el pivote
   * @param instancia InstanciaVector<T> que se va a dividir
   * @returns std::pair con dos punteros únicos a InstanciaVector<T>, 
   *          el primero con los elementos menores o iguales al pivote y 
   *          el segundo con los mayores
   */
  std::pair<
    std::unique_ptr<InstanciaVector<T>>,
    std::unique_ptr<InstanciaVector<T>>
  > dividir(const InstanciaVector<T>& instancia) const override {
    const auto& datos = instancia.getDatos();

    T pivote = datos[0];
    std::vector<T> menores, mayores;
    for (size_t i = 1; i < datos.size(); ++i) {
      (datos[i] < pivote ? menores : mayores).push_back(datos[i]);
    }

    menores.push_back(pivote);
    return {std::make_unique<InstanciaVector<T>>(menores), std::make_unique<InstanciaVector<T>>(mayores)};
  }

  /**
   * @brief Combina las soluciones de dos subproblemas en una solución completa
   * @param s1 SolucionVector<T> del subproblema izquierdo
   * @param s2 SolucionVector<T> del subproblema derecho
   * @returns SolucionVector<T> combinando s1 y s2 en orden
   */
  SolucionVector<T> combinar(const SolucionVector<T>& s1, const SolucionVector<T>& s2) const override {
    const auto& menores = s1.datos();
    const auto& mayores = s2.datos();

    std::vector<T> resultado;
    resultado.reserve(menores.size() + mayores.size());

    resultado.insert(resultado.end(), menores.begin(), menores.end());
    resultado.insert(resultado.end(), mayores.begin(), mayores.end());

    return SolucionVector<T>(resultado);
  }
};

#endif