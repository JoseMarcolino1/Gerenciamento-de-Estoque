#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tam 10

typedef struct Tpilha{
    int codigo;
    char nome[50];
    int quantidade;
    struct Tpilha *ant;
} Tpilha;

typedef struct pilha{
   Tpilha *topo;
}pilha;


typedef struct Tfila {
    char nome[50]; //nome da pessoa
    int nvl_dif;// regra das prioridades
    struct Tfila *prox;
} Tfila;

typedef struct {
   Tfila *inicio;
   Tfila *fim;
} fila;

void create_pilha(pilha *p){
  p->topo =NULL;
}


//função pilha vazia
int   pilha_vazia(pilha *p){

   if(p->topo ==NULL){
    return 1; //Pilha está vazia
   }else{
    return 0; //pilha tem elementos
   }
}


void empilha(pilha *p,int codigo,char nome[],int quantidade){

    Tpilha *novo=malloc(sizeof(Tpilha));
    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->codigo = codigo;
    novo->ant = p->topo;//anterior aponte para o de baixo
    p->topo = novo;

    novo=NULL;
    free(novo);
    return;

}

void desempilha(pilha *p){

    if(pilha_vazia(p)==1){
        printf("pilha vazia\n");
        printf("nao é possivel remover \n");
        getch();
    }else
    {
        Tpilha *aux = malloc(sizeof(Tpilha));
        aux = p->topo;
        p->topo = aux->ant;
        aux ->ant= NULL;
        free(aux);
    }

}

// função para diminuir a quantidade de um item na pilha
void diminui_quantidade(pilha *p, pilha *p2, int codigo){
    Tpilha *atual = p->topo;
    //laço para percorrer a fila ate achar o item que contem o msm codigo
    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->ant;
    }
    //quando achar o item retirar 1;
    if (atual != NULL) {
        atual->quantidade--;
        if(atual->quantidade <= 0)
        {
            printf("Estamos sem esse item em estoque.Iremos pedi-lo e assim que chegar te informaremos ");
            empilha(p2,atual->codigo,atual->nome,atual->quantidade);
            getch();
        }else
        {
            printf("Voce realizou o pedido com sucesso. Aguarde um instante que iremos te entregar ");
            getch();
        }
    }
}


void createfila(fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int fila_vazia(fila *f) {
    if (f->inicio == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void inserir_prioridade(fila *f, char nome[], int nvl_dif) {
    //cria um novo
    Tfila *novo = (Tfila*) malloc(sizeof(Tfila));
    strcpy(novo->nome, nome);
    novo->nvl_dif = nvl_dif;
    novo->prox = NULL;

    if (fila_vazia(f)) { //primeira vez
        f->inicio = novo; //inicio aponta para novo
        f->fim = novo; //Ajusta-se o fim
    } else {
        if (nvl_dif > 1) {
            //se o primeiro elemento da fila for menor que 3(nivel mais alto) não é prioritario
            if (f->inicio->nvl_dif < 2) {
                //insere o novo nó como prioridade no inicio da fila
                novo->prox = f->inicio;
                f->inicio = novo;
            } else {
                Tfila *aux = f->inicio;
                while (aux->prox != NULL && aux->prox->nvl_dif > 1) {
                    aux = aux->prox;
                }
                novo->prox = aux->prox;
                aux->prox = novo;
            }
        } else { //insere no final da fila - não é prioridade
            f->fim->prox = novo;
            f->fim = novo; //Ajusta-se o fim
        }
    }
}

// função para desenfileirar o primeiro elemento da fila
int desenfileirar(fila *f, Tfila *elemento) {
    if (fila_vazia(f)) {
        return 0; // fila vazia, não há elementos para desenfileirar
    } else {
        Tfila *aux = f->inicio;
        *elemento = *aux; // copia o primeiro elemento da fila para a variável elemento

        f->inicio = f->inicio->prox; // atualiza o inicio da fila
        free(aux); // libera a memória alocada para o elemento desenfileirado

        if (f->inicio == NULL) {
            f->fim = NULL; // se a fila ficar vazia, o fim também deve ser atualizado
        }

        return 1; // elemento desenfileirado com sucesso
    }
}



void mostra_fila(fila *f){
    Tfila *aux = f->inicio;
    while(aux != NULL) {
        printf("\n| Nome do cliente:%s \n| nivel do problema: %d ", aux->nome, aux->nvl_dif);
        aux = aux->prox; //incrementa o ponteiro
    }
    printf("|");
}

void mostrar(pilha *p){

  Tpilha *aux;
  aux = p->topo;

  while(aux !=NULL){
    printf("\n %d | %s | %d",aux->codigo, aux->nome, aux->quantidade);
    aux=aux->ant;

  }
}



void menu(){

    fila *f=(fila*)malloc(sizeof(fila));
    createfila(f);

    pilha *p1=malloc(sizeof(pilha));
    create_pilha(p1);

    pilha *p2=malloc(sizeof(pilha));
    create_pilha(p2);

    empilha(p1, 1, "Item 1", 10);
    empilha(p1, 2, "Item 2", 5);
    empilha(p1, 3, "Item 3", 20);


 int op;  //opção recursiva

 do{
     system("cls");
     printf("\n Fila: \n");
     mostra_fila(f);

     printf("\n\n");
     printf("1 - Adicionar chamado \n");
     printf("2 - Retirar chamado \n");
     printf("3 - Ver estoque \n");
     printf("4 - Pedir produto \n");
     printf("5 - Sair \n ");

     printf("\n\n Informe a opcao :>_");
     scanf("%d",&op);

    switch(op){

      case 1:{
      char nome[50];
      int nivel;
      do
      {
            printf("Informe o nome do cliente e o nivel do problema(de 1 a 2): ");
            scanf("%s%d",&nome, &nivel);
      }while(nivel < 1 || nivel > 2);

      inserir_prioridade(f, nome, nivel);

      break;
     }


     case 2:{
          Tfila x;
          if(fila_vazia(f)==1){

            printf("\n \n Nao e possivel remover ");
            printf(" ---> Fila Vazia!!\n");
            getch();

          }else{

           desenfileirar(f,&x);
           printf("\n\tO pedido do cliente %s foi retirado \n\n",x.nome);

           getch();

           }
          break;
      }

      case 3:{
            mostrar(p1);
            getch();

          break;
         }

      case 4:{
        int opc;
        opc = 0;
            printf("1)Produto A \n 2)Produto B \n 3)Produto C\n");
            printf("Informe qual produto ira escolher(selecione entre 1,2 ou 3)...: ");
            scanf("%d", &opc);
             if(opc > 3 || opc < 1)
                printf("Você digitou um numero invalido, porfavor digite novamente o produto desejado");

        if(opc == 1)
        {
             diminui_quantidade(p1,p2,1);
        }


        if(opc == 2)
        {
            diminui_quantidade(p1,p2,2);
        }

        if(opc == 3)
        {
            diminui_quantidade(p1,p2,3);
        }


    break;

    }


     case 5:
        op=5;
    }

 }while(op != 5);
}

int main()
{

    menu();

    printf("\n\n");
    return 0;
}

