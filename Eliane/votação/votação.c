#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max 50
#define maxNome 60
#define maxSigla 10

typedef struct Pessoa {
    char nome[maxNome]; // nome da pessoa
    int idade; // idade da pessoa 
} Pessoa;

typedef struct Professor {
    Pessoa pes; // assim professor tem nome e idade
    int codigo; // código do professor
    char depto[maxSigla]; // departamento onde trabalha
} Professor;

typedef struct Aluno {
    Pessoa pes; // assim aluno tem nome e idade
    int matricula; // número de matrícula do aluno 
    int ano; // ano no curso. 
    char depto[maxSigla]; // departamento onde estuda
} Aluno;

typedef struct TC {
    int codigo;
    int autor; // equivalente à matrícula do aluno autor
    int orientador; // equivalente ao código do professor
    char titulo[maxNome]; // título do TC
    int qtdeVotos; // somatório dos votos recebidos
} TC;

typedef struct Eleitor {
    char cpf[15];
    bool votou; // true se já votou; false se não votou
    int codigoTC;
} Eleitor; // Ensure to properly end the struct definition

// Declaração de variáveis globais
Professor docentes[max];
int qtdeDocentes = 0;
Aluno formandos[max];
int qtdeFormandos = 0;
TC listaTCs[max];
int qtdeTCs = 0;
Eleitor comissao[max];
int qtdeEleitores = 0;

// Prototipação das funções
void carregarDados();
void lerProfessores();
void lerAlunos();
void lerTCs(char* nomeArquivo);
void lerEleitores();
bool validarCPF(const char* cpf);
void iniciarVotacao();
void continuarVotacao();
void menuPrincipal();
void menuVotacao();
void registrarVoto(const char* cpf);
void suspenderVotacao();
void concluirVotacao();
void salvarVotosParcial();
void salvarVotosResultado();

// Função principal
int main() {
    carregarDados();
    menuPrincipal();
    return 0;
}

// Carregar dados de arquivos
void carregarDados() {
    lerProfessores();
    lerAlunos();
    lerTCs("TC_BCC.txt");
    lerTCs("TC_BSI.txt");
    lerTCs("TC_ADS.txt");
    lerTCs("TC_GTI.txt");
    lerTCs("TC_BEC.txt");
    lerEleitores();
}

// Ler professores
void lerProfessores() {
    FILE* arq = fopen("professor.txt", "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo de professores.\n");
        exit(1);
    }
    
    fscanf(arq, "%d", &qtdeDocentes);
    for (int i = 0; i < qtdeDocentes; i++) {
        fscanf(arq, "%d %s %d %[^\n]", &docentes[i].codigo, docentes[i].depto, &docentes[i].pes.idade, docentes[i].pes.nome);
    }
    fclose(arq);
}

// Ler alunos
void lerAlunos() {
    FILE* arq = fopen("aluno.txt", "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo de alunos.\n");
        exit(1);
    }
    
    fscanf(arq, "%d", &qtdeFormandos);
    for (int i = 0; i < qtdeFormandos; i++) {
        fscanf(arq, "%d %d %s %d %[^\n]", &formandos[i].matricula, &formandos[i].ano, formandos[i].depto, &formandos[i].pes.idade, formandos[i].pes.nome);
    }
    fclose(arq);
}

// Ler TCs de um departamento
void lerTCs(char* nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return; // Arquivo pode não existir
    }
    
    int quantidadeTCs;
    fscanf(arq, "%d", &quantidadeTCs);
    for (int i = 0; i < quantidadeTCs; i++) {
        fscanf(arq, "%d %d %d %[^\n]", &listaTCs[qtdeTCs].codigo, &listaTCs[qtdeTCs].autor, &listaTCs[qtdeTCs].orientador, listaTCs[qtdeTCs].titulo);
        listaTCs[qtdeTCs].qtdeVotos = 0; // Inicializando a quantidade de votos
        qtdeTCs++;
    }
    fclose(arq);
}

// Ler eleitores
void lerEleitores() {
    FILE* arq = fopen("comissao.txt", "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo de comissao.\n");
        exit(1);
    }
    
    fscanf(arq, "%d", &qtdeEleitores);
    for (int i = 0; i < qtdeEleitores; i++) {
        fscanf(arq, "%s", comissao[i].cpf);
        comissao[i].votou = false;
        comissao[i].codigoTC = -1; // Inicializando o código do TC votado
    }
    fclose(arq);
}

// Validar CPF (apenas um exemplo de validação, você deve implementar corretamente)
bool validarCPF(const char* cpf) {
    if (strlen(cpf) != 14) {
        return false;
    }
    // Exemplo de validação simplificada
    return true; // Retornar true se o CPF for válido, false caso contrário
}

// Iniciar votação
void iniciarVotacao() {
    menuVotacao();
}

// Continuar votação
void continuarVotacao() {
    // Implementar lógica para continuar votação
    menuVotacao();
}

// Menu principal
void menuPrincipal() {
    char escolha;
    do {
        printf("MENU 1:\n");
        printf("a) Iniciar nova votação\n");
        printf("b) Continuar votação gravada\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
        escolha = tolower(escolha);
        
        switch (escolha) {
            case 'a':
                iniciarVotacao();
                break;
            case 'b':
                continuarVotacao();
                break;
            default:
                printf("Escolha inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 'a' && escolha != 'b');
}

// Menu de votação
void menuVotacao() {
    char escolha;
    do {
        printf("MENU 2:\n");
        printf("a) Entrar com voto\n");
        printf("b) Suspender votação\n");
        printf("c) Concluir votação\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
        escolha = tolower(escolha);
        
        switch (escolha) {
            case 'a': {
                char cpf[15];
                printf("Digite seu CPF: ");
                scanf("%s", cpf);
                registrarVoto(cpf);
                break;
            }
            case 'b':
                suspenderVotacao();
                break;
            case 'c':
                concluirVotacao();
                break;
            default:
                printf("Escolha inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 'a' && escolha != 'b' && escolha != 'c');
}

// Registrar voto
void registrarVoto(const char* cpf) {
    // Validar CPF
    if (!validarCPF(cpf)) {
        printf("CPF inválido!\n");
        return;
    }

    // Verificar se o CPF pertence à comissão
    int idxEleitor = -1;
    for (int i = 0; i < qtdeEleitores; i++) {
        if (strcmp(comissao[i].cpf, cpf) == 0) {
            idxEleitor = i;
            break;
        }
    }

    if (idxEleitor == -1) {
        printf("CPF não pertence à comissão!\n");
        return;
    }

    // Verificar se já votou
    if (comissao[idxEleitor].votou) {
        printf("Você já votou!\n");
        return;
    }

    // Obter código do TC
    int codigoTC;
    printf("Digite o código do TC que você deseja votar: ");
    scanf("%d", &codigoTC);

    // Verificar se o TC existe
    bool tcExistente = false;
    for (int i = 0; i < qtdeTCs; i++) {
        if (listaTCs[i].codigo == codigoTC) {
            listaTCs[i].qtdeVotos++;
            comissao[idxEleitor].votou = true;
            comissao[idxEleitor].codigoTC = codigoTC; // Armazena qual TC foi votado
            tcExistente = true;
            printf("Voto registrado com sucesso!\n");
            break;
        }
    }

    if (!tcExistente) {
        printf("Código do TC inválido!\n");
    }
}

// Suspender votação
void suspenderVotacao() {
    printf("Votação suspensa.\n");
    // Implementar lógica de suspensão
}

// Concluir votação
void concluirVotacao() {
    printf("Votação concluída.\n");
    // Implementar lógica de conclusão e salvar resultados
    salvarVotosResultado();
}

// Salvar votos parciais (caso necessário)
void salvarVotosParcial() {
    // Implementar lógica para salvar votos parciais
}

// Salvar votos e resultado final
void salvarVotosResultado() {
    FILE* arq = fopen("resultado.txt", "w");
    if (!arq) {
        printf("Erro ao abrir o arquivo para salvar resultados.\n");
        return;
    }
    
    for (int i = 0; i < qtdeTCs; i++) {
        fprintf(arq, "TC: %d | Título: %s | Votos: %d\n", listaTCs[i].codigo, listaTCs[i].titulo, listaTCs[i].qtdeVotos);
    }
    fclose(arq);
    printf("Resultados salvos com sucesso.\n");
}

