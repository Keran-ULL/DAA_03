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
** Archivo MergeSort.h: Implementación del algoritmo MergeSort
**/

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../core/divideYvenceras.h"
#include "../ordenacion/InstanciaVector.h"
#include "../ordenacion/SolucionVector.h"
#include "../exceptions/exceptions.h"
#include <vector>
#include <algorithm>

template <typename T>
class MergeSort : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {

 private:

  void merge(std::vector<T>& v, int l, int m, int r) {
    std::vector<T> aux(r - l + 1);

    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
      if (v[i] <= v[j]) aux[k++] = v[i++];
      else aux[k++] = v[j++];
    }

    while (i <= m) aux[k++] = v[i++];
    while (j <= r) aux[k++] = v[j++];

    for (int t = 0; t < k; ++t)
      v[l + t] = aux[t];
  }

  void mergeSort(std::vector<T>& v, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSort(v, l, m);
    mergeSort(v, m + 1, r);
    merge(v, l, m, r);
  }

 public:

  SolucionVector<T> ejecutar(const InstanciaVector<T>& instancia) override {
    try {
      std::vector<T> copia = instancia.getDatos();
      mergeSort(copia, 0, copia.size() - 1);
      return SolucionVector<T>(copia);
    }
    catch (...) {
      throw AlgorithmExecutionException("MergeSort");
    }
  }

  std::string nombre() const override {
    return "MergeSort";
  }
};

#endif


