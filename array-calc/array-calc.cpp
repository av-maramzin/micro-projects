#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <cstdint>

#include <chrono>
#include <iostream>
using namespace std;

// experiments parameters
const unsigned int size = 100000;
const unsigned int range = 100;

inline int random(int range) {
    return rand() % range;
}

template <typename T>
class Function 
{
    public:
        Function() {}
        virtual T operator()() const = 0;
};

template <typename T>
class Array_Sum : public Function<T>
{
    public:
        Array_Sum(T* array, uint64_t size)
            : array(array), array_size(size) {}

        T operator()() const
        {
            T sum = 0;
            for (uint64_t i = 0; i < array_size; i++) 
            {
                sum += array[i];                
            }
            return sum;
        }

    private:
        T* array;
        uint64_t array_size;
};

template <typename T>
class Array_Min : public Function<T>
{
    public:
        Array_Min(T* array, uint64_t size)
            : array(array), array_size(size) {}

        T operator()() const
        {
            T min = array[0];
            for (uint64_t i = 1; i < array_size; i++) 
            {
                if (array[i] < min) 
                {
                    min = array[i];
                }
            }
            return min;
        }

    private:
        T* array;
        uint64_t array_size;
};

template <typename T>
auto conduct_experiment(Function<T>& func) {
    auto start_time = chrono::high_resolution_clock::now();
    func();
    auto end_time = chrono::high_resolution_clock::now();
    return (end_time - start_time);
}

// arrays to conduct experiments on
static uint64_t a[size];
static uint64_t b[size];

int main() {

    // initialize arrays
    std::srand(std::time(0));

    for (unsigned int i = 0; i < size; i++) {
        a[i] = random(range);     
        b[i] = random(range);     
    }

    Array_Sum<uint64_t> a_sum{a, size};
    Array_Sum<uint64_t> b_sum{b, size};

    Array_Min<uint64_t> a_min{a, size};
    Array_Min<uint64_t> b_min{b, size};

    // run experiments
    cout << "array sum: ";
    cout << "a: " << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(a_sum) ).count()/1000000 << " seconds.\n";
    cout << "b: " << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(b_sum) ).count()/1000000 << " seconds.\n";

    cout << "array min: ";
    cout << "a: " << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(a_min) ).count()/1000000 << " seconds.\n";
    cout << "b: " << (double)chrono::duration_cast<chrono::microseconds>( conduct_experiment(b_min) ).count()/1000000 << " seconds.\n";

    return 0;
}
