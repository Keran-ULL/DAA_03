/**
** Universidad de La Laguna
** Escuela Superior de Ingeniería y Tecnología
** Grado en Ingeniería Informática
** Asignatura: Diseño y Análisis de Algoritmos
** Curso: 3º
** Práctica 1: Complejidad Computacional
** Autores: Marco Pérez Padilla, Keran Miranda González
** Fecha: 03/03/2026
**
** Archivo main.cpp: Programa principal
**/

#include <iostream>

#include "help_functions.h"
#include "exceptions.h"

#include "utils/GeneradorVectores.h"
#include "utils/MedidorTiempos.h"
#include "utils/TablaResultados.h"

#include "ordenacion/MergeSort.h"
#include "ordenacion/QuickSort.h"

using namespace std;

/* ===========================================
   FUNCIONES AUXILIARES DE EJECUCIÓN
   =========================================== */

void EjecutarModoDebug(int algoritmoSeleccionado, size_t tamano) {

  GeneradorVectores<int> generador(tamano, 0, 100);
  auto instanciaBase = generador.generar();
  auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

  cout << "\nInstancia generada:\n";
  instancia->mostrar(cout);
  cout << "\n\n";

  if (algoritmoSeleccionado == 1 || algoritmoSeleccionado == 3) {
    MergeSort<int> ms;
    auto solucion = ms.ejecutar(*instancia);

    cout << "Resultado MergeSort:\n";
    solucion.mostrar(cout);
    cout << "\n\n";
  }

  if (algoritmoSeleccionado == 2 || algoritmoSeleccionado == 3) {
    QuickSort<int> qs;
    auto solucion = qs.ejecutar(*instancia);

    cout << "Resultado QuickSort:\n";
    solucion.mostrar(cout);
    cout << "\n\n";
  }
}


void EjecutarModoNormal(int algoritmoSeleccionado,
                        size_t tamano,
                        int experimentos) {

  TablaResultados tabla;

  for (int i = 0; i < experimentos; ++i) {

    GeneradorVectores<int> generador(tamano, 0, 10000);
    auto instanciaBase = generador.generar();
    auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

    if (algoritmoSeleccionado == 1 || algoritmoSeleccionado == 3) {
      MergeSort<int> ms;
      double tiempo =
        MedidorTiempos::medir<MergeSort<int>,
                              InstanciaVector<int>,
                              SolucionVector<int>>(ms, *instancia);

      tabla.agregarResultado(ms.nombre(), tamano, tiempo);
    }

    if (algoritmoSeleccionado == 2 || algoritmoSeleccionado == 3) {
      QuickSort<int> qs;
      double tiempo =
        MedidorTiempos::medir<QuickSort<int>,
                              InstanciaVector<int>,
                              SolucionVector<int>>(qs, *instancia);

      tabla.agregarResultado(qs.nombre(), tamano, tiempo);
    }
  }

  cout << "\n=== RESULTADOS ===\n";
  tabla.mostrar();
}


/* ===========================================
   MAIN
   =========================================== */

int main(int argc, char* argv[]) {

  int argStatus = ValidateArguments(argc, argv);
  if (argStatus != -1)
    return argStatus;

  try {

    int modo = AskExecutionMode();
    if (modo == 0)
      return 0;

    int algoritmo = AskAlgorithmChoice();
    size_t tamano = AskInstanceSize();

    if (modo == 1) {
      int experimentos = AskNumberOfExperiments();
      EjecutarModoNormal(algoritmo, tamano, experimentos);
    }
    else if (modo == 2) {
      EjecutarModoDebug(algoritmo, tamano);
    }

  }
  catch (const DAAException& e) {
    cerr << "Error: " << e.what() << endl;
  }
  catch (const std::exception& e) {
    cerr << "Unexpected error: " << e.what() << endl;
  }

  return 0;
}
