#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estruturas de dados
typedef struct {
    int codigo;
    char departamento[4];
    int idade;
    char nome[100];
} Professor;

typedef struct {
    int matricula;
    int ano;
    char departamento[4];
    int idade;
    char nome[100];
} Aluno;

typedef struct {
    int codigoTC;
    int alunoAutor;
    int professorOrientador;
    char titulo[100];
} TC;

typedef struct {
    char cpf[15]; // formato: xxx.xxx.xxx-yy
    int votou;    // 0 para não, 1 para sim
    int votoTC;   // Código do TC votado
} Eleitor;

// Vetores globais e contadores
Professor docentes[MAX];
Aluno formandos[MAX];
TC listaTCs[MAX];
Eleitor comissao[MAX];

int qtdeDocentes = 0;
int qtdeFormandos = 0;
int qtdeTCs = 0;
int qtdeEleitores = 0;

void lerProfessores() {
    FILE *file = fopen("professor.txt", "r");
    if (!file) {
        printf("Erro ao abrir arquivo professor.txt\n");
        exit(1);
    }

    fscanf(file, "%d", &qtdeDocentes); // Lê a quantidade de professores

    for (int i = 0; i < qtdeDocentes; i++) {
        fscanf(file, "%d %s %d %[^\n]", &docentes[i].codigo, docentes[i].departamento, 
               &docentes[i].idade, docentes[i].nome);
    }

    fclose(file);
}

void lerAlunos() {
    FILE *file = fopen("aluno.txt", "r");
    if (!file) {
        printf("Erro ao abrir arquivo aluno.txt\n");
        exit(1);
    }

    fscanf(file, "%d", &qtdeFormandos); // Lê a quantidade de alunos

    for (int i = 0; i < qtdeFormandos; i++) {
        fscanf(file, "%d %d %s %d %[^\n]", &formandos[i].matricula, &formandos[i].ano, 
               formandos[i].departamento, &formandos[i].idade, formandos[i].nome);
    }

    fclose(file);
}

void lerTCs(char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        exit(1);
    }

    int qtde;
    fscanf(file, "%d", &qtde); // Lê a quantidade de TCs no departamento

    for (int i = 0; i < qtde; i++) {
        fscanf(file, "%d %d %d %[^\n]", &listaTCs[qtdeTCs].codigoTC, &listaTCs[qtdeTCs].alunoAutor, 
               &listaTCs[qtdeTCs].professorOrientador, listaTCs[qtdeTCs].titulo);
        
        // Verificações:
        // Verificar se o aluno existe e se o departamento é o correto
        int alunoEncontrado = 0;
        for (int j = 0; j < qtdeFormandos; j++) {
            if (formandos[j].matricula == listaTCs[qtdeTCs].alunoAutor) {
                alunoEncontrado = 1;
                break;
            }
        }
        if (!alunoEncontrado) {
            printf("Erro: Aluno não encontrado para o TC %d\n", listaTCs[qtdeTCs].codigoTC);
            exit(1);
        }

        // Verificar se o professor existe
        int professorEncontrado = 0;
        for (int j = 0; j < qtdeDocentes; j++) {
            if (docentes[j].codigo == listaTCs[qtdeTCs].professorOrientador) {
                professorEncontrado = 1;
                break;
            }
        }
        if (!professorEncontrado) {
            printf("Erro: Professor orientador não encontrado para o TC %d\n", listaTCs[qtdeTCs].codigoTC);
            exit(1);
        }

        qtdeTCs++;
    }

    fclose(file);
}

void lerComissao() {
    FILE *file = fopen("comissao.txt", "r");
    if (!file) {
        printf("Erro ao abrir arquivo comissao.txt\n");
        exit(1);
    }

    fscanf(file, "%d", &qtdeEleitores); // Lê a quantidade de eleitores

    for (int i = 0; i < qtdeEleitores; i++) {
        fscanf(file, "%s", comissao[i].cpf);
        comissao[i].votou = 0; // Inicialmente, ninguém votou
        comissao[i].votoTC = -1; // Sem voto ainda
    }

    fclose(file);
}

int validarCPF(char *cpf) {
    // Verifica se o formato é xxx.xxx.xxx-yy
    if (strlen(cpf) != 14) return 0;
    if (cpf[3] != '.' || cpf[7] != '.' || cpf[11] != '-') return 0;

    // Verificar se todos os outros caracteres são dígitos
    for (int i = 0; i < 14; i++) {
        if (i == 3 || i == 7 || i == 11) continue;
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }

    return 1; // CPF válido no formato
}


