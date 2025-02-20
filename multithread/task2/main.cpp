#include <algorithm>
#include <random>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
/*
*/
std::once_flag flag;
void print_head(){
    std::cout<< "Количество аппаратных ядер - "
             << std::thread::hardware_concurrency()
             << std::endl<< "\t "<< 1000<< '\t'<< 10'000
             << '\t'<< 100'000<< '\t'<< 1'000'000<< std::endl;
    std::cout<< "1 потоков ";
}

void fill_vector( std::vector<int>& v){
    std::random_device rnd_device;
    std::mt19937 gen{ rnd_device()};
    std::uniform_int_distribution<int> dist{ -10, 10};
    auto randNum=[ &](){ return dist(gen);};
    std::generate( v.begin(), v.end(), randNum);
}

void sum_vector( std::vector <int>& v, const std::vector <int>& v2){
    std::transform( v.begin(), v.end(), v2.begin(), v.begin(), std::plus<int>());
}

void thread_vector( std::vector <int>& v, std::vector <int>& v2, short num){
    std::vector<std::thread> vt;
    auto start = std::chrono::steady_clock::now();
    for( size_t i{0}; i < num; i++){
        vt.push_back(std::thread([ &](){
            std::call_once(flag, print_head);
            sum_vector(v, v2);
            })
        );
    }
    auto end = std::chrono::steady_clock::now();
    for( auto& tr: vt){
        tr.join();
    }
    std::chrono::duration< double, std::milli> time= end- start;
    std::cout<< time.count()<< 's'<< '\t';
}
//////////////////////////////////
int main( int argc, char** argv){
    bool b{ false};
    for( short i{1}; i<= 16; i*=2){
        if(b){std::cout<< i<< " потоков ";}
        for(int j{ 1000}; j< 1000001; j*=10){
            std::vector <int> v1(j);
            std::vector <int> v2(j);
            fill_vector(v1);
            fill_vector(v2);
            thread_vector(v1, v2, i);
        }
        std::cout<< std::endl;
        b= true;
    }
    return 0;
}
