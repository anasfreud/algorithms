#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX_DIS 10
#define BASE 3

int fromTernary(int* a, int n) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x += a[i] * pow(3, i);
    }
    return x;
}

void printRow(int* a, int n) {
    cout << "row: ";
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    cout << endl;
}


struct Formula {
    int maxDisCnt = 0;
    int varCnt = 0;

    bool* d;

    Formula(int n) {
        varCnt = n;
        maxDisCnt = pow(3, n);
        d = new bool[maxDisCnt];
        generate();
    }

    Formula(string s) {
        fromString(s);
    }

    void generate() {
        d[0] = true;
        for (int i = 1; i < maxDisCnt; i++) {
            d[i] = rand() % 2;
        }
    }

    string getString() {

        string result = "";

        for (int i = 1; i < maxDisCnt; i++) {
            if (d[i]) {
                result += "(";

                int x = i;
                int cnt = varCnt;
                
                while (x) {
                    int n = x % BASE;

                    if (n) {
                        if (n == 1) {
                            result += "-";
                        }
                        result += "x" + to_string(cnt);
                        if (x / BASE != 0) {
                            result += "|";
                        }
                    }

                    x /= BASE;
                    cnt--;
                }
                result += ")&";
                
            }
        }
        result.erase(result.length() - 1, 1);
        return result;
    }

    void resolution() {

        int** a;
        a = new int* [maxDisCnt];

        for (int i = 0; i < maxDisCnt; i++) {
            a[i] = new int[varCnt];

            int x = i;
            for (int j = 0; j < varCnt; j++) {
                a[i][j] = x % BASE;
                x /= BASE;
            }
        }

        int changes = 1;

        while (changes != 0) {

            changes = 0;

            for (int i = 0; i < maxDisCnt; i++) {
                if (!d[i]) {
                    continue;
                }

                for (int j = i + 1; j < maxDisCnt; j++) {
                    if (!d[j]) {
                        continue;
                    }

                    int cont = 0;
                    for (int q = 0; q < varCnt; q++) {
                        if ((a[i][q] == 1 && a[j][q] == 2) || (a[i][q] == 2 && a[j][q] == 1)) {
                            cont++;
                        }
                    }

                    if (cont > 0) {
                        int* b = new int[varCnt];
                    
                        for (int q = 0; q < varCnt; q++) {
                            if (a[i][q] == 0 || a[j][q] == 0) {
                                b[q] = a[i][q] + a[j][q];
                            }
                            else if (a[i][q] == a[j][q]) {
                                b[q] = a[i][q];
                            }
                            else {
                                b[q] = 0;
                            }
                        }

                        d[i] = false;
                        d[j] = false;
                        d[fromTernary(b, varCnt)] = true;

                      
                        changes++;
                        break;
                    }
                }
            }
        }
    }


    void fromString(string s) 
    {
        int m = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'x') {
                int p = 0;
                i++;
                while (isdigit(s[i])) {
                    p = p * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                m = max(m, p);
            }
        }

        varCnt = m;
        maxDisCnt = pow(3, m);

        d = new bool[maxDisCnt];
        memset(d, 0, maxDisCnt);

        int* b = new int[varCnt];
        memset(b, 0, varCnt * 4);

        bool t = false;

        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            switch (c) {
            case '&':
                d[fromTernary(b, varCnt)] = true;
                memset(b, 0, varCnt * 4);
                break;
            case '-':
                t = true;
                i++;
            case 'x':
                int p = 0;
                i++;
                while (isdigit(s[i])) {
                    p = p * 10 + (s[i] - '0');
                    i++;
                }
                i--;
                b[p - 1] = t ? 1 : 2;
                t = false;
                break;
            }
        }

        d[fromTernary(b, varCnt)] = true;

        //for (int i = 0; i < maxDisCnt; i++) {
        //    cout << d[i] << endl;
        //}
    }
};



int main()
{
    srand(time(nullptr));

    string s;
    cin >> s;

    Formula g{ s };
    string gStr = g.getString();
    cout << gStr << endl;
    return 0;
}
