#include "MyMatrix.h"
#include <algorithm>

void mult_MatOnVect(MyMatrix* A, std::vector<real>* B);
void mult_MatOnMat(MyMatrix* A, MyMatrix* B);
void LU_dec(MyMatrix* A);
void LU_dec2(MyMatrix* A);
void forward_sol(MyMatrix* A, std::vector<real>* F);
void backward_sol(MyMatrix* A, std::vector<real>* F);
void LU_sol(MyMatrix* A, std::vector<real>* F);

void CalcX(MyMatrix* A, std::vector<real>* F);
void CalcY(MyMatrix* A, std::vector<real>* F);

MyMatrix HilbertMat(const unsigned size); //all stored in
