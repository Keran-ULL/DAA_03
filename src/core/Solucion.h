#ifndef SOLUCION_HPP
#define SOLUCION_HPP

#include <iostream>

/**
 * @brief Clase base abstracta que representa
 *        la solución de un problema.
 *
 * Separada de Instancia para cumplir SRP.
 */
class Solucion {
public:
    virtual ~Solucion() = default;

    /**
     * @brief Muestra la solución por pantalla.
     */
    virtual void mostrar(std::ostream& os) const = 0;
};

#endif
