#ifndef INSTANCIA_HPP
#define INSTANCIA_HPP

#include <iostream>

/**
 * @brief Clase base abstracta que representa
 *        una instancia de un problema.
 *
 * Cumple el principio SRP: solo modela el problema.
 */
class Instancia {
public:
    virtual ~Instancia() = default;

    /**
     * @brief Devuelve el tamaño de la instancia.
     *        Útil para experimentación.
     */
    virtual size_t size() const = 0;

    /**
     * @brief Muestra la instancia por pantalla.
     */
    virtual void mostrar(std::ostream& os) const = 0;
};

#endif
