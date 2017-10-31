#ifndef MONITOR_H
#define MONITOR_H

#include <mutex>
#include <condition_variable>
#include <vector>
#include <stdio.h>
#include "pessoa.h"

using namespace std;

class Monitor{

public:
    Monitor(int);
    ~Monitor();
    void Insert(Pessoa, vector<Pessoa>*);
    void Remove(vector<Pessoa>*);
    char getSex();

private:
    mutex mtx;
    condition_variable full;
    condition_variable empty;
    int bufferSize;
    int count;
    char sex;
};

#endif // MONITOR_H
