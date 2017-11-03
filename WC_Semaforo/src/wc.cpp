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
vector<thread> fila;
vector<Pessoa> pessoas;
Semaforo *semaforo;
Semaforo *semBin;
bool flag = true;

void utilizar(Pessoa pessoa){
	semaforo->P();
	printf(" %c     %i      %i           %is        %s\n", pessoa.getSexo(), pessoa.getId(), (capacidade - semaforo->getContador()), pessoa.getTempo(), " Entrou");
	this_thread::sleep_for(seconds(pessoa.getTempo()));
	printf(" %c     %i      %i           %is        %s\n", pessoa.getSexo(), pessoa.getId(), (capacidade - semaforo->getContador()-1), pessoa.getTempo(), " Saiu");
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
			if(sexo_usado == pessoa.getSexo()){
				capacidadeAtual -= 1;
				utilizar(pessoa);
				capacidadeAtual += 1;
				return;
			}
		}
	}
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

	printf("Sexo | Id | Em uso | Tempo de uso |   Status\n");
	printf("==================================================\n");

	for(int i = 0; i < tamanhoFila; i++){
		printf(" %c     %i      %i           %is        %s\n", pessoas[i].getSexo(), pessoas[i].getId(), (capacidade - semaforo->getContador()), pessoas[i].getTempo(), " Esperando");
		this_thread::sleep_for(milliseconds(50));
		fila.push_back(thread(entrar, pessoas[i]));
	}

	for (int i = 0; i < tamanhoFila; i++){
		fila[i].join();
	}
	
	return 0;
}