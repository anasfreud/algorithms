#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

unsigned long long cnt;

vector<int> add(vector<int>, vector<int>);

vector<int> sub(vector<int>, vector<int>);

vector<int> mult(vector<int>, vector<int>);

vector<int> naiveMult(vector<int>, vector<int>);

vector<int> shift(vector<int>, int);

void extend(vector<int>&, vector<int>&);

void normalize(vector<int>&);

vector<int> randomNumber(int);


int main()
{
	srand(time(nullptr));
	int n = 1024;
	cnt = 0;
	vector<int> n1 = randomNumber(n);
	vector<int> n2 = randomNumber(n);
	mult(n1, n2);
	cout << n << " " << cnt << endl;
	/*for (int n = 1024; n <= 8192; n += 1024) {
		cnt = 0;
		vector<int> n1 = randomNumber(n);
		vector<int> n2 = randomNumber(n);
		mult(n1, n2);
		cout << n << " " << cnt << endl;
	}*/

	return 0;
}

vector<int> randomNumber(int n)
{
	vector<int> v;
	v.push_back(rand() % 9 + 1);

	for (int i = 1; i < n; i++) {
		v.push_back(rand() % 10);
	}
	return v;
}


vector<int> add(vector<int> a, vector<int> b)
{
	cnt++;
	if (a.size() < b.size()) {
		return add(b, a);
	}

	cnt += a.size(); // ?
	vector<int> result = a;

	for (int i = 0; i < b.size(); i++) {
		cnt += 2;
		result[i] += b[i];
	}

	return result;
}

vector<int> sub(vector<int> a, vector<int> b)
{
	cnt++;
	if (a.size() < b.size()) {
		return add(b, a);
	}

	cnt += a.size(); // ?
	vector<int> result = a;

	for (int i = 0; i < b.size(); i++) {
		cnt += 2;
		result[i] -= b[i];
	}

	return result;
}

void normalize(vector<int>& n)
{
	for (int i = 0; i < n.size(); i++) {
		cnt++;
		if (n[i] >= 10) {
			cnt += 2;
			if (i == n.size() - 1) {
				n.push_back(0); // ?
			}

			n[i + 1] += n[i] / 10;
			n[i] = n[i] % 10;
			cnt += 6;

		}
		else {
			cnt++;
			if (n[i] < 0) {
				n[i] += 10;
				n[i + 1] -= 1;
				cnt += 5;
			}
		}
	}
}

void extend(vector<int>& a, vector<int>& b)
{
	cnt += 4;
	int n = max(a.size(), b.size());
	n += n % 2;


	for (int i = a.size(); i < n; i++) {
		cnt++;
		a.push_back(0);
	}

	for (int i = b.size(); i < n; i++) {
		cnt++;
		b.push_back(0);
	}

}


vector<int> mult(vector<int> a, vector<int> b)
{
	cnt += 2;
	if (a.size() <= 1) {
		return naiveMult(a, b);
	}

	extend(a, b);

	cnt++;
	int n = a.size();

	cnt += 12; // ?

	vector<int> a1{ a.begin(), a.begin() + n / 2 };
	vector<int> a2{ a.begin() + n / 2, a.end() };

	vector<int> b1{ b.begin(), b.begin() + n / 2 };
	vector<int> b2{ b.begin() + n / 2, b.end() };

	vector<int> p1 = mult(a1, b1);
	vector<int> p2 = mult(a2, b2);
	vector<int> p3 = mult(sub(a2, a1), sub(b1, b2));
	
	cnt += 3;

	vector<int> s1 = add(shift(p2, n), shift(p2, n / 2));
	vector<int> s2 = shift(p3, n / 2);
	vector<int> s3 = add(shift(p1, n / 2), p1);

	return add(add(s1, s2), s3);
}

vector<int> naiveMult(vector<int> a, vector<int> b)
{
	vector<int> result;
	int r = a[0] * b[0];

	cnt += 3;

	while (r > 0) {
		result.push_back(r % 10);
		r /= 10;
		cnt += 4;
	}

	return result;
}

vector<int> shift(vector<int> v, int k)
{
	for (int i = 0; i < k; i++) {
		cnt++;
		v.insert(v.begin(), 0);
	}
	return v;
}


