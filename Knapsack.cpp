#include <iostream>
#include <conio.h>

using namespace std;

#define max(a,b)(a>b?a:b)

int Value(const int *val, const int *s, int **a, int N, int S)
{
	int result;
	if (N == 0) return 0;
	if (a[N - 1][S - 1] != 100) return a[N - 1][S - 1];
	if (s[N - 1] > S) result = Value(val, s, a, N - 1, S);
	else result = max(val[N - 1] + Value(val, s, a, N - 1, S - s[N - 1]), Value(val, s, a, N - 1, S));
	a[N - 1][S - 1] = result;
	
	return result;
}

void GetSeq(int **a,const int *s,const int N,int S,const char *name)
{
	if (N - 1 == 0)
	{
		if (a[N - 1][S - 1] == 100)
		{
			GetSeq(a, s, N - 1, S, name);
		}
		else
		{
			cout << name[N - 1];
			GetSeq(a, s, N - 1, S - s[N - 1], name);
		}
	}
	else if (N-2>=0)
	{
		if (a[N - 1][S - 1] == a[N - 2][S - 1])
		{
			GetSeq(a, s, N - 1, S, name);
		}
		else
		{
			cout << name[N - 1];
			GetSeq(a, s, N - 1, S - s[N - 1], name);
		}
	}
}

int main()
{
	int v[] = { 7, 9, 5, 12, 14, 6, 12 };
	int s[] = { 3, 4, 2, 6, 7, 3, 5 };
	char name[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

	int size = sizeof(v) / sizeof(*v);
	int reqSize = 15;
	int **arr = new int*[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = new int[reqSize];
		for (int j = 0; j < reqSize; j++)
		{
			arr[i][j] = 100;
		}
	}

	cout << Value(v, s, arr, size, reqSize) << endl;
	GetSeq(arr, s, size, reqSize, name);
	_getch();
	return 0;
}
