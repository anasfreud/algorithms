#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX_DIS 20

int cnt = 0;

void strToSet(string s, set<vector<int>>& d) {
	cnt++;
	int size = 0;
	for (int i = 0; i < s.length(); i++) {
		cnt++;
		if (s[i] == 'x') {
			int p = 0;
			i++;
			cnt += 3;
			while (isdigit(s[i])) {
				p = p * 10 + (s[i] - '0');
				i++;
				cnt += 6;
			}
			i--;
			size = max(size, p);
			cnt += 4;
		}
	}

	vector<int> v(size, 0);
	bool t = true;
	cnt++;

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		cnt ++;

		switch (c)
		{
		case '&':
			cnt += 2;
			d.insert(v);
			v.assign(size, 0);
			break;
		case '-':
			t = false;
			i++;
			cnt += 3;
		case 'x':
			int p = 0;
			i++;
			cnt += 3;
			while (isdigit(s[i])) {
				p = p * 10 + (s[i] - '0');
				i++;
				cnt += 6;
			}
			i--;
			v[p - 1] = t + 1;
			t = true;
			cnt += 6;
			break;
		}
	}
	cnt++;
	d.insert(v);
}

string setToStr(set<vector<int>> d) {
	cnt++;
	string result = "";
	for (auto it = d.begin(); it != d.end(); it++) {
		vector<int> a = *it;
		result += "(";
		cnt += 2;

		for (int i = 0; i < a.size(); i++) {
			cnt++;
			if (a[i] == 1) {
				cnt += 5;
				result += "-x" + to_string(i + 1) + "|";
			}
			else if (a[i] == 2) {
				cnt += 6;
				result += "x" + to_string(i + 1) + "|";
			}
		}
		cnt += 2;
		if (result[result.length() - 1] != '(') {
			cnt += 2;
			result.erase(result.length() - 1);
		}
		cnt += 2;
		result += ")&";

	}
	cnt++;
	if (result.length() > 0) {
		cnt += 2;
		result.erase(result.length() - 1);
	}
	return result;
}

string KNF(int n) {

	set<vector<int>> d;
	cnt += 2;
	int disCnt = rand() % MAX_DIS;

	vector<int> v;
	
	for (int i = 0; i < disCnt; i++) {
		cnt += 2;
		v.clear();
		int nulls = 0;
		for (int j = 0; j < n; j++) {
			cnt += 3;
			v.push_back(rand() % 3);
			if (v[j] == 0) {
				cnt++;
				nulls++;
			}
		}
		cnt++;
		if (nulls != v.size()) {
			cnt++;
			d.insert(v);
		}
	}
	
	return setToStr(d);
}

// возвращает false, если формула точно невыполнима, иначе true
bool RES(string s) {

	set<vector<int>> d;
	strToSet(s, d);

	bool changes = true;
	cnt += 2;

	while (changes) {
		cnt++;
		changes = false;

		for (auto it1 = d.begin(); it1 != d.end(); it1++) {
			auto it2 = it1;
			it2++;
			cnt += 2;
			
			for (it2; it2 != d.end(); it2++) {

				vector<int> a = *it1;
				vector<int> b = *it2;

				int comm = 0;
				int cont = 0;
				cnt += 4;
				for (int i = 0; i < a.size(); i++) {
					cnt += 7;
					if ((a[i] == 1 && b[i] == 2) || a[i] == 2 && b[i] == 1) {
						cnt++;
						cont++;
					} else if (a[i] == b[i]) {
						cnt += 2;
						comm++;
					} else {
						break;
					}
				}
				cnt += 4;
				if (cont == 1 && comm == a.size() - 1) {
					changes = true;

					it2 = d.erase(it2);
					it1 = d.erase(it1);

					vector<int> c;
					int nulls = 0;
					cnt += 6;
					for (int i = 0; i < a.size(); i++) {
						cnt += 4;
						c.push_back(a[i] == b[i] ? a[i] : 0);
						if (c[i] == 0) {
							nulls++;
							cnt++;
						}
					}

					if (nulls == c.size()) {
						cnt += 2;
						d.clear();
						d.insert(c);
						return false;
					}

					d.insert(c);
					cnt += 2;

					break;
				}
			}
			cnt++;
			if (changes) {
				break;
			}
		}
	}
	return true;
}

int main()
{
	srand(time(nullptr));

	set<vector<int>> d;

	for (int n = 10; n <= 200; n += 10) {
		cnt = 0;
		RES(KNF(n));
		cout << cnt << endl;
	}

	return 0;
}
