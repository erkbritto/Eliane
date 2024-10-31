#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para uma tarefa
typedef struct Task {
    char description[100];
    struct Task *next;
} Task;

// Estrutura para a lista de tarefas
typedef struct {
    Task *head;
} TaskList;

// Estrutura para a fila de tarefas
typedef struct {
    Task *front;
    Task *rear;
} TaskQueue;

// Estrutura para a pilha de tarefas
typedef struct {
    Task *top;
} TaskStack;

// Função para criar uma nova tarefa
Task* createTask(const char *description) {
    Task *newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strncpy(newTask->description, description, sizeof(newTask->description) - 1);
    newTask->description[sizeof(newTask->description) - 1] = '\0';
    newTask->next = NULL;
    return newTask;
}

// Função para inicializar a lista de tarefas
void initTaskList(TaskList *list) {
    list->head = NULL;
}

// Função para adicionar uma tarefa à lista
void addTaskToList(TaskList *list, const char *description) {
    Task *newTask = createTask(description);
    newTask->next = list->head;
    list->head = newTask;
}

// Função para imprimir a lista de tarefas recursivamente
void printTaskListRecursive(Task *task) {
    if (task == NULL) {
        return;
    }
    printf("%s\n", task->description);
    printTaskListRecursive(task->next);
}

// Função para inicializar a fila de tarefas
void initTaskQueue(TaskQueue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

// Função para adicionar uma tarefa à fila
void enqueueTask(TaskQueue *queue, const char *description) {
    Task *newTask = createTask(description);
    if (queue->rear == NULL) {
        queue->front = newTask;
        queue->rear = newTask;
    } else {
        queue->rear->next = newTask;
        queue->rear = newTask;
    }
}

// Função para remover uma tarefa da fila
Task* dequeueTask(TaskQueue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    Task *removedTask = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    return removedTask;
}

// Função para imprimir a fila de tarefas
void printTaskQueue(TaskQueue *queue) {
    Task *current = queue->front;
    printf("Tarefas na fila:\n");
    while (current != NULL) {
        printf("%s\n", current->description);
        current = current->next;
    }
}

// Função para inicializar a pilha de tarefas
void initTaskStack(TaskStack *stack) {
    stack->top = NULL;
}

// Função para adicionar uma tarefa à pilha
void pushTask(TaskStack *stack, const char *description) {
    Task *newTask = createTask(description);
    newTask->next = stack->top;
    stack->top = newTask;
}

// Função para remover uma tarefa da pilha
Task* popTask(TaskStack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    Task *removedTask = stack->top;
    stack->top = stack->top->next;
    return removedTask;
}

// Função para imprimir a pilha de tarefas
void printTaskStack(TaskStack *stack) {
    Task *current = stack->top;
    printf("Tarefas na pilha:\n");
    while (current != NULL) {
        printf("%s\n", current->description);
        current = current->next;
    }
}

// Função principal
int main() {
    TaskList taskList;
    TaskQueue taskQueue;
    TaskStack taskStack;

    initTaskList(&taskList);
    initTaskQueue(&taskQueue);
    initTaskStack(&taskStack);

    int choice;
    char description[100];

    while (1) {
        printf("\nGerenciador de Tarefas\n");
        printf("1. Adicionar tarefa à lista\n");
        printf("2. Adicionar tarefa à fila\n");
        printf("3. Adicionar tarefa à pilha\n");
        printf("4. Remover tarefa da lista\n");
        printf("5. Remover tarefa da fila\n");
        printf("6. Remover tarefa da pilha\n");
        printf("7. Listar tarefas da lista\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar(); // Consumir o caractere de nova linha

        switch (choice) {
            case 1:
                printf("Descrição da tarefa: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remover nova linha
                addTaskToList(&taskList, description);
                break;
            case 2:
                printf("Descrição da tarefa: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remover nova linha
                enqueueTask(&taskQueue, description);
                break;
            case 3:
                printf("Descrição da tarefa: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remover nova linha
                pushTask(&taskStack, description);
                break;
            case 4:
                // Remover tarefa da lista (só para simplicidade, removendo do início)
                if (taskList.head != NULL) {
                    Task *removedTask = taskList.head;
                    taskList.head = taskList.head->next;
                    printf("Tarefa removida da lista: %s\n", removedTask->description);
                    free(removedTask);
                } else {
                    printf("Lista de tarefas vazia.\n");
                }
                break;
            case 5:
                {
                    Task *removedTask = dequeueTask(&taskQueue);
                    if (removedTask != NULL) {
                        printf("Tarefa removida da fila: %s\n", removedTask->description);
                        free(removedTask);
                    } else {
                        printf("Fila de tarefas vazia.\n");
                    }
                }
                break;
            case 6:
                {
                    Task *removedTask = popTask(&taskStack);
                    if (removedTask != NULL) {
                        printf("Tarefa removida da pilha: %s\n", removedTask->description);
                        free(removedTask);
                    } else {
                        printf("Pilha de tarefas vazia.\n");
                    }
                }
                break;
            case 7:
                printf("Tarefas na lista:\n");
                printTaskListRecursive(taskList.head);
                break;
            case 8:
                // Exibir o estado final das estruturas de dados
                printf("Estado final das estruturas de dados:\n");
                printTaskListRecursive(taskList.head);
                printTaskQueue(&taskQueue);
                printTaskStack(&taskStack);
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
