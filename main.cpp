#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

int main()
{
	//可能用到的函数声明
	void caesar_en(char arr[], int n1, int n2);
	char caesar_de_class(char n, int m);
	void caesar_de(char arr[], int n1, int n2);
	void caesar_de_nokey(char arr[]);
	int gcd(int a, int b);
	void affine_en(char arr[], int a1, int b1, int a2, int b2);
	int bezout(int a, int n);
	void affine_de(char arr[], int a1, int b1, int a2, int b2);
	bool permut_test(int arr[], int n);
	void permut_en(char arr[], int arr0[], int col);
	int find(int arr[], int n, int k);
	void permut_de(char arr[], int arr0[], int col);
	void fence_en(char arr[], int n);
	void fence_de(char arr[], int n);
	void insert_char(char arr[], int n1, int n2, vector<char>&vec);
	void remove_char(vector<char> vec, int n1, int n2);
	char arr[] = "abcdef 123456 ABCDEF";
	vector<char> vec;
	insert_char(arr,2,2,vec);
	remove_char(vec, 2, 2);
	return 0;
}

//凯撒密码：加密
void caesar_en(char arr[], int n1, int n2)
{
	if (n1 >= 26 || n1 <= 0)
	{
		cout << "uneffective encryption to letters";
		cout << endl;
		return;
	}
	else if (n2 >= 10 || n1 <= 0)
	{
		cout << "uneffective encryption to numbers";
		cout << endl;
		return;
	}
	else
	{
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= 'a' && arr[i] <= 'z')
				arr[i] = ((arr[i] + n1 - 'a') % 26) + 'a';
			else if (arr[i] >= 'A' && arr[i] <= 'Z')
				arr[i] = ((arr[i] + n1 - 'A') % 26) + 'A';
			else if (arr[i] >= '0' && arr[i] <= '9')
				arr[i] = ((arr[i] + n2 - '0') % 10) + '0';
		}
		cout << arr << endl;
	}
	return;
}

//由于凯撒密码解密计算时会出现负数，对正负数进行分类讨论
inline char caesar_de_class(char n, int m)
{
	return n >= 0 ? n % m : m - (abs(n) % m);
}

//凯撒密码：解密
void caesar_de(char arr[], int n1, int n2)
{
	if (n1 >= 26 || n1 <= 0)
	{
		cout << "uneffective decryption to letters";
		cout << endl;
		return;
	}
	else if (n2 >= 10 || n1 <= 0)
	{
		cout << "uneffective decryption to numbers";
		cout << endl;
		return;
	}
	else
	{
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= 'a' && arr[i] <= 'z')
				arr[i] = caesar_de_class(arr[i] - n1 - 'a', 26) + 'a';
			else if (arr[i] >= 'A' && arr[i] <= 'Z')
				arr[i] = caesar_de_class(arr[i] - n1 - 'A', 26) + 'A';
			else if (arr[i] >= '0' && arr[i] <= '9')
				arr[i] = caesar_de_class(arr[i] - n2 - '0', 10) + '0';
		}
		cout << arr << endl;
	}
	return;
}

//凯撒密码无秘钥解密
void caesar_de_nokey(char arr[])
{
	//先遍历字母的秘钥
	for (int l = 1; l < 26; l++)
	{
		cout << "key of letters = " << l << ":";
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= 'a' && arr[i] <= 'z')
				cout << char(caesar_de_class(arr[i] - l - 'a', 26) + 'a');
			else if (arr[i] >= 'A' && arr[i] <= 'Z')
				cout << char(caesar_de_class(arr[i] - l - 'A', 26) + 'A');
			else
				cout << arr[i];
		}
		cout << endl;
	}
	int n1 = 0;
	cout << "please enter the key of letters you suspect" << endl;
	cin >> n1;
	for (int i = 0; arr[i] != '\0'; i++)
	{
		if (arr[i] >= 'a' && arr[i] <= 'z')
			arr[i] = caesar_de_class(arr[i] - n1 - 'a', 26) + 'a';
		else if (arr[i] >= 'A' && arr[i] <= 'Z')
			arr[i] = caesar_de_class(arr[i] - n1 - 'A', 26) + 'A';
	}
	cout << "now the sentence is :" << arr << endl;
	//再遍历数字的秘钥
	for (int l = 1; l < 10; l++)
	{
		cout << "key of numbers = " << l << ":";
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= '0' && arr[i] <= '9')
				cout << char(caesar_de_class(arr[i] - l - '0', 10) + '0');
			else
				cout << arr[i];
		}
		cout << endl;
	}
	int n2 = 0;
	cout << "please enter the key of numbers you suspect" << endl;
	cin >> n2;
	for (int i = 0; arr[i] != '\0'; i++)
	{
		if (arr[i] >= '0' && arr[i] <= '9')
			arr[i] =  caesar_de_class(arr[i] - n2 - '0', 10) + '0';
	}
	cout << "now the sentence is :" << arr << endl;
	return;
}

//判断最大公约数
int gcd(int a, int b)
{
	int r;
	while (b > 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

//仿射密码：加密
void affine_en(char arr[], int a1, int b1,int a2,int b2)
{
	if (gcd(a1,26) != 1 || a1 <= 0)
	{
		cout << "uneffective encryption to letters";
		cout << endl;
		return;
	}
	else if (gcd(a2, 10) != 1 || a2 <= 0)
	{
		cout << "uneffective encryption to numbers";
		cout << endl;
		return;
	}
	else
	{
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= 'a' && arr[i] <= 'z')
				arr[i] = (((arr[i] - 'a') * a1) + b1) % 26 + 'a';
			else if (arr[i] >= 'A' && arr[i] <= 'Z')
				arr[i] = (((arr[i] - 'A') * a1) + b1) % 26 + 'A';
			else if (arr[i] >= '0' && arr[i] <= '9')
				arr[i] = (((arr[i] - '0') * a2) + b2) % 10 + '0';
		}
		cout << arr << endl;
	}
	return;
}

//裴蜀定理反向求s
int bezout(int a,int n) 
{
	for (int i = 1; i < n; i++) 
	{
		if (a * i % n == 1) 
		{
			return i;
		}
	}
}

//仿射密码：解密
void affine_de(char arr[], int a1, int b1, int a2, int b2)
{
	if (gcd(a1, 26) != 1 || a1 <= 0)
	{
		cout << "uneffective decryption to letters";
		cout << endl;
		return;
	}
	else if (gcd(a2, 10) != 1 || a2 <= 0)
	{
		cout << "uneffective decryption to numbers";
		cout << endl;
		return;
	}
	else
	{
		int s1 = bezout(a1, 26);
		int s2 = bezout(a2, 10);
		for (int i = 0; arr[i] != '\0'; i++)
		{
			if (arr[i] >= 'a' && arr[i] <= 'z')
				arr[i] = (((arr[i] - 'a') * s1) + b1 * (26 - s1)) % 26 + 'a';
			else if (arr[i] >= 'A' && arr[i] <= 'Z')
				arr[i] = (((arr[i] - 'A') * s1) + b1 * (26 - s1)) % 26 + 'A';
			else if (arr[i] >= '0' && arr[i] <= '9')
				arr[i] = (((arr[i] - '0') * s2) + b2 * (10 - s2)) % 10 + '0';
		}
		cout << arr << endl;
	}
	return;
}

//置换密码，检验给出的序列是否合法
bool permut_test(int arr[],int n)
{
	int * arr0 = new int[n];
	for (int i = 0; i < n; i++)
		arr0[i] = arr[i];
	//排序
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (arr0[j] < arr0[j - 1])
			{
				int temp = arr0[j];
				arr0[j] = arr0[j - 1];
				arr0[j - 1] = temp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (arr0[i] != i)
			return 0;
	}
	delete[] arr0;
	return 1;
}

//置换密码：加密
void permut_en(char arr[], int arr0[], int col)
{
	int length = strlen(arr);
	if (length <= col || permut_test(arr0, col) == 0)
	{
		cout << "uneffective encryption";
		cout << endl;
		return;
	}
	else
	{
		if (length % col == 0)
		{
			int row = length / col;
			char* temp = new char[length];
			for (int i = 0; i < length; i++)
			{
				temp[i] = arr[i];
			}
			for (int i = 0; i < length; i++)
			{
				int j = i / col;
				int k = i % col;
				arr[i] = temp[j * col + arr0[k]];
			}
			delete[] temp;
		}
		else
		{
			cout << "the length of sentence must be a multiple of column" << endl;
			return;
		}
		cout << arr << endl;
	}
	return;
}

//在数组中找到对应的值并返回下标
inline int find(int arr[], int n, int k)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == k)
			return i;
	}
	return -1;
}

//置换密码：解密
void permut_de(char arr[], int arr0[], int col)
{
	int length = strlen(arr);
	if (length <= col || permut_test(arr0, col) == 0)
	{
		cout << "uneffective decryption";
		cout << endl;
		return;
	}
	else
	{
		if (length % col == 0)
		{
			int row = length / col;
			char* temp = new char[length];
			for (int i = 0; i < length; i++)
			{
				temp[i] = arr[i];
			}
			for (int i = 0; i < length; i++)
			{
				int j = i / col;
				int k = i % col;
				arr[i] = temp[j * col + find(arr0,col,k)];
			}
			delete[] temp;
		}
		else
		{
			cout << "the length of sentence must be a multiple of column" << endl;
			return;
		}
		cout << arr << endl;
	}
	return;
}

//栅栏密码：加密
void fence_en(char arr[], int n)
{
	int length = strlen(arr);
	if (length == n || length % n != 0)
	{
		cout << "uneffective encryption";
		cout << endl;
		return;
	}
	else
	{
		char* temp = new char[length];
		int m = length / n;
		for (int i = 0; i < length; i++)
		{
			temp[i] = arr[i];
		}
		for (int i = 0; i < length; i++)
		{
			int j = i / n;
			int k = i % n;
			arr[i] = temp[k * m + j];
		}
		cout << arr << endl;
		delete[] temp;
	}
	return;
}

//栅栏密码：解密
void fence_de(char arr[], int n)
{
	int length = strlen(arr);
	if (length == n || length % n != 0)
	{
		cout << "uneffective decryption";
		cout << endl;
		return;
	}
	else
	{
		char* temp = new char[length];
		int m = length / n;
		for (int i = 0; i < length; i++)
		{
			temp[i] = arr[i];
		}
		for (int i = 0; i < length; i++)
		{
			int j = i / m;
			int k = i % m;
			arr[i] = temp[k * n + j];
		}
		cout << arr << endl;
		delete[] temp;
	}
	return;
}

//在密文中插入无效字符
void insert_char(char arr[], int n1, int n2, vector<char>& vec)
{
	//vec为空vector
	for (int i = 0; arr[i] != '\0'; i++)
		vec.push_back(arr[i]);
	int temp = n1;
	//重复原位置的字符
	vec.insert(vec.begin() + temp,vec[temp]);
	int size_vec = vec.size();
	for (int i = n1; i < size_vec; i++)
	{
		if (i - temp == n2 + 1)
		{
			temp = i;
			vec.insert(vec.begin() + temp, vec[temp]);
			size_vec = vec.size();//随时更新
		}
	}
	vector<char>::iterator p;
	for (p = vec.begin(); p != vec.end(); p++)
	{
		cout << *p;
	}
	cout << endl;
	return;
}

//从密文中移除无效字符
void remove_char(vector<char> vec, int n1, int n2)
{
	int temp = n1;
	vec.erase(vec.begin() + temp);
	int size_vec = vec.size();
	for (int i = n1; i < size_vec; i++)
	{
		if (i - temp == n2)
		{
			temp = i;
			vec.erase(vec.begin() + temp);
			size_vec = vec.size();//随时更新
		}
	}
	vector<char>::iterator p;
	for (p = vec.begin(); p != vec.end(); p++)
	{
		cout << *p;
	}
	cout << endl;
	return;
}
