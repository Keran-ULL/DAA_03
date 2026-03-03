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
** Archivo MergeSort.h: Implementación del algoritmo MergeSort
**/
#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include "../core/divideYvenceras.h"
#include "InstanciaVector.h"
#include "SolucionVector.h"
#include <vector>
#include <memory>

/**
 * @brief Implementación de MergeSort usando el esquema Divide y Vencerás
 */
template <typename T>
class MergeSort 
: public DivideYVenceras<InstanciaVector<T>, SolucionVector<T>> {

public:

    const char* nombre() const override {
        return "MergeSort";
    }

protected:

    bool esPequeno(const InstanciaVector<T>& instancia) const override {
        return instancia.getDatos().size() <= 1;
    }

    SolucionVector<T> resolverPequeno(
        const InstanciaVector<T>& instancia
    ) const override {
        return SolucionVector<T>(instancia.getDatos());
    }

    std::pair<
        std::unique_ptr<InstanciaVector<T>>,
        std::unique_ptr<InstanciaVector<T>>
    >
    dividir(const InstanciaVector<T>& instancia) const override {

        const auto& datos = instancia.getDatos();
        size_t mitad = datos.size() / 2;

        std::vector<T> izquierda(datos.begin(), datos.begin() + mitad);
        std::vector<T> derecha(datos.begin() + mitad, datos.end());

        return {
            std::make_unique<InstanciaVector<T>>(izquierda),
            std::make_unique<InstanciaVector<T>>(derecha)
        };
    }

    SolucionVector<T> combinar(
    const SolucionVector<T>& s1,
    const SolucionVector<T>& s2
) const override {

    const auto& v1 = s1.datos();
    const auto& v2 = s2.datos();

    std::vector<T> resultado;
    resultado.reserve(v1.size() + v2.size());

    size_t i = 0, j = 0;

    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j])
            resultado.push_back(v1[i++]);
        else
            resultado.push_back(v2[j++]);
    }

    while (i < v1.size())
        resultado.push_back(v1[i++]);

    while (j < v2.size())
        resultado.push_back(v2[j++]);

    return SolucionVector<T>(resultado);
}

};

#endif



