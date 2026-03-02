#ifndef MEDIDOR_TIEMPOS_HPP
#define MEDIDOR_TIEMPOS_HPP

#include <chrono>

/**
 * @brief Clase para medir el tiempo de ejecución de un algoritmo.
 */
class MedidorTiempos {
public:
    /**
     * @brief Mide el tiempo (en milisegundos) que tarda ejecutar un algoritmo sobre una instancia.
     *
     * @tparam Algoritmo Tipo de algoritmo (debe tener ejecutar(instancia))
     * @tparam Instancia Tipo de instancia
     * @tparam Solucion Tipo de solución
     * @param algoritmo Referencia al algoritmo a medir
     * @param instancia Referencia a la instancia sobre la que ejecutar
     * @return Tiempo en milisegundos (double)
     */
    template <typename Algoritmo, typename Instancia, typename Solucion>
    static double medir(Algoritmo& algoritmo, const Instancia& instancia) {
        auto inicio = std::chrono::high_resolution_clock::now();
        Solucion sol = algoritmo.ejecutar(instancia);
        auto fin = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duracion = fin - inicio;
        return duracion.count();
    }
};

#endif
