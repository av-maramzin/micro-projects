#include <cstdlib>
#include <ctime>
#include <cmath>

#include <chrono>
#include <iostream>
using namespace std;

auto conduct_experiment(void(*func)(void)) {
    auto start_time = chrono::high_resolution_clock::now();
    func();
    auto end_time = chrono::high_resolution_clock::now();
    return (end_time - start_time);
}

// experiments parameters
const unsigned int size = 100000;
const unsigned int range = 100;

inline int random(int range) {
    return rand() % range;
}

// arrays to conduct experiments on
static int a[size];
static int b[size];
static int c[size];

void array_min();
void array_sum();

int main() {

    // initialize arrays
    std::srand(std::time(0));

    for (unsigned int i = 0; i < size; i++) {
        a[i] = random(range);     
        b[i] = random(range);     
        c[i] = random(range);     
    }

    // run experiments
    cout << "array sum: ";
    cout << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(array_sum) ).count()/1000000 << " seconds.\n";

    cout << "array min: ";
    cout << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(array_min) ).count()/1000000 << " seconds.\n";

    return 0;
}

void array_sum() {
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum = 0;

    for (unsigned int i = 0; i < size; i++) {
        sum1 += a[i];     
    }

    for (unsigned int i = 0; i < size; i++) {
        sum2 += b[i];     
    }

    for (unsigned int i = 0; i < size; i++) {
        sum3 += c[i];     
    }

    sum = sum1 + sum2 + sum3;
    cout << "array sum: " << sum << endl;
}

void array_min() {
    int min1 = 0;
    int min2 = 0;
    int min3 = 0;
    int min = 0;

    min1 = a[0];
    for (unsigned int i = 0; i < size; i++) {
        if (a[i] < min1) min1 = a[i];
    }
    
    min2 = a[0];
    for (unsigned int i = 0; i < size; i++) {
        if (a[i] < min2) min2 = a[i];
    }
    
    min3 = a[0];
    for (unsigned int i = 0; i < size; i++) {
        if (a[i] < min3) min3 = a[i];
    }

    min = (min1 < min2) ? min1 : min2;
    min = (min < min3) ? min : min3;
    
    cout << "array min: " << min << endl;
}
