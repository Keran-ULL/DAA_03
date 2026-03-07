#ifndef SOLUCION_SCHEDULING_HPP
#define SOLUCION_SCHEDULING_HPP

#include "../core/Solucion.h"
#include <vector>
#include <iostream>

class SolucionScheduling : public Solucion {

private:

  std::vector<std::vector<int>> plan_;
  int score_;

public:

  SolucionScheduling(int days,int employees)
    : plan_(days,std::vector<int>(employees,-1)),
      score_(0) {}

  void set(int d,int e,int shift){
    plan_[d][e]=shift;
  }

  int get(int d,int e) const {
    return plan_[d][e];
  }

  void setScore(int s){
    score_=s;
  }

  int score() const{
    return score_;
  }

  void mostrar(std::ostream& os) const override {

    os<<"Score: "<<score_<<"\n";

    for(size_t d=0;d<plan_.size();d++){

      os<<"Day "<<d<<": ";

      for(size_t e=0;e<plan_[d].size();e++)
        os<<plan_[d][e]<<" ";

      os<<"\n";
    }
  }

  int getDays() const {
      return plan_.size();
  }

  int getEmployees() const {
      if (!plan_.empty()) return plan_[0].size();
      return 0;
  }
};

#endif