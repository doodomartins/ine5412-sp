#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <algorithm>



#define NUM_THREADS 11
#define SIZE 9


// Agrupamento 07
// nome do aluno: Douglas Marcelino Beppler Martins 13104674
// nome do aluno: Maike de Paula Santos 13100763
// nome do aluno: Ruan Ramon de Olveira 13200672


/* Estrutura usada para ajudar a setar a linha e coluna cada thread deve começar a trabalhar */
typedef struct{
 int row;
 int column;
} parameters;

using namespace std;

// Matriz com os blocos validos
// int table[SIZE][SIZE] = {{1,2,3,1,2,3,1,2,3},
// 						{4,5,6,4,5,6,4,5,6},
// 						{7,8,9,7,8,9,7,8,9},
// 						{1,2,3,1,2,3,1,2,3},
// 						{4,5,6,4,5,6,4,5,6},
// 						{7,8,9,7,8,9,7,8,9},
// 						{1,2,3,1,2,3,1,2,3},
// 						{4,5,6,4,5,6,4,5,6},
// 						{7,8,9,7,8,9,7,8,9}};

// Matriz com linhas e colunas validas
// int table[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9},
// 						 {2,3,4,5,6,7,8,9,1},
// 						 {3,4,5,6,7,8,9,1,2},
// 						 {4,5,6,7,8,9,1,2,3},
// 						 {5,6,7,8,9,1,2,3,4},
// 						 {6,7,8,9,1,2,3,4,5},
// 						 {7,8,9,1,2,3,4,5,6},
// 						 {8,9,1,2,3,4,5,6,7},
// 						 {9,1,2,3,4,5,6,7,8}};

// Matriz com tudo valido
int table[SIZE][SIZE] = {{8,3,5,4,1,6,9,2,7},
						 {2,9,6,8,5,7,4,3,1},
						 {4,1,7,2,9,3,6,5,8},
						 {5,6,9,1,3,4,7,8,2},
						 {1,2,3,6,7,8,5,4,9},
						 {7,4,8,5,2,9,1,6,3},
						 {6,5,2,7,8,1,3,9,4},
						 {9,8,1,3,4,5,2,7,6},
						 {3,7,4,9,6,2,8,1,5}};

/*
 * Método que verifica as linhas. Uma única thread é responsavel por executá-lo.
 *
 * Cada linha do jogo é copiada para um array auxiliar, que é então ordenado.
 * Feito isso, é verificado se o array ordenado contém todos os numeros de 1 a 9 sem repetição.
 * Caso não haja repetição, a linha é válida e é retornado 1.
 * Caso contrário, a linha é inválida e é retornado 0.
 */
void* verifyRow(void* a){
	int valid = 1;
	int line[SIZE];

	for(int i = 0; i < SIZE; i++){
		//Copy line
		copy(table[i], table[i] + SIZE, line);

		sort(line, line + SIZE);
		
	 	for(int j = 0; j < SIZE; j++){
	 		if(line[j] != j+1){
	 			valid = 0;
				int* ret = new int();
				*ret = valid;	
				return (void*) ret;
	 		}
		}
	}
	int* ret = new int();
	*ret = valid;	
	return (void*) ret;
}


/*
 * Método que verifica as colunas. Uma única thread é responsavel por executá-lo.
 *
 * Cada coluna do jogo é copiada para um array auxiliar, que é então ordenado.
 * Feito isso, é verificado se o array ordenado contém todos os numeros de 1 a 9 sem repetição.
 * Caso não haja repetição, a coluna é válida e é retornado 1.
 * Caso contrário, a coluna é inválida e é retornado 0.
 */
void* verifyColumn(void* a){
	int valid = 1;
	int column[SIZE];

	for(int i = 0; i < SIZE; i++){
		//Copy column
		for(int j = 0; j < SIZE; j++){
			column[j] = table[j][i];
		}
		sort(column, column + SIZE);
		
	 	for(int l = 0; l < SIZE; l++){
	 		if(column[l] != l +1){
	 			valid = 0;
				int* ret = new int();
				*ret = valid;	
				return (void*) ret;
	 		}
		}

	}
	int* ret = new int();
	*ret = valid;	
	return (void*) ret;
}


/*
 * Método que verifica um determinado bloco. Cada thread é responsavel por executá-lo 
 * passando a informação de um único bloco por parametro.
 *
 * Cada linha do bloco especificado é copiada para um array auxiliar unidimensional, que é então ordenado.
 * Feito isso, é verificado se o array ordenado contém todos os numeros de 1 a 9 sem repetição.
 * Caso não haja repetição, o bloco é válido e é retornado 1.
 * Caso contrário, o bloco é inválido e é retornado 0.
 */
void* verifyBlock(void* param){
	parameters* p = (parameters*) param;
	int valid = 1;
	int blockSize = 3;
	int block[SIZE];
	int line = p->row;
	int col = p->column;

	for(int i = 0; i < blockSize; i++){
		copy(table[line+i] + col, table[line+i] + col + blockSize, block + blockSize*i);
	}

	sort(block, block + SIZE);
		
	for(int i = 0; i < SIZE; i++){
		if(block[i] != i +1){
			valid = 0;
			int* ret = new int();
			*ret = valid;	
			return (void*) ret;
		}
	}
	/*
		Desaloca a struct
	*/
	free(p);

	int* ret = new int();
	*ret = valid;	
	return (void*) ret;
}



int main(){
	/*
	 * Variáveis que conterão os valores de retorno dos métodos executados pelas threads
	 */
	int threadBlockResult[SIZE];
	int* threadLineResult;
	int* threadColResult;

	/*
	 * Uma thread para verificar a linha, uma para a coluna e 9 para os blocos.
	 */
	pthread_t threadLine, threadCol, threadsBlock[SIZE];

	/*
	 * Criação das threads com o método pthread_create para verificar linhas e colunas, passando por parâmetro, em ordem:
	 * a referência da thread a ser criada
	 * os atributos da thread(NULL pois assim a mesma receberá atributos default)
	 * a rotina a ser executada pela thread
	 * o parâmero a ser passado para a rotina(NULL no caso de a rotina não utilizar parâmetros).
	 *
	 * OBS: mesmo que as rotinas verifyRow e verifyColumn recebam NULL no quarto argumento,
	 * é obrgatório implementá-las como se fossem receber um parâmetro.
	 */
    pthread_create(&threadLine, NULL, &verifyRow, NULL);
 	pthread_create(&threadCol, NULL, &verifyColumn, NULL);
 
 	/*
	 * Criação das threads com o método pthread_create para verificar os blocos. 
	 * Para descrição da função de cada parâmetro, ver comentário acima.
	 * Neste caso, como são 9 threads, são executados dois for para setar os valores da struct que identificará o bloco a ser analisado
	 * e esta struct será então o quarto parâmetro do pthread_create.
	 */
	int count = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			
			parameters *data = (parameters *) malloc(sizeof(parameters));
			data->row = i*3;
			data->column = j*3;
			pthread_create(&threadsBlock[count], NULL, &verifyBlock, data);
			
			count++;		
		}
	}



	/*
	 * Aguarda as threads que verificam as linhas e as colunas terminarem com o método pthread_join, passando por parâmetro, em ordem:
	 * a thread a ser aguardada
	 * referência da variável que conterá o valor de retorno do método executado pela thread.
	 */
 	pthread_join(threadLine, (void**)&threadLineResult);
	pthread_join(threadCol, (void**)&threadColResult);

    for(int i = 0; i < SIZE; i++){
    	int* temp;
		pthread_join(threadsBlock[i], (void**)&temp);
		threadBlockResult[i] = *temp;
	}

	bool valid = true;

	/*
	 * Verifica o valor retornado pelos métodos executados pelas threads obtido nos métodos acima(pthread_join)
	 * Caso algum valor seja 0, a solução é inválida.
	 * Caso contrário, a solução é válida.
	 */
    if (*threadLineResult == 0){
		cout << "Invalido linha.\n";
		valid = false;
    }

    if (*threadColResult == 0){
		cout << "Invalido col.\n";
		valid = false;
    }

	for(int i = 0; i < SIZE; i++){
		if(threadBlockResult[i] == 0){
			cout << "Invalido bloco.\n";
			valid = false;
			break;
		}
	}

	if(valid){
		cout << "solução válida.\n";
	}
}
