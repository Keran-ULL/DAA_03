/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 1/2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo QuickSort.h: Implementación del algoritmo QuickSort
**/

#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

/**
 * @brief Implementación de QuickSort usando Divide y Vencerás
 */
template <typename T>
class QuickSort 
: public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {

public:

    const char* nombre() const override {
        return "QuickSort";
    }

protected:

    // Caso base: instancia pequeña
    bool esPequeno(const InstanciaVector<T>& instancia) const override {
        return instancia.getDatos().size() <= 1;
    }

    // Resolver instancia pequeña
    SolucionVector<T> resolverPequeno(
        const InstanciaVector<T>& instancia
    ) const override {
        return SolucionVector<T>(instancia.getDatos());
    }

    // Dividir la instancia en dos subproblemas
    std::pair<
        std::unique_ptr<InstanciaVector<T>>,
        std::unique_ptr<InstanciaVector<T>>
    >
    dividir(const InstanciaVector<T>& instancia) const override {

        const auto& datos = instancia.getDatos();

        if (datos.size() <= 1) {
            return {
                std::make_unique<InstanciaVector<T>>(datos),
                std::make_unique<InstanciaVector<T>>(std::vector<T>{})
            };
        }

        T pivote = datos[0];

        std::vector<T> menores;
        std::vector<T> mayores;

        for (size_t i = 1; i < datos.size(); ++i) {
            if (datos[i] <= pivote)
                menores.push_back(datos[i]);
            else
                mayores.push_back(datos[i]);
        }

        return {
            std::make_unique<InstanciaVector<T>>(menores),
            std::make_unique<InstanciaVector<T>>(mayores)
        };
    }

    // Combinar las soluciones de los subproblemas
    SolucionVector<T> combinar(
        const SolucionVector<T>& s1,
        const SolucionVector<T>& s2
    ) const override {

        const auto& menores = s1.datos();
        const auto& mayores = s2.datos();

        std::vector<T> resultado;
        resultado.reserve(menores.size() + mayores.size());

        resultado.insert(resultado.end(), menores.begin(), menores.end());
        resultado.insert(resultado.end(), mayores.begin(), mayores.end());

        return SolucionVector<T>(resultado);
    }

};

#endif


