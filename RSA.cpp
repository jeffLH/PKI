#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
using namespace std;

unsigned long long Plaintext;//����
unsigned long long Ciphertext;//����
//int n, e = 0, d;
int n;
int e;
int d;

//������ת��
int BianaryTransform(int num, int bin_num[])
{

	int i = 0, mod = 0;

	//ת��Ϊ�����ƣ������ݴ�temp[]������
	while (num != 0)
	{
		mod = num % 2;
		bin_num[i] = mod;
		num = num / 2;
		i++;
	}

	//���ض���������λ��
	return i;
}

//����ƽ������
long long Modular_Exonentiation(long long a, int b, int n)
{
	int c = 0, bin_num[1000];
	long long d = 1;
	int k = BianaryTransform(b, bin_num) - 1;

	for (int i = k; i >= 0; i--)
	{
		c = 2 * c;
		d = (d * d) % n;
		if (bin_num[i] == 1)
		{
			c = c + 1;
			d = (d * a) % n;
		}
	}
	return d;
}

//����1000��������
int ProducePrimeNumber(int prime[])
{
	int c = 0, vis[1001];
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= 1000; i++)if (!vis[i])
	{
		prime[c++] = i;
		for (int j = i * i; j <= 1000; j += i)
			vis[j] = 1;
	}

	return c;
}


//ŷ�������չ�㷨
int Exgcd(int m, int n, int& x)
{
	int x1, y1, x0, y0, y;
	x0 = 1; y0 = 0;
	x1 = 0; y1 = 1;
	x = 0; y = 1;
	int r = m % n;
	int q = (m - r) / n;
	while (r)
	{
		x = x0 - q * x1; y = y0 - q * y1;
		x0 = x1; y0 = y1;
		x1 = x; y1 = y;
		m = n; n = r; r = m % n;
		q = (m - r) / n;
	}
	return n;
}

//RSA��ʼ��
void RSA_Initialize()
{
	//ȡ��1000������������prime[]������
	int prime[5000];
	int count_Prime = ProducePrimeNumber(prime);

	//���ȡ��������p,q
	srand((unsigned)time(NULL));
	int ranNum1 = rand() % count_Prime;
	int ranNum2 = rand() % count_Prime;
	int p = prime[ranNum1], q = prime[ranNum2];

	n = p * q;

	int On = (p - 1) * (q - 1);


	//��ŷ�������չ�㷨��e,d
	for (int j = 3; j < On; j += 1331)
	{
		int gcd = Exgcd(j, On, d);
		if (gcd == 1 && d > 0)
		{
			e = j;
			break;
		}

	}

}

//RSA����
unsigned long long RSA_Encrypt()
{
	Ciphertext = Modular_Exonentiation(Plaintext, e, n);

	return Ciphertext;
}

//RSA����
unsigned long long RSA_Decrypt()
{
	Ciphertext = Modular_Exonentiation(Ciphertext, d, n);
	
	return Ciphertext;
}


//�㷨��ʼ��
void Initialize(unsigned long long Plain, int N, int E, int D)  //2537,13,937
{
	Plaintext = Plain;
	n = N;
	e = E;
	d = D;
	/*
	while (!e)
		RSA_Initialize();*/
}
/*
int main()
{
	unsigned long long Plain = 0b1111000011110000;
	Initialize(Plain);

	while (!e)
		RSA_Initialize();

	RSA_Encrypt();

	RSA_Decrypt();

	return 0;
}
*/