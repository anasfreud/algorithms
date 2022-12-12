#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

#define BASE 3

int fromTernary(int* a, int n) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x += a[i] * pow(3, n - i - 1);
    }
    return x;
}

struct Formula {
    int maxDisCnt = 0;
    int varCnt = 0;

    bool* d;
    int** table;

    void generate(string s) {
        makeTable();
        fromString(s);
    }

    void generate(int n) {
        varCnt = n;
        maxDisCnt = pow(3, n);

        makeTable();

        d = new bool[maxDisCnt];
        d[0] = true;
        for (int i = 1; i < maxDisCnt; i++) {
            d[i] = rand() % 2;
        }
    }

    void makeTable() {
        table = new int* [maxDisCnt];
        for (int i = 0; i < maxDisCnt; i++) {
            table[i] = new int[varCnt];
            int x = i;
            for (int j = varCnt - 1; j >= 0; j--) {
                table[i][j] = x % BASE;
                x /= BASE;
            }
        }
    }

    string getString() {

        int disCnt = 0;
        for (int i = 1; i < maxDisCnt; i++) {
            if (d[i]) {
                disCnt++;
            }
        }
        if (!disCnt) {
            return "()";
        }

        string result = "";
        makeTable();
        for (int i = 1; i < maxDisCnt; i++) {
            if (d[i]) {
                result += "(";

                for (int q = 0; q < varCnt; q++) {
                    if (table[i][q] == 1) {
                        result += "-x" + to_string(q + 1) + "|";

                    } else if (table[i][q] == 2) {
                        result += "x" + to_string(q + 1) + "|";
                    }
                }
                result.erase(result.length() - 1, 1);
                result += ")&";
            }
        }
        result.erase(result.length() - 1, 1);
        return result;
    }

    void resolution() {

        makeTable();
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
                    int comm = 0;

                    for (int q = 0; q < varCnt; q++) {
                        if ((table[i][q] == 1 && table[j][q] == 2) || (table[i][q] == 2 && table[j][q] == 1)) {
                            cont++;
                        } else if (table[i][q] == table[j][q]) {
                            comm++;
                        } else {
                            break;
                        }
                    }

                    if (cont == 1 && comm == varCnt - 1) {
                        int* b = new int[varCnt];

                        for (int q = 0; q < varCnt; q++) {
                            if (table[i][q] == table[j][q]) {
                                b[q] = table[i][q];
                            }
                            else {
                                b[q] = 0;
                            }
                        }

                        d[i] = false;
                        d[j] = false;
                        int p = fromTernary(b, varCnt);

                        if (p == 0) {
                            memset(d, 0, maxDisCnt);
                            return;
                        }

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
    }
};



int main()
{
    srand(time(nullptr));
    
    Formula f;
    f.generate(2);
    cout << f.getString() << endl;
    f.resolution();
    cout << f.getString() << endl;

    return 0;
}
