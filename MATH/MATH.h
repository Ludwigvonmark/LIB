#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

//Numerical algorithms, double floating point precission

#include <vector>
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>  
#include <time.h>
#include <string>
#include <algorithm>
#include <functional>
#include <limits>

#include "FPU.h"//Floating point utilities
#include "VEC.h"//Vector ops
#include "MTR.h"//Matricial ops
#include "DIF.h"//Diferential calculus
#include "SLV.h"//Solvers algortithms
#include "OPT.h"//Optimization algortithms
#include "CMB.h"//Combinatory algorithms
#include "STA.h"//Statistics
#include "INTRP.h"//Interpolation algorithms
#include "NRM.hpp"//Normalization algorithms
#include "RND.h"//Normalization algorithms

//COMMON ALGORITHMS
int factorial(int n){
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
//COMMON ALGORITHMS

#endif // AXFPL_H_INCLUDED
