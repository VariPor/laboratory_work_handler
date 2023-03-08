#include <iostream>
#include "variable_data.h"

using namespace std;

double VariableData::error(double measurement) {

  switch(int(VariableData::instrumentError.first)) {
    case 0: { // relative error
      return VariableData::instrumentError.second / measurement;
    }
    case 1: { // absolute error
      return VariableData::instrumentError.second;
    }
    default: {
      throw "Wrong ErrorType!";
    }
  }
    
}
