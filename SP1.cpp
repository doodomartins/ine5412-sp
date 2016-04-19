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
int table[SIZE][SIZE] = {{1,2,3,4,4,6,7,8,9},
						 {2,3,4,5,6,7,8,9,1},
						 {3,4,5,6,7,8,9,1,2},
						 {4,5,6,7,8,9,1,2,3},
						 {5,6,7,8,9,1,2,3,4},
						 {6,7,8,9,1,2,3,4,5},
						 {7,8,9,1,2,3,4,5,6},
						 {8,9,1,2,3,4,5,6,7},
						 {9,1,2,3,4,5,6,7,8}};

void* verifyRow(void* a){
	int *valid = (int*) a;
	int line[SIZE];

	for(int i = 0; i < SIZE; i++){
		//Copy line
		copy(table[i], table[i] + SIZE, line);
		for (int k = 0; k < SIZE; ++k){
			cout << line[k] << " ";
		}
		
		sort(line, line + SIZE);
		
	 	for(int j = 0; j < SIZE; j++){
	 		if(line[j] != j+1){
	 			*valid = 0;
	 			return (void*) valid;
	 		}
		}
		if(*valid == 1){
			cout << "Line " << i << " is valid\n";
		}
	}
	//TODO ver o que faço aqui, retorno false?
}

void* verifyColumn(void* a){
	int *valid = (int*) a;
	int column[SIZE];

	for(int j = 0; j < SIZE; j++){
		//Copy column
		for(int i = 0; i < SIZE; i++){
			column[i] = table[j][i];
		}
		for (int k = 0; k < SIZE; ++k){
			cout << column[k] << "\n";
		}

		sort(column, column + SIZE);
		
	 	for(int i = 0; i < SIZE; i++){
	 		if(column[i] != i +1){
	 			*valid = 0;
	 			return (void*) valid;
	 		}
		}

		if(*valid == 1){
			cout << "Col " << j << " is valid\n";
		}
	}
	//TODO delete p
	//TODO ver o que faço aqui, retorno false?
}

void* verifyBlock(void* a){
	parameters* p = (parameters*) a;

	int valid = 1;
	//block Size
	int blockSize = 3;
	int block[SIZE];

	int line = p->row;
	int col = p->column;

	for(int i = 0; i < blockSize; i++){
		copy(table[line+i] + col, table[line+i] + col + blockSize, block + blockSize*i);
	}

	for (int i = 0; i < SIZE; i++){
		if(i%3 == 0){
			cout << "\n";
		}
		cout << block[i] << " ";
	}	
	

	sort(block, block + SIZE);
		
	for(int i = 0; i < SIZE; i++){
		if(block[i] != i +1){
			valid = 0;
			// return (void*) &valid;
		}
	}


	free(a);
	cout<<"\n";

}



int main(){
	int isRowValid = 1;
	int isColValid = 1;
	int isBlockValid[SIZE];

	int threadLineResult;

	// pthread_t threadsBlock[SIZE];

	pthread_t threadLine, threadCol;
    pthread_create(&threadLine, NULL, &verifyRow, &isRowValid);
 	// pthread_create(&threadCol, NULL, &verifyColumn, &isColValid);

 	//TODO como pegar o retorno? 
 	pthread_join(threadLine, NULL);
	// pthread_join(threadCol, NULL);

	// int count = 0;
	// for (int i = 0; i < 3; i++){
	// 	for (int j = 0; j < 3; j++) {
			
	// 		parameters *data = (parameters *) malloc(sizeof(parameters));
	// 		data->row = i*3;
	// 		data->column = j*3;

	// 		pthread_create(&threadsBlock[count], NULL, &verifyBlock, data);
	// 		cout<<"\n\n";
	// 		count++;
	// 	}


	// }
    
 //    for(int i = 0; i < SIZE; i++){

 // 		//TODO como pegar o retorno? 
	// 	pthread_join(threadsBlock[i], NULL);
	// }
}

// int maina() {

// 	//Vetor para mais fácil criação, deleção e manipulação das threads que verificam os "quadrados" do sudoku 
// 	pthread_t Threads[NUM_THREADS];
// 	int threadResult[NUM_THREADS];

// 	for(int i=0; i<2 ;i++){
// 	      parameters *data = (parameters *) malloc(sizeof(parameters));
// 	      data->row = 1;
// 	      data->column = 1;
// 	      int rtnCreate = pthread_create(&Threads[i], NULL, varrerLinhaColuna, &threadResult);
//       	        if (rtnCreate){
//         	   cout << "ERROR; return code from pthread_create() is : " <<  rtnCreate;
//         	   exit(-1);
//       		}
// 	}

// 	int index = 2;
//  	for(int i=1; i<8 ;i+3) {
// 	   for(int n=1; n<8 ; n+3) {
// 		parameters *data = (parameters *) malloc(sizeof(parameters));
// 		data->row = i;
// 		data->column = i;
// 		int rtnCreate = pthread_create(&Threads[index], NULL, varrerQuadrado, &threadResult);
//       		if (rtnCreate){
//         		 cout << "ERROR; return code from pthread_create() is : " <<  rtnCreate;
//          		 exit(-1);
//       	        }
// 		index += 1;
// 	      }
// 	    }

// 	for(int i=0; i<10 ;i++) {
// 		pthread_join(Threads[i], NULL);
// 	}

// 	cout << "O sudoku foi respondido corretamente, parabéns !!! " << endl;
// 	return 0;
// }
