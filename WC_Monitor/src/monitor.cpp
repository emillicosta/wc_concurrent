#include "../includes/monitor.h"
#include "../includes/pessoa.h"

#include <vector>

Monitor::Monitor(int bufferSize){
    this->bufferSize = bufferSize;
    this->count = 0;
}

Monitor::~Monitor(){
}

char Monitor::getSex(){
    return this->sex;
}

void Monitor::Insert(Pessoa item, vector<Pessoa> *buffer){
    unique_lock<mutex> lck(this->mtx);

    if(this->count == 0){
        this->sex = item.getSexo();
        buffer->push_back(item);
        this->count++;
        printf(" %c     %i      %i           %is        %s\n", item.getSexo(), item.getId(), this->count, item.getTempo(), " Entrou");
        //cout << " " << item.getSexo() << "     " << item.getId() << "      " << this->count << "           " << item.getTempo() << "s        Entrou" << endl;

        if(this->count == 1){
            this->empty.notify_all();
        }
        return;
    }

    if(this->count == this->bufferSize){
        this->full.wait(lck);
    }

    buffer->push_back(item);
    this->count++;
    printf(" %c     %i      %i           %is        %s\n", item.getSexo(), item.getId(), this->count, item.getTempo(), " Entrou");
    //cout << " " << item.getSexo() << "     " << item.getId() << "      " << this->count << "           " << item.getTempo() << "s        Entrou" << endl;

    if(this->count == 1){
        this->empty.notify_all();
    }
}

void Monitor::Remove(vector<Pessoa> *buffer){
    unique_lock<mutex> lck(this->mtx);
    if(this->count == 0){
        this->empty.wait(lck);
    }

    Pessoa item = buffer->at(0);
    buffer->erase(buffer->begin());
    this->count--;

    if(this->count == (this->bufferSize - 1)){
        this->full.notify_all();
    }

    if(this->count == 0){
        if(this->sex == 'H'){
            this->sex = 'M';
        }else{
            this->sex = 'H';
        }
        this->full.notify_all();
    }
}
