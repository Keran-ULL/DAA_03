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
#include <memory>
#include <string>

#include "help/help_functions.h"
#include "exceptions/exceptions.h"

#include "utils/GeneradorVectores.h"
#include "utils/MedidorTiempos.h"
#include "utils/TablaResultados.h"

// Ordenación
#include "ordenacion/mergeSort.h"
#include "ordenacion/quickSort.h"

// Scheduling
#include "scheduling/InstanciaScheduling.hpp"
#include "scheduling/SolucionSchedulling.hpp"
#include "scheduling/SchedulingParser.hpp"
#include "scheduling/SchedulingDyV.hpp"

using namespace std;

/* ===========================================
   FUNCIONES AUXILIARES DE EJECUCIÓN
   =========================================== */

// ==== Ordenación ====
void EjecutarDebugOrdenacion(int algoritmo, size_t tamano) {
    GeneradorVectores<int> generador(tamano, 0, 100);
    auto instanciaBase = generador.generar();
    auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

    cout << "\nInstancia generada:\n";
    instancia->mostrar(cout);
    cout << "\n\n";

    if (algoritmo == 1 || algoritmo == 3) {
        MergeSort<int> ms;
        auto solucion = ms.ejecutar(*instancia);
        cout << "Resultado MergeSort:\n";
        solucion.mostrar(cout);
        cout << endl;
    }

    if (algoritmo == 2 || algoritmo == 3) {
        QuickSort<int> qs;
        auto solucion = qs.ejecutar(*instancia);
        cout << "Resultado QuickSort:\n";
        solucion.mostrar(cout);
        cout << endl;
    }
}

void EjecutarNormalOrdenacion(int algoritmo, size_t tamano, int experimentos) {
    TablaResultados tabla;

    for (int i = 0; i < experimentos; ++i) {
        GeneradorVectores<int> generador(tamano, 0, 10000);
        auto instanciaBase = generador.generar();
        auto* instancia = dynamic_cast<InstanciaVector<int>*>(instanciaBase.get());

        if (algoritmo == 1 || algoritmo == 3) {
            MergeSort<int> ms;
            double tiempo = MedidorTiempos::medir<MergeSort<int>,
                                                   InstanciaVector<int>,
                                                   SolucionVector<int>>(ms, *instancia);
            tabla.agregarResultado(ms.nombre(), tamano, tiempo);
        }

        if (algoritmo == 2 || algoritmo == 3) {
            QuickSort<int> qs;
            double tiempo = MedidorTiempos::medir<QuickSort<int>,
                                                   InstanciaVector<int>,
                                                   SolucionVector<int>>(qs, *instancia);
            tabla.agregarResultado(qs.nombre(), tamano, tiempo);
        }
    }

    cout << "\n=== RESULTADOS ===\n";
    tabla.mostrar();
}

// ==== Scheduling ====
void EjecutarDebugScheduling(const std::string& archivo) {
    auto instancia = SchedulingParser::parse(archivo);

    cout << "Instancia Scheduling cargada:\n";
    instancia.mostrar(cout);

    SchedulingDyV dyv;
    auto solucion = dyv.ejecutar(instancia);

    cout << "\nSolución obtenida:\n";
    solucion.mostrar(cout);
}

void EjecutarNormalScheduling(const std::string& archivo) {
    auto instancia = SchedulingParser::parse(archivo);

    SchedulingDyV dyv;
    auto tiempo = MedidorTiempos::medir<SchedulingDyV,
                                        InstanciaScheduling,
                                        SolucionScheduling>(dyv, instancia);

    cout << "Tiempo de ejecución SchedulingDyV: " << tiempo << " s\n";
}

/* ===========================================
   MAIN
   =========================================== */

int main() {
    try {
        cout << "Seleccione tipo de problema:\n";
        cout << "1 - Ordenación (MergeSort/QuickSort)\n";
        cout << "2 - Scheduling (planificación empleados)\n";
        int problema;
        cin >> problema;

        if (problema == 1) {
            int modo = AskExecutionMode();
            if (modo == 0) return 0;

            int algoritmo = AskAlgorithmChoice();
            size_t tamano = AskInstanceSize();

            if (modo == 1) {
                int experimentos = AskNumberOfExperiments();
                EjecutarNormalOrdenacion(algoritmo, tamano, experimentos);
            } else {
                EjecutarDebugOrdenacion(algoritmo, tamano);
            }
        }
        else if (problema == 2) {
            cout << "Ingrese ruta del archivo JSON de instancia: ";
            string archivo;
            cin >> archivo;

            int modo = AskExecutionMode();
            if (modo == 0) return 0;

            if (modo == 1)
                EjecutarNormalScheduling(archivo);
            else
                EjecutarDebugScheduling(archivo);
        }
        else {
            cerr << "Problema inválido\n";
            return 1;
        }
    }
    catch (const DAAException& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}