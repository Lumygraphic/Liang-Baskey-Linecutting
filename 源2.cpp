#include<cstdio>
#include<cmath>
#include<algorithm>
#include<stack>
#include<iostream>
#include<iomanip>
#include<cstring>
#include <unordered_map>

using namespace std;

char mode[1000];//储存模式字符串
char text[1000];//储存文本字符串
int table[128];//储存表

void Shift_table(int size)//为模式字符串每一个字符创建移动表
{
	for (int i = 0; i < 128; i++)
	{
		table[i] = size;
	}

	for (int j = 0; j < size - 1; j++)
	{
		table[mode[j]] = size - 1 - j;
	}

}

int HorspoolMatching(int size1, int size2)
{
	int i = size1 - 1;
	while (i < size2)
	{
		//cout << endl << "尾部元素呆过的位置：" << i + 1 << endl;
		int k = 0;
		//通过计数来判断字符串匹配 
		while (k <= size1 - 1 && mode[size1 - 1 - k] == text[i - k]) {
			k++;
		}
		if (k == size1) return i - size1 + 2;
		//如果匹配完了，就直接返回查找字符串在文本中所匹配到的第一个位置 实际上是i-(size_m-1) +1 
		else i = i + table[text[i]];
		//如果没有匹配到全部 按照移动表来进行移动 

	}
	return -1;//匹配完未找到
}

int main()
{
	string ch1, ch2;
	cout << "请输入文本字符串" << endl;
	gets_s(text);
	
	cout << "请输入模式字符串：" << endl;
	gets_s(mode);
	
	Shift_table(strlen(mode));//创建移动表

	int index = HorspoolMatching(strlen(mode), strlen(text));//计算匹配位置

	//cout << "模式匹配首位为" << index << endl;
	cout << text << endl;
	cout << mode << endl;

	//输出模式字符串每个字符的移动量
	for (int k = 0; k < strlen(mode) - 1; k++)
	{
		cout << mode[k] << ":" << table[mode[k]] << endl;
	}
	cout << "else:" << strlen(mode) << endl;//未出现在模式字符串里的字符移动量

	cout << index << endl;//输出模式匹配到的位置
	return 0;
}