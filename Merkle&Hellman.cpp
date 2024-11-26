#include <iostream>
#include <vector>
#include <string>
using namespace std;

//���������� ���������
const char Txt[] = "� ����� ������ ���������: ������ ���� ������� ��, ��� ���������� �������, ��� ����� ������ �������.";
int Txt_len = 347;
int Q, R;
string s = "", decod = "";
vector<int> cod;

//����� ���
int gcd(int a, int b){
	while (b != 0) {					// ��������� �������.
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//����������������� ������������������
int SVP[8];                                 //������ ��� �������� 8 ���������  ����������������� ������������������
void MakeSVR() {
	srand(time(NULL));
	SVP[0] = rand() % 100 + 1;				// ������������� ������� ��������
	int sum = SVP[0];
	for (int i = 1; i < 8; i++) {			//� ����� ��������� ��������� ��������,�������
		SVP[i] = sum + rand() % 3 + 1;		//������ ������ ����������� �� ��������� ����� �� 1 �� 3.
		sum = sum + SVP[i];
	}
	Q = sum + 5;
	while (!(gcd(Q, R) == 1))					
	{//���������� ���������
		srand(time(NULL));					//��������� R, ���� Q � R ��
		R = rand() % 100 + 1;				//����� ������� �������� (�.�. �� ��� ����� 1).
	}
}

//���������� ���������� ������������������
int Norm[8];								//������ ��� �������� ��������������� ������������������.
void NormPosl() {
	for (int i = 0; i < 8; i++)				//� ����� ������ ������� SVP[i] ���������� �� R � ������� 
		Norm[i] = (SVP[i] * R) % Q;			//�� ������ Q, ��� ������� ��������������� ������������������.
	cout << "��������" << endl;
	cout << s << endl << endl;
}
//�������� ���� �� ������� � ��������� ��������������� ������� �� Norm
void Coder() {
	int sum = 0;
	for (int c = 0; c < s.length(); c++) {		//�������� �� ������� ������� ������
		for (int bit = 0; bit < 8; bit++)		//�������� �� ������� �� 8 ����� �������
			if (((s.at(c) >> bit) & 0b1) == 1)	//�������� ���� ������� s[c] ������ �� bit �������. � ���������, �������� �� ��������� ��� ������ 1.
				sum = sum + Norm[bit];			//����������� ��������������� ������� �� ������� Norm �� ������� bit
		cod.push_back(sum);						//����� ��������� ���� ����� ������� s[c], �������� sum ����������� � ������
		sum = 0;								//������������ � 0 ��� ���������� �������.
	}
	cout << "��������" << endl;
	for (int k = 0; k < cod.size(); k++)
		cout << cod.at(k) << ' ';
	cout << endl << endl;
}

//����� ������������������ ��������� ��� R, ��� ����� y
int  Evclida_plus() {
	int a = Q, b = R, x = 0, y = 0;
	int q, r, x1, x2, y1, y2, d;
	if (b == 0) {
		d = a, x = 1, y = 0;
		return d;
	}
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;

	while (b > 0) {
		q = a / b, r = a - q * b;			//������� ������� q � ������� r
		x = x2 - q * x1, y = y2 - q * y1;	//��������� �������� x � y � �������������� ���������� ��������
		a = b, b = r;						//��������� a � b ��� ��������� ��������
		x2 = x1, x1 = x, y2 = y1, y1 = y;
	}
	d = a, x = x2, y = y2;					//d ����� ���, � y � ��� ������� ����������������� �������� �������
	return y;
}

//������� �����������
void Decoder() {
	int C = 0, i = 7, sum = 0;
	int X = Evclida_plus();

	if (X < 0)
		X = Q - abs(X);
	for (int c = 0; c < cod.size(); c++) {
		sum = 0;
		C = (cod.at(c) * X) % Q;		//C ��� ������������ ��������������� ������� � X, ������ �� ������ Q
		while (i > -1) {
			if (SVP[i] <= C) {			//���������� ���� ���������� ���� �� 7 �� 0, ����� ������������ ������
				C = C - SVP[i];			//������� �������� �� C 
				sum = sum + pow(2, i);  //�������� ��������������� ������� ������ � sum
			}
			i--;
		}
		decod.push_back((char)sum);
		i = 7;
	}
	cout << "�����������" << endl;
	cout << decod << endl << endl;
}

//����� ��������
int Menu() {
	bool Exit = true;
	char buf[100] = {};
	while (Exit){
		char Key = '0';
		cout << endl << "����� ������ ��� ���������" << endl << endl << "����� ������� : 1" << endl;
		cout << "������� ������ ������������: 2" << endl << "������ ����� �� ����: 3" << endl;
		cout << "��������� ������ : 4" << endl << "������� ����� ������ : ";
		Key = getchar();
		cin.ignore(1);
		int A = 0;
		if (Key < '1' || Key>'4')
			Key = '5';
		switch (Key){
		case '1':
			s = Txt;
			Exit = false;
			break;
		case '2':
			s = "������� ������ ������������";
			Exit = false;
			break;
		case '3':
			getline(cin, s);
			Exit = false;
			break;
		case '4':
			return -100;
		default:
			cout << "�������� ����� ����!" << endl;
			break;
		}
	}
	return 1;
}

int main(void){
	setlocale(LC_ALL, "RU");
	while (true) {
		if (Menu() == -100) break;
		cout << "��������" << endl << s << endl << endl;
		MakeSVR();
		NormPosl();
		Coder();
		Decoder();
		s.clear();
		cod.clear();
		decod.clear();
	}
}