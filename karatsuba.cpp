#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>


using namespace std;


void read(vector<int>& v)
{
	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++) {
		v.push_back(s[i] - '0');
	}
}

void print(vector<int> v)
{
	for (int i = v.size() - 1; i >= 0; i--) {
		cout << v[i] << ' ';
	}
	cout << endl;
}


vector<int> add(vector<int>, vector<int>);
vector<int> sub(vector<int>, vector<int>);
void normalize(vector<int>&);
void extend(vector<int>&, vector<int>&);
vector<int> mul(vector<int>, vector<int>);
vector<int> naiveMul(vector<int>, vector<int>);
vector<int> shift(vector<int>, int);
vector<int> randomNumber(int);


int main()
{
	srand(time(nullptr));
	
	
	for (int n = 1024; n <= 8192; n += 1024) {
		cout << n << endl;
		vector<int> n1 = randomNumber(n);
		vector<int> n2 = randomNumber(n);
		mul(n1, n2);
	}

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
	if (a.size() < b.size()) {
		return add(b, a);
	}

	vector<int> result = a;

	for (int i = 0; i < b.size(); i++) {
		result[i] += b[i];
	}

	return result;
}

vector<int> sub(vector<int> a, vector<int> b)
{
	if (a.size() < b.size()) {
		return add(b, a);
	}

	vector<int> result = a;

	for (int i = 0; i < b.size(); i++) {
		result[i] -= b[i];
	}

	return result;
}

void normalize(vector<int>& n)
{
	for (int i = 0; i < n.size(); i++) {

		if (n[i] >= 10) {
			if (i == n.size() - 1) {
				n.push_back(0);
			}
			n[i + 1] += n[i] / 10;
			n[i] = n[i] % 10;

		} else if (n[i] < 0) {
			n[i] += 10;
			n[i + 1] -= 1;
		}
	}
}

void extend(vector<int>& a, vector<int>& b)
{
	int n = max(a.size(), b.size());
	n += n % 2;

	for (int i = a.size(); i < n; i++) {
		a.push_back(0);
	}

	for (int i = b.size(); i < n; i++) {
		b.push_back(0);
	}

}


vector<int> mul(vector<int> a, vector<int> b)
{
	if (a.size() <= 1) {
		return naiveMul(a, b);
	}

	extend(a, b);

	int n = a.size();

	vector<int> a1{ a.begin(), a.begin() + n / 2 };
	vector<int> a2{ a.begin() + n / 2, a.end() };

	vector<int> b1{ b.begin(), b.begin() + n / 2 };
	vector<int> b2{ b.begin() + n / 2, b.end() };

	vector<int> p1 = mul(a1, b1);
	vector<int> p2 = mul(a2, b2);
	vector<int> p3 = mul(sub(a2, a1), sub(b1, b2));
	
	vector<int> s1 = add(shift(p2, n), shift(p2, n / 2));
	vector<int> s2 = shift(p3, n / 2);
	vector<int> s3 = add(shift(p1, n / 2), p1);

	return add(add(s1, s2), s3);
}

vector<int> naiveMul(vector<int> a, vector<int> b)
{
	vector<int> result;
	int r = a[0] * b[0];

	while (r) {
		result.push_back(r % 10);
		r /= 10;
	}

	return result;
}

vector<int> shift(vector<int> v, int k)
{
	for (int i = 0; i < k; i++) {
		v.insert(v.begin(), 0);
	}
	return v;
}


