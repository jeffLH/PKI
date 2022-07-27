#include"define.h"
#include<bitset>

using namespace std;

// �ǶԳƼ��ܵĶԳ���Կ�ַ�
// 
// �������ģ��������ǣ�
// ���췽ֱ����ͶƱ���ṩ��Կ
// �������췽��Կ�ѹ�����Ϊ�·���(n,e)�����ֺ�С��Ϊ�˷���ģ�⣩ n, e, d = 2537, 13, 937
// (n,d)˽Կֻ�����췽֪����
// *���⣬Ϊ�˷���ģ�⣬ͶƱ�ߵĹ�Կ˽Կ�����췽һ��(ֻ��Ϊ�˷���ģ������)���������췽֪��ͶƱ�߹�Կ



int main()
{
	ifstream infile;
	infile.open("K.txt", ios::in);
	string K;
	getline(infile, K);
	unsigned int KK1[128];
	unsigned int KK2[128];
	unsigned int KK3[3];
	unsigned int KK4[3];
	unsigned int KK5[3];
	unsigned int KK6[3];
	for (int i = 0; i < 256; i++)
	{
		//cout << K[i];
	}cout << endl;
	int j = 0;
	int p, q;
	for (int i = 0; i < 128; i++)
	{
		if (K[j] <= '9')
			p = int(K[j]) - 48;
		else
			p = int(K[j]) - 87;
		if (K[j + 1] <= '9')
			q = int(K[j + 1]) - 48;
		else
			q = int(K[j + 1]) - 87;
		KK1[i] = p * 16 + q;
		//cout << hex << setw(2) << setfill('0') << KK1[i];
		j += 2;
	}cout << endl;
	getline(infile, K);
	for (int i = 0; i < 256; i++)
	{
		//cout << K[i];
	}cout << endl;
	j = 0;
	for (int i = 0; i < 128; i++)
	{
		if (K[j] <= '9')
			p = int(K[j]) - 48;
		else
			p = int(K[j]) - 87;
		if (K[j + 1] <= '9')
			q = int(K[j + 1]) - 48;
		else
			q = int(K[j + 1]) - 87;
		KK2[i] = p * 16 + q;
		//cout << hex << setw(2) << setfill('0') << KK2[i];
		j += 2;
	}

		
	
	
	cout << "************************************************" << endl;
	cout << "1.�ǶԳƼ��ܵ���Կ�ַ�" << endl;
	cout << "2.���췽��ͶƱ���ṩ��Կ" << endl;
	cout << "3.˫������֪����Կ��˽Կ����" << endl;
	cout << "************************************************" << endl << endl << endl;

// ��һ�� ���췽 �� ͶƱ�� �����Լ���ID��һ�����������N1
// ʹ��ͶƱ�ߵĹ�Կ���м���
// ��������ű�����Ψһ�ı�־�����Ϣ����
// E(PU_b,[N1,ID]
	cout << "��һ����<���췽> �� <ͶƱ��> ���ܷ����Լ���ID��һ�����������N1" << endl;
	srand(time(0));// �����ѡ�������黻һ������������㷨�����㷨�������
	int N1 = rand() % 99999999;
	int ID = 20200046; // ���췽��ID���������Ϊȷ����Կ�ַ������
	cout <<"�����N1: " << hex << setw(8) << setfill('0') << N1 <<"   ";
	cout <<"���췽ID: " << hex << setw(8) << setfill('0') << ID << "\n";

	long long N1_ID = 0;// ��N1��ID���������ÿ��ռ4�ֽڣ���8�ֽ� N1_ID     xxxxxxxx_xxxxxxxx
	N1_ID = N1_ID | N1; //����λ��ֵ:��λ����
	N1_ID = N1_ID << 32; //�ƶ�����λ,�ƶ� 32 bits,���ֽ�
	N1_ID = N1_ID | ID; //����λ��ֵ
	//cout << hex << setw(16) << setfill('0') << N1_ID << "\n";

	unsigned long long Plain;
	cout <<"��������: "<< hex << setw(16) << setfill('0') << N1_ID << "\n";
	cout << "************************RSA����************************" << endl;
	unsigned long long cipher; //����
	unsigned long long ciphertext[8];  //����������
	unsigned long long plaintext[8];  //������ͽ��ܣ�ģ���ͶƱ���յ�������Ϣ���ܵĹ���
	for (int i = 0; i < 8; i++) //�Ѽ������������뱾��ʽ����
	{
		Plain = N1_ID % 256;
		N1_ID = N1_ID / 256;
		Initialize(Plain, 2537, 13, 937);
		cipher = RSA_Encrypt();
		//cout << cipher << "  ";
		ciphertext[i] = cipher;
		cipher = RSA_Decrypt();
		//cout << cipher << "  ";
		plaintext[i] = cipher;
	}
	cout << endl;
	
	long long N1_ID_en = ciphertext[0];
	long long base = 256*16;
	for (int i = 1; i < 8; i++)
	{
		N1_ID_en += ciphertext[i] * base;
		base *= 256*16;
	}
	cout << "�ռ䴫��: " << hex << setw(16) << setfill('0') << N1_ID_en << endl << endl;

	//���ܺ����Ϣ���ݸ�ͶƱ�ߣ�Ҳ����������Կ����
	//�ڶ��� ͶƱ�߽��ܺ����N1,Ȼ���Լ������һ��N2�������һ�������췽��Կ���ܴ������췽
	//E(PU_a,[N1,N2]

	cout << "�ڶ�����<ͶƱ��> �յ��������������N1,���Լ������N2����������췽��Կ���ܴ��� <���췽>" << endl;
	long long N1_ID_get = plaintext[0];
	base = 256;
	for (int i = 1; i < 8; i++)
	{
		N1_ID_get += plaintext[i] * base;
		base *= 256;
	}
	cout << "��������: " << hex << setw(16) << setfill('0') << N1_ID_get << "\n";
	int N1_b = 0;                   
	N1_b = N1_b | (N1_ID_get >> 32);     //��ȡN1������N1_b
	cout <<"���N1: " << hex << setw(8) << setfill('0') << N1_b << "   ";

	int N2 = rand() % 66666666;// �����ѡ�������黻һ������������㷨�����㷨�������
	cout <<"�������N2: "<< hex << setw(8) << setfill('0') << N2 << "\n";
	long long N1_N2 = 0;// ��N1��N2���������ÿ��ռ4�ֽڣ���8�ֽ� N1_N2     xxxxxxxx_xxxxxxxx
	N1_N2 = N1_N2 | N1_b; //����λ��ֵ:��λ����
	N1_N2 = N1_N2 << 32; //�ƶ�����λ,�ƶ� 32 bits,���ֽ�
	N1_N2 = N1_N2 | N2; //����λ��ֵ
	
	cout << "��������: " << hex << setw(16) << setfill('0') << N1_N2 << endl ;
	cout << "************************RSA����************************" << endl << endl;
	for (int i = 0; i < 8; i++) //�Ѽ������������뱾��ʽ����
	{
		Plain = N1_N2 % 256;
		N1_N2 = N1_N2 / 256;
		Initialize(Plain, 2537, 13, 937);
		cipher = RSA_Encrypt();
		//cout << cipher << "  ";
		ciphertext[i] = cipher;
		cipher = RSA_Decrypt();
		//cout << cipher << "  ";
		plaintext[i] = cipher;
	}

	
	long long N1_N2_en = ciphertext[0];
	base = 256*16;
	for (int i = 1; i < 8; i++)
	{
		N1_N2_en += ciphertext[i] * base;
		base *= 256*16;
	}
	cout << "�ռ䴫��: " << hex << setw(16) << setfill('0') << N1_N2_en << endl << endl;

	
	//���ܺ����Ϣ���ݸ����췽
	//������ ���췽��ȡN2��ʹ��ͶƱ�ߵĹ�Կ���ܺ󴫸�ͶƱ�ߣ���˼����Ϣ���������췽��Ҳ������Կ�ַ���
	//de_RSA(N1_N2);//**������RSA���ܽ����е����⣬��ʱ��׷��������Ҫ��
	cout << "��������<���췽>��ȡN2��ʹ��ͶƱ�ߵĹ�Կ���ܺ󴫸�ͶƱ�ߣ���˼����Ϣ���������췽��Ҳ������Կ�ַ���" << endl;
	long long N1_N2_get = plaintext[0];
	base = 256;
	for (int i = 1; i < 8; i++)
	{
		N1_N2_get += plaintext[i] * base;
		base *= 256;
	}

	cout << "��������: " << hex << setw(16) << setfill('0') << N1_N2_get << "\n";

	int N2_a = 0;                    
	N2_a = N2_a | N1_N2_get;     //��ȡN2������N2_a
	cout << "��ȡN2: " << hex << setw(8) << setfill('0') << N2_a <<"  ����֤ȷ����Ϣ���� <���췽> " << endl<<endl ;

	
	//���Ĳ� �������ͬʱ���У����췽��ѡ����Ҫ���ݵĶԳƼ�����Կ K��
	//�����Լ���˽Կ����ǩ����ǩ���󽫽����ͶƱ�ߵĹ�Կ���м���
	//C = E(PU_b , E(PR_a , K))
	cout << "���Ĳ���<���췽> ѡ��ԳƼ�����Կ K�������Լ���˽Կ����ǩ��������ͶƱ�ߵĹ�Կ���м���" << endl;
	

	cout << endl << endl;
	cout << "�Գ���ԿK: ";
	for (int i = 0; i < 128; i++)
		cout << hex << setw(2) << setfill('0') << KK1[i];
	
	cout <<endl<< "************************RSA����************************" << endl;
	cout << endl << endl ;

	//M = en_RSA(K); //��ԿΪ���췽��˽Կ
	unsigned long long ciphertextK[128];  //����������
	unsigned long long plaintextK[128];  //������ͽ��ܣ�ģ���ͶƱ���յ�������Ϣ���ܵĹ���
	for (int i = 0; i < 128; i++) 
	{
		Plain = KK1[i];
		Initialize(Plain, 2537, 937, 13);   //  ����������D��E��λ��
		cipher = RSA_Encrypt();
		ciphertextK[i] = cipher;
		cipher = RSA_Decrypt();
		plaintextK[i] = cipher;
	}

	//C = en_RSA(M); //��ԿΪͶƱ�ߵĹ�Կ
	unsigned long long ciphertextKK[128];  //����������
	unsigned long long plaintextKK[128]; // ������ͽ��ܣ�ģ���ͶƱ���յ�������Ϣ���ܵĹ���
	for (int i = 0; i < 128; i++)
	{
		Plain = KK1[i];
		Initialize(Plain, 2537, 13, 937);   //  ����������D��E��λ��
		cipher = RSA_Encrypt();
		ciphertextKK[i] = cipher;
		cipher = RSA_Decrypt();
		plaintextKK[i] = cipher;
	}

	cout << "�ռ䴫��: ";
	for (int i = 0; i < 128; i++)
	{
		cout << hex << setw(3) << setfill('0') << ciphertextKK[i];
	}cout<< endl << endl << endl;
	//���岽 ͶƱ���յ� C �� N2 ��֪�����췽������K
	//K = D(PU_a,D(PR_b,C)
	cout << "���岽��<ͶƱ��> �õ� K   --->   K = D(PU_a,D(PR_b,C)" << endl;
	cout << "K_get = ";
	for (int i = 0; i < 128; i++)
	{
		cout << hex << setw(2) << setfill('0') << plaintextK[i];
	}
	cout << endl << endl << endl;
	
}
