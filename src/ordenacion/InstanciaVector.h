#ifndef INSTANCIA_VECTOR_HPP
#define INSTANCIA_VECTOR_HPP

#include "../core/Instancia.hpp"
#include <vector>
#include <iostream>

/**
 * @brief Representa una instancia del problema de ordenación.
 *
 * Encapsula un vector de elementos a ordenar.
 * No se encarga de generar datos aleatorios (cumple SRP).
 *
 * @tparam T Tipo de los elementos del vector.
 */
template <typename T>
class InstanciaVector : public Instancia {

public:

    /**
     * @brief Constructor a partir de un vector existente.
     */
    explicit InstanciaVector(const std::vector<T>& datos) : datos_(datos) {}

    /**
     * @brief Devuelve el tamaño de la instancia.
     */
    size_t tamano() const override {
      return datos_.size();
    }

    /**
     * @brief Permite acceder a los datos (solo lectura).
     */
    const std::vector<T>& datos() const {
      return datos_;
    }

    /**
     * @brief Muestra la instancia por pantalla.
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

