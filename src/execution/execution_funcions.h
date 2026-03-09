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
** Archivo execution_functions.h: Funciones de ejecución de algoritmos 
**/

#ifndef EXECUTION_FUNCTIONS_H
#define EXECUTION_FUNCTIONS_H

#include <string>
#include "../ordenacion/InstanciaVector.h"
#include "../ordenacion/SolucionVector.h"
#include "../ordenacion/mergeSort.h"
#include "../ordenacion/quickSort.h"
#include "../analysis/MedidorTiempos.h"
#include "../analysis/TablaResultados.h"
#include "../scheduling/SchedulingDyV.hpp"
#include "../scheduling/SchedulingParser.hpp"
#include "../scheduling/SolucionSchedulling.hpp"

void EjecutarDebugOrdenacion(int algoritmo, size_t size);
void EjecutarNormalOrdenacion(int algoritmo, size_t size, int experimentos);
void EjecutarDebugScheduling(const std::string& archivo);
void EjecutarNormalScheduling(const std::string& archivo);
void EjecutarDebugOrdenacion(int algoritmo, size_t size, const std::string& archivo_salida);
void EjecutarNormalOrdenacion(int algoritmo, size_t size, int experimentos, const std::string& archivo_salida);
void EjecutarDebugScheduling(const std::string& archivo, const std::string& archivo_salida);
void EjecutarNormalScheduling(const std::string& archivo, const std::string& archivo_salida);

#endif