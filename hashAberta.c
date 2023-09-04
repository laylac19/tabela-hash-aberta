#include "hashAberta.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para verificar se um número é primo
bool primoVerificador(int num) {
    if (num <= 1) {
        return false;
    }
    int i;
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Função para encontrar o próximo número primo
int proximoPrimo(int num) {
    int next = num + 1;
    while (!primoVerificador(next)) {
        next++;
    }
    return next;
}

// Função para gerar valor hash do tipo inteiro
int gerarHash(int entrada, int tamanho_vetor) {
    return entrada % tamanho_vetor;
}

// Função para recalcula o valor com colisao (sondagem linear)
int colisao(int entrada, int tamanho) {
    return 1; // Sondagem linear simples, apenas adiciona 1 ao índice
}

// Função para recalcula o hash quando tem colisao (sondagem linear)
int reHash(int entrada, int hash, int tamanho_lista) {
    return (hash + colisao(entrada, tamanho_lista)) % tamanho_lista;
}

void entradaUsuario(int *tamanhoBaseDados, int *escolhaHash,
                    int *tamanhoTabela) {
    printf("-------------------- MENU --------------------\n");

    // Validação para escolher o tamanho da base de dados
    do {
        printf("* Tamanho da base de dados *\n");
        printf("\t 1. 1 mil números\n");
        printf("\t 2. 100 mil números\n");
        printf(" Escolha o tamanho da base de dados: ");
        scanf("%d", tamanhoBaseDados);

        if (*tamanhoBaseDados != 1 && *tamanhoBaseDados != 2) {
            printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
        }
    } while (*tamanhoBaseDados != 1 && *tamanhoBaseDados != 2);

    // Validação para escolher a função de hash
    do {
        printf("\n* Função Hash *\n");
        printf("\t 1. Hash Duplo 1\n");
        printf("\t 2. Hash Duplo 2\n");
        printf(" Escolha a função Hash: ");
        scanf("%d", escolhaHash);

        if (*escolhaHash != 1 && *escolhaHash != 2) {
            printf("Escolha inválida. Por favor, escolha 1 ou 2.\n");
        }
    } while (*escolhaHash != 1 && *escolhaHash != 2);

    // Validação para escolher o tamanho da tabela hash
    do {
        printf("\n * Tamanho da Tabela Hash *\n");
        printf("\t 1. 10%% (Multiplicação por 1.1)\n");
        printf("\t 2. 25%% (Multiplicação por 1.25)\n");
        printf("\t 3. 50%% (Multiplicação por 1.5)\n");
        printf(" Escolha do tamanho da Tabela Hash: ");
        scanf("%d", tamanhoTabela);

        if (*tamanhoTabela != 1 && *tamanhoTabela != 2 && *tamanhoTabela != 3) {
            printf("Escolha inválida. Por favor, escolha 1, 2 ou 3.\n");
        }
    } while (*tamanhoTabela != 1 && *tamanhoTabela != 2 && *tamanhoTabela != 3);
}

int *lerArquivoBaseDados(int tamanhoBaseDados, int *tamanhoBase) {
    int *baseDados;

    // Verifica o tamanho da base de dados escolhido pelo usuário e faz a leitura do arquivo
    if (tamanhoBaseDados == 1) {
        baseDados = lerArquivo("randInt1K.txt", tamanhoBase); // lê e armazena os dados em 'baseDados'
    } else if (tamanhoBaseDados == 2) {
        baseDados = lerArquivo("randInt100K.txt", tamanhoBase); // lê e armazena os dados em 'baseDados'
    } else {
        // Se o tamanho da base de dados não for 1 ou 2, exibe uma mensagem de erro
        printf("Opção inválida.\n");

        // Define o tamanho da base como zero pois a leitura falhou
        *tamanhoBase = 0;

        // Retorna NULL para indicar que a leitura falhou
        return NULL;
    }

    // Retorna o ponteiro para os dados da base de dados lidos do arquivo
    return baseDados;
}

int calcularTamanhoTabelaPrimo(int tamanhoTabela, int tamanhoBase) {
    int tamanhoTabelaPrimo;

    // Seleciona um tamanho da tabela com base na escolha do usuário
    switch (tamanhoTabela) {
        case 1:
            // Calcula um tamanho da tabela multiplicando o tamanho base por 1.1 e encontra o primo mais próximo
            tamanhoTabelaPrimo = proximoPrimo(tamanhoBase * 1.1);
            break;
        case 2:
            // Calcula um tamanho da tabela multiplicando o tamanho base por 1.25 e encontra o primo mais próximo
            tamanhoTabelaPrimo = proximoPrimo(tamanhoBase * 1.25);
            break;
        case 3:
            // Calcula um tamanho da tabela multiplicando o tamanho base por 1.5 e encontra o primo mais próximo
            tamanhoTabelaPrimo = proximoPrimo(tamanhoBase * 1.5);
            break;
        default:
            // Se a opção do tamanho da tabela não for válida, exibe uma mensagem de erro
            printf("Opção inválida.\n");

            // Define tamanhoTabelaPrimo como -1 para indicar um erro com um valor negativo
            tamanhoTabelaPrimo = -1;
            break;
    }

    // Retorna o tamanho da tabela primo calculado ou -1 em caso de erro
    return tamanhoTabelaPrimo;
}

void manipularTabela(HashAberta *tabela, int *baseDados, int tamanhoBase, int escolhaHash) {
    // Insere os elementos da base de dados na tabela hash
    int i;
    for (i = 0; i < tamanhoBase; i++) {
        inserir(tabela, baseDados[i], escolhaHash);
    }
     printf("OK\n");
    // Gera uma chave de busca aleatória a partir da base de dados
    srand(time(NULL));
    int chaveBusca = baseDados[rand() % tamanhoBase];


    // Inicia a medição do tempo de busca
    clock_t inicioBusca = clock();

    // Realiza a busca na tabela hash
    int resultado = buscar(tabela, chaveBusca, escolhaHash);

    // Finaliza a medição do tempo de busca
    clock_t fimBusca = clock();

    // Exibe o resultado da busca
    if (resultado != -1) {
        printf("Chave %d encontrada na posição %d\n", chaveBusca, resultado);
    } else {
        printf("Chave %d não encontrada.\n", chaveBusca);
    }

    // Calcula o tempo de busca em segundos e exibe
    double tempoBusca = (double)(fimBusca - inicioBusca) / CLOCKS_PER_SEC;
    printf("Tempo de busca: %.6f segundos\n", tempoBusca);
}

void medirTempoProcessamento(clock_t inicioTotal, clock_t inicioPrimo, clock_t fimPrimo) {
    // Calcula o tempo de cálculo do número primo em segundos
    double tempoPrimo = (double)(fimPrimo - inicioPrimo) / CLOCKS_PER_SEC;

    // Calcula o tempo total de processamento em segundos desde o início até este ponto
    double tempoTotal = (double)(clock() - inicioTotal) / CLOCKS_PER_SEC;

    // Exibe o tempo de cálculo do número primo
    printf("Tempo de cálculo do número primo: %.6f segundos\n", tempoPrimo);

    // Exibe o tempo total de processamento
    printf("Tempo total de processamento: %.6f segundos\n", tempoTotal);
}

int *lerArquivo(const char *nomeArquivo, int *tamanho) {
    // Abre o arquivo para leitura
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("\n\n Erro ao abrir o arquivo.\n\n");
        exit(1);
    } else {
        printf("\n\n Sucesso ao abrir arquivo.\n\n");
    }

    // Tamanho inicial do array de dados
    int capacidade = 1000;
    int *dados = (int *)malloc(capacidade * sizeof(int));
    if (dados == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    int numero;
    *tamanho = 0;

    while (fscanf(arquivo, "%d", &numero) == 1) {
        if (*tamanho == capacidade) {
            // Se o tamanho atual atingiu a capacidade, realoca o array com o dobro do tamanho
            capacidade *= 2;
            dados = (int *)realloc(dados, capacidade * sizeof(int));
            if (dados == NULL) {
                printf("Erro ao alocar memória.\n");
                exit(1);
            }
        }

        dados[(*tamanho)++] = numero;
    }

    // Redimensiona o array para o tamanho real
    dados = (int *)realloc(dados, (*tamanho) * sizeof(int));

    // Fecha o arquivo após a leitura
    fclose(arquivo);
    printf("Erro ao alocar memória.\n");
    return dados;
}



int encontraPrimo(int n) {
  int primo;
  while (1) {
    n++; // Avança para o próximo número para verificar se é primo
    int ehPrimo = 1; // Assume que o número é primo até que se prove o contrário

    // Verifica se o número é divisível por algum número de 2 até a raiz quadrada de n
    int i;
    for (i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        ehPrimo = 0; // Se for divisível, não é primo
        break;
      }
    }

    if (ehPrimo) {
      primo = n; // Se não foi encontrado nenhum divisor, o número é primo
      break; // Sai do loop
    }
  }

  return primo; // Retorna o primeiro número primo encontrado após n
}

HashAberta *criarTabela(int tamanho) {
  // Aloca memória para a estrutura HashAberta
  HashAberta *tabela = (HashAberta *)malloc(sizeof(HashAberta));
  if (tabela == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }

  // Define o tamanho da tabela
  tabela->tamanho = tamanho;

  // Aloca memória para o array que armazenará os elementos da tabela
  tabela->tabela = (int *)malloc(tamanho * sizeof(int));
  if (tabela->tabela == NULL) {
    printf("Erro ao alocar memória.\n");
    exit(1);
  }

  // Inicializa a tabela com valores padrão (-1, indicando posição vazia)
  int i;
  for (i = 0; i < tamanho; i++) {
    tabela->tabela[i] = -1;
  }

  // Retorna a tabela recém-criada
  return tabela;
}


int inserir(HashAberta *tabela, int chave, int escolhaHash) {
    // Implementação da inserção com tratamento de colisões por sondagem linear
    int index = gerarHash(chave, tabela->tamanho);

    // Enquanto o índice não estiver vazio (já ocupado por outra chave)
    while (tabela->tabela[index] != -1) {
        // Calcula o próximo índice com base na colisão
        index = reHash(chave, index, tabela->tamanho);
    }

    // Quando encontrar um índice vazio, insere a chave na tabela nesse índice
    tabela->tabela[index] = chave;

    // Retorna o índice onde a chave foi inserida
    return index;
}

int buscar(HashAberta *tabela, int chave, int escolhaHash) {
    // Implementação da busca com tratamento de colisões por sondagem linear
    int index = gerarHash(chave, tabela->tamanho);

    // Enquanto o índice não corresponder à chave e não encontrar uma posição vazia
    while (tabela->tabela[index] != chave) {
        // Se encontrar uma posição vazia, significa que a chave não está na tabela
        if (tabela->tabela[index] == -1) {
            return -1; // Retorna -1 para indicar que a chave não foi encontrada
        }

        // Calcula o próximo índice com base na colisão
        index = reHash(chave, index, tabela->tamanho);
    }

    // Quando encontrar a chave, retorna o índice onde ela está na tabela
    return index;
}

void destruirTabela(HashAberta *tabela) {
    // Libera a memória alocada para o array de elementos da tabela
    free(tabela->tabela);

    // Libera a memória alocada para a estrutura HashAberta em si
    free(tabela);
}

