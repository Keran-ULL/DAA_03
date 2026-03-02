#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

template <typename T>
class MergeSort : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {
protected:
    bool esPequeno(const InstanciaVector<T>& instancia) const override {
      return instancia.tamano() <= 1;
    }

    SolucionVector<T> resolverPequeno(const InstanciaVector<T>& instancia) const override {
      return SolucionVector<T>(instancia.datos());
    }

    std::pair<std::unique_ptr<InstanciaVector<T>>, std::unique_ptr<InstanciaVector<T>>>
    dividir(const InstanciaVector<T>& instancia) const override {
      const auto& datos = instancia.datos();
      size_t mitad = datos.size() / 2;
      std::vector<T> iz(datos.begin(), datos.begin() + mitad);
      std::vector<T> dr(datos.begin() + mitad, datos.end());
      return {
        std::make_unique<InstanciaVector<T>>(iz),
        std::make_unique<InstanciaVector<T>>(dr)
      };
    }

    SolucionVector<T> combinar(const SolucionVector<T>& s1, const SolucionVector<T>& s2) const override {
        // Merge de dos vectores ordenados
      const auto& v1 = s1.datos();
      const auto& v2 = s2.datos();
      std::vector<T> resultado;
      resultado.reserve(v1.size() + v2.size());
      size_t i = 0, j = 0;
      while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) resultado.push_back(v1[i++]);
        else resultado.push_back(v2[j++]);
      }
      while (i < v1.size()) resultado.push_back(v1[i++]);
      while (j < v2.size()) resultado.push_back(v2[j++]);
      return SolucionVector<T>(resultado);
    }

public:
    const char* nombre() const override { return "MergeSort"; }
};

#endif
