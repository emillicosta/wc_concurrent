#include <stdio.h>
#include <thread>
#include <vector>
#include <cstdlib>
#include <chrono>

// #include <iostream>
// #include <unistd.h>
// #include <cstdlib>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <chrono>
// #include <thread>
// #include <stdlib.h>
// #include <time.h>

#include "../includes/pessoa.h"
#include "monitor.cpp"

using namespace std::chrono;
using namespace std;

int capacidade;
int tamanhoFila;

void utilizar(Monitor *monitor, vector<Pessoa> *buffer, Pessoa p){
	while(monitor->getSex() != p.getSexo() && buffer->size() > 0){
        
    }
	monitor->Insert(p, buffer);
	this_thread::sleep_for(seconds(p.getTempo()));
	monitor->Remove(buffer);
	printf(" %c     %i      %lu           %is        %s\n", p.getSexo(), p.getId(), buffer->size(), p.getTempo(), " Saiu");
	//consumir(monitor, buffer, p);
}

void entrar(Monitor *monitor, vector<Pessoa> *buffer){
	int sexoInt, temp;
	vector<thread> pessoas;
	srand(time(NULL));

	for(int i = 1; i <= tamanhoFila; i++){
		sexoInt = rand() % 2;
		temp = (rand() % 5) + 1;
		char sexo;		

		if(sexoInt == 0){
			sexo = 'H';
		}else{
			sexo = 'M';
		}

		Pessoa p(sexo, i, temp);
		this_thread::sleep_for(milliseconds(50));
		pessoas.push_back(thread(utilizar, monitor, buffer, p));
	}

	for(int i = 0; i < tamanhoFila; i++){
		pessoas[i].join();
	}
}

int main(int argc, const char * argv[]){	
	printf("Qual a capacidade do banheiro? ");
	scanf("%i", &capacidade);
	printf("Quantas pessoas na fila? ");
	scanf("%i", &tamanhoFila);

	printf("Sexo | Id | Em uso | Tempo de uso |   Status\n");
	printf("==================================================\n");

	vector<Pessoa> buffer;
    thread banheiro;
    Monitor *monitor;
    monitor = new Monitor(capacidade);

    banheiro = thread(entrar, monitor, &buffer);

    banheiro.join();
	
	return 0;
}