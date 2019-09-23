#include "simpletest.h"
#include "avl.h"

#define MAX 15

//Funcao pra testar se esta balanceando corretamente
int isBalanced(Nodo_AVL *p){
	int left, right, diff;
	left = avl_height(p->left);
	right = avl_height(p->right);
	diff = abs(left - right);
	if(diff>1)
		return 0;
	else
		return 1;
}

void test_create(){
	DESCRIBE("CRIA ARVORE");
		WHEN("Eu crio uma ARVORE");


		IF("Uma chave");
			THEN("Resultado deve ser ponteiro");
			Nodo_AVL *p = avl_insert(NULL,1);
			isNotNull(p);

		THEN("Deve ter altura 0");
			isEqual(avl_height(p),0);

		avl_destroy(p);
}


void test_insert(){
	int i;
	Nodo_AVL *p = NULL;

	DESCRIBE("INSERE ELEMENTOS");
		WHEN("Eu insiro elementos");
		IF("Insiro um numero razoavel MAX");
			THEN("Deve inserir todos");
				for(i=1; i<=MAX; i++){
					p = avl_insert(p,i);
					isNotNull_Spaced(p);
				}
				printf("\n");

			THEN("Deve nao estar vazia");
				isNotEqual(avl_height(p),0);

			THEN("Deve imprimir a arvore balanceada");
				print_tree(p,0);

			THEN("Deve encontrar todas as chaves inseridas");
				for(i=1; i<=MAX; i++){
					isNotNull_Spaced(avl_search(p,i));
				}
				printf("\n");

			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				isEqual(isBalanced(p),1);
	
	

			THEN("Funcao print_inOrder deve imprimir todos os elementos na ordem");
				printf("\t");
				print_inOrder(p);
				printf("\n\n");

	avl_destroy(p);
}







void test_rotations(){
	int i;
	Nodo_AVL *p = NULL;

	DESCRIBE("Testando as rotacoes");
	DESCRIBE("ROTACAO RR");
		WHEN("Eu insiro elementos em ordem");
				for(i=1; i<8; i++){
					p = avl_insert(p,i);
				}

			THEN("Deve imprimir a arvore balanceada");
				print_tree(p,0);

			THEN("Deve encontrar todas as chaves inseridas");
				for(i=1; i<8; i++){
					isNotNull_Spaced(avl_search(p,i));
				}
				printf("\n");

			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				isEqual(isBalanced(p),1);
		avl_destroy(p);
		p = NULL;

	
	DESCRIBE("ROTACAO LL");
		WHEN("Eu insiro elementos em ordem inversa");
				for(i=7; i>=1; i--){
					p = avl_insert(p,i);
				}

			THEN("Deve imprimir a arvore balanceada");
				print_tree(p,0);

			THEN("Deve encontrar todas as chaves inseridas");
				for(i=1; i<8; i++){
					isNotNull_Spaced(avl_search(p,i));
				}
				printf("\n");

			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				isEqual(isBalanced(p),1);
		avl_destroy(p);
		p = NULL;
	
	DESCRIBE("ROTACAO RL");
		WHEN("Eu insiro elementos");
				p = avl_insert(p,1);
				p = avl_insert(p,3);
				p = avl_insert(p,2);
				p = avl_insert(p,6);
				p = avl_insert(p,4);
				p = avl_insert(p,7);
				p = avl_insert(p,5);
				
				

			THEN("Deve imprimir a arvore balanceada");
				print_tree(p,0);

			THEN("Deve encontrar todas as chaves inseridas");
				for(i=1; i<8; i++){
					isNotNull_Spaced(avl_search(p,i));
				}
				printf("\n");

			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				isEqual(isBalanced(p),1);
		avl_destroy(p);
		p = NULL;
		
	DESCRIBE("ROTACAO LR");
		WHEN("Eu insiro elementos");
				p = avl_insert(p,7);
				p = avl_insert(p,5);
				p = avl_insert(p,6);
				p = avl_insert(p,1);
				p = avl_insert(p,4);
				p = avl_insert(p,3);
				p = avl_insert(p,2);
				
				

			THEN("Deve imprimir a arvore balanceada");
				print_tree(p,0);

			THEN("Deve encontrar todas as chaves inseridas");
				for(i=1; i<8; i++){
					isNotNull_Spaced(avl_search(p,i));
				}
				printf("\n");

			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				isEqual(isBalanced(p),1);
		avl_destroy(p);
		p = NULL;
}

void test_delete(){
	int i;
	Nodo_AVL *p = NULL;
	DESCRIBE("AVL - DELETA ELEMENTOS");
	
		for(i=1; i<=MAX; i++){
			p = avl_insert(p,i);
		}

		WHEN("Quando remover um nodo");
			THEN("Deve conseguir remover E");
			THEN("Alturas da sub-arvore direita e esquerda nao podem ter diferença maior que 1");
				for(i=1; i<=MAX; i++){
					p = avl_delete(p,i);
					if(p){isEqual_Spaced(isBalanced(p),1);}
				}
			printf("\n");

			THEN("Ponteiro deve ser NULL");
				isNull(p);
}



void test_diverse(){
	int i;
	Nodo_AVL *p = NULL;

	DESCRIBE("Teste de diferentes balanceamentos");
	
		for(i=1; i<=8; i++){
			p = avl_insert(p,i);
		}
		print_tree(p,0);


		THEN("Altura da arvore deve ser 3");
			isEqual(avl_height(p),3);

		WHEN("Remove 5 e 1");
			p = avl_delete(p,5);
			p = avl_delete(p,1);
			print_tree(p,0);
			THEN("Altura deve ser 2");
				isEqual(avl_height(p),2);

		WHEN("Remove 8 e 7");
			p = avl_delete(p,8);
			p = avl_delete(p,7);
			print_tree(p,0);
			THEN("Altura deve ser 2");
				isEqual(avl_height(p),2);

		WHEN("Remove 4 (raiz)");
			p = avl_delete(p,4);
			print_tree(p,0);
			THEN("Altura deve ser 1");
				isEqual(avl_height(p),1);

		WHEN("Remove 2, 3 e 6");
			p = avl_delete(p,2);
			p = avl_delete(p,3);
			p = avl_delete(p,6);
			print_tree(p,0);
			THEN("Altura deve ser -1");
				isEqual(avl_height(p),-1);

}

int main () {
	test_create();
	test_insert();
	test_delete();
	test_diverse();
	test_rotations();
}
