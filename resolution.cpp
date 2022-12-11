#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <set>

using namespace std;

#define MAX_DIS 10
#define BASE 3

string toTernary(int x) {
    string s;
    while (x) {
        s += to_string(x % BASE);
        x /= BASE;
    }
    return s;
}

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

    void generate() {
        d[0] = true;
        for (int i = 1; i < maxDisCnt; i++) {
            d[i] = rand() % 2;
            
        }
    }

    string getString() {

        string result = "";
        int dis = 0;
        for (int i = 1; i < maxDisCnt; i++) {

            if (d[i]) {

                result += " (";
                dis++;

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
                            result += " | ";
                        }
                    }

                    x /= BASE;
                    cnt--;
                }
                result += ") & \n";
                
            }
        }
        result += "()";
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

        for (int i = 0; i < maxDisCnt; i++) {
            if (d[i]) {
                cout << i << " " << toTernary(i) << " ";
                printRow(a[i], varCnt);
            }
        }
        cout << endl;

        
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
                        printRow(a[i], varCnt);
                        printRow(a[j], varCnt);
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

                        cout << "result ";
                        printRow(b, varCnt);
                        cout << endl;

                        int p = fromTernary(b, varCnt);
                        d[i] = false;
                        d[j] = false;
                        d[p] = true;

                      
                        changes++;
                        break;
                    }
                }
            }
        }
    }
};



int main()
{
    srand(time(nullptr));

    Formula f{ 2 };
    cout << f.getString() << endl;
    f.resolution();
    cout << endl << f.getString() << endl;

    return 0;
}
