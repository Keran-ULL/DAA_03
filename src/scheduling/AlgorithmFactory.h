#ifndef ALGORITHM_FACTORY_HPP
#define ALGORITHM_FACTORY_HPP

#include <memory>
#include <string>

#include "../core/algoritmo.h"
#include "../libreries/json.hpp"

#include "SchedulingDyV.hpp"
#include "SchedulingDP.hpp"
#include "SchedullingSolver.hpp"
#include "SchedulingGreedy.hpp"


using json = nlohmann::json;

/**
 * @brief Factory para crear algoritmos de planificación a partir de JSON.
 *
 * Permite construir recursivamente algoritmos como:
 *
 * BinaryDivideAndConquer
 *     └── BinaryDivideAndConquer
 *            └── Greedy
 *
 */
class AlgorithmFactory {
public:

  static std::unique_ptr<
      Algoritmo<InstanciaScheduling, SolucionSchedulling>>
  create(const json& config) {

    std::string clase = config.at("class");

    /*
    -------------------------------------------------
    GREEDY
    -------------------------------------------------
    */

    if (clase == "Greedy") {
      return std::make_unique<SchedulingGreedy>();
    }

    /*
    -------------------------------------------------
    PROGRAMACIÓN DINÁMICA
    -------------------------------------------------
    */

    if (clase == "SchedulingDP") {
      return std::make_unique<SchedulingDP>();
    }

    /*
    -------------------------------------------------
    DIVIDE Y VENCERÁS
    -------------------------------------------------
    */

    if (clase == "BinaryDivideAndConquer") {

      if (!config.contains("smallSolver")) {
        throw std::runtime_error(
          "BinaryDivideAndConquer requiere smallSolver");
      }

      auto smallSolver =
        create(config.at("smallSolver"));

      return std::make_unique<SchedulingDyV>(
          std::move(smallSolver));
    }

    /*
    -------------------------------------------------
    ERROR
    -------------------------------------------------
    */

    throw std::runtime_error(
        "Algoritmo no reconocido: " + clase);
  }
};

#endif
