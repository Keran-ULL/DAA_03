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
** Archivo QuickSort.h: Implementación del algoritmo QuickSort
**/

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../core/divideYvenceras.h"
#include "../ordenacion/InstanciaVector.h"
#include "../ordenacion/SolucionVector.h"
#include "../exceptions/exceptions.h"
#include <vector>

template <typename T>
class QuickSort : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {

 private:

  int particion(std::vector<T>& v, int low, int high) {
    T pivote = v[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
      if (v[j] <= pivote) {
        ++i;
        std::swap(v[i], v[j]);
      }
    }
    std::swap(v[i + 1], v[high]);
    return i + 1;
  }

  void quickSort(std::vector<T>& v, int low, int high) {
    if (low < high) {
      int pi = particion(v, low, high);
      quickSort(v, low, pi - 1);
      quickSort(v, pi + 1, high);
    }
  }

 public:

  SolucionVector<T> ejecutar(const InstanciaVector<T>& instancia) override {
    try {
      std::vector<T> copia = instancia.getDatos();
      quickSort(copia, 0, copia.size() - 1);
      return SolucionVector<T>(copia);
    }
    catch (...) {
      throw AlgorithmExecutionException("QuickSort");
    }
  }

  std::string nombre() const override {
    return "QuickSort";
  }
};

#endif

