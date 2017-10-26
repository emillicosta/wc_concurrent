#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <stdlib.h>   
#include <time.h>  

//#include "../includes/semaforo.h"
#include "../includes/pessoa.h"
#include "semaforo.cpp"

using namespace std::chrono;
using namespace std;

int capacidade;
int capacidadeAtual;
int tamanhoFila;
char sexo_usado;
Semaforo *semaforo;
Semaforo *semBin;

void utilizar(Pessoa pessoa){
	semaforo->P();
	printf(" %c     %i          %i               %is        %s\n", pessoa.getSexo(), pessoa.getId(), (capacidade - semaforo->getContador()), pessoa.getTempo(), " Entrou");
	this_thread::sleep_for(seconds(pessoa.getTempo()));
	printf(" %c     %i          %i               %is        %s\n", pessoa.getSexo(), pessoa.getId(), (capacidade - semaforo->getContador()), pessoa.getTempo(), " Saiu");
	semaforo->V();
}

void entrar(Pessoa pessoa){
	while(true){
		if(capacidade == capacidadeAtual){
			semBin->P();
			sexo_usado = pessoa.getSexo();
			capacidadeAtual -= 1;
			semBin->V();
			utilizar(pessoa);
			capacidadeAtual += 1;
			return;
		}else{
			semBin->V();
			if(sexo_usado == pessoa.getSexo()){
				capacidadeAtual -= 1;
				utilizar(pessoa);
				capacidadeAtual += 1;
				return;
			}
		}
	}

	
	// if(semaforo->getContador() == capacidade){
	// 	semBin->P();
	// 	sexo_usado = s;
	// 	printf(" %c     %i          %i                 %is        %s\n", s, id, semaforo->getContador(), temp, " Entrou");
	// 	utilizar(s, id, temp);
	// 	semBin->V();
	// }else{
	// 	if(sexo_usado == s){
	// 		printf(" %c     %i          %i                 %is        %s\n", s, id, semaforo->getContador(), temp, " Entrou");
	// 		utilizar(s, id, temp);
	// 	}
	// }

	
	//printf(" %c     %i          %i                 %is        %s\n", s, id, semaforo->getContador(), temp, " Entrou");
	// mutex->V();
	// if(sexo_usado == s && semaforo->getContador() > 0){
	// 	semaforo->P();
	// 	printf(" %c     %i          %i                 %is        %s\n", s, id, semaforo->getContador(), temp, " Entrou");
	// 	flag = false;
	// }
}

int main(int argc, const char * argv[]){
	
	int sexoInt, temp;
	printf("Qual a capacidade do banheiro? ");
	scanf("%i", &capacidade);
	printf("Quantas pessoas na fila? ");
	scanf("%i", &tamanhoFila);

	capacidadeAtual = capacidade;

	semaforo = new Semaforo(1230,capacidade,IPC_CREAT|0600);
	semBin = new Semaforo(1231,1,IPC_CREAT|0600);

	srand(time(NULL));

	vector<Pessoa> pessoas;
	vector<thread> fila;

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
		pessoas.push_back(p);
	}

	printf("Sexo | Id | Qtd de pessoas | Tempo de uso |  Status\n");
	printf("======================================================\n");

	for(int i = 0; i < tamanhoFila; i++){
		printf(" %c     %i          %i               %is        %s\n", pessoas[i].getSexo(), pessoas[i].getId(), (capacidade - semaforo->getContador()), pessoas[i].getTempo(), " Esperando");
		fila.push_back(thread(entrar, pessoas[i]));

		// if(sexo == 0){
		// 	printf(" %c     %i          %i                 %is        %s\n", 'H', id, semaforo->getContador(), temp, " Esperando");
		// 	fila.push_back(thread(entrar, 'H', temp, id));
		// 	id++;
		// }else{
		// 	printf(" %c     %i          %i                 %is        %s\n", 'M', id, semaforo->getContador(), temp, " Esperando");
		// 	fila.push_back(thread(entrar, 'M', temp, id));
		// 	id++;
		// }
	}

	for (int i = 0; i < tamanhoFila; i++){
		fila[i].join();
	}

	
	// 	this_thread::sleep_for (seconds(1));
	
	return 0;
}