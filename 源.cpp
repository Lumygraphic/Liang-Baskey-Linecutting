#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
#include<iostream>
#include <iomanip>

using namespace std;

int hs[100];
//void BuildMaxheap(int A[], int len);
void heapAdjust(int A[], int k, int len);//函数声明，不写会报错
//void heapSort(int A[], int len);



void BuildMaxheap(int A[], int len)//建立大根堆
{
	for (int i = len / 2; i > 0; i--)//从最后一个非叶结点开始反复调整堆
	{
		heapAdjust(A, i, len);
	}
}

void heapAdjust(int A[], int k, int len)//调整大根堆
{
	A[0] = A[k];//A[0]暂存子树根节点
	for (int i = 2 * k; i <= len; i *= 2)//将以A[k]为根的子树进行调整
	{
		if (i < len && A[i] < A[i + 1])
		{
			i++;
		}
		if (A[0] >= A[i])
		{
			break;
		}
		else
		{
			A[k] = A[i];
			k = i;
		}

	}
	A[k] = A[0];//将被筛选结点的值放入最终位置
}

void heapSort(int A[], int len)//堆排序
{
	BuildMaxheap(A, len);//初始建堆

	for (int i = len; i > 1; i--)//n-1趟交换建堆过程
	{
		swap(A[i], A[1]);//输出堆顶元素（通过和堆底元素交换）
		heapAdjust(A, 1, i - 1);//调整，把剩余i-1个元素整理成堆
	}
}

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> hs[i];
	}
	cout << "排序前：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << hs[i];
		if (i != n)
			cout << ",";
	}
	cout << endl;

	BuildMaxheap(hs, n);
	cout << "第一次建堆：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << hs[i];
		if (i != n)
			cout << ",";
	}
	cout << endl;

	heapSort(hs, n);
	cout << "排序后：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << hs[i];
		if (i != n)
			cout << ",";
	}
	cout << endl;
	return 0;
}

