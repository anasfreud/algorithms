#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int cnt;

class LongInt
{
private:
	int   m_length = 0;
	int * m_digits = nullptr;
	bool  m_sign = true;

public:
	LongInt()
	{
		resize(0);
	}
	LongInt(int len)
	{
		resize(len);
	}

	int length()
	{
		return m_length;
	}
	int sign()
	{
		return m_sign;
	}
	void setSign(bool sign)
	{
		m_sign = sign;
		cnt++;
	}
	int& operator[] (int i)
	{
		return m_digits[i];
	}

	// изменение размера числа
	void resize(int len)
	{
		clearMemory();
		m_length = len;
		m_digits = new int[m_length];
	}

	// добавление нового разряда
	void addDigit(int d)
	{
		cnt += 2;
		int* newDigits = new int[m_length + 1];
		for (int i = 0; i < m_length; i++) {
			newDigits[i] = m_digits[i];
			cnt++;
		}
		newDigits[m_length] = d;
		m_length++;
		delete[] m_digits;
		m_digits = newDigits;
		cnt += 3;
	}

	// удаление ведущих нулей
	void deleteZeroes()
	{
		cnt += 2;
		while (m_length >= 0 && m_digits[m_length - 1] == 0) {
			m_length--;
			cnt += 3;
		}
	}

	// очистка динамической памяти
	void clearMemory()
	{
		if (m_digits != nullptr) {
			delete[] m_digits;
			m_digits = nullptr;
		}
	}
};	

// сумма двух чисел по модулю
LongInt absAdd(LongInt, LongInt);

// разность двух чисел по модулю
LongInt absSub(LongInt, LongInt);

// сумма двух чисел с учетом знаков
LongInt add(LongInt, LongInt);

// разность двух чисел с учетом знаков
LongInt sub(LongInt, LongInt);

// сдвиг числа на n разрядов влево
LongInt shift(LongInt, int);

// разбиение числа на две части одинаковой длины
pair<LongInt, LongInt> split(LongInt);

// произведение двух чисел по алгоритму Карацубы
LongInt mult(LongInt, LongInt);

// заполнение числа случайными цифрами
void fillRandom(LongInt&);

int main()
{
	srand(time(0));
	
	for (int i = 1024; i <= 8192; i += 1024) {
		cnt = 0;
		LongInt a{ i };
		fillRandom(a);
		LongInt b{ i };
		fillRandom(b);
		LongInt m = mult(a, b);
		cout << cnt << '\n';

		a.clearMemory();
		b.clearMemory();
		m.clearMemory();

	}

	return 0;
}

LongInt absAdd(LongInt a, LongInt b)
{
	cnt++;
	if (a.length() < b.length()) {
		return absAdd(b, a);
	}

	LongInt r{ a.length()};

	cnt++;
	int temp = 0;
	for (int i = 0; i < a.length(); i++) {
		r[i] = a[i] + temp;
		cnt += 3;
		if (i < b.length())
		{
			r[i] += b[i];
			cnt += 2;
		}

		temp = r[i] / 10;
		r[i] %= 10;
		cnt += 4;
	}

	cnt++;
	if (temp > 0) {
		r.addDigit(temp);
	}

	return r;
}

LongInt absSub(LongInt a, LongInt b)
{
	cnt++;
	if (a.length() < b.length()) {
		return absSub(b, a);
	}

	LongInt r{ a.length()};

	cnt++;
	int temp = 0;
	for (int i = 0; i < a.length(); i++) {
		r[i] = a[i] - temp;
		
		cnt += 3;
		if (i < b.length()) {
			r[i] -= b[i];
			cnt += 2;
		}
		
		cnt++;
		if (r[i] < 0) {
			r[i] += 10;
			temp = 1;
			cnt += 3;
		} else {
			temp = 0;
			cnt++;
		}
	}

	r.deleteZeroes();
	return r;	
}

LongInt add(LongInt a, LongInt b)
{
	cnt++;
	if (a.length() < b.length()) {
		return add(b, a);
	}

	cnt++;
	LongInt r;
	if (a.sign() == b.sign()) {
		r = absAdd(a, b);
		r.setSign(a.sign());
	} else {
		int i = a.length() - 1;
		cnt += 3;
		if (a.length() == b.length()) {
			cnt += 2;
			while (i >= 0 && a[i] == b[i]) {
				i--;
				cnt += 3;
			}
		}

		cnt += 2;
		if (a.length() != b.length() || a[i] > b[i]) {
			r = absSub(a, b);
			r.setSign(a.sign());
		} else {
			r = absSub(b, a);
			r.setSign(false);
		}

	}
	return r;
}

LongInt sub(LongInt a, LongInt b)
{
	b.setSign(!b.sign());
	cnt++;
	return add(a, b);
}

LongInt shift(LongInt x, int k)
{
	cnt++;
	LongInt r{ x.length() + k};
	r.setSign(x.sign());

	for (int i = 0; i < k; i++) {
		r[i] = 0;
		cnt++;
	}
	for (int i = k; i < x.length() + k; i++) {
		r[i] = x[i - k];
		cnt += 2;
	}
	return r;
}

pair<LongInt, LongInt> split(LongInt x)
{
	cnt++;
	int length = x.length() / 2;
	LongInt x1{ length };
	LongInt x2{ length };

	for (int i = 0; i < length; i++) {
		x1[i] = x[i];
		cnt++;
	}
	for (int i = length; i < x.length(); i++) {
		x2[i - length] = x[i];
		cnt += 2;
	}

	return make_pair(x1, x2);
}

LongInt mult(LongInt a, LongInt b)
{
	LongInt r;

	cnt += 2;
	if (a.length() == b.length() && a.length() <= 1) {
		cnt += 2;
		r.addDigit(a[0] * b[0]);
		r.setSign(a.sign() == b.sign());
		return r;
	}

	pair<LongInt, LongInt> aSplit = split(a);
	pair<LongInt, LongInt> bSplit = split(b);

	int n = a.length();
	cnt++;

	LongInt first = mult(aSplit.first, bSplit.first);
	LongInt second = mult(aSplit.second, bSplit.second);
	LongInt sub1 = sub(aSplit.second, aSplit.first);
	LongInt sub2 = sub(bSplit.first, bSplit.second);
	LongInt comb = mult(sub1, sub2);
	LongInt shift1 = shift(second, n);
	LongInt shift2 = shift(second, n / 2);
	LongInt shift3 = shift(comb, n / 2);
	LongInt shift4 = shift(first, n / 2);

	cnt += 3;
	r = add(add(
		add(shift1, shift2),
		shift3),
		add(shift4, first));
	
	cnt++;
	r.setSign(a.sign() == b.sign());

	first.clearMemory();
	second.clearMemory();
	sub1.clearMemory();
	sub2.clearMemory();
	comb.clearMemory();
	aSplit.first.clearMemory();
	aSplit.second.clearMemory();
	bSplit.first.clearMemory();
	bSplit.second.clearMemory();
	shift1.clearMemory();
	shift2.clearMemory();
	shift3.clearMemory();
	shift4.clearMemory();

	return r;
}

void fillRandom(LongInt& x)
{
	x[0] = rand() % 9 + 1;
	for (int i = 1; i < x.length(); i++) {
		x[i] = rand() % 10;
	}
}
