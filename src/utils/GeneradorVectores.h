/**
** Universidad de La Laguna
** Escuela Superior de Ingenieria y Tecnologia
** Grado en Ingenieria Informatica
** Asignatura: Diseño y Analisis de Algoritmos
** Curso: 3º
** Practica 2: Divide y Venceras
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo GeneradorVectores.h: Generador de instancias vectoriales
**/

#ifndef GENERADOR_VECTORES_H
#define GENERADOR_VECTORES_H

#include "GeneradorInstancias.h"
#include "../ordenacion/InstanciaVector.h"
#include "../exceptions/exceptions.h"
#include <random>
#include <memory>

template <typename T> class GeneradorVectores : public GeneradorInstancias {
 private:
  size_t tamano_;
  T min_;
  T max_;

 public:
  GeneradorVectores(size_t size, T min, T max) : tamano_(size), min_(min), max_(max) {
    if (tamano_ == 0) {throw InvalidSizeException(tamano_);}
    if (min_ > max_) {throw InstanceGenerationException("min > max");}
  }

  std::unique_ptr<Instancia> generar() const override {
    try {
      std::vector<T> datos(tamano_);

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(min_, max_);

      for (size_t i = 0; i < tamano_; ++i) {
        datos[i] = dist(gen);
      }

      return std::make_unique<InstanciaVector<T>>(datos);
    }
    catch (...) {
      throw InstanceGenerationException("unexpected generation failure");
    }
  }
};

#endif
