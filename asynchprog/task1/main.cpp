#include <algorithm>
#include <random>
#include <vector>
#include <future>
#include <iostream>
using namespace std;
/*
*/
template<typename T>
void selectionSort(vector<T>& vec){
    auto future =  async([&](){
        for (auto it = vec.begin(); it < vec.end()-1; ++it){
            auto minIt = it;
            for (auto it2 = it + 1; it2 <vec.end(); ++it2)
                if ((*it2) <(*minIt)) minIt = it2;
            if (minIt != it)
                swap((*it), *(minIt));
        }
    });
}

void fillVector( std::vector<int>& v){
    std::random_device rnd_device;
    std::mt19937 gen{ rnd_device()};
    std::uniform_int_distribution<int> dist{ -10, 10};
    auto randNum=[ &](){ return dist(gen);};
    std::generate( v.begin(), v.end(), randNum);
}
//////////////////////////////////
int main( int argc, char** argv){
    cout << "Hello World!" << endl;
    std::vector <int> vec(20);
    fillVector(vec);

    cout<< "before v1: ";
    for( auto& v: vec) cout<< v<< ' ';
    cout<< endl;

    selectionSort(vec);

    promise<vector<int>> pr;
    pr.set_value(vec);
    auto future = pr.get_future();

    cout<< "after  v1: ";
    for( auto& v: future.get()) cout<< v<< ' ';
    cout<< endl;

    return 0;
}
