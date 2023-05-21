#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdio>
#include<vector>

using namespace std;

//vector<int> ls;//用模板创建动态数组
int ls[100];

void InsertSort(int a[], int n)//直接插入排序
{
	int i, j;
	int temp;
	for (i = 0; i < n - 1; i++)
	{
		if (a[i] > a[i + 1])
		{
			temp = a[i + 1];
			for (j = i; temp < a[j]; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
	}

	cout << "The InsertSort ordered array is" << endl;
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main()
{
	int n;
	cout << "Please enter the number of the array" << endl;
	cin >> n;
	//vector<int> ls(n);
	cout << "Please enter the arraay" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> ls[i];
	}
	InsertSort(ls, n);
	return 0;
}
