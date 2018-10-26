#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace::std;

typedef double real;

int N;// размер матрицы
int M;// полуширина ленты

vector <real> F;// вектор правой части
vector <real> Y;// прямой ход
vector <real> X;// решение

vector<vector <real>> Aal;
vector<vector <real>> Aau;
vector <real> Adi;

#define Lal Aal
#define Uau Aau
#define Udi Adi

// al - нижний треугольник
// au - верхний треугольник
// di - диагональ




void CalcY()
{
	real sum;

	for (int i = 0; i < N; i++)
	{
		int j = i - M;
		sum = 0;
		for (int jL = 0; jL < M; jL++, j++)
		{
			if (j < 0) continue;
			sum += Lal[i][jL] * Y[j];
		}
		Y[i] = F[i] - sum;
	}

}



void CalcX()
{
	for (int i = N - 1; i >= 0; i--)
	{
		int j = i - M;
		real Xi = Y[i] / Udi[i];
		for (int jL = 0; jL < M; jL++, j++)
		{
			if (j < 0) continue;
			Y[j] -= Uau[i][jL] * Xi;

		}
		X[i] = Xi;
	}

}



// раскладывает A на LU
void CalcLU()
{
	for (int i = 0; i < N; i++)
	{
		real sumD = 0;
		int j = i - M;
		for (int jL = 0; jL < M; jL++, j++)
		{

			if (j < 0)continue;

			real sumL = 0;
			real sumU = 0;

			int kU = i - j;
			for (int kL = 0; kL < jL; kL++, kU++)
			{
				sumL += Lal[i][kL] * Uau[j][kU];
				sumU += Uau[i][kL] * Lal[j][kU];
			}

			Lal[i][jL] = (Lal[i][jL] - sumL) / Adi[j];
			Uau[i][jL] = Uau[i][jL] - sumU;
			sumD += Lal[i][jL] * Uau[i][jL];
		}
		Adi[i] = Adi[i] - sumD;
	}

}



void Input(ifstream& file)
{
	file >> N;
	file >> M;


	Aal.resize(N, vector<real>(M, 0.0));
	Aau.resize(N, vector<real>(M, 0.0));

	Y.resize(N, 0.0);
	X.resize(N, 0.0);

	Adi.resize(N);
	F.resize(N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			file >> Aal[i][j];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			file >> Aau[i][j];


	for (int i = 0; i < N; i++)
		file >> Adi[i];

	for (int i = 0; i < N; i++)
		file >> F[i];


}

//void createAkMatrix(vector<vector<real>>&matrix, int k)
//{
//  srand(time(0));
//  real sum;
//  for (int i = 0; i < N; i++)
//  {
//      sum = 0;
//      int j = i - M;
//      for (; j < N; j++)
//      {
//          if (j < 0)continue;
//          if (i != j)
//          {
//              matrix[i][j] = (rand() % 4)*(-1);
//              sum += matrix[i][j];
//          }
//      }
//      matrix[i][i] = abs(sum);
//  }
//  matrix[0][0] += pow(10, (k*(-1)));
//
//
//}

vector<vector<real>> createGilbMatrix(int k)
{
	vector<vector<real>> matrix;
	matrix.resize(k, vector < real>(k, 0.0));

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			matrix[i][j] = 1 / (i + j - 1);
	return matrix;
}


void MatrixOutFile(vector<vector<real>>MyVector, ofstream&File)
{
	for (int i = 0; i < MyVector.size(); i++)
	{
		{
			for (int j = 0; j < MyVector.size(); j++)
				File << MyVector[i][j] << " ";
		}
		File << endl;
	}
}


int main()
{

	ifstream inputFile("D:/input.txt");
	Input(inputFile);
	CalcLU();

	CalcY();
	CalcX();

	cout.precision(25);
	for (int i = 0; i < N; i++)
		cout << X[i] << endl;

	system("pause");


}