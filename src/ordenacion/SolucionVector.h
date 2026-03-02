#ifndef SOLUCION_VECTOR_HPP
#define SOLUCION_VECTOR_HPP

#include "../core/Solucion.h"
#include <vector>
#include <iostream>

/**
 * @brief Representa la solución de un problema de ordenación.
 *
 * Almacena un vector ordenado.
 *
 * @tparam T Tipo de los elementos.
 */
template <typename T>
class SolucionVector : public Solucion {

public:

    /**
     * @brief Constructor a partir de un vector ordenado.
     */
    explicit SolucionVector(const std::vector<T>& datos) : datos_(datos) {}

    /**
     * @brief Permite acceder a los datos de la solución.
     */
    const std::vector<T>& datos() const {
      return datos_;
    }

    /**
     * @brief Muestra la solución por pantalla.
     */
    void mostrar(std::ostream& os) const override {
      os << "[ ";
      for (const auto& elem : datos_) {
        os << elem << " ";
      }
      os << "]";
    }

private:
  std::vector<T> datos_;
};

#endif
