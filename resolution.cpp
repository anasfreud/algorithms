#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <set>

using namespace std;

#define MAX_DIS 10
#define BASE 3

int toTernary(int x) {
    int n = 0;

    while (x) {
        n = n * 10 + (x % BASE);
        x /= BASE;
    }

    return n;
}


struct Formula {
    int maxDisCnt = 0;
    int varCnt = 0;
    int disCnt = 0;
    bool* d;


    Formula(int n) {
        varCnt = n;
        maxDisCnt = pow(3, n);
        d = new bool[maxDisCnt];
        generate();
    }

    void generate() {
        for (int i = 1; i < maxDisCnt; i++) {
            d[i] = rand() % 2;
            if (d[i]) {
                disCnt++;
            }
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
                result += ")";
                if (dis != disCnt) {
                    result += " & \n";
                }
            }
        }
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


        // x1 & -x1
        // x1 | x2 & -x1 | x3 =
        // убираю диз -
        // добвавляю новый

        // 2 1
        // 1 2


        //0 0 - 0
        //0 1 - 1
        //0 2 - 2
        //1 0 - 1
        //1 1 - 1
        //1 2 - 0
        //2 0 - 2
        //2 1 - 0
        //2 2 - 2
        

        for (int i = 0; i < maxDisCnt; i++) {
            for (int k = 0; k < maxDisCnt; k++) {

                int* b = new int[varCnt];

                for (int j = 0; j < varCnt; j++) {
                    if (a[i][j] == 0 || a[k][j] == 0) {
                        b[j] = a[i][j] + a[k][j];
                    } else if (a[i][j] == a[k][j]) {
                        b[i] = a[i][j];
                    } else {
                        b[i] = 0;
                    }

                }

                d[i] = false;
                d[k] = false;
                int p = 0;
                for (int j = 0; j < varCnt; j++) {
                    p = p * BASE + b[j];
                }
                d[p] = true;
                disCnt--;
            }




            /*for (int j = 0; j < varCnt; j++) {
                for (int k = 0; k < maxDisCnt; k++) {
                    if (abs(a[i][j] - a[k][j]) == 1) {
                        d[i] = false;
                        d[k] = false;
                        int* b = new int[varCnt];
                        for (int q = 0; q < maxDisCnt; q++) {

                        }



                    }
                }
            }*/
        }






        for (int i = 0; i < maxDisCnt; i++) {
            for (int j = 0; j < varCnt; j++) {
                cout << a[i][j];
            }
            cout << endl;
        }

    }
};

 

int main()
{
    srand(time(nullptr));

    Formula f{ 3 };
    cout << f.getString();
    //f.resolution();

	return 0;
}
