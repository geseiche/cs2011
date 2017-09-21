/* 
 * Grace Seiche - geseiche
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {

	//allotted 8 local variables

	//for dealing with diagonal
	int temp;
	int index;

	//bounds for nested for-loops
	int row, col, i, j;

	//variables to hold block sizes
	int block_row;
	int block_col;

	//assigning block sizes based on the matrix
	if(M==64 && N==64){
		block_row = 40;
		block_col = 4;
	} else {
		block_row = 16;
		block_col = 8;
	}


	for(row = 0; row<N; row+=block_row){//iterate block by block through the rows

		for(col= 0; col<M; col+=block_col){//iterate block by block through the columns

			for(i = 0; i<block_row && (i+row)<N; i++){//iterate through all the rows in the block

				for(j = 0; j<block_col && (j+col)<M; j++){//iterate through all the columns in the block

					if((col+j)!=(row+i)){//check to make sure it is not a diagonal
						B[col+j][row+i]=A[row+i][col+j];//do the direct assignment
					} else {//if it is a diagonal, store in local variables so B is not accessed
						temp = A[row+i][row+i];
						index = row + i;
					}
				}
				//assign the temp value to the diagonal
				if(i + row == index){
					B[index][index] = temp;
				}
			}
		}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

