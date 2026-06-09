#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_ANIMAIS 100
#define MAX_LIMITE 50

typedef struct {
    int id;
    char nome[MAX_LIMITE];
    char especie[MAX_LIMITE];
    char raca[MAX_LIMITE];
    int idade;
    char dono[MAX_LIMITE];
    int ativo; 
} Animal;


void cadastrarAnimal(Animal lista[1], int *total);
void consultarAnimais(Animal lista[2], int total);
void alterarAnimal(Animal lista[3], int total);
void excluirAnimal(Animal lista[4], int total);
int buscarPorId(Animal lista[5], int total, int id);

int main() {
	SetConsoleOutputCP(CP_UTF8);
    Animal clinica[MAX_ANIMAIS];
    int totalAnimais = 0;
    int opcao;

    do {
        printf("\n--- SISTEMA VETERINÁRIO ---\n");
        printf("1. Cadastrar Animal\n");
        printf("2. Consultar Animais\n");
        printf("3. Alterar Animal\n");
        printf("4. Excluir Animal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarAnimal(clinica, &totalAnimais);
                break;
            case 2:
                consultarAnimais(clinica, totalAnimais);
                break;
            case 3:
                alterarAnimal(clinica, totalAnimais);
                break;
            case 4:
                excluirAnimal(clinica, totalAnimais);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

//1
void cadastrarAnimal(Animal lista[], int *total) {
    if (*total >= MAX_ANIMAIS) {
        printf("Erro: Capacidade máxima do sistema atingida.\n");
        return;
    }

    Animal novo;
    novo.id = *total + 1; 
    novo.ativo = 1;       

    printf("\n--- Cadastrar Novo Animal (ID: %d) ---\n", novo.id);
    
    printf(" Informe o Nome do animal: ");
    fgets(novo.nome, MAX_LIMITE, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0; 

    printf(" Informe a Espécie (ex: gato, cachorro, passaro, etc...): ");
    fgets(novo.especie, MAX_LIMITE, stdin);
    novo.especie[strcspn(novo.especie, "\n")] = 0;

    printf("Raça: ");
    fgets(novo.raca, MAX_LIMITE, stdin);
    novo.raca[strcspn(novo.raca, "\n")] = 0;

    printf("Idade: ");
    scanf("%d", &novo.idade);
    getchar();

    printf("Nome do tutor/dono: ");
    fgets(novo.dono, MAX_LIMITE , stdin);
    novo.dono[strcspn(novo.dono, "\n")] = 0;

    lista[*total] = novo;
    (*total)++;
    
    printf("Animal cadastrado com sucesso!\n");
}

//2
void consultarAnimais(Animal lista[], int total) {
    int encontrados = 0;
    printf("\n--- Lista de Animais Cadastrados ---\n");
    
    for (int i = 0; i < total; i++) {
        if (lista[i].ativo == 1) {
            printf("ID: %d | Nome: %s | Espécie: %s | Raça: %s | Idade: %d anos | Dono: %s\n",
                   lista[i].id, lista[i].nome, lista[i].especie, lista[i].raca, lista[i].idade, lista[i].dono);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum animal cadastrado ou ativo no momento.\n");
    }
}
//3
void alterarAnimal(Animal lista[], int total) {
    int id, indice;
    
    printf("\n--- Alterar Dados do Animal ---\n");
    printf("Digite o ID do animal que deseja alterar: ");
    scanf("%d", &id);
    getchar();

    indice = buscarPorId(lista, total, id);

    if (indice != -1) {
        printf("Modificando dados de: %s\n", lista[indice].nome);
        
        printf("Novo Nome: ");
        fgets(lista[indice].nome,MAX_LIMITE, stdin);
        lista[indice].nome[strcspn(lista[indice].nome, "\n")] = 0;

        printf("Nova Espécie: ");
        fgets(lista[indice].especie, MAX_LIMITE, stdin);
        lista[indice].especie[strcspn(lista[indice].especie, "\n")] = 0;

        printf("Nova Raça: ");
        fgets(lista[indice].raca, MAX_LIMITE, stdin);
        lista[indice].raca[strcspn(lista[indice].raca, "\n")] = 0;

        printf("Nova Idade: ");
        scanf("%d", &lista[indice].idade);
        getchar();

        printf("Novo Tutor: ");
        fgets(lista[indice].dono, MAX_LIMITE, stdin);
        lista[indice].dono[strcspn(lista[indice].dono, "\n")] = 0;

        printf("Dados atualizados com sucesso!\n");
    } else {
        printf("Animal com ID %d não encontrado ou inativo.\n", id);
    }
}

// 4
void excluirAnimal(Animal lista[], int total) {
    int id, indice;

    printf("\n--- Excluir Registro de Animal ---\n");
    printf("Digite o ID do animal que deseja excluir: ");
    scanf("%d", &id);
    getchar();

    indice = buscarPorId(lista, total, id);

    if (indice != -1) {

        lista[indice].ativo = 0;
        printf("Animal '%s' excluído com sucesso do sistema!\n", lista[indice].nome);
    } else {
        printf("Animal com ID %d não encontrado ou já excluído.\n", id);
    }
}

int buscarPorId(Animal lista[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (lista[i].id == id && lista[i].ativo == 1) {
            return i; 
        }
    }
    return -1;
}