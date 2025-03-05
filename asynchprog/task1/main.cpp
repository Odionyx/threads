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
    for (auto it = vec.begin(); it < vec.end()-1; ++it){
        promise<typename vector<T>::iterator> pr;
        auto future = pr.get_future();
        auto minIt = it;

        auto res= async([&](){
            for (auto it2 = it + 1; it2 <vec.end(); ++it2)
                if ((*it2) <(*minIt)) minIt = it2;
            pr.set_value(minIt);
        });
        future.get();
        if (minIt != it)
            swap((*it), *(minIt));
    }
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

    cout<< "after  v1: ";
    for( auto& v: vec) cout<< v<< ' ';
    cout<< endl;
    return 0;
}
