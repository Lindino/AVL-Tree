 /*OBSERVACAO GERAL*/
 /** Não esquecer de implementar as rotações como 
 funções internas auxiliares(só precisam ser implementadas no avl.c)
    As funcoes necessárias para implementacao sao(no minimo):

  Nodo_AVL *rotation_LL(Nodo_AVL *raiz)  (Rotacao Simples a Direita)
  Nodo_AVL *rotation_RR(Nodo_AVL *raiz)  (Rotacao Simples a Esquerda)
  Nodo_AVL *rotation_LR(Nodo_AVL *raiz)  (Rotacao Dupla a Direita)
  Nodo_AVL *rotation_RL(Nodo_AVL *raiz)  (Rotacao Dupla a Esquerda)

 */

#include <stdio.h>
#include <stdlib.h>

/* Um nodo não difere de um nodo de árvore binária a não ser pelo armazenamento da altura */
typedef struct node_avl{
	int key;
	int height;
	struct node_avl *left, * right;
}Nodo_AVL;

/*Ja implementadas no arquivo avl.c*/
void print_tab(int level);
void print_tree( Nodo_AVL *current, int level);



/** Insere um nodo na árvore e realiza as rotações necessárias
 * @param root a raiz da árvore
 * @param key chave a ser inserida
 * @return nova raiz se inseriu, NULL se erro */
 Nodo_AVL *avl_insert(Nodo_AVL *current, int key);



 /** Busca uma chave na árvore
  * @param root a raiz da árvore
  * @param key chave a ser removida
  * @return ponteiro para nodo se encontrou, NULL se erro ou árvore vazia*/  
 Nodo_AVL *avl_search(Nodo_AVL *current, int key);



 /** Remove um nodo na árvore e realiza as rotações necessárias
  * @param root a raiz da árvore
  * @param key chave a ser removida
  * @return nova raiz se removeu, NULL se erro ou árvore vazia*/  
 Nodo_AVL *avl_delete(Nodo_AVL *current, int key);



/** Remove todos os elementos de uma árvore
  * @param root a raiz da árvore*/
 void avl_destroy(Nodo_AVL *current);



/** Retorna a altura de uma árvore 
 * @param root a raiz da árvore
 * @return altura*/
 int avl_height(Nodo_AVL *current);



/** Imprime a árvore na saida no formato inOrder com chaves separadas por espaço
 * @param root a raiz da árvore*/
 void print_inOrder(Nodo_AVL *current);



