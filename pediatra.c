#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pediatria.h"
#include <locale.h>


paciente_t *primeiro_paciente(char *nome, int idade, float peso, float altura, char genero) {
    paciente_t *novo = (paciente_t *)malloc(sizeof(paciente_t));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o paciente.\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->peso = peso;
    novo->altura = altura;
    novo->genero = genero;
    novo->prox = NULL;

    return novo;
}

void novo_paciente(paciente_t *primeiro, char *nome, int idade, float peso, float altura, char genero) {
    paciente_t *atual = primeiro;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    paciente_t *novo = (paciente_t *)malloc(sizeof(paciente_t));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para o paciente.\n");
        return;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->peso = peso;
    novo->altura = altura;
    novo->genero = genero;
    novo->prox = NULL;

    atual->prox = novo;
}

IMCInfantil calcula_imc(paciente_t *crianca) {
    if (crianca->altura <= 0) {
        printf("Altura invalida.\n");
        return ABAIXO; 
    }

    float imc = crianca->peso / (crianca->altura * crianca->altura);

    if (imc < 14.5) {
        return ABAIXO;
    } else if (imc >= 14.5 && imc < 18.5) {
        return NORMAL;
    } else if (imc >= 18.5 && imc < 22.0) {
        return SOBREPESO;
    } else {
        return OBESIDADE;
    }
}

void exibe_categoria(IMCInfantil categoria) {
    switch (categoria) {
        case ABAIXO:
            printf("Abaixo do peso\n");
            break;
        case NORMAL:
            printf("Peso normal\n");
            break;
        case SOBREPESO:
            printf("Sobrepeso\n");
            break;
        case OBESIDADE:
            printf("Obesidade\n");
            break;
        default:
            printf("Categoria desconhecida\n");
    }
}

  int main() {
    char nome[100];
    int idade;
    float peso, altura;
    char genero;
    int continuar;

    paciente_t *lista_pacientes = NULL;

    printf("=== Cadastro de Pacientes para Calculo de IMC Infantil ===\n");
    do {
        printf("\nDigite o nome da crianca: ");
        scanf(" %[^\n]", nome);

        printf("Digite a idade da crianca (6 a 15 anos): ");
        scanf("%d", &idade);

        printf("Digite o peso da crianca (em kg): ");
        scanf("%f", &peso);

        printf("Digite a altura da crianca (em metros): ");
        scanf("%f", &altura);

        printf("Digite o genero da crianca (M para masculino, F para feminino): ");
        scanf(" %c", &genero);

        if (lista_pacientes == NULL) {
            lista_pacientes = primeiro_paciente(nome, idade, peso, altura, genero);
            if (lista_pacientes == NULL) {
                printf("Erro ao criar o primeiro paciente.\n");
                return 1;
            }
        } else {
            novo_paciente(lista_pacientes, nome, idade, peso, altura, genero);
        }

        printf("\nDeseja adicionar outro paciente? (1 para Sim, 0 para Não): ");
        scanf("%d", &continuar);

    } while (continuar == 1);

    
    printf("\n=== Resultados dos Calculos de IMC ===\n");
    paciente_t *atual = lista_pacientes;
    while (atual != NULL) {
        printf("\nNome: %s, Idade: %d, Peso: %.1f kg, Altura: %.2f m, Genero: %c\n", 
               atual->nome, atual->idade, atual->peso, atual->altura, atual->genero);

        IMCInfantil categoria = calcula_imc(atual);
        printf("IMC: %.2f - Categoria: ", atual->peso / (atual->altura * atual->altura));
        exibe_categoria(categoria);

        atual = atual->prox;
    }

    atual = lista_pacientes;
    while (atual != NULL) {
        paciente_t *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    return 0;
}
