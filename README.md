# Análise de mecanismo de sincronização aplicado ao problema do banheiro unissex
Trabalho de programação concorrente, no qual usaremos mecanismos de sincronização simulando um banheiro.

## Instruções para execução
Para executar cada uma das implementações execute o seguinte comando no terminal:

g++ -std=c++11 WC_Monitor/src/wc.cpp -o wcMonitor -pthread && ./wcMonitor

ou

g++ -std=c++11 WC_Semaforo/src/wc.cpp -o wcSemaforo -pthread && ./wcSemaforo

Em seguida defina a capacidade do banheiro e a quantidade de pessoas na fila.

## Desenvolvedores
- Débora Emilli Costa Oliveira
- Raul Silveira Silva