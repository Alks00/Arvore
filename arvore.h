#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct no
{
    struct no *esq;
    struct no *dir;
    int chave;
    char info[10];   
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

void liberarMemoria(No* no){
    if(no == NULL){
        return;
    }

    liberarMemoria(no -> esq);
    liberarMemoria(no -> dir);

    free(no);
}

void quantidadeElementos(Tree* tree){
    printf("A arvore possui %d elementos\n", tree -> quant);
}

void imprimirEmOrdem(No* no){
    if(no != NULL){
        if (no -> esq != NULL)
        {
            imprimirEmOrdem(no -> esq);
        }

        printf("%d - %s\n", no -> chave, no -> info);

        if (no -> dir != NULL)
        {
            imprimirEmOrdem(no -> dir);
        }
    }
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

int fator_balanceamento(No* no){
    int fator = 0;

    if(no -> esq){
        fator += altura(no -> esq);
    }

    if(no -> dir){
        fator -= altura(no -> dir);
    }

    return fator;
}

No* rotacionarEsqEsq(No* no){
    No* aux = no;
    No* esq = aux -> esq;

    aux -> esq = esq -> dir;
    esq -> dir = aux;

    return esq;
}

No* rotacionarEsqDir(No* no){
    No* aux = no;
    No* esq = aux -> esq;
    No* dir = esq -> dir;

    aux -> esq = dir -> dir;
    esq -> dir = dir -> esq;
    dir -> esq = esq;
    dir -> dir = aux;
}

No* rotacionarDirEsq(No* no){
    No* aux = no;
    No* dir = aux -> dir;
    No* esq = dir -> esq;

    aux -> dir = esq -> esq;
    dir -> esq = esq -> dir;
    esq -> dir = dir;
    esq -> esq = aux;

    return esq;
}

No* rotacionarDirDir(No* no){
    No* aux = no;
    No* dir = aux -> dir;

    aux -> dir = dir -> esq;
    dir -> esq = aux;

    return dir;
}

No* balancear_No(No* no){
    No* noBalanceado = NULL;

    if (no -> esq)
    {
        no -> esq = balancear_No(no -> esq);
    }

    if (no -> dir)
    {
        no -> dir = balancear_No(no -> dir);
    }

    int fb = fator_balanceamento(no);
    
    if (fb >=2)
    {
        if (fator_balanceamento(no -> esq) <= -1)
        {
            noBalanceado = rotacionarEsqDir(no);
        }else
        {
            noBalanceado = rotacionarEsqEsq(no);
        }
    }else if (fb <= -2)
    {
        if (fator_balanceamento(no -> dir) >= 1)
        {
            noBalanceado = rotacionarDirEsq(no);
        }else
        {
            noBalanceado = rotacionarDirDir(no);
        }
    }else
    {
        noBalanceado = no;
    }
    
    return noBalanceado;
}

void balancear(Tree* tree){
    No * nova_raiz = NULL;

	nova_raiz = balancear_No (tree -> raiz);

	if (nova_raiz != tree -> raiz){
		tree -> raiz = nova_raiz;
	}
}

void adicionar(Tree* tree,int valor,char *info){
    No* proxNo = NULL;
    No* aux = NULL;


    No* no = (No*)malloc(sizeof(No));

    no -> chave = valor;
    no -> dir = NULL;
    no -> esq = NULL;
    strcpy(no -> info,info);

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

No* remover(No* no,int chave){
    if (no -> chave == chave)
    {
        if (no -> dir == NULL && no -> esq == NULL)
        {
            return NULL;
        }else
        {
            if (no -> dir == NULL && no -> esq != NULL)
            {
                return no -> esq;
            }else if (no -> dir != NULL && no -> esq == NULL)
            {
                return no -> dir;
            }else
            {
                No* aux = no -> dir;
                while (aux -> esq != NULL)
                {
                    aux = aux -> esq;
                }
                strcpy(no -> info,aux -> info);
                aux -> chave = chave;
                no -> dir = remover(no -> dir, chave);
                free(aux);
            }
        }
    }else
    {
        if (no -> chave > chave)
        {
            if (no -> esq != NULL)
            {
                no -> esq = remover(no -> esq, chave);
            }
        }else if (no -> chave < chave)
        {
            if (no -> dir != NULL)
            {
                no -> dir = remover(no -> dir, chave);
            }
        }
    }
    return no;  
}

/*void remover(No* no,int chave){
    No* aux = no;
    No* ant;

    while (aux -> chave != chave){
        if (aux -> chave > chave)
        {
            ant = aux;
            aux = aux -> esq;
        }else
        {
            ant = aux;
            aux = aux -> dir;
        }
    }

    if (aux -> dir == NULL && aux -> esq == NULL)
    {
        free(aux);
    }else if(aux -> dir == NULL && aux -> esq != NULL)
    {
        if (ant -> dir == aux)
        {
            ant -> dir = aux -> esq;
        }else
        {
            ant -> esq = aux -> esq;
        }
        free(aux);
    }else if (aux -> dir != NULL && aux -> esq == NULL)
    {
        if (ant -> dir == aux)
        {
            ant -> dir = aux -> dir;
        }else
        {
            ant -> esq = aux -> dir;
        }
        free(aux);
    }else
    {
        
    }
    
    
}
*/
void buscarElemento(No* no,int chave){
    No* aux;
    aux = no;
    
    if (aux == NULL)
    {
        printf("Arvore vazia!\n");
    }else{
        do
        {
            if (aux -> chave > chave)
            {
                aux = aux -> esq;
            }else if (aux -> chave < chave)
            {
                aux = aux -> dir;
            }
        } while (aux -> chave != chave);
    }    
    
    printf("%d - %s\n",aux -> chave, aux -> info);
    
}