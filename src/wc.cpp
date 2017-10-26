#include <unistd.h>
#include <iostream>
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
#include "semaforo.cpp"

using namespace std::chrono;
using namespace std;

int capacidade;
char sexo_usado;
Semaforo *semaforo;
Semaforo *print;

void run(char s, int temp){
	bool flag = true;
	while(flag){
		if(semaforo->getContador() == capacidade){
			sexo_usado = s;
			semaforo->P();
			cout << "entrou " << s <<"\ncapacidade atual é " << semaforo->getContador() << "\nTempo de mijo" << temp <<"\n";
			this_thread::sleep_for (seconds(temp));
			semaforo->V();
			cout << "saiu " << s <<"\n capacidade atual é " << semaforo->getContador() << "\n";
			flag = false;
		}else{
			if(sexo_usado == s && semaforo->getContador() > 0){
				semaforo->P();
				cout << "entrou " << s <<"\ncapacidade atual é " << semaforo->getContador() << "\nTempo de mijo" << temp <<"\n";
				this_thread::sleep_for (seconds(temp));
				semaforo->V();
				cout << "saiu " << s <<"\n capacidade atual é " << semaforo->getContador() << "\n";
				flag = false;
			}

		}
	}
}

int main(int argc, const char * argv[]){
	
	int sexo, temp;
	cout << "Qual a capacidade do banheiro?\n";
	cin >> capacidade;

	semaforo = new Semaforo(1230,capacidade,IPC_CREAT|0600);

	vector<thread> homens;
	vector<thread> mulheres;

	srand (time(NULL));

	while(true){
		sexo = rand() % 2;
		temp = (rand() % 5) + 1;
		//homem = 0; mulher = 1
		if(sexo == 0){
			cout << "chegou um homem \n";
			homens.push_back(thread(run, 'H', temp));

		}else{
			cout << "chegou uma mulher \n";
			mulheres.push_back(thread(run, 'M', temp));
		}
		this_thread::sleep_for (seconds(1));
	}
	
	return 0;
}