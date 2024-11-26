#include <iostream>
#include <vector>
#include <string>
using namespace std;

//подопытное сообщение
const char Txt[] = "Я помню чудное мгновенье: Передо мной явилась ты, Как мимолетное виденье, Как гений чистой красоты.";
int Txt_len = 347;
int Q, R;
string s = "", decod = "";
vector<int> cod;

//поиск нод
int gcd(int a, int b){
	while (b != 0) {					// алгоритма Евклида.
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

//сверхвозрастающая последовательность
int SVP[8];                                 //массив для хранения 8 элементов  сверхвозрастающей последовательности
void MakeSVR() {
	srand(time(NULL));
	SVP[0] = rand() % 100 + 1;				// инициализация первого элемента
	int sum = SVP[0];
	for (int i = 1; i < 8; i++) {			//В цикле создаются следующие элементы,которые
		SVP[i] = sum + rand() % 3 + 1;		//всегда больше предыдущего на случайное число от 1 до 3.
		sum = sum + SVP[i];
	}
	Q = sum + 5;
	while (!(gcd(Q, R) == 1))					
	{//вычисление множителя
		srand(time(NULL));					//генерация R, пока Q и R не
		R = rand() % 100 + 1;				//будут взаимно простыми (т.е. их НОД равен 1).
	}
}

//вычисление нормальной последовательности
int Norm[8];								//массив для хранения нормализованной последовательности.
void NormPosl() {
	for (int i = 0; i < 8; i++)				//В цикле каждый элемент SVP[i] умножается на R и берется 
		Norm[i] = (SVP[i] * R) % Q;			//по модулю Q, что создает нормализованную последовательность.
	cout << "ОРИГИНАЛ" << endl;
	cout << s << endl << endl;
}
//выделяем биты из символа и добавляем соответствующий элемент из Norm
void Coder() {
	int sum = 0;
	for (int c = 0; c < s.length(); c++) {		//проходит по каждому символу строки
		for (int bit = 0; bit < 8; bit++)		//проходит по каждому из 8 битов символа
			if (((s.at(c) >> bit) & 0b1) == 1)	//сдвигает биты символа s[c] вправо на bit позиций. И проверяет, является ли последний бит равным 1.
				sum = sum + Norm[bit];			//добавляется соответствующий элемент из массива Norm по индексу bit
		cod.push_back(sum);						//После обработки всех битов символа s[c], значение sum добавляется в вектор
		sum = 0;								//сбрасывается в 0 для следующего символа.
	}
	cout << "ШИФРОВКА" << endl;
	for (int k = 0; k < cod.size(); k++)
		cout << cod.at(k) << ' ';
	cout << endl << endl;
}

//поиск мультипликативного обратного для R, это будет y
int  Evclida_plus() {
	int a = Q, b = R, x = 0, y = 0;
	int q, r, x1, x2, y1, y2, d;
	if (b == 0) {
		d = a, x = 1, y = 0;
		return d;
	}
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;

	while (b > 0) {
		q = a / b, r = a - q * b;			//Находим частное q и остаток r
		x = x2 - q * x1, y = y2 - q * y1;	//Обновляем значения x и y с использованием предыдущих значений
		a = b, b = r;						//Обновляем a и b для следующей итерации
		x2 = x1, x1 = x, y2 = y1, y1 = y;
	}
	d = a, x = x2, y = y2;					//d будет НОД, а y — это искомый мультипликативный обратный элемент
	return y;
}

//функция расшифровки
void Decoder() {
	int C = 0, i = 7, sum = 0;
	int X = Evclida_plus();

	if (X < 0)
		X = Q - abs(X);
	for (int c = 0; c < cod.size(); c++) {
		sum = 0;
		C = (cod.at(c) * X) % Q;		//C это произведение закодированного символа и X, взятое по модулю Q
		while (i > -1) {
			if (SVP[i] <= C) {			//Внутренний цикл перебирает биты от 7 до 0, чтобы декодировать символ
				C = C - SVP[i];			//вычитая значения из C 
				sum = sum + pow(2, i);  //добавляя соответствующие степени двойки к sum
			}
			i--;
		}
		decod.push_back((char)sum);
		i = 7;
	}
	cout << "РАСШИФРОВКА" << endl;
	cout << decod << endl << endl;
}

//Выбор действия
int Menu() {
	bool Exit = true;
	char buf[100] = {};
	while (Exit){
		char Key = '0';
		cout << endl << "Выбор текста для обработки" << endl << endl << "Текст Пушкина : 1" << endl;
		cout << "Безделёв Сергей Владимирович: 2" << endl << "Ввести текст от руки: 3" << endl;
		cout << "Завершить работу : 4" << endl << "Введите номер пункта : ";
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
			s = "Безделёв Сергей Владимирович";
			Exit = false;
			break;
		case '3':
			getline(cin, s);
			Exit = false;
			break;
		case '4':
			return -100;
		default:
			cout << "Неверный номер меню!" << endl;
			break;
		}
	}
	return 1;
}

int main(void){
	setlocale(LC_ALL, "RU");
	while (true) {
		if (Menu() == -100) break;
		cout << "ОРИГИНАЛ" << endl << s << endl << endl;
		MakeSVR();
		NormPosl();
		Coder();
		Decoder();
		s.clear();
		cod.clear();
		decod.clear();
	}
}