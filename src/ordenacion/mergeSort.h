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
** Archivo MergeSort.h: Implementación del algoritmo MergeSort
**/

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

/**
 * @brief Implementación de MergeSort usando el esquema Divide y Vencerás
 */
template <typename T> class MergeSort : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {
 public:
  /**
   * @brief Devuelve el nombre del algoritmo
   * @returns "MergeSort"
   */
  const char* name() const override {
    return "MergeSort";
  }

 protected:
  /**
   * @brief Determina si la instancia es suficientemente pequeña
   * @param instancia InstanciaVector<T> a comprobar
   * @returns true si tiene 1 elemento o menos, false en caso contrario
   */
  bool isSmall(const InstanciaVector<T>& instancia) const override {
    return instancia.getDatos().size() <= 1;
  }

  /**
   * @brief Resuelve directamente una instancia pequeña
   * @param instancia InstanciaVector<T> considerada pequeña
   * @returns SolucionVector<T> con los mismos elementos
   */
  SolucionVector<T> solveSmall(const InstanciaVector<T>& instancia) const override {
    return SolucionVector<T>(instancia.getDatos());
  }

  /**
   * @brief Divide la instancia en dos subproblemas
   * @param instancia InstanciaVector<T> a dividir
   * @returns std::pair con dos punteros únicos a InstanciaVector<T>,
   *          el primero con la mitad izquierda, el segundo con la mitad derecha
   */
  std::pair<
    std::unique_ptr<InstanciaVector<T>>, 
    std::unique_ptr<InstanciaVector<T>>
  > dividir(const InstanciaVector<T>& instancia) const override {
    const auto& datos = instancia.getDatos();
    size_t mitad = datos.size() / 2;

    std::vector<T> izquierda(datos.begin(), datos.begin() + mitad);
    std::vector<T> derecha(datos.begin() + mitad, datos.end());

    return {
        std::make_unique<InstanciaVector<T>>(izquierda),
        std::make_unique<InstanciaVector<T>>(derecha)
    };
  }

  /**
   * @brief Combina dos soluciones parciales en una solución completa
   * @param s1 SolucionVector<T> de la primera mitad
   * @param s2 SolucionVector<T> de la segunda mitad
   * @returns SolucionVector<T> combinando ambas soluciones de forma ordenada
   */
  SolucionVector<T> combinar(const SolucionVector<T>& s1, const SolucionVector<T>& s2) const override {
    const auto& v1 = s1.datos();
    const auto& v2 = s2.datos();

    std::vector<T> resultado;
    resultado.reserve(v1.size() + v2.size());

    size_t i = 0, j = 0;

    while (i < v1.size() && j < v2.size()) {
      resultado.push_back(v1[i] <= v2[j] ? v1[i++] : v2[j++]);
    }

    while (i < v1.size()) resultado.push_back(v1[i++]);
    while (j < v2.size()) resultado.push_back(v2[j++]);

    return SolucionVector<T>(resultado);
  }
};

#endif