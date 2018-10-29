#include "MyMatrix.h"
#include <algorithm>

void LU_dec(MyMatrix* A);
void LU_dec2(MyMatrix* A);
void forward_sol(MyMatrix A, std::vector<real> F);
std::vector<double> backward_sol(MyMatrix A, std::vector<real> F);
void LU_sol(MyMatrix* A, std::vector<real>* F);
void makeDetNotZero(MyMatrix * A, int k);
MyMatrix HilbertMat(const unsigned size); //all stored in
