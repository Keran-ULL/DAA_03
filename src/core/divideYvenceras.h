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
** Archivo divideYvenceras.h: Representación de una clase plantilla base para cualquier problema DYV
**/

#ifndef DIVIDE_Y_VENCERAS_H
#define DIVIDE_Y_VENCERAS_H

#include "algoritmo.h"
#include <memory>
#include <utility>

/**
 * @brief Template Method para algoritmos Divide y Vencerás binarios
 *
 * @tparam InstanciaType Hereda de Instancia
 * @tparam SolucionType Hereda de Solucion
 */
template <typename InstanciaType, typename SolucionType> class DivideYVenceras : public Algoritmo<InstanciaType, SolucionType> {
 public:

  /**
   * @brief Ejecuta el algoritmo sobre una instancia concreta
   * 
   * @param instancia Instancia a resolver
   * @returns SolucionType Solución obtenida tras aplicar DYV
   */
  SolucionType ejecutar(const InstanciaType& instancia) final {
    if (isSmall(instancia)) {return solveSmall(instancia);}
    auto subproblemas = dividir(instancia);
    SolucionType sol1 = ejecutar(*subproblemas.first);
    SolucionType sol2 = ejecutar(*subproblemas.second);
    return combinar(sol1, sol2);
  }

 protected:
  virtual bool isSmall(const InstanciaType& instancia) const = 0;
  virtual SolucionType solveSmall(const InstanciaType& instancia) const = 0;
  virtual std::pair<std::unique_ptr<InstanciaType>, std::unique_ptr<InstanciaType>> dividir(const InstanciaType& instancia) const = 0;
  virtual SolucionType combinar(const SolucionType& s1, const SolucionType& s2) const = 0;
};

#endif
