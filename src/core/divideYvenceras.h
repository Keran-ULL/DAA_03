#ifndef DIVIDE_Y_VENCERAS_HPP
#define DIVIDE_Y_VENCERAS_HPP

#include "algoritmo.h"
#include <memory>
#include <utility>

/**
 * @brief Template Method para algoritmos Divide y Vencerás binarios
 *
 * @tparam InstanciaType Hereda de Instancia
 * @tparam SolucionType Hereda de Solucion
 */
template <typename InstanciaType, typename SolucionType>
class DivideYVenceras : public Algoritmo<InstanciaType, SolucionType> {
public:
    SolucionType ejecutar(const InstanciaType& instancia) final {
      if (esPequeno(instancia)) {
        return resolverPequeno(instancia);
      }
      auto subproblemas = dividir(instancia);
      SolucionType sol1 = ejecutar(*subproblemas.first);
      SolucionType sol2 = ejecutar(*subproblemas.second);
      return combinar(sol1, sol2);
    }

protected:
    virtual bool esPequeno(const InstanciaType& instancia) const = 0;
    virtual SolucionType resolverPequeno(const InstanciaType& instancia) const = 0;

    /**
     * @brief Divide en dos subproblemas y devuelve punteros únicos.
     */
    virtual std::pair<std::unique_ptr<InstanciaType>, std::unique_ptr<InstanciaType>> dividir(const InstanciaType& instancia) const = 0;

    virtual SolucionType combinar(const SolucionType& s1, const SolucionType& s2) const = 0;
};

#endif
