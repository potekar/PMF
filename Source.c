#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//---------------------------------------------------------------------
void writeA(int arr[], int s)
{
	printf("niz je:[ ");
	for (int i = 0; i < s; i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("]\n");
}

void writeM(int mat[][5000], int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}
//---------------------------------------------------------------------

void create(int mat[][5000], int n, int m, int procMin, int procMax)
{
	printf("\n");
	long procR,brojNula,br=0,temp;

	srand(clock(NULL));

	procR = rand() % ((procMax - 1) - procMin) + procMin;
	brojNula = (n * m) * 0.01 * procR;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (br<brojNula)
				mat[i][j] = 0;
			else 
				mat[i][j] = 1;

			br++;
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int rn = rand() % n;
			int rm = rand() % m;

			temp = mat[i][j];
			mat[i][j] = mat[rn][rm];
			mat[rn][rm] = temp;
		}
	}
}

//----------------------------------------------------------------------

void transformToCSR(int mat[][5000], int m, int n, long A[], int IA[], int JA[])
{
	int br = 0;

	for (int i = 0; i < m * m; i++)
	{
		A[i] = 0;
		IA[i] = 0;
		JA[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mat[i][j] == 1)
			{
				A[br] = mat[i][j];
				IA[br] = i;
				JA[br] = j;
				br++;
			}
		}

	}
}

//--------------------------------------------------------------------

int AA[5000][5000];
int BB[5000][5000];
int CC[5000][5000];

void sum(int mat[5000][5000], int m, int n, int procMin, int procMax)
{
	create(mat, n, m, procMin, procMax);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			AA[i][j] = mat[i][j];
		}
	}

	create(mat,n, m, procMin, procMax);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			BB[i][j] = mat[i][j];
		}
	}

	int t1 = clock();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			CC[i][j] = AA[i][j] + BB[i][j];
		}
	}

	int t2 = clock();
	printf("\nPocetno vrijeme je %d , izlazno vrijeme je %d, vrijeme izvrsavanja programa je %d", t1, t2, t2 - t1);
	
}

//-------------------------------------------------------------------
int ap[5000][5000];
int bp[5000][5000];
int cp[5000][5000];

void product(int mat[][5000], int n, int m, int procMin, int procMax)
{

	create(mat, n, m, procMin, procMax);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			ap[i][j] = mat[i][j];
			//printf("%d ", A[i][j]);
		}
		//printf("\n");

	}

	create(mat, n, m, procMin, procMax);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			bp[i][j] = mat[i][j];
			//printf("%d ", B[i][j]);
		}
		//printf("\n");
	}
	
	int t1 = clock();

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cp[i][j] = 0;

			for (int k = 0; k < m; k++)
			{
				cp[i][j] += ap[i][k] * bp[k][j];
			}
		}
		
	}

	int t2 = clock();
	printf("\nPocetno vrijeme je %d , izlazno vrijeme je %d, vrijeme izvrsavanja programa je %d", t1, t2,t2-t1);
}

//-------------------------------------------------------------------
void sumCSR(long A1[], int IA1[], int JA1[], long A2[], int IA2[], int JA2[], long A3[], int IA3[], int JA3[], long A[], int IA[], int JA[], int mat[][5000], int n, int m, int procMin, int procMax)
{
	create(mat, n, m, procMin, procMax);
	transformToCSR(mat, m, n, A, IA, JA);

	int br = 0;

	for (int i = 0; A[i] == 1; i++)
	{
		A1[i] = A[i];
		IA1[i] = IA[i];
		JA1[i] = JA[i];
		br++;
	}


	int tempa = br;

	create(mat, n, m, procMin, procMax);
	transformToCSR(mat, m, n, A, IA, JA);


	br = 0;

	for (int i = 0; A[i] == 1; i++)
	{
		A2[i] = A[i];
		IA2[i] = IA[i];
		JA2[i] = JA[i];
		br++;
	}

	int tempb = br;



	br = 0;
	int ind = 0;

	int t1 = clock();
	int i = 0, j = 0;

	while (i < tempa && j < tempb)
	{
		if (IA1[i] < IA2[j])
		{
			A3[ind] = A1[i];
			IA3[ind] = IA1[i];
			JA3[ind] = JA1[i];
			i++;
		}

		else if (IA1[i] > IA2[j])
		{
			A3[ind] = A2[j];
			IA3[ind] = IA2[j];
			JA3[ind] = JA2[j];
			j++;
		}

		else if (IA1[i] == IA2[j])
		{
			if (JA1[i] < JA2[j])
			{
				A3[ind] = A1[i];
				IA3[ind] = IA1[i];
				JA3[ind] = JA1[i];
				i++;
			}
			else if (JA1[i] > JA2[j])
			{

				A3[ind] = A2[j];
				IA3[ind] = IA2[j];
				JA3[ind] = JA2[j];
				j++;
			}

			else if (JA1[i] == JA2[j])
			{
				A3[ind] = A2[j] + A1[i];
				IA3[ind] = IA2[j];
				JA3[ind] = JA2[j];
				j++;
				i++;
			}
		}

		ind++;

	}

	int t2 = clock();


	printf("\n[ CSR ]Pocetno vrijeme je %d , izlazno vrijeme je %d, vrijeme izvrsavanja programa je %d", t1, t2, t2 - t1);

	
}
//-------------------------------------------------------------------


long A[80000000];
long A1[80000000];
long A2[80000000];
long A3[80000000];
int IA[5000], JA[5000];
int IA1[5000], JA1[5000];
int IA2[5000], JA2[5000];
int IA3[5000], JA3[5000];
int mat[5000][5000];
int main()
{
	
	int n = 500, m = 500, procMin =40, procMax =50;
	
	sum(mat, m, n, procMin, procMax);
	
	
	sumCSR(A1, IA1, JA1, A2, IA2, JA2, A3, IA3, JA3, A, IA, JA, mat, n, m, procMin, procMax);
	

	product(mat, n, m, procMin, procMax);
	
	return 0;
}

