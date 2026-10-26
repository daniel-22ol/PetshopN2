#include <stdio.h>
#include <string.h>

#define MAX_ITENS 50
#define MAX_TENTATIVAS 3

char funcionario[30];

char nome_cliente[50];
char telefone_cliente[20];
int tem_cliente = 0;

char nome_pet[50];
char especie_pet[20];
char raca_pet[30];
char porte_pet[20];
int porte_codigo = 0;
int tem_pet = 0;

char nomes_categorias[3][20] = {"ALIMENTOS", "ACESSORIOS", "HIGIENE"};

char nomes_produtos[3][3][30] = {
    {"Racao cao 10kg", "Racao gato 3kg", "Petisco"},
    {"Coleira", "Guia", "Caminha"},
    {"Shampoo", "Tapete higienico", "Escova"}
};

float precos_produtos[3][3] = {
    {120.00, 65.00, 15.00},
    {25.00, 30.00, 80.00},
    {18.00, 45.00, 22.00}
};

char desc_itens[MAX_ITENS][60];
int qtd_itens[MAX_ITENS];
float val_itens[MAX_ITENS];
int total_itens = 0;
float total_geral = 0;

void registrarItem(char descricao[], int quantidade, float valor) {
    if (total_itens >= MAX_ITENS) {
        printf("\n[ERRO] Limite de itens do atendimento atingido!\n");
        return;
    }
    strcpy(desc_itens[total_itens], descricao);
    qtd_itens[total_itens] = quantidade;
    val_itens[total_itens] = valor;
    total_itens++;
    total_geral += valor;
}

int login(void) {
    char usuario[30], senha[30];
    int tentativas = 0;

    while (tentativas < MAX_TENTATIVAS) {
        printf("\n===== LOGIN DO FUNCIONARIO =====\n");
        printf("Usuario: ");
        scanf(" %29[^\n]", usuario);
        printf("Senha: ");
        scanf(" %29[^\n]", senha);

        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "1234") == 0) {
            strcpy(funcionario, usuario);
            printf("\nBem-vindo(a), %s!\n", funcionario);
            return 1;
        }
        tentativas++;
        printf("Usuario ou senha incorretos! (%d/%d)\n", tentativas, MAX_TENTATIVAS);
    }
    printf("\nNumero maximo de tentativas atingido. Encerrando...\n");
    return 0;
}

void menuCadastros(void) {
    int opcao, escolha;

    do {
        printf("\n--------- CADASTROS ----------\n");
        printf(" 1 - Cadastrar cliente\n");
        printf(" 2 - Cadastrar pet\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nNome do cliente: ");
                scanf(" %49[^\n]", nome_cliente);
                printf("Telefone: ");
                scanf(" %19[^\n]", telefone_cliente);
                tem_cliente = 1;
                printf("=> Cliente cadastrado!\n");
                break;

            case 2:
                if (tem_cliente == 0) {
                    printf("\n[ERRO] Cadastre o cliente primeiro!\n");
                } else {
                    printf("\nNome do pet: ");
                    scanf(" %49[^\n]", nome_pet);

                    do {
                        printf("Especie (1 - Cao, 2 - Gato): ");
                        scanf("%d", &escolha);
                    } while (escolha != 1 && escolha != 2);
                    if (escolha == 1) strcpy(especie_pet, "Cao");
                    else strcpy(especie_pet, "Gato");

                    printf("Raca: ");
                    scanf(" %29[^\n]", raca_pet);

                    do {
                        printf("Porte (1 - Pequeno, 2 - Medio, 3 - Grande): ");
                        scanf("%d", &porte_codigo);
                    } while (porte_codigo < 1 || porte_codigo > 3);
                    if (porte_codigo == 1) strcpy(porte_pet, "Pequeno");
                    else if (porte_codigo == 2) strcpy(porte_pet, "Medio");
                    else strcpy(porte_pet, "Grande");

                    tem_pet = 1;
                    printf("=> Pet cadastrado!\n");
                }
                break;

            case 0:
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

float valorBanho(int porte) {
    switch (porte) {
        case 1:  return 40.00;
        case 2:  return 60.00;
        case 3:  return 80.00;
        default: return 0;
    }
}

float valorTosa(int tipo) {
    switch (tipo) {
        case 1:  return 35.00;
        case 2:  return 70.00;
        case 3:  return 90.00;
        default: return 0;
    }
}

float valorVeterinaria(int tipo) {
    switch (tipo) {
        case 1:  return 120.00;
        case 2:  return 80.00;
        case 3:  return 150.00;
        default: return 0;
    }
}

void menuTosa(void) {
    int tipo;
    float valor;

    printf("\n--- TIPO DE TOSA ---\n");
    printf(" 1 - Higienica   R$ %.2f\n", valorTosa(1));
    printf(" 2 - Completa    R$ %.2f\n", valorTosa(2));
    printf(" 3 - Na tesoura  R$ %.2f\n", valorTosa(3));
    printf(" 0 - Voltar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &tipo);

    if (tipo == 0) return;
    valor = valorTosa(tipo);
    if (valor == 0) {
        printf("\nOpcao invalida!\n");
        return;
    }
    if (tipo == 1) registrarItem("Tosa higienica", 1, valor);
    else if (tipo == 2) registrarItem("Tosa completa", 1, valor);
    else registrarItem("Tosa na tesoura", 1, valor);
    printf("=> Tosa adicionada: R$ %.2f\n", valor);
}

void menuVeterinaria(void) {
    int tipo;
    float valor;

    printf("\n--- VETERINARIA ---\n");
    printf(" 1 - Consulta  R$ %.2f\n", valorVeterinaria(1));
    printf(" 2 - Vacina    R$ %.2f\n", valorVeterinaria(2));
    printf(" 3 - Exame     R$ %.2f\n", valorVeterinaria(3));
    printf(" 0 - Voltar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &tipo);

    if (tipo == 0) return;
    valor = valorVeterinaria(tipo);
    if (valor == 0) {
        printf("\nOpcao invalida!\n");
        return;
    }
    if (tipo == 1) registrarItem("Veterinaria - Consulta", 1, valor);
    else if (tipo == 2) registrarItem("Veterinaria - Vacina", 1, valor);
    else registrarItem("Veterinaria - Exame", 1, valor);
    printf("=> Servico adicionado: R$ %.2f\n", valor);
}

void menuServicos(void) {
    int opcao;
    float valor;

    if (tem_pet == 0) {
        printf("\n[ERRO] Cadastre o cliente e o pet antes de escolher servicos!\n");
        return;
    }

    do {
        printf("\n---------- SERVICOS ----------\n");
        printf(" 1 - Banho\n");
        printf(" 2 - Tosa\n");
        printf(" 3 - Veterinaria\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                valor = valorBanho(porte_codigo);
                registrarItem("Banho", 1, valor);
                printf("=> Banho (porte %s) adicionado: R$ %.2f\n", porte_pet, valor);
                break;
            case 2:
                menuTosa();
                break;
            case 3:
                menuVeterinaria();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 0);
}

void menuCategoria(int cat) {
    int i, produto, quantidade;
    float valor;

    do {
        printf("\n--------- %s ----------\n", nomes_categorias[cat]);
        for (i = 0; i < 3; i++) {
            printf(" %d - %-18s R$ %.2f\n", i + 1, nomes_produtos[cat][i], precos_produtos[cat][i]);
        }
        printf(" 0 - Voltar\n");
        printf("Produto: ");
        scanf("%d", &produto);

        if (produto >= 1 && produto <= 3) {
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            
            if (quantidade <= 0) {
                printf("\nQuantidade invalida!\n");
            } else {
                valor = precos_produtos[cat][produto - 1] * quantidade;
                registrarItem(nomes_produtos[cat][produto - 1], quantidade, valor);
                printf("Valor: R$ %.2f\n=> Produto adicionado!\n", valor);
            }
        } else if (produto != 0) {
            printf("\nOpcao invalida!\n");
        }
    } while (produto != 0);
}

void menuProdutos(void) {
    int opcao;

    do {
        printf("\n---------- PRODUTOS ----------\n");
        printf(" 1 - Alimentos\n");
        printf(" 2 - Acessorios\n");
        printf(" 3 - Higiene\n");
        printf(" 0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuCategoria(0); break;
            case 2: menuCategoria(1); break;
            case 3: menuCategoria(2); break;
            case 0: break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

void comprovanteFinal(void) {
    int i;

    printf("\n==================================================\n");
    printf("              COMPROVANTE DE ATENDIMENTO\n");
    printf("==================================================\n");
    printf("Funcionario: %s\n", funcionario);
    if (tem_cliente)
        printf("Cliente: %s (Tel: %s)\n", nome_cliente, telefone_cliente);
    else
        printf("Cliente: (nao cadastrado)\n");
    if (tem_pet)
        printf("Pet: %s - %s, %s, porte %s\n", nome_pet, especie_pet, raca_pet, porte_pet);
    else
        printf("Pet: (nao cadastrado)\n");
    printf("--------------------------------------------------\n");

    if (total_itens == 0) {
        printf("Nenhum item registrado.\n");
    } else {
        for (i = 0; i < total_itens; i++) {
            printf("%-26s Qtd: %-3d R$ %8.2f\n", desc_itens[i], qtd_itens[i], val_itens[i]);
        }
    }
    printf("--------------------------------------------------\n");
    printf("TOTAL DO ATENDIMENTO:           R$ %8.2f\n", total_geral);
    printf("==================================================\n");
}

int main(void) {
    int opcao;

    if (!login()) {
        return 0;
    }

    do {
        printf("\n==============================\n");
        printf("     PETSHOP SCOOBY DOO\n");
        printf("==============================\n");
        printf(" 1 - Cadastros\n");
        printf(" 2 - Servicos\n");
        printf(" 3 - Produtos\n");
        printf(" 4 - Comprovante final\n");
        printf(" 0 - Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuCadastros(); break;
            case 2: menuServicos(); break;
            case 3: menuProdutos(); break;
            case 4: comprovanteFinal(); break;
            case 0: printf("\nEncerrando o sistema. Ate logo!\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

