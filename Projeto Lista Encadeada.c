#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define TAM 255

typedef struct node{
    char nome[TAM];
    int rg;
    struct node *proximo;
}node;

typedef struct lista{
    struct node *inicio;
    int tamanho;
}lista;

void limpaTela(){
    system("CLS");
}

void imprimeEncadeada(lista *listaEncadeada){

    //Ponteiro cursor auxiliar.
    node *atual = listaEncadeada->inicio;

    while( atual != NULL){
        printf("Nome: %s, RG:%d \n", atual->nome, atual->rg);
        atual = atual->proximo;
    }

}

void addComecoEncadeada(lista *listaEncadeada, char nome[], int rg){

    //cria um novo node a ser colocado
    node *novoNode = (node*) malloc(sizeof(node));

    //novoNode->nome = nome
    strcpy(novoNode->nome, nome);
    novoNode->rg = rg;

    //direciona o ponteiro do novo node ao antigo node inicial da lista
    novoNode->proximo = listaEncadeada->inicio;

    //direciona o ponteiro do inicio para o novo node;
    listaEncadeada->inicio = novoNode;

    //aumenta do tamanho da lista
    listaEncadeada->tamanho += 1;

}

void addFimEncadeada(lista *listaEncadeada, char nome[], int rg){

    //cria um novo node com o proximo sendo NULL
    //depois percorre toda a lista ate o ultimo node e faz ele apontar para o novo node.

    node *novoNode = (node*) malloc(sizeof(node));

    //novoNode->nome = nome
    strcpy(novoNode->nome, nome);
    novoNode->rg = rg;

    novoNode->proximo = NULL;

    //percorre a lista inteira ate o ultimo node

    //Ponteiro cursor auxiliar.
    node *atual = listaEncadeada->inicio;

    while(atual != NULL){

        //ocasião na qual ele chega ao ultimo node e o direciona para o novo.
        if(atual->proximo == NULL){
            atual->proximo = novoNode;
            listaEncadeada->tamanho += 1;
            return;
        }

        //atualiza o cursor
        atual = atual->proximo;
    }

}

void addPosicaoEncadeada(lista *listaEncadeada, char nome[], int rg, int posicao){

    //cursor temporario para percorrer a lista e um contador.
    node *atual = listaEncadeada->inicio;
    int cont = 0;

    //novo node
    node *novoNode = (node*) malloc(sizeof(node));

    //novoNode->nome = nome
    strcpy(novoNode->nome, nome);
    novoNode->rg = rg;
    //temporariamente ele não tem um node para apontar
    novoNode->proximo = NULL;

    while(cont <= posicao){

        //quando chega um antes da posicao desejada.
        if(cont == posicao - 1){

            //aux do node, ele precisa gravar o proximo do novo elemento
            node *aux = (node*) malloc(sizeof(node));

            //guardando o proximo do node a ser substituido
            aux->proximo = atual->proximo;

            //linkando o node anterior ao novo
            atual->proximo = novoNode;

            //linkando o novo ao antigo da posicao.
            novoNode->proximo = aux->proximo;

            free(aux);
        }

        //atualiza para o proximo node
        atual = atual->proximo;
        cont++;
    }

    listaEncadeada->tamanho += 1;

}

void removeInicioEncadeada(lista *listaEncadeada){

    //Lista de apenas um node.
    if(listaEncadeada->inicio->proximo == NULL){

        //cria um novo node a ser colocado
        node *novoNode = (node*) malloc(sizeof(node));

        //novoNode->nome = nome
        strcpy(novoNode->nome, "-");
        novoNode->rg = 0;
        novoNode->proximo = NULL;

        listaEncadeada->inicio = novoNode;
        listaEncadeada->tamanho -= 1;

    }else{
        //faz o ponteiro principal para o proximo valor;
        listaEncadeada->inicio = listaEncadeada->inicio->proximo;
        listaEncadeada->tamanho -= 1;
    }


}

void removeFinalEncadeada(lista *listaEncadeada){



    node *atual = listaEncadeada->inicio;

    while(atual->proximo != NULL && atual->proximo->proximo != NULL){

        //percorrendo ate o penultimo nó
        atual = atual->proximo;

    }

    //agora o 'atual' é o penultimo nó, e o atual ->proximo é o ultimo nó.

    free(atual->proximo);
    atual->proximo = NULL;
    listaEncadeada->tamanho--;

}

void removePosicaoEncadeada(lista *listaEncadeada, int posicao){



    //Ponteiro cursor auxiliar
    node *atual = listaEncadeada->inicio;

    //contador de posições
    int cont = 0;

    while(cont <= posicao){

        if(cont == posicao - 1){

            node *aux = (node*) malloc(sizeof(node));

            //aux recebe o elemento a ser eliminado.
            aux = atual->proximo;

            //faz com que o proximo pule um elemento.
            atual->proximo = aux->proximo;

            free(aux);

            listaEncadeada->tamanho--;

        }
        //Passa o cursor para o proximo elemento
        atual = atual->proximo;
        cont++;
    }

}

char* retornaNomeEncadeada(lista *listaEncadeada, int rg){

    node *atual = listaEncadeada->inicio;

    while(atual != NULL){

        if(atual->rg == rg){

            char* nome = (char*)malloc(TAM * sizeof(char));

            //nome = atual->nome
            strcpy(nome, atual->nome);
            return nome;
        }

        //percorrendo a lista
        atual = atual->proximo;

    }

    char* nomeNaoEncontrado = (char*)malloc(TAM * sizeof(char));
    strcpy(nomeNaoEncontrado, "NaoEncontrado");
    return nomeNaoEncontrado;

}

int main (){

    //localizando o programa para pt_br.
    setlocale(LC_ALL, "Portuguese");

    //variavel auxiliar para a escolha da operação;
    int funcaoDesejada = 1;

    //inicializando o inicio da lista encadeada.
    lista *listaEncadeada = (lista*)malloc(sizeof(lista));
    listaEncadeada->inicio = NULL;
    listaEncadeada->tamanho = 0;

    while(funcaoDesejada < 9 && funcaoDesejada > 0){

        printf("\n");
        imprimeEncadeada(listaEncadeada);
        printf("\n");

        printf("Operações. \n");
        printf("1 - Inserção de um node no inicio da lista\n");
        printf("2 - Insercao de um node no fim da lista \n");
        printf("3 - Insercao de um node na posicao N \n");
        printf("4 - Retirar um node do inicio da lista \n");
        printf("5 - Retirar um node no fim da lista \n");
        printf("6 - Retirar um node na posicao N \n");
        printf("7 - Procurar um node com o campo RG \n");
        printf("8 - Imprimir a Lista. \n");
        printf("9 - Sair do sistema. \n");
        printf("\nTAMANHO DA LISTA %d \n", listaEncadeada->tamanho);
        printf("\nEscolha um numero e pressione ENTER: \n");

        //pega a função desejada do usuario.
        scanf("%d", &funcaoDesejada);

        //basta ler
        limpaTela();

        //Variaveis para valores novos
        char nome[TAM];
        int rg,posicao;

        //switch case para decição
        switch(funcaoDesejada){

            case 1:
                printf("1 - Inserção de um node no inicio da lista\n");

                //obtendo nome do usuario.
                printf("Digite um nome: ");
                getchar();
                scanf("%[^\n]", nome);

                //obtendo rg do usuario.
                printf("Digite um rg: ");
                scanf("%d", &rg);

                addComecoEncadeada(listaEncadeada, nome, rg);
                break;

            case 2:
                printf("2 - Insercao de um node no fim da lista \n");

                //obtendo nome do usuario.
                printf("Digite um nome: ");
                getchar();
                scanf("%[^\n]", nome);

                //obtendo rg do usuario.
                printf("Digite um rg: ");
                scanf("%d", &rg);

                if(listaEncadeada->tamanho == 0){
                    addComecoEncadeada(listaEncadeada, nome, rg);
                }else{
                    addFimEncadeada(listaEncadeada, nome, rg);
                }

                break;

            case 3:
                printf("3 - Insercao de um node na posicao N \n");

                //obtendo nome do usuario.
                printf("Digite a posição: ");
                scanf("%d", &posicao);

                //obtendo nome do usuario
                printf("Digite um nome: ");
                getchar();
                scanf("%[^\n]", nome);

                //obtendo rg do usuario.
                printf("Digite um rg: ");
                scanf("%d", &rg);

                if(posicao == 0){
                    addComecoEncadeada(listaEncadeada, nome, rg);
                    break;
                }else if(posicao == listaEncadeada->tamanho - 1){
                    addFimEncadeada(listaEncadeada, nome, rg);
                    break;
                }else{
                    addPosicaoEncadeada(listaEncadeada, nome, rg, posicao);
                    break;
                }

            case 4:
                printf("4 - Retirar um node do inicio da lista \n");

                if(listaEncadeada->tamanho == 0){
                    printf("Lista Vazia!");
                    break;
                }else{
                    removeInicioEncadeada(listaEncadeada);
                    break;
                }

            case 5:
                printf("5 - Retirar um node no fim da lista \n");

                if(listaEncadeada->tamanho == 0){
                    printf("Lista Vazia!");
                    break;
                }else if(listaEncadeada->tamanho == 1){
                     removeInicioEncadeada(listaEncadeada);
                    break;
                }else{
                    removeFinalEncadeada(listaEncadeada);
                    break;
                }

            case 6:
                printf("6 - Retirar um node na posicao N \n");

                //obtendo nome do usuario.
                printf("Digite a posição: ");
                scanf("%d", &posicao);

                if(posicao == 0){
                    removeInicioEncadeada(listaEncadeada);
                }else if(posicao == listaEncadeada->tamanho - 1){
                    removeFinalEncadeada(listaEncadeada);
                }else{
                    removePosicaoEncadeada(listaEncadeada,posicao);
                }

            case 7:
                printf("7 - Procurar um node com o campo RG \n");

                //obtendo rg a ser buscado do usuario.
                printf("Digite um rg: ");
                scanf("%d", &rg);

                printf("%s\n ",retornaNomeEncadeada(listaEncadeada, rg));


            case 8:
                imprimeEncadeada(listaEncadeada);
                break;

        }

    }

}
