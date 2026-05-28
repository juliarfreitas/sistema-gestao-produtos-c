#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 10
#define TAM_NOME 50

char produtos[MAX_PRODUTOS][TAM_NOME];
int totalProdutos = 0;

// Protótipos
void Menu();
int Resposta();
void ListarProdutos();
bool ValidarResposta(int opcao);
void ExibirMenu();
void MostrarCabecalho();
void LimparTela();
void CadastrarProdutos();
void ReordenarProdutos(int indice);
int BuscarPorNome();
void ExcluirProdutos();
bool Sair();
bool ConfirmarSaida();
void SalvarProdutoEmArquivo();
void CarregarProdutosDoArquivo();

// ================= FUNÇÕES =================

void LimparTela() {
    system("cls"); // Windows
}

void MostrarCabecalho() {
    printf("=====================================\n");
    printf("   SISTEMA DE GESTÃO DE PRODUTOS\n");
    printf("   Autor: JULIA REBOUCAS FREITAS\n");
    printf("=====================================\n\n");
}

void Menu() {
    printf("1 - Listar Produtos\n");
    printf("2 - Cadastrar Produto\n");
    printf("3 - Excluir Produto\n");
    printf("4 - Buscar Produto\n");
    printf("5 - Sair\n\n");
}

int Resposta() {
    int opcao;
    printf("Escolha uma opção (1-5): ");
    scanf("%d", &opcao);
    return opcao;
}

void ListarProdutos() {
    printf("\n📦 LISTA DE PRODUTOS:\n");

    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        printf("%d | %s\n", i + 1, produtos[i]);
    }
}

void CadastrarProdutos() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", produtos[totalProdutos]);

    totalProdutos++;
    printf("✅ Produto cadastrado com sucesso!\n");
}

void ReordenarProdutos(int indice) {
    for (int i = indice; i < totalProdutos - 1; i++) {
        strcpy(produtos[i], produtos[i + 1]);
    }
}

int BuscarPorNome() {
    char nome[TAM_NOME];

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i], nome) == 0) {
            return i;
        }
    }

    return -1;
}

void ExcluirProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto para excluir!\n");
        return;
    }

    ListarProdutos();

    int numero;
    printf("Digite o número do produto que deseja excluir: ");
    scanf("%d", &numero);

    if (numero < 1 || numero > totalProdutos) {
        printf("Número inválido!\n");
        return;
    }

    int indice = numero - 1;
    ReordenarProdutos(indice);
    totalProdutos--;

    printf("🗑️ Produto excluído com sucesso!\n");
}

void SalvarProdutoEmArquivo() {
    FILE *arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar arquivo!\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%s\n", produtos[i]);
    }

    fclose(arquivo);
}

void CarregarProdutosDoArquivo() {
    FILE *arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL) return;

    while (fgets(produtos[totalProdutos], TAM_NOME, arquivo) != NULL) {
        produtos[totalProdutos][strcspn(produtos[totalProdutos], "\n")] = '\0';
        totalProdutos++;
    }

    fclose(arquivo);
}

bool ConfirmarSaida() {
    char letra;

    printf("Tem certeza que deseja sair? (S/N): ");
    scanf(" %c", &letra);

    if (letra == 'n' || letra == 'N') {
        return false;
    }

    SalvarProdutoEmArquivo();
    return true;
}

bool Sair() {
    return ConfirmarSaida();
}

bool ValidarResposta(int opcao) {
    bool continuar = true;

    switch (opcao) {
        case 1:
            ListarProdutos();
            break;

        case 2:
            CadastrarProdutos();
            break;

        case 3:
            ExcluirProdutos();
            break;

        case 4: {
            int indice = BuscarPorNome();
            if (indice != -1) {
                printf("Produto encontrado: %s\n", produtos[indice]);
            } else {
                printf("Produto não encontrado.\n");
            }
            break;
        }

        case 5:
            continuar = !Sair();
            break;

        default:
            printf("Opção inválida!\n");
    }

    return continuar;
}

void ExibirMenu() {
    int opcao;
    bool continuar;

    do {
        LimparTela();
        MostrarCabecalho();
        Menu();
        opcao = Resposta();
        continuar = ValidarResposta(opcao);

        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();

    } while (continuar);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    CarregarProdutosDoArquivo();
    ExibirMenu();
    return 0;
}
