#ifndef ALGORITMO_HPP
#define ALGORITMO_HPP

#include "Instancia.h"
#include "Solucion.h"

/**
 * @brief Clase base de un algoritmo.
 *
 * @tparam Instancia Debe heredar de Instancia
 * @tparam Solucion Debe heredar de Solucion
 */
template <typename InstanciaType, typename SolucionType>
class Algoritmo {
public:
    virtual ~Algoritmo() = default;

    /**
     * @brief Ejecuta el algoritmo sobre una instancia.
     */
    virtual SolucionType ejecutar(const InstanciaType& instancia) = 0;

    /**
     * @brief Devuelve el nombre del algoritmo.
     */
    virtual const char* nombre() const = 0;
};

#endif
