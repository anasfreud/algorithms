#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_REORDERS = 10;

bool** G1;
bool** G2;
int n;
unsigned long long cnt;

// вывод графа
void print(bool** g, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << g[i][j] << ' ';
        }
        cout << endl;
    }
}


// изоморфный граф на основе G1
void make_iso()
{
    // переставляем одновременно случайные строки и столбцы в G2, чтобы получить граф, изоморфный G1


    int cnt = rand() % MAX_REORDERS;
    for (int k = 0; k < cnt; k++)
    {
        int v1 = rand() % n;
        int v2 = rand() % n;


        // меняются местами строки
        for (int i = 0; i < n; i++)
        {
            swap(G2[v1][i], G2[v2][i]);
        }

        // меняются местами столбцы
        for (int i = 0; i < n; i++)
        {
            swap(G2[i][v1], G2[i][v2]);
        }
    }
}


// проверка двух графов на изоморфизм
bool iso()
{
    int* p = new int[n];
    for (int i = 0; i < n; i++) {
        p[i] = i;
        cnt++;
    }


    int* d1 = new int[n];
    int* d2 = new int[n];

    for (int i = 0; i < n; i++) {
        cnt += 2;
        d1[i] = d2[i] = 0;
        for (int j = 0; j < n; j++) {
            d1[i] += (G1[i][j] == 1);
            d2[i] += (G2[i][j] == 1);
            cnt += 6;
        }
    }

    do {
        bool trigger = true;
        cnt++;
        for (int i = 0; i < n && trigger; i++)
        {
            cnt++;
            if (d1[i] != d2[p[i]]) {
                trigger = false;
                cnt++;
                break;
            }
            for (int j = 0; j < n; j++)
            {
                cnt++;
                if (G1[i][j] != G2[p[i]][p[j]]) {
                    cnt++;
                    trigger = false;
                    break;
                }
            }
        }
        cnt++;
        if (trigger) {
            return true;
        }

        cnt++;
    } while (next_permutation(p, p + n));

    return false;
}

int main()
{
    srand(time(nullptr));

    cin >> n;
    G1 = new bool* [n];
    G2 = new bool* [n];

    for (int i = 0; i < n; i++)
    {
        G1[i] = new bool[n];
        G2[i] = new bool[n];
    }

    // заполнение матриц смежности графов G1 и G2 случайными одинаковыми значениями

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                G1[i][i] = G2[i][i] = 0;
            }
            else
            {
                //G1[i][j] = G2[i][j] = G1[j][i] = G2[j][i] = rand() % 2;
                G1[i][j] = G1[j][i] = rand() % 2;
                G2[i][j] = G2[j][i] = rand() % 2;
            }
        }
    }

    //make_iso();

    /*print(G1, n);
    cout << endl;
    print(G2, n);*/

    cout << endl << iso() << endl;
    cout << cnt << endl;

    return 0;
}
