#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include <tuple>
/*
*/
std::mutex m;

void multiBar(short i){
    std::vector<std::tuple<const char*, int>> cols{
        {"id", 2},
        {"Progress Bar", 16},
        {"Time", 18}
    };
    const int bar_size = 16;
    int k = 0;
    int rowNum = i + 2;
    int colNum = std::get<int>(cols.at(0)) + 2;

    m.lock();
    if (i == 0){
        for (std::tuple<const char*, int> col : cols){
            std::cout<< std::get<const char*>(col)<< '\t';
        }
    }
    std::cout << "\033[" << std::this_thread::get_id() << ";0H" << i;
    m.unlock();

    auto start = std::chrono::steady_clock::now();
    for (int x = 0; x < bar_size; ++x){
        int col_x = colNum + x;
        k = rand() % 25+ i;
        std::this_thread::sleep_for(std::chrono::milliseconds(k * 100));
        std::cout << "\033[" << rowNum<< ';' << col_x;
        if (x == k)
            std::cout<< "H\033[41m "<< std::flush;
        else
            std::cout<< "H\033[42m "<< std::flush;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    colNum += std::get<int>(cols.at(2));

    std::lock_guard<std::mutex> lock_trh_m(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(k+ 500));
    std::cout << "\033[49m\033[" << rowNum << ';' << colNum << 'H'
        << time.count() << 's';
    std::cout<< std::endl<< std::flush;
}
///////////////////////////////////////
int main(int argc, const char **argv){
    std::system("cls");
    //    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    //    std::cout << "\033[1;32m Hello World! \033[0m" << std::endl;
    try {
        int n = 4;
        std::thread* thr_arr = new std::thread[n];
        for (int i = 0; i < n; ++i)
        {
            thr_arr[i] = std::thread(multiBar, i);
        }
        for (int i = 0; i < n; ++i){
            if (thr_arr[i].joinable())
                thr_arr[i].join();
        }
        delete[] thr_arr;
        thr_arr= nullptr;
        std::cout << std::endl<< std::endl<< std::endl;
    } catch (...){
        std::cerr<< std::endl;
        std::cerr<< "What is this?: "<< __func__<< std::endl;
    }
    return 0;
}
