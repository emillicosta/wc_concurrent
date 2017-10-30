#ifndef _PESSOA_H_
#define _PESSOA_H_

class Pessoa{
	private:
		char sexo;
		int id;
		int tempo;

	public:

		Pessoa(char s_, int id_, int tempo_){
			sexo = s_;
			id = id_;
			tempo = tempo_;
		}

		char getSexo(){
			return sexo;
		}

		int getId(){
			return id;
		}

		int getTempo(){
			return tempo;
		}
};

#endif