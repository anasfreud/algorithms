#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <fstream>
#include <algorithm>
using namespace std;

const int N = 2000;


int h(string x)
{
    int hash = 0;
    for (int i = 0; i < x.size(); i++) {
        hash += x[i];
    }
    return hash % N;
}

string randomObj() 
{
    int length = rand() % 16 + 5;
    string s;
    for (int i = 0; i < length; i++) {
        s += rand() % 128;
    }
    return s;

}


struct HashTable
{
    string table[N];
    int objCount = 0;
    double alpha;

    int randoms[N];

    int addObj(string obj)
    {
        if (alpha < 1) {
            int collisions = 0;

            objCount++;

            int hash = h(obj);
            randomRehash(hash, collisions);
            table[hash] = obj;

            alpha = (double)objCount / N;
            return collisions;

        } else {
            return 0;
        }
    }

    void linearRehash(int& hash, int& collisions)
    {
        while (table[hash] != "") {
            collisions++;
            hash = (hash + 1) % N;
        }
    }

    void randomRehash(int& hash, int& collisions)
    {
        int j = 0;
        while (table[hash] != "") {
            collisions++;
            hash = (hash + randoms[j]) % N;
            j++;
        }
    }

    void setRandoms()
    {
        for (int i = 0; i < N; i++) {
            randoms[i] = i + 1;
        }

        unsigned seed = time(nullptr);
        shuffle(randoms, randoms + N, default_random_engine(seed));    
    }
};



int main()
{
    ofstream out("output.txt");

    srand(time(nullptr));

    for (double alpha = 0.05; alpha <= 0.95; alpha += 0.05) {
        int sum = 0;
        for (int k = 0; k < 1000; k++) {
            HashTable table;
            table.setRandoms();
            while (table.alpha < alpha) {
                sum += table.addObj(randomObj());
            }
        }
        out << (double)sum / 1000 << endl;
    }

    
    return 0;
}
