/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 3: Divide Y Vencerás
** Autor: Marco Pérez Padilla, Keran Miranda González
** Correo: alu0101469348@ull.edu.es, alu0101485904@ull.edu.es
** Fecha: 07/03/2026
**
** Archivo execution_functions.cc: Implementación de funciones de ejecucion
**/

#include "execution_funcions.h"
#include "../generators/GeneradorVectores.h"

#include <iostream>

/**
 * @brief Ejecuta algoritmos de ordenación en modo debug.
 *
 * Muestra la instancia generada y los resultados de los algoritmos.
 *
 * @param algoritmo Código del algoritmo (1=MergeSort, 2=QuickSort, 3=Ambos)
 * @param size Tamaño de la instancia a generar
 */
void EjecutarDebugOrdenacion(int algoritmo, size_t size) {
  GeneradorVectores<int> generador(size, 0, 100);
  auto instanciaBase = generador.generar();
  auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

  std::cout << "\nInstancia generada:\n";
  instancia->mostrar(std::cout);
  std::cout << "\n\n";

  if (algoritmo == 1 || algoritmo == 3) {
    MergeSort<int> ms;
    auto solucion = ms.ejecutar(*instancia);
    std::cout << "Resultado MergeSort:\n";
    solucion.mostrar(std::cout);
    std::cout << std::endl;
  }

  if (algoritmo == 2 || algoritmo == 3) {
    QuickSort<int> qs;
    auto solucion = qs.ejecutar(*instancia);
    std::cout << "Resultado QuickSort:\n";
    solucion.mostrar(std::cout);
    std::cout << std::endl;
  }
}

/**
 * @brief Ejecuta algoritmos de ordenación en modo normal y mide tiempos.
 *
 * Realiza múltiples experimentos y muestra los resultados en una tabla.
 *
 * @param algoritmo Código del algoritmo (1=MergeSort, 2=QuickSort, 3=Ambos)
 * @param size Tamaño de la instancia a generar
 * @param experimentos Número de experimentos a ejecutar
 */
void EjecutarNormalOrdenacion(int algoritmo, size_t size, int experimentos) {
  TablaResultados tabla;

  for (int i = 0; i < experimentos; ++i) {
    GeneradorVectores<int> generador(size, 0, 10000);
    auto instanciaBase = generador.generar();
    auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

    if (algoritmo == 1 || algoritmo == 3) {
      MergeSort<int> ms;
      double tiempo = MedidorTiempos::medir<MergeSort<int>, InstanciaVector<int>, SolucionVector<int>>(ms, *instancia);
      tabla.agregarResultado(ms.name(), size, tiempo);
    }

    if (algoritmo == 2 || algoritmo == 3) {
        QuickSort<int> qs;
        double tiempo = MedidorTiempos::medir<QuickSort<int>, InstanciaVector<int>, SolucionVector<int>>(qs, *instancia);
        tabla.agregarResultado(qs.name(), size, tiempo);
    }
  }

  std::cout << "\n=== RESULTADOS ===\n";
  tabla.mostrar();
}

/**
 * @brief Ejecuta el algoritmo SchedulingDyV en modo debug.
 *
 * Muestra la instancia cargada y la solución obtenida.
 *
 * @param archivo Ruta al archivo JSON de la instancia
 */
void EjecutarDebugScheduling(const std::string& archivo) {
  auto instancia = SchedulingParser::parse(archivo);

  std::cout << "Instancia Scheduling cargada:\n";
  instancia.mostrar(std::cout);

  SchedulingDyV dyv;
  auto solucion = dyv.ejecutar(instancia);

  std::cout << "\nSolución obtenida:\n";
  solucion.mostrar(std::cout);
}

/**
 * @brief Ejecuta el algoritmo SchedulingDyV en modo normal.
 *
 * Mide el tiempo de ejecución sobre la instancia cargada desde archivo.
 *
 * @param archivo Ruta al archivo JSON de la instancia
 */
void EjecutarNormalScheduling(const std::string& archivo) {
  auto instancia = SchedulingParser::parse(archivo);

  SchedulingDyV dyv;
  double tiempo = MedidorTiempos::medir<SchedulingDyV, InstanciaScheduling, SolucionScheduling>(dyv, instancia);

  std::cout << "Tiempo de ejecución SchedulingDyV: " << tiempo << " ms\n";
}