#ifndef TABLA_RESULTADOS_HPP
#define TABLA_RESULTADOS_HPP

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

/**
 * @brief Clase para almacenar y mostrar resultados de tiempo de algoritmos.
 */
class TablaResultados {
public:
    /**
     * @brief Añade un resultado a la tabla
     *
     * @param nombreAlgoritmo Nombre del algoritmo
     * @param tamano Tamaño de la instancia
     * @param tiempo Tiempo en milisegundos
     */
    void agregarResultado(const std::string& nombreAlgoritmo, size_t tamano, double tiempo) {
        resultados.push_back({nombreAlgoritmo, tamano, tiempo});
    }

    /**
     * @brief Muestra la tabla completa por pantalla
     */
    void mostrar() const {
        std::cout << std::left << std::setw(15) << "Algoritmo"
                  << std::setw(10) << "Tamano"
                  << std::setw(12) << "Tiempo(ms)" << "\n";
        std::cout << "---------------------------------------\n";
        for (const auto& r : resultados) {
            std::cout << std::left << std::setw(15) << r.algoritmo
                      << std::setw(10) << r.tamano
                      << std::setw(12) << r.tiempo << "\n";
        }
    }

private:
    struct Resultado {
      std::string algoritmo;
      size_t tamano;
      double tiempo;
    };
    std::vector<Resultado> resultados;
};

#endif
