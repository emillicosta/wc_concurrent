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
	this_thread::sleep_for(seconds(pessoa.getTempo()));
	monitor->Remove(buffer, p);
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
		monitor->Insert(p, buffer);
		fila.push_back(thread(utilizar, monitor, buffer, p));
	}

	for(int i = 0; i < tamanhoFila; i++){
		fila[i].join();
	}
}

// void consumir(Monitor *monitor, vector<Pessoa> *buffer, Pessoa p){
	
// 		monitor->Remove(buffer);
// 		qtdUsada += 1;
// 		if(qtdUsada == tamanhoFila){
// 			break;
// 		}
// 	}
// }

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
    //consumidor = thread(consumir, monitor, &buffer);

    banheiro.join();
    //consumidor.join();
	
	return 0;
}