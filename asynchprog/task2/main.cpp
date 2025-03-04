#include <algorithm>
#include <execution>
#include <random>
#include <vector>
#include <future>
#include <iostream>
using namespace std;
/*
*/
template<typename Iter,typename T>
void paraForEach(Iter begin, Iter end, T t){
    size_t size= distance(t.begin(), t.end());
    if(!size) return;
    if(size==1) return;
    Iter middle= begin;
    advance(middle, size/2);
    std::future<void> ft = std::async(&paraForEach<Iter, T>,begin,middle,t);
    try{
        auto half = async(paraForEach< Iter, T>, begin, middle, std::ref(t));
        for_each( std::execution::par, middle, end, [&](int& i){ cout<< ++i<< ' ';});
    } catch(...){
        ft.wait();
        cerr<< __func__<< endl<< flush;
        throw;
    }
    ft.get();
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
    std::vector <int> vec(4);
    fillVector(vec);

    cout<< "before v1: ";
    for( auto& v: vec) cout<< v<< ' ';
    cout<< endl;

    cout<< "after  v1: ";
    paraForEach(vec.begin(), vec.end(), vec);
    return 0;
}
