#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

// размер хэш-таблицы. Инициализируется в main
int N;
double L;

int valuesM[] = { 10, 20, 30, 40, 50, 100, 500, 1000 };
int valuesS[] = { 2, 5, 10, 100 };

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
    string* urls = nullptr;
    int M = 0;

    void generate(int size)
    {
        M = size;

        if (urls != nullptr) {
            delete[] urls;
        }

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

    URLs u;

    for (int i = 0; i < 8; i++) {
        int M = valuesM[i];
        N = M * 2;
        
        // N = 2^L. L - максимальная длина хэша в двоичной системе
        L = ceil(log2(N));
    
        // генерация множества уникальных URL
        u.generate(M);

        // битовый массив, заполненный нулями
        bool* bitmap = new bool[L];


        for (int j = 0; j < 4; j++) {
            int s = M * valuesS[j]; // мощность потока

            double sumMe = 0;
            double sumE = 0;
            double sumD = 0;

            for (int k = 0; k < 1000; k++) {

                for (int i = 0; i < L; i++) {
                    bitmap[i] = 0;
                }

                // начало потока

                for (int w = 0; w < s; w++) {

                    string obj = u.getURL();

                    int index = rang(h(obj));
                    bitmap[index] = 1;
                }

                int R = 0;
                while (R < L && bitmap[R] == 1) {
                    R++;
                }

                double Me = pow(2, R) / 0.77351;
                double E = M - Me;
                double D = E / M;

                sumMe += Me;
                sumE += E;
                sumD += D;

            }

            sumMe /= 1000;
            sumE /= 1000;
            sumD /= 1000;

            cout << "m = " << M << " s = " << s << " : " << sumMe << ' ' << sumE << ' ' << sumD << endl;
        }
    }
  
	return 0;
}
