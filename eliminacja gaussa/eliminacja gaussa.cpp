#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

double h;

//FUNKCJE DO ZADANIA 1
void HilbertMatrix(int N, double** H);
void displayMatrix(int N, double** H);
void computeVec(int N, double** H, double* b);
void plotVec(int N, double* v);
void gauss(int N, double** A, double* x, double* b);
//FUNKCJE DO ZADANIA 2
void ComputeMatrix(int Q, double** K);
void ComputeVector(int n, double* F, double* x);

int main()
{
	//ZADANIE 1
	int N;
	double* b, * x;//funcja prawych stron i wektor niewiadomych
	printf("Podaj N: ");
	scanf("%d", &N);
	b = (double*)malloc(N * sizeof(double));
	x = (double*)malloc(N * sizeof(double));
	double** H = (double**)malloc(N * sizeof(double));

	for (int i = 0; i < N; i++) 
	{
      H[i] = (double*)malloc(N * sizeof(double));
	}

	HilbertMatrix(N, H);
	displayMatrix(N, H);
	computeVec(N, H, b);
	gauss(N, H, x, b);
	printf("\nX: ");
	for (int i = 0; i < N; i++)
	{
		printf("%lf ", x[i]);
	}

	//ZADANIE 2
	FILE* wynik_zad2 = fopen("wynik_zad2.txt", "w");
	int Q; //liczba przedziałow, będzie służyła do zaalokowania miejsca w tablicy K
	printf("\nPodaj Q: ");
	scanf("%d", &Q);
	h = pow(Q, -1);

	double** K = (double**)malloc((Q + 1) * sizeof(double)); //tablica K, współczynników
	double* T, * F; //T - macierz niewiadomych; F - macierz prawych stron
	T = (double*)malloc((Q + 1) * sizeof(double));

	double* y = (double*)malloc((Q + 1) * sizeof(double));
	for (int i = 0; i <= Q; i++)
	{
		y[i] = i * h;
	}

	F = (double*)malloc((Q + 1) * sizeof(double));
	F[0] = 273; //K
	F[Q] = 300; //K

	for (int i = 0; i < (Q + 1); i++)
	{
		K[i] = (double*)malloc((Q + 1) * sizeof(double));
	}
	ComputeMatrix(Q, K);
	ComputeVector(Q, F, y);
	gauss(Q+1, K, T, F);
	fprintf(wynik_zad2, "T:\n");
	for (int i = 0; i < Q; i++)
	{
		fprintf(wynik_zad2, "%lf\n", T[i]);
	}

	FILE* wynikHilbert = fopen("wynikHilbert.txt", "w"); //wynik potrzebny do zobrazowania jak złe wyniki dałaby macierz hilberta zamiast K

	double** h = (double**)malloc((Q+1) * sizeof(double));

	for (int i = 0; i < (Q+1); i++)
	{
		h[i] = (double*)malloc((Q+1) * sizeof(double));
	}
	HilbertMatrix(Q + 1, h);
	double* t = (double*)malloc((Q + 1) * sizeof(double)); //nowa macierz niewiadomych
	gauss(Q + 1, h, t, F);
	for (int i = 0; i < Q; i++)
	{
		fprintf(wynikHilbert, "%lf\n", t[i]);
	}

	free(K);
	free(H);
	free(T);
	free(h);
	free(t);
	fclose(wynik_zad2);
	fclose(wynikHilbert);
	return 0;
}
//Zad1
void HilbertMatrix(int N, double** H)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			H[i][j] = (1.0/(1 + i + j));
		}
	}
}
void displayMatrix(int N, double** H)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%lf", H[i][j]);
		}
		printf("\n");
	}
}
void computeVec(int N, double** H, double* b)
{
	double x = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			x += H[i][j];
		}
		b[i] = x;
		x = 0;
	}
	plotVec(N, b);
}
void plotVec(int N, double* v)
{
	printf("\nWektor b: ");
	for (int i = 0; i < N; i++)
	{
		printf("%lf", v[i]);
	}
}
//Zad2
void ComputeMatrix(int Q, double** K)
{
	K[0][0] = 1;
	K[Q][Q] = 1;

	//zapisanie na pierwszej i skrajnej ostatniej komórce wartosci 1, a w ich wierszach tylko 0
	for (int i = 0; i < Q; i++)
	{
		K[0][i + 1] = 0;
		K[Q][i] = 0;
	}

	//pętle dobrze ustawione, aby działać wewnątrz przedziału i nie ingerować w wartości skrajnych wierszy
	for (int i = 1; i < Q; i++)
	{
		for (int j = 0; j < (Q + 1); j++)
		{
			K[i][j] = 0;
		}
	}
	for (int i = 1; i < Q; i++)
	{
		for (int j = 0; j < (Q + 1); j++)
		{
			K[i][i - 1] = 1;
			K[i][i] = -2;
			K[i][i + 1] = 1;
		}
	}
	for (int i = 0; i < (Q + 1); i++)
	{
		for (int j = 0; j < (Q + 1); j++)
		{
			printf("%lf ", K[i][j]);
		}
		printf("\n");
	}
}
void ComputeVector(int n, double* F, double* x)
{
	
	int lambda = 58;
	for (int i = 1; i < n; i++)
	{
		F[i] = (-10000 * sin(M_PI * x[i]) / lambda) * pow(h, 2);
	}

	for (int i = 0; i <= n; i++)
	{
		printf("%lf\n", F[i]);
	}
}
