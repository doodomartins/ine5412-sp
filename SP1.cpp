#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <algorithm>



#define NUM_THREADS 11
#define SIZE 9


// Agrupamento 07
// nome do aluno:
// nome do aluno:
// nome do aluno: Ruan Ramon de Olveira 13200672


/* Estrutura usada para ajudar a setar a linha e coluna cada thread deve começar a trabalhar */
typedef struct{
 int row;
 int column;
} parameters;

using namespace std;

//LINHA E COLUNA CERTAS
int table[SIZE][SIZE] = {{1,2,3,4,5,6,7,8,9},
						 {2,3,4,5,6,7,8,9,1},
						 {3,4,5,6,7,8,9,1,2},
						 {4,5,6,7,8,9,1,2,3},
						 {5,6,7,8,9,1,2,3,4},
						 {6,7,8,9,1,2,3,4,5},
						 {7,8,9,1,2,3,4,5,6},
						 {8,9,1,2,3,4,5,6,7},
						 {9,1,2,3,4,5,6,7,8}};

void verifyRow(){
	// parameters* param =  (parameters*) p;
	bool valid = true;
	int line[SIZE];
	copy(table[4], table[4] + SIZE, line);
	sort(line, line + SIZE);
	
 	for(int i = 0; i < SIZE; i++){
 		if(line[i] != i +1){
 			valid = false;
 		}
	}
	//TODO ver o que faço aqui, retorno false?
}

void verifyColumn(){
	// parameters* param =  (parameters*) p;
	bool valid = true;
	int line[SIZE];
	copy(table[4], table[4] + SIZE, line);
	sort(line, line + SIZE);
	
 	for(int i = 0; i < SIZE; i++){
 		if(line[i] != i +1){
 			valid = false;
 		}
	}
	//TODO ver o que faço aqui, retorno false?
}


int main(){
	verifyRow();
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
