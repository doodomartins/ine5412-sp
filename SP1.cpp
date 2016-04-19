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

//LINHA E COLUNA CERTAS
// int table[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9},
// 						 {4,5,6,5,6,7,8,9,1},
// 						 {9,8,7,6,7,8,9,1,2},
// 						 {4,5,6,7,8,9,1,2,3},
// 						 {5,6,7,8,9,1,2,3,4},
// 						 {6,7,8,9,1,2,3,4,5},
// 						 {7,8,9,1,2,3,4,5,6},
// 						 {8,9,1,2,3,4,5,6,7},
// 						 {9,1,2,3,4,5,6,7,8}};

int table[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9},
						 {2,3,4,5,6,7,8,9,1},
						 {3,4,5,6,7,8,9,1,2},
						 {4,5,6,7,8,9,1,2,3},
						 {5,6,7,8,9,1,2,3,4},
						 {6,7,8,9,1,2,3,4,5},
						 {7,8,9,1,2,3,4,5,6},
						 {8,9,1,2,3,4,5,6,7},
						 {9,1,2,3,4,5,6,7,8}};

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

	//TODO pro maike, tenho que dar free no retorno dai?
	int* ret = new int();
	*ret = valid;	
	return (void*) ret;
}



int main(){
	int isRowValid = 1;
	int isColValid = 1;
	int isBlockValid[SIZE];
	int* threadLineResult;
	int* threadColResult;

	pthread_t threadLine, threadCol, threadsBlock[SIZE];
    pthread_create(&threadLine, NULL, &verifyRow, &isRowValid);
 	pthread_create(&threadCol, NULL, &verifyColumn, &isColValid);
 

	int count = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			
			parameters *data = (parameters *) malloc(sizeof(parameters));
			data->row = i*3;
			data->column = j*3;
			pthread_create(&threadsBlock[count], NULL, &verifyBlock, data);
			
			int* temp;
			pthread_join(threadsBlock[count], (void**)&temp);
			count++;
		
		}
	}



	/*
		Aguarda as threads terminarem
	*/
 	// pthread_join(threadLine, (void**)&threadLineResult);
	pthread_join(threadCol, (void**)&threadColResult);

    if (*threadLineResult == 0){
		cout << "Invalido linha\n";
    }

    if (*threadColResult == 0){
		cout << "Invalido col\n";
    }

    for(int i = 0; i < SIZE; i++){
    	int* temp;
		pthread_join(threadsBlock[i], (void**)&temp);
		isBlockValid[i] = *temp;
	}

	for(int i = 0; i < SIZE; i++){
		if(isBlockValid[i] == 0){
			cout << "Invalido bloco\n";
			return 0;
		}
	}
}
