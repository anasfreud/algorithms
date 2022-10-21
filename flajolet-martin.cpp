#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// размер хэш-таблицы. Инициализируется в main
int N;
double L;

// генерирует случайную ссылку
string randomURL()
{
    string url;
    for (int i = 0; i < 4; i++) {
        url += to_string(rand() % 256);
        if (i < 3) {
            url += ".";
        }
    }
    return url;
}


// множество уникальных URL мощности M
struct URLs {
    string* urls;
    int M;

    void generate(int size)
    {
        M = size;
        urls = new string[M];
        for (int i = 0; i < M; i++) {
            urls[i] = randomURL();
        }
    }

    string getURL()
    {
        int index = rand() % M;
        return urls[index];
    }
};


// хэш-функция
int h(string url)
{
    int hash = 0;
    for (int i = 0; i < url.size(); i++) {
        hash += url[i];
    }
    return hash % N;
}


// ранг хэша
int rang(int x)
{
    if (x == 0) {
        return L;
    }

    int r = 0;
    while (x % 2 == 0) {
        x /= 2;
        r++;
    }
    return r;
}



int main()
{
    srand(time(nullptr));
    
    int M;
    cin >> M;
    N = M * 2;

    // генерация множества уникальных URL
    URLs u;
    u.generate(M);


    // N = 2^L. L - максимальная длина хэша в двоичной системе
    L = ceil(log2(N));

    // битовый массив, заполненный нулями
    bool* bitmap = new bool[L];
    for (int i = 0; i < L; i++) {
        bitmap[i] = 0;
    }

    // начало потока

    int s = 3; // мощность потока

    for (int i = 0; i < s; i++) {

        string obj = u.getURL();

        int index = rang(h(obj));
        bitmap[index] = 1;
    }

    int R = 0;
    while (R < L && bitmap[R] == 1) {
        R++;
    }

    double Me = pow(2, R) / 0.77351;
    cout << Me << endl;

    //посчитать me

	return 0;
}
