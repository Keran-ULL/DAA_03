#ifndef GENERADOR_INSTANCIAS_HPP
#define GENERADOR_INSTANCIAS_HPP

#include "../core/Instancia.hpp"
#include <memory>

/**
 * @brief Clase abstracta para generar instancias de cualquier tipo de problema.
 */
class GeneradorInstancias {
public:
    virtual ~GeneradorInstancias() = default;

    /**
     * @brief Genera una instancia del problema.
     * @return Puntero único a la instancia creada.
     */
    virtual std::unique_ptr<Instancia> generar() const = 0;
};

#endif
