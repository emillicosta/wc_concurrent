#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>
#include "pessoa.h"

class Monitor{

public:
    Monitor(int);
    ~Monitor();
    void Insert(Pessoa, std::vector<Pessoa>*);
    void Remove(std::vector<Pessoa>*);

private:
    std::mutex mtx;
    std::condition_variable full;
    std::condition_variable empty;
    int bufferSize;
    int count;
    char sex;
};

#endif // MONITOR_H
