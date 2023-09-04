#ifndef HASH_ABERTA_H
#define HASH_ABERTA_H

#include <time.h>
#include <stdbool.h>

// Definição de uma estrutura para a tabela hash aberta
typedef struct {
    int *tabela;    // Array para armazenar os elementos da tabela
    int tamanho;    // Tamanho da tabela
} HashAberta;

// Função para obter entrada do usuário
void entradaUsuario(int *tamanhoBaseDados, int *escolhaHash, int *tamanhoTabela);

// Função para ler uma base de dados a partir de um arquivo
int *lerArquivoBaseDados(int tamanhoBaseDados, int *tamanhoBase);

// Função para calcular um tamanho de tabela primo com base em alguns parâmetros
int calcularTamanhoTabelaPrimo(int tamanhoTabela, int tamanhoBase);

// Função para manipular a tabela hash (inserir, buscar, etc.)
void manipularTabela(HashAberta *tabela, int *baseDados, int tamanhoBase, int escolhaHash);

// Função para medir o tempo de processamento de algumas operações
void medirTempoProcessamento(clock_t inicioTotal, clock_t inicioPrimo, clock_t fimPrimo);

// Função para ler um arquivo e retornar seu conteúdo em um array
int *lerArquivo(const char *nomeArquivo, int *tamanho);

// Função para encontrar um número primo próximo a 'n'
int encontraPrimo(int n);

// Função para criar uma nova tabela hash aberta
HashAberta *criarTabela(int tamanho);

// Função para inserir um valor na tabela hash
int inserir(HashAberta *tabela, int chave, int escolhaHash);

// Função para buscar um valor na tabela hash
int buscar(HashAberta *tabela, int chave, int escolhaHash);

// Funções para tratamento de colisões por sondagem linear
int gerarHash(int entrada, int tamanho_vetor);
int colisao(int entrada, int tamanho);
int reHash(int entrada, int hash, int tamanho_lista);

// Função para destruir uma tabela hash e liberar a memória alocada
void destruirTabela(HashAberta *tabela);

#endif

