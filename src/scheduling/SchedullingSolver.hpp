#ifndef SCHEDULING_SOLVER_HPP
#define SCHEDULING_SOLVER_HPP

#include "InstanciaScheduling.hpp"
#include "SolucionSchedulling.hpp"

class SchedulingSolver {

private:

  const InstanciaScheduling& instancia_;
  SolucionScheduling best_;

public:

  SchedulingSolver(const InstanciaScheduling& i)
    : instancia_(i),
      best_(i.getDays(), i.getEmployees()) {}

  SolucionScheduling solve() {

    SolucionScheduling actual(instancia_.getDays(),
                              instancia_.getEmployees());

    backtrack(0,0,actual);

    return best_;
  }

private:

  void backtrack(int d,int e,SolucionScheduling& sol){

    if(d == instancia_.getDays()){
      evaluar(sol);
      return;
    }

    int next_d = d;
    int next_e = e+1;

    if(next_e == instancia_.getEmployees()){
      next_e = 0;
      next_d++;
    }

    for(int t=0;t<instancia_.getShifts();t++){

      sol.set(d,e,t);

      backtrack(next_d,next_e,sol);
    }
  }

  void evaluar(SolucionScheduling& sol){

    int score=0;

    for(int d=0;d<instancia_.getDays();d++)
      for(int e=0;e<instancia_.getEmployees();e++){

        int t=sol.get(d,e);

        score+=instancia_.getSatisfaction(e,d,t);
      }

    if(score>best_.score()){
      best_=sol;
      best_.setScore(score);
    }
  }
};

#endif