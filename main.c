#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Inclui o cabeçalho personalizado para a estrutura HashAberta e outras funções
#include "hashAberta.h"

int main() {
	setlocale(LC_ALL, "Portuguese");
  clock_t inicioTotal = clock(); // Registrar o início do tempo total de execução

  int tamanhoBaseDados, escolhaHash, tamanhoTabela;
  int *baseDados, tamanhoBase;
  int tamanhoTabelaPrimo;

  // Solicita ao usuário que insira escolhas relacionadas ao programa
  entradaUsuario(&tamanhoBaseDados, &escolhaHash, &tamanhoTabela);

  clock_t inicioPrimo =
      clock(); // Registrar o início do cálculo do número primo

  // Lê a base de dados a partir de um arquivo e obtém o tamanho da base
  baseDados = lerArquivoBaseDados(tamanhoBaseDados, &tamanhoBase);

  if (baseDados == NULL) {
    printf("Erro ao ler a base de dados.\n");
    return 1; // Encerra o programa com código de erro
  }

  // Calcula o tamanho da tabela hash baseado nas escolhas do usuário
  tamanhoTabelaPrimo = calcularTamanhoTabelaPrimo(tamanhoTabela, tamanhoBase);
  if (tamanhoTabelaPrimo == -1) {
    printf("Erro ao calcular o tamanho da tabela hash.\n");
    free(baseDados); // Libera a memória alocada para a base de dados
    return 1; // Encerra o programa com código de erro
  }

  // Cria uma tabela hash com o tamanho calculado
  HashAberta *tabela = criarTabela(tamanhoTabelaPrimo);

  if (tabela == NULL) {
    printf("Erro ao criar a tabela hash.\n");
    free(baseDados); // Libera a memória alocada para a base de dados
    return 1; // Encerra o programa com código de erro
  }

  // Realiza operações na tabela hash com base na base de dados e escolha de função de hash
  manipularTabela(tabela, baseDados, tamanhoBase, escolhaHash);

  clock_t fimPrimo = clock();
  
  // Mede e exibe o tempo de processamento do cálculo do número primo e o tempo total de execução
  medirTempoProcessamento(inicioTotal, inicioPrimo, fimPrimo);

  // Libera a memória alocada para a tabela hash e a base de dados
  destruirTabela(tabela);
  free(baseDados);

  return 0; // Encerra o programa com sucesso
}
