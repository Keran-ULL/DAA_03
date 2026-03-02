#ifndef GENERADOR_VECTORES_HPP
#define GENERADOR_VECTORES_HPP

#include "GeneradorInstancias.h"
#include "../ordenacion/InstanciaVector.h"
#include <random>
#include <memory>
#include <vector>

/**
 * @brief Genera instancias de tipo InstanciaVector<T> con números aleatorios.
 *
 * @tparam T Tipo de los elementos.
 */
template <typename T>
class GeneradorVectores : public GeneradorInstancias {
public:
    /**
     * @param tamano Tamaño del vector
     * @param min Valor mínimo
     * @param max Valor máximo
     */
    GeneradorVectores(size_t tamano, T min, T max) : tamano_(tamano), min_(min), max_(max) {}

    /**
     * @brief Genera una instancia aleatoria.
     */
    std::unique_ptr<Instancia> generar() const override {
        std::vector<T> datos(tamano_);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(min_, max_);
        for (size_t i = 0; i < tamano_; ++i) {
          datos[i] = dist(gen);
        }
        return std::make_unique<InstanciaVector<T>>(datos);
    }

private:
    size_t tamano_;
    T min_;
    T max_;
};

#endif
