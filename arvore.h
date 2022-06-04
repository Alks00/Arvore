#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no
{
    struct no *esq;
    struct no *dir;
    int chave;   
}No;

typedef struct arvore
{
    int quant;
    No *raiz;
}Tree;

Tree* criar_arvore(){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree -> raiz = NULL;
    tree -> quant = 0;
    return tree;
}

int altura(No* no){
    int altura_esq = 0, altura_dir = 0;

    if (no -> esq)
    {
        altura_esq = altura(no -> esq);
    }
    if (no -> dir)
    {
        altura_dir = altura(no -> dir);
    }

    return fmax(altura_dir,altura_esq) + 1;
    
}

void balancear(Tree* tree){

}

void adicionar(Tree* tree,int valor){
    no* proxNo = NULL;
    no* aux = NULL;


    No* no = (No*)malloc(sizeof(No));
    no -> chave = valor;
    no -> dir = NULL;
    no -> esq = NULL;

    if (tree -> raiz == NULL)
    {
        tree -> raiz = no;
    }else {
        proxNo = tree -> raiz;
        while (proxNo != NULL)
        {
            aux = proxNo;

            if (valor < proxNo -> chave)
            {
                proxNo = proxNo -> esq;
            }else if (valor > proxNo -> chave)
            {
                proxNo = proxNo -> dir;
            }else if (valor == proxNo -> chave)
            {
                return;
            }
        }

        if (valor < aux -> chave)
        {
            aux -> esq = no;
            tree -> quant++;
        }else if (valor > aux -> chave)
        {
            aux -> dir = no;
            tree -> quant++;
        }
        
        balancear(tree);
    }
    
    
}