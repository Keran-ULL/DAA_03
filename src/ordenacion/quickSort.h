#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

template <typename T>
class QuickSort : public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {
protected:
    bool esPequeno(const InstanciaVector<T>& instancia) const override {
      return instancia.tamano() <= 1;
    }

    SolucionVector<T> resolverPequeno(const InstanciaVector<T>& instancia) const override {
      return SolucionVector<T>(instancia.datos());
    }

    std::pair<std::unique_ptr<InstanciaVector<T>>, std::unique_ptr<InstanciaVector<T>>> dividir(const InstanciaVector<T>& instancia) const override {
      const auto& datos = instancia.datos();
      std::vector<T> menores, mayores;
      T pivote = datos.back();
      ultimoPivote = pivote;
      for (size_t i = 0; i < datos.size() - 1; ++i) {
        if (datos[i] < pivote) menores.push_back(datos[i]);
        else mayores.push_back(datos[i]);
      }
      return {
        std::make_unique<InstanciaVector<T>>(menores),
        std::make_unique<InstanciaVector<T>>(mayores)
      };
    }

    SolucionVector<T> combinar(const SolucionVector<T>& s1, const SolucionVector<T>& s2) const override {
      std::vector<T> resultado = s1.datos();
      resultado.push_back(ultimoPivote);
      const auto& d2 = s2.datos();
      resultado.insert(resultado.end(), d2.begin(), d2.end());
      return SolucionVector<T>(resultado);
    }

private:
    mutable T ultimoPivote;

public:
    const char* nombre() const override { return "QuickSort"; }
};

#endif

