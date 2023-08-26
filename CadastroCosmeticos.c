#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int casa, size;

FILE *pont_arq;

typedef struct
{
    int id;
    char marca[50];
    char produto[100];
    char cor[70];
    float preco;
    int ano_fabric;
    int ano_venc;
    float peso;
    char tipo_volume;
} droga;

void criar(droga *cadastros);
void adicionar(droga *cadastros);
void remover(droga *cadastros);
void editar(droga *cadastros);
void listar_arq(droga cadastro);
void listar_vet(droga *cadastros);
void salvar(droga cadastro, droga *cadastros);
void esvazia(droga *cadastros);
int validar_id(droga *cadastros, int id);

int main()
{
    int opc;
    droga *cadastros;
    droga cadastro;
    do
    {
        printf("\n___________________________________________________\n");
        printf("Digite a opcao:\n\n [1] Criar primeiro registro.");
        printf("\n [2] Adicionar registros.");
        printf("\n [3] Remover registros.");
        printf("\n [4] Editar registros.");
        printf("\n [5] Listagem completa dos dados salvos.");
        printf("\n [6] Listagem completa dos dados.");
        printf("\n [7] Salvar alteracoes no arquivo.");
        printf("\n [8] Carregar dados salvos.");
        printf("\n [0] Sair.");
        printf("\n___________________________________________________\n");
        scanf("%i", &opc);
        system("clear || cls");
        switch (opc)
        {
        case 1:
        {
            printf("Digite a quantidade inicial de cosmeticos a serem registrados: ");
            scanf("%i", &size);
            system("clear || cls");
            size++;
            cadastros = (droga *)malloc(size * sizeof(droga));
            esvazia(cadastros);
            criar(cadastros);
        }
        break;
        case 2:
            adicionar(cadastros);
            break;
        case 3:
            remover(cadastros);
            break;
        case 4:
            editar(cadastros);
            break;
        case 5:
            listar_arq(cadastro);
            break;
        case 6:
            listar_vet(cadastros);
            break;
        case 7:
            salvar(cadastro, cadastros);
            break;
        case 8:
            pont_arq = fopen("cosmeticos.dat", "r");
            size = 0;
            do
            {
                fread(&cadastro, sizeof(droga), 1, pont_arq);
                if (!feof(pont_arq))
                    size++;
            } while (!feof(pont_arq));
            fclose(pont_arq);
            size++;
            cadastros = (droga *)malloc(size * sizeof(droga));
            esvazia(cadastros);
            pont_arq = fopen("cosmeticos.dat", "r");
            fseek(pont_arq, 0, SEEK_SET);
            casa = 0;
            do
            {
                fread(&cadastro, sizeof(droga), 1, pont_arq);
                if (!feof(pont_arq))
                {
                    strcpy(cadastros[casa].marca, cadastro.marca);
                    strcpy(cadastros[casa].produto, cadastro.produto);
                    strcpy(cadastros[casa].cor, cadastro.cor);
                    cadastros[casa].ano_fabric = cadastro.ano_fabric;
                    cadastros[casa].ano_venc = cadastro.ano_venc;
                    cadastros[casa].id = cadastro.id;
                    cadastros[casa].preco = cadastro.preco;
                    cadastros[casa].peso = cadastro.peso;
                    cadastros[casa].tipo_volume = cadastro.tipo_volume;
                    casa++;
                }
            } while (!feof(pont_arq));
            fclose(pont_arq);
            printf("\n%i cosmeticos carregados para o vetor.", casa);
            break;
        case 0:
            printf("\nO nome dela eh Maura, oh mulher que machucou meu coracao :(\n");
            break;
        default:
            printf("\nCodigo invalido, tente novamente.");
        }
    } while (opc);
}

void criar(droga *cadastros)
{
    int validacao, id;
    getchar();
    for (casa = 0; casa < (size - 1); casa++)
    {
        printf("\n___________________________________________________\n");
        printf("Insira os dados do cosmetico %i:", casa);
        printf("\n___________________________________________________\n");
        do
        {
            printf("\nID: ");
            scanf("%i", &id);
            validacao = validar_id(cadastros, id);
            if (validacao == 1)
                printf("\nEste id ja esta em uso. Tente novamente.");
        } while (validacao == 1);
        cadastros[casa].id = id;
        getchar();
        printf("\nMarca: ");
        gets(cadastros[casa].marca);
        printf("\nProduto: ");
        gets(cadastros[casa].produto);
        printf("\nCor da embalagem: ");
        gets(cadastros[casa].cor);
        printf("\nPreco (em R$): ");
        scanf("%f", &cadastros[casa].preco);
        printf("\nAno de fabricacao: ");
        scanf("%i", &cadastros[casa].ano_fabric);
        printf("\nAno do vencimento: ");
        scanf("%i", &cadastros[casa].ano_venc);
        printf("\nPeso (em gramas): ");
        scanf("%f", &cadastros[casa].peso);
        do
        {
            getchar();
            printf("\nTipo do volume. 'L' ou 'S': ");
            scanf("%c", &cadastros[casa].tipo_volume);
        } while ((cadastros[casa].tipo_volume != 'l') && (cadastros[casa].tipo_volume != 's') && (cadastros[casa].tipo_volume != 'L') && (cadastros[casa].tipo_volume != 'S'));
        system("clear || cls");
    }
}

void adicionar(droga *cadastros)
{
    int qtd, id, validacao;
    printf("Digite a quantidade de cosmeticos que quer registrar agora: ");
    scanf("%i", &qtd);
    size = size + qtd;
    cadastros = (droga *)realloc(cadastros, size * sizeof(droga));
    for (casa; casa < (size - 1); casa++)
    {
        printf("\n___________________________________________________\n");
        printf("Insira os dados do cosmetico %i:", casa);
        printf("\n___________________________________________________\n");
        do
        {
            printf("\nID: ");
            scanf("%i", &id);
            validacao = validar_id(cadastros, id);
            if (validacao == 1)
                printf("\nEste id ja esta em uso. Tente novamente.");
        } while (validacao == 1);
        cadastros[casa].id = id;
        getchar();
        printf("\nMarca: ");
        gets(cadastros[casa].marca);
        printf("\nProduto: ");
        gets(cadastros[casa].produto);
        printf("\nCor da embalagem: ");
        gets(cadastros[casa].cor);
        printf("\nPreco (em R$): ");
        scanf("%f", &cadastros[casa].preco);
        printf("\nAno de fabricacao: ");
        scanf("%i", &cadastros[casa].ano_fabric);
        printf("\nAno do vencimento: ");
        scanf("%i", &cadastros[casa].ano_venc);
        printf("\nPeso (em gramas): ");
        scanf("%f", &cadastros[casa].peso);
        do
        {
            getchar();
            printf("\nTipo do volume. 'L' ou 'S': ");
            scanf("%c", &cadastros[casa].tipo_volume);
        } while ((cadastros[casa].tipo_volume != 'l') && (cadastros[casa].tipo_volume != 's') && (cadastros[casa].tipo_volume != 'L') && (cadastros[casa].tipo_volume != 'S'));
        system("clear || cls");
    }
    cadastros[size - 1].ano_fabric = 0;
}

void esvazia(droga *cadastros)
{

    int c1;
    for (c1 = 0; c1 < size; c1++)
    {
        cadastros[c1].ano_fabric = 0;
        cadastros[c1].ano_venc = 0;
        cadastros[c1].id = 0;
        cadastros[c1].preco = 0;
        cadastros[c1].peso = 0;
        cadastros[c1].tipo_volume = ' ';
        strcpy(cadastros[c1].marca, "");
        strcpy(cadastros[c1].produto, "");
        strcpy(cadastros[c1].cor, "");
    }
}

void remover(droga *cadastros)
{
    int id, c1, c2, c3, to_erase;
    printf("Digite o ID do cosmetico que deseja apagar dos registros: ");
    scanf("%i", &id);
    for (c1 = 0; c1 <= size; c1++)
    {
        if (cadastros[c1].id == id)
        {
            to_erase = c1;
            c1 = size + 10;
        }
    }
    for (c2 = to_erase; c2 < size; c2++)
    {
        c3 = c2 + 1;
        if (cadastros[c3].ano_fabric == 0)
        {
            cadastros[c2].ano_fabric = 0;
            cadastros[c2].ano_venc = 0;
            cadastros[c2].id = 0;
            cadastros[c2].preco = 0;
            cadastros[c2].peso = 0;
            cadastros[c2].tipo_volume = ' ';
            strcpy(cadastros[c2].marca, "");
            strcpy(cadastros[c2].produto, "");
            strcpy(cadastros[c2].cor, "");
            size--;
            cadastros = (droga *)realloc(cadastros, size * sizeof(droga));
            casa = c2;
            c2 = size + c2 + 1;
        }
        else
        {
            // cadastros[c2] = cadastros[c3];
            strcpy(cadastros[c2].marca, cadastros[c3].marca);
            strcpy(cadastros[c2].produto, cadastros[c3].produto);
            strcpy(cadastros[c2].cor, cadastros[c3].cor);
            cadastros[c2].ano_fabric = cadastros[c3].ano_fabric;
            cadastros[c2].ano_venc = cadastros[c3].ano_venc;
            cadastros[c2].id = cadastros[c3].id;
            cadastros[c2].preco = cadastros[c3].preco;
            cadastros[c2].peso = cadastros[c3].peso;
            cadastros[c2].tipo_volume = cadastros[c3].tipo_volume;
        }
    }
}

void editar(droga *cadastros)
{
    int id, code, c1, to_edit, validacao, edit_id;
    do
    {
        printf("\nDigite o id do cosmetico que deseja editar ou 0 para cancelar: ");
        scanf("%i", &id);
        system("clear || cls");
        if (id != 0)
        {
            to_edit = 0;
            for (c1 = 0; c1 < (size - 1); c1++)
            {
                if (cadastros[c1].id == id)
                {
                    to_edit = c1;
                    c1 = size + 1;
                    printf("Digite o campo que deseja editar: ");
                    printf("\n [1] ID.");
                    printf("\n [2] Marca.");
                    printf("\n [3] Produto.");
                    printf("\n [4] Cor da embalagem.");
                    printf("\n [5] Preco.");
                    printf("\n [6] Ano de fabricacao.");
                    printf("\n [7] Ano do vencimento.");
                    printf("\n [8] Peso do produto.");
                    printf("\n [9] Tipo do volume.");
                    scanf("%i", &code);
                    system("clear || cls");
                    getchar();
                    switch (code)
                    {
                    case 1:
                    {
                        do
                        {
                            printf("\nDigite o novo ID: ");
                            scanf("%i", &edit_id);
                            validacao = validar_id(cadastros, edit_id);
                            if (validacao == 1)
                                printf("\nEste id ja esta em uso. Tente novamente.");
                        } while (validacao == 1);
                        cadastros[to_edit].id = edit_id;
                    }
                    break;
                    case 2:
                    {
                        printf("\nDigite a nova marca: ");
                        gets(cadastros[to_edit].marca);
                    }
                    break;
                    case 3:
                    {
                        printf("\nDigite o novo produto: ");
                        gets(cadastros[to_edit].produto);
                    }
                    break;
                    case 4:
                    {
                        printf("\nDigite a nova cor da embalagem: ");
                        gets(cadastros[to_edit].cor);
                    }
                    break;
                    case 5:
                    {
                        printf("\nDigite o novo preco: ");
                        scanf("%f", &cadastros[to_edit].preco);
                    }
                    break;
                    case 6:
                    {
                        printf("\nDigite o novo ano de fabricacao: ");
                        scanf("%i", &cadastros[to_edit].ano_fabric);
                    }
                    break;
                    case 7:
                    {
                        printf("\nDigite o novo ano do vencimento: ");
                        scanf("%i", &cadastros[to_edit].ano_venc);
                    }
                    break;
                    case 8:
                    {
                        printf("\nDigite o novo peso (em gramas): ");
                        scanf("%f", &cadastros[to_edit].peso);
                    }
                    break;
                    case 9:
                    {
                        // do
                        //{
                        // getchar();
                        printf("\nDigite o novo tipo do volume. 'L' ou 'S': ");
                        scanf("%c", &cadastros[to_edit].tipo_volume);
                        // getchar();
                        while ((cadastros[to_edit].tipo_volume != 'l') && (cadastros[to_edit].tipo_volume != 's') && (cadastros[to_edit].tipo_volume != 'L') && (cadastros[to_edit].tipo_volume != 'S'))
                        {
                            getchar();
                            printf("\n'L' ou 'S': ");
                            scanf("%c", &cadastros[to_edit].tipo_volume);
                        }
                        to_edit = 9999; // para desbugar um loop que essa opcao gerava (;
                    }
                    }
                }
            }
            if (to_edit == 0)
            {
                printf("\nID inexistente, tente novamente.\n");
            }
        }
        else
        {
            break;
        }
    } while (to_edit == 0);
    system("clear || cls");
}

void listar_vet(droga *cadastros)
{
    int c1;
    printf("\n*****COSMETICOS CADASTRADOS NO VETOR:*****");
    printf("\n___________________________________________________\n");
    for (c1 = 0; c1 < casa; c1++)
    {
        printf("\nID: %i", cadastros[c1].id);
        printf("\nMarca: %s", cadastros[c1].marca);
        printf("\nProduto: %s", cadastros[c1].produto);
        printf("\nCor da embalagem: %s", cadastros[c1].cor);
        printf("\nPreco: R$ %.2f", cadastros[c1].preco);
        printf("\nAno de fabricacao: %i", cadastros[c1].ano_fabric);
        printf("\nAno do vencimento: %i", cadastros[c1].ano_venc);
        printf("\nPeso: %.2fg", cadastros[c1].peso);
        printf("\nTipo do volume: %c", cadastros[c1].tipo_volume);
        printf("\n___________________________________________________\n");
    }
}

void salvar(droga cadastro, droga *cadastros)
{
    // implementar função que salva só as linhas que foram alteradas
    int c1;
    pont_arq = fopen("cosmeticos.dat", "w");
    printf("Salvando...");
    // para testar:
    // fwrite(&cadastros, sizeof(droga), (size-1), pont_arq);
    for (c1 = 0; c1 < (size - 1); c1++)
    {
        // para testar:
        // fwrite(&cadastros[c1], sizeof(droga), 1, pont_arq);
        strcpy(cadastro.marca, cadastros[c1].marca);
        strcpy(cadastro.produto, cadastros[c1].produto);
        strcpy(cadastro.cor, cadastros[c1].cor);
        cadastro.ano_fabric = cadastros[c1].ano_fabric;
        cadastro.ano_venc = cadastros[c1].ano_venc;
        cadastro.id = cadastros[c1].id;
        cadastro.preco = cadastros[c1].preco;
        cadastro.peso = cadastros[c1].peso;
        cadastro.tipo_volume = cadastros[c1].tipo_volume;
        fwrite(&cadastro, sizeof(droga), 1, pont_arq);
    }
    fclose(pont_arq);
}

void listar_arq(droga cadastro)
{
    pont_arq = fopen("cosmeticos.dat", "r");
    fseek(pont_arq, 0, SEEK_SET);
    printf("\n*****COSMETICOS CADASTRADOS NO ARQUIVO:*****");
    printf("\n___________________________________________________\n");
    do
    {
        fread(&cadastro, sizeof(droga), 1, pont_arq);
        if (!feof(pont_arq))
        {
            printf("\nID: %i", cadastro.id);
            printf("\nMarca: %s", cadastro.marca);
            printf("\nProduto: %s", cadastro.produto);
            printf("\nCor da embalagem: %s", cadastro.cor);
            printf("\nPreco: R$ %.2f", cadastro.preco);
            printf("\nAno de fabricacao: %i", cadastro.ano_fabric);
            printf("\nAno do vencimento: %i", cadastro.ano_venc);
            printf("\nPeso: %.2fg", cadastro.peso);
            printf("\nTipo do volume: %c", cadastro.tipo_volume);
            printf("\n___________________________________________________\n");
        }
    } while (!feof(pont_arq));
    fclose(pont_arq);
}

int validar_id(droga *cadastros, int id)
{
    int c1;
    for (c1 = 0; c1 < casa; c1++)
    {
        if (cadastros[c1].id == id)
        {
            return 1;
            break;
        }
    }
    return 0;
}