#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(int argc, char const *argv[])
{
    int opc=0,chave;
    char info[10];
    Tree* tree;

    do
    {
        printf("===============Menu===============\n");
        printf("Selecione uma opção:\n");
        printf("1  - Criar Arvore\n");
        printf("2  - Adicionar\n");
        printf("3  - Remover\n");
        printf("4  - Imprimir\n");
        printf("5  - Altura\n");
        printf("6  - Quantidade de elementos\n");
        printf("7  - Buscar\n");
        printf("8  - Limpar Arvore\n");
        printf("9  - Sair\n");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:
            tree = criar_arvore();
            break;
        case 2:
            printf("Digite o codigo:\n");
            scanf("%d",&chave);
            getchar();
            printf("Digite o nome:\n");
            gets(info);
            printf("\n\n");
            adicionar(tree,chave,info);

            break;
        case 3:
            printf("Digite a chave:\n");
            scanf("%d", &chave);
            printf("\n\n");

            remover(tree->raiz,chave);
            break;
        case 4:
            imprimirEmOrdem(tree -> raiz);
            break;
        case 5:
            printf("A arvore possui altura: %d",altura(tree -> raiz));
            printf("\n\n");
            break;
        case 6:
            printf("A arvore possui %d elementos",quantidadeElementos(tree -> raiz));
            printf("\n\n");
            break;
        case 7:
            printf("Digite a chave:\n");
            scanf("%d", &chave);

            buscarElemento(tree->raiz, chave);
            break;
        case 8:
            liberarMemoria(tree -> raiz);
        break;
        
        default:
            break;
        }
    } while (opc < 9);

    return 0;
}
