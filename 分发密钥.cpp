#include"define.h"
#include<bitset>

using namespace std;

// 非对称加密的对称密钥分发
// 
// 在这里，我模拟的情形是：
// 主办方直接向投票者提供密钥
// 并且主办方公钥已公布，为下方的(n,e)（数字很小是为了方便模拟） n, e, d = 2537, 13, 937
// (n,d)私钥只有主办方知道。
// *另外，为了方便模拟，投票者的公钥私钥与主办方一致(只是为了方便模拟情形)，并且主办方知道投票者公钥



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
	cout << "1.非对称加密的密钥分发" << endl;
	cout << "2.主办方向投票者提供密钥" << endl;
	cout << "3.双方互相知道公钥，私钥保密" << endl;
	cout << "************************************************" << endl << endl << endl;

// 第一步 主办方 向 投票者 发送自己的ID和一个随机交互号N1
// 使用投票者的公钥进行加密
// 随机交互号被用来唯一的标志这次消息传递
// E(PU_b,[N1,ID]
	cout << "第一步：<主办方> 向 <投票者> 加密发送自己的ID和一个随机交互号N1" << endl;
	srand(time(0));// 随机数选出，建议换一个随机数生成算法，该算法不够随机
	int N1 = rand() % 99999999;
	int ID = 20200046; // 主办方的ID，可以理解为确认密钥分发者身份
	cout <<"随机数N1: " << hex << setw(8) << setfill('0') << N1 <<"   ";
	cout <<"主办方ID: " << hex << setw(8) << setfill('0') << ID << "\n";

	long long N1_ID = 0;// 将N1和ID组合起来，每个占4字节；共8字节 N1_ID     xxxxxxxx_xxxxxxxx
	N1_ID = N1_ID | N1; //赋高位的值:低位接收
	N1_ID = N1_ID << 32; //移动到高位,移动 32 bits,四字节
	N1_ID = N1_ID | ID; //赋低位的值
	//cout << hex << setw(16) << setfill('0') << N1_ID << "\n";

	unsigned long long Plain;
	cout <<"加密内容: "<< hex << setw(16) << setfill('0') << N1_ID << "\n";
	cout << "************************RSA加密************************" << endl;
	unsigned long long cipher; //密文
	unsigned long long ciphertext[8];  //存所有密文
	unsigned long long plaintext[8];  //在这里就解密，模拟简化投票者收到加密信息解密的过程
	for (int i = 0; i < 8; i++) //把加密内容以密码本形式加密
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
	cout << "空间传播: " << hex << setw(16) << setfill('0') << N1_ID_en << endl << endl;

	//加密后把信息传递给投票者，也就是申请密钥的人
	//第二步 投票者解密后求出N1,然后自己随机出一个N2，打包到一起，用主办方公钥加密传给主办方
	//E(PU_a,[N1,N2]

	cout << "第二步：<投票者> 收到并解密密文求出N1,和自己的随机N2，打包用主办方公钥加密传给 <主办方>" << endl;
	long long N1_ID_get = plaintext[0];
	base = 256;
	for (int i = 1; i < 8; i++)
	{
		N1_ID_get += plaintext[i] * base;
		base *= 256;
	}
	cout << "解密内容: " << hex << setw(16) << setfill('0') << N1_ID_get << "\n";
	int N1_b = 0;                   
	N1_b = N1_b | (N1_ID_get >> 32);     //获取N1，记作N1_b
	cout <<"获得N1: " << hex << setw(8) << setfill('0') << N1_b << "   ";

	int N2 = rand() % 66666666;// 随机数选出，建议换一个随机数生成算法，该算法不够随机
	cout <<"随机生成N2: "<< hex << setw(8) << setfill('0') << N2 << "\n";
	long long N1_N2 = 0;// 将N1和N2组合起来，每个占4字节；共8字节 N1_N2     xxxxxxxx_xxxxxxxx
	N1_N2 = N1_N2 | N1_b; //赋高位的值:低位接收
	N1_N2 = N1_N2 << 32; //移动到高位,移动 32 bits,四字节
	N1_N2 = N1_N2 | N2; //赋低位的值
	
	cout << "加密内容: " << hex << setw(16) << setfill('0') << N1_N2 << endl ;
	cout << "************************RSA加密************************" << endl << endl;
	for (int i = 0; i < 8; i++) //把加密内容以密码本形式加密
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
	cout << "空间传播: " << hex << setw(16) << setfill('0') << N1_N2_en << endl << endl;

	
	//加密后把信息传递给主办方
	//第三步 主办方提取N2，使用投票者的公钥加密后传给投票者，意思是信息来自于主办方，也就是密钥分发者
	//de_RSA(N1_N2);//**我这里RSA加密解密有点问题，暂时不追究，反正要换
	cout << "第三步：<主办方>提取N2，使用投票者的公钥加密后传给投票者，意思是信息来自于主办方，也就是密钥分发者" << endl;
	long long N1_N2_get = plaintext[0];
	base = 256;
	for (int i = 1; i < 8; i++)
	{
		N1_N2_get += plaintext[i] * base;
		base *= 256;
	}

	cout << "解密内容: " << hex << setw(16) << setfill('0') << N1_N2_get << "\n";

	int N2_a = 0;                    
	N2_a = N2_a | N1_N2_get;     //获取N2，记作N2_a
	cout << "获取N2: " << hex << setw(8) << setfill('0') << N2_a <<"  经验证确认消息来自 <主办方> " << endl<<endl ;

	
	//第四步 与第三步同时进行，主办方用选择所要传递的对称加密密钥 K，
	//并用自己的私钥进行签名，签名后将结果用投票者的公钥进行加密
	//C = E(PU_b , E(PR_a , K))
	cout << "第四步：<主办方> 选择对称加密密钥 K，先用自己的私钥进行签名，再用投票者的公钥进行加密" << endl;
	

	cout << endl << endl;
	cout << "对称密钥K: ";
	for (int i = 0; i < 128; i++)
		cout << hex << setw(2) << setfill('0') << KK1[i];
	
	cout <<endl<< "************************RSA加密************************" << endl;
	cout << endl << endl ;

	//M = en_RSA(K); //密钥为主办方的私钥
	unsigned long long ciphertextK[128];  //存所有密文
	unsigned long long plaintextK[128];  //在这里就解密，模拟简化投票者收到加密信息解密的过程
	for (int i = 0; i < 128; i++) 
	{
		Plain = KK1[i];
		Initialize(Plain, 2537, 937, 13);   //  ！！！调换D和E的位置
		cipher = RSA_Encrypt();
		ciphertextK[i] = cipher;
		cipher = RSA_Decrypt();
		plaintextK[i] = cipher;
	}

	//C = en_RSA(M); //密钥为投票者的公钥
	unsigned long long ciphertextKK[128];  //存所有密文
	unsigned long long plaintextKK[128]; // 在这里就解密，模拟简化投票者收到加密信息解密的过程
	for (int i = 0; i < 128; i++)
	{
		Plain = KK1[i];
		Initialize(Plain, 2537, 13, 937);   //  ！！！调换D和E的位置
		cipher = RSA_Encrypt();
		ciphertextKK[i] = cipher;
		cipher = RSA_Decrypt();
		plaintextKK[i] = cipher;
	}

	cout << "空间传输: ";
	for (int i = 0; i < 128; i++)
	{
		cout << hex << setw(3) << setfill('0') << ciphertextKK[i];
	}cout<< endl << endl << endl;
	//第五步 投票者收到 C 和 N2 ；知道主办方发来了K
	//K = D(PU_a,D(PR_b,C)
	cout << "第五步：<投票者> 得到 K   --->   K = D(PU_a,D(PR_b,C)" << endl;
	cout << "K_get = ";
	for (int i = 0; i < 128; i++)
	{
		cout << hex << setw(2) << setfill('0') << plaintextK[i];
	}
	cout << endl << endl << endl;
	
}
