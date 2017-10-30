#include "../includes/monitor.h"
#include "../includes/pessoa.h"

#include <vector>

Monitor::Monitor(int bufferSize){
    this->bufferSize = bufferSize;
    this->count = 0;
}

Monitor::~Monitor(){
}

void Monitor::Insert(Pessoa item, std::vector<Pessoa> *buffer){
    std::unique_lock<std::mutex> lck(this->mtx);

    if(this->count == 0){
        this->sex = item.getSexo();
        buffer->push_back(item);
        this->count++;
        std::cout << " " << item.getSexo() << "     " << item.getId() << "      " << this->count << "           " << item.getTempo() << "s        Entrou" << std::endl;

        if(this->count == 1){
            this->empty.notify_all();
        }
        return;
    }

    if(this->count == this->bufferSize || this->sex != item.getSexo()){
        this->full.wait(lck);
    }

    buffer->push_back(item);
    this->count++;
    std::cout << " " << item.getSexo() << "     " << item.getId() << "      " << this->count << "           " << item.getTempo() << "s        Entrou" << std::endl;

    if(this->count == 1){
        this->empty.notify_all();
    }
}

void Monitor::Remove(std::vector<Pessoa> *buffer, Pessoa p){
    std::unique_lock<std::mutex> lck(this->mtx);
    if(this->count == 0){
        this->empty.wait(lck);
    }

    Pessoa item = buffer->at(0);
    buffer->erase(buffer->begin());
    this->count--;
    std::cout << " " << item.getSexo() << "     " << item.getId() << "      " << this->count << "           " << item.getTempo() << "s        SAIU" << std::endl;

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
