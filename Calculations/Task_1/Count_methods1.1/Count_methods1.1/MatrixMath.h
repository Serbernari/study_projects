#include "MyMatrix.h"


void mult_MatOnVect(MyMatrix* A, std::vector<real>* B);
void mult_MatOnMat(MyMatrix* A, MyMatrix* B);
void LU_dec(MyMatrix* A);
void forward_sol(MyMatrix* A, std::vector<real>* F);
void backward_sol(MyMatrix* A, std::vector<real>* F);
void LU_sol(MyMatrix* A, std::vector<real>* F);
MyMatrix HilbertMat(const unsigned size); //all stored in
/*
vector LU_solution(MyMatrix* A, Mymatrix* B); //������� ���� ������� �� ����������
vector Gauss_silution(���������� ������� � ������); //������� ���� ������� ������
MyMatrix MakeHilbertMatrix(seed); // ����� ������� ���������
����� ����� ����� �����. 
*/