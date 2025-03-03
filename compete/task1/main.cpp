#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
/*
*/
void is_customer(std::atomic< short>& cnt){
    while( cnt.load(std::memory_order_relaxed)< 10){
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 1000 });
        cnt.store(++cnt, std::memory_order_seq_cst);
        std::cout<< "c> "<< cnt.load()<< std::endl;
    }
}

void is_operator(std::atomic< short>& cnt){
    while (cnt.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 2000 });
        cnt.store(--cnt, std::memory_order_seq_cst);
        std::cout<< "o< "<< cnt.load()<< std::endl;
    }
}

int main( int argc, char** argv){
    std::cout << "Hello!" << std::endl;
    std::atomic< short> cnt;
    std::thread t1( is_customer, std::ref(cnt));
    std::this_thread::sleep_for(std::chrono::duration<double, std::milli> { 1000 });
    std::thread t2( is_operator, std::ref(cnt));
    t1.join();
    t2.join();
    return 0;
}
