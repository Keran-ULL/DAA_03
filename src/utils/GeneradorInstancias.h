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
** Archivo GeneradorInstancias.h: Generador de instancias 
**/

#ifndef GENERADOR_INSTANCIAS_H
#define GENERADOR_INSTANCIAS_H

#include "../core/Instancia.h"
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
