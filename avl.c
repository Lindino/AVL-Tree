#include "avl.h"

//Funções para realizar as rotações.
int FB(Nodo_AVL *current);
Nodo_AVL *Testes_rotacoes(Nodo_AVL *current);
Nodo_AVL *rotation_LR(Nodo_AVL *current);
Nodo_AVL *rotation_RL(Nodo_AVL *current);
Nodo_AVL *rotation_LL(Nodo_AVL *current);
Nodo_AVL *rotation_RR(Nodo_AVL *current);

void print_tab(int level){
  int i;
  for (i = 0; i < level; i++ )
    printf("\t");
}

void print_tree( Nodo_AVL *current, int level ){
  if ( current == NULL ) {
    print_tab(level );
    printf("~\n");
  } else {
    print_tree( current->right, level + 1 );
    print_tab(level);
    printf ("%d", current->key);
    print_tree( current->left, level + 1 );
  }
}



Nodo_AVL *avl_insert(Nodo_AVL *current, int key){
	
	//Caso a posição atual for nula, segue da seguinte forma:
	if(current == NULL) {
		
		//Cria um bloco de estruturas...
		if((current = malloc(sizeof(Nodo_AVL))) == NULL) {
			printf("ERRO!\n");
			exit(1);
		}
		
		//...E atribui a ela os dados correspondentes, inserindo o valor desejado (KEY).		
		current->height = 0;
		current->key = key;
		current->left = NULL;
		current->right = NULL;
		return current;

	//Caso haja qualquer valor na posição atual, compara o elemento atual com o valor que será inserido.
	//Se o valor for maior quer o elemento atual, irá chamar a função de novo para o lado direito da árvore.
	} else if(current->key < key) {
		current->right = avl_insert(current->right, key);

		//Realiza testes de balanceamento depois de ter inserido o elemento.
		current = Testes_rotacoes(current);
		return current;
	
	//Se o valor for menor quer o elemento atual, irá chamar a função de novo para o lado esquerdo da árvore.
	} else if(current->key > key) {
		current->left = avl_insert(current->left, key);
		
		//Realiza testes de balanceamento depois de ter inserido o elemento.
		current = Testes_rotacoes(current);
		return current;
	} else {
		return NULL;
	}
}
 
Nodo_AVL *avl_delete(Nodo_AVL *current, int key) {
	
	//Testa se a posição atual é nula.
	if(current != NULL) {
		
		//Realiza a procura do elemento que deseja deletar:
		//Se o elemento atual for menor que o desejado, chama a função novamente para a subárvore da direita.
		if(current->key < key) {
			current->right = avl_delete(current->right, key);
		} 

		//Se o elemento atual for maior que o desejado, chama a função novamente para a subárvore da esquerda.
		else if(current->key > key) {
			current->left = avl_delete(current->left, key);
		} 
		
		//Quando o elemento atual tiver o valor que será apagado, realiza verificações se o mesmo tem filhos.
		else {
			
			//Caso ele tenha nenhum ou apenas 1 filho...
			if((current->left == NULL) || (current->right == NULL)) {
				Nodo_AVL *No;
				
				//Verifica se existe algum filho, caso tenha o ponteiro NO aponta para ele.
				if(current->left != NULL)
					No = current->left;
				else
					No = current->right;

				//Se o elemento atual não tiver nenhum filho:
				if(No == NULL){

					//O ponteiro No recebe o elemento atual...
					No = current;
                	
                	//Elemento atual recebe NULL.
                	current = NULL;
                	free(No);
            	
                /*Caso tenha 1 filho, independentemente se for filho da direita ou esquerda, elemento atual recebe o filho
                ou seja duplico o filho, e libero a celula de memoria que o ponteiro No está apontando.*/
            	} else {
            		*current = *No;
            		free(No);
            	}

            //Se o elemento atual tiver dois filhos.
        	} else if((current->right != NULL) && (current->left != NULL)) {
					Nodo_AVL *No;
					
					//Realiza a procura do maior elemento da subárvore a esquerda.
					No = current->left;
					while(No->right != NULL) {
						No = No->right;
					}

					//Depois de achar o elemento, copia o valor dele no lugar do elemento que será apagado.
					current->key = No->key;

					//Chamo a função deletar para apagar o elemento repetido, no qual estará a mais direita da subárvore da esquerda.
					current->left = avl_delete(current->left, No->key);
			}
		}
	}

	//Depois de ter apagado o elemento, necessita verificar o balanceamento.
	//Caso o elemento atual for nulo, retorno ele mesmo.
	if(current == NULL) {
		return current;
    }

    //Verifica se a árvore está balanceada.
    current = Testes_rotacoes(current);

    //Retorna depois de balanceada.
 	return current;
}

void print_inOrder(Nodo_AVL *current){

	//Testa se existe elemento na árvore.
	if(current != NULL){

		//Chama a função para o elemento a esquerda.
		print_inOrder(current->left);
		printf("%d ", current->key);
		print_inOrder(current->right);
	}
}

//Irá chamar recursivamente a função até achar uma folha, apagando-a.
void avl_destroy(Nodo_AVL *current){

	//Testa se a árvore não está vazia.
	if(current != NULL) {

		//Se o elemento atual não tiver filho, apago ele.
		if((current->right == NULL) && (current->left == NULL)) {
			free(current);

		//Caso tenha filho a direita chama a função novamente para a o filho.
		} else if(current->right != NULL) {
			avl_destroy(current->right);

		//Caso tenha filho a esquerda chama a função novamente para a o filho.
		} else if(current->left != NULL) {
			avl_destroy(current->left);
		
		//Caso tenha dois filhos, chama a função para os dois filhos.
		} else {
			avl_destroy(current->right);
			avl_destroy(current->left);
		}	
	}
}

Nodo_AVL *avl_search(Nodo_AVL *current, int key){

	//Caso não tenha o elemento que desejado, retorna nulo.
	if(current == NULL) {
		return NULL;
	} 

	//Se o elemento for maior que o atual, chama recursivamente a função avl_search para a subárvore da direita.
	else if(current->key < key) {
		current->right = avl_search(current->right, key);
	} 

	//Se o elemento for menor que o atual, chama recursivamente a função avl_search para a subárvore da esquerda.
	else if(current->key > key) {
		current->left = avl_search(current->left, key);
	} 

	//Caso encontrar o elemento na árvore, retorna ele para a main.
	else {
		return current;
	}
}

int avl_height(Nodo_AVL *raiz) {
	int left, right;

	//Determina a altura das folhas vazias.
	if(raiz == NULL) {
		return -1;
	}

	//Chama a função pa os dois lados, esquerdo e direito.
	left = avl_height(raiz->left);
	right = avl_height(raiz->right);

	//A altura correta será o maior caminho da folha até a raiz
	if(left > right) {
		return left + 1;		//Soma +1 pois define -1 a altura das folhas vazias.
	} else {
		return right + 1;		//Soma +1 pois define -1 a altura das folhas vazias.
	}
}

//Calcula o fator de balanceamento.
int FB(Nodo_AVL *current){
	if(current == NULL) {
		return 0;
	}

	//Altura da subárvore da esquerda menos a altura subárvore da direita.
	return avl_height(current->left) - avl_height(current->right);
}

//Rotação a direita.
Nodo_AVL *rotation_LL(Nodo_AVL *current) {
	Nodo_AVL *no;

	//No aponta para o filho da esquerda do atual elemento.
	no = current->left;

	//Caso no tenha filho a direita, irá para a esquerda do elemento atual.
	current->left = no->right;

	//No da direita aponta para o elemento atual.
	no->right = current;

	//Finalizando, retorna o no ja rotacionado.
	return no;
}

//Rotação a esquerda.
Nodo_AVL *rotation_RR(Nodo_AVL *current){
	Nodo_AVL *no;

	//No aponta para o filho da direita do atual elemento.
	no = current->right;

	//Caso no tenha filho a esquerda, irá para a direita do elemento atual.
	current->right = no->left;

	//No da esquerda aponta para o elemento atual.
	no->left = current;

	//Finalizando, retorna o no ja rotacionado.
	return no;
}

//Rotação a esquerda e depois a direita.
Nodo_AVL *rotation_LR(Nodo_AVL *current){

	//Realiza uma rotação a esquerda.
	current->left = rotation_RR(current->left);

	//Realiza uma rotação a direita.
	current = rotation_LL(current);
	return current;
}

//Rotação a direita e depois a esquerda.
Nodo_AVL *rotation_RL(Nodo_AVL *current){

	//Realiza uma rotação a esquerda.
	current->right = rotation_LL(current->right);

	//Realiza uma rotação a esquerda.
	current = rotation_RR(current);
	return current;
}

//Função que testa se a árvore está balanceada.
Nodo_AVL *Testes_rotacoes(Nodo_AVL *current) {
	Nodo_AVL *no;

	//Testa se tem elemento para rotacionar.
	if(current != NULL) {

		//Calcula o Fator de balanceamento.
		current->height = FB(current);

		//Caso o Fator de balanceamento for 2 positivo, está desbalanceado para esquerda.
		if(current->height > 1) {

			//Calcula o Fator de balanceamento do seu filho a esquerda.
			no = current->left;
			no->height = FB(no);

			//Caso o FB for positivo, rotaciona para a direita.
			//Caso contrário, se for negativo, realiza uma rotação a esquerda e depois para a direita.
			if(no->height >= 0) {
				current = rotation_LL(current);
			} else {
				current = rotation_LR(current);
			}

			//Testa novamente se está balanceada.
			current = Testes_rotacoes(current);
			return current;
		}

		//Caso o Fator de balanceamento for 2 negativo, está desbalanceado para direita.
		if(current->height < -1) {

			//Calcula o Fator de balanceamento do seu filho a direita.
			no = current->right;
			no->height = FB(no);

			//Caso o FB for negativo, rotaciona para a esquerda.
			//Caso contrário, se for positivo, realiza uma rotação a direita e depois para a esquerda.
			if(no->height >= 0){
				current = rotation_RL(current);
			} else {
				current = rotation_RR(current);
			}

			//Testa novamente se está balanceada.
			current = Testes_rotacoes(current);
			return current;
		} 

		//Se não precisar rotacionar, retorna o elemento.
		else {
			return current;
		}
	}
}
