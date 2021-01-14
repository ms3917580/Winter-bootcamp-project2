#include <stdio.h>
#define N 9
#define UNASSIGNED 0

int exist_row(int sudoku[N][N], int row, int num){
	for (int col = 0; col < 9; col++) {
		if (sudoku[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int exist_col(int sudoku[N][N], int col, int num) {
	for (int row = 0; row < 9; row++) {
		if (sudoku[row][col] == num) {
			return 1;
		}
	}
	return 0;
}

int exist_box(int sudoku[N][N], int startRow, int startCol, int num) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (sudoku[row + startRow][col + startCol] == num) {
				return 1;
			} 
		}
	}
	return 0;
}

int safe_num(int sudoku[N][N], int row, int col, int num) {
	return !exist_row(sudoku, row, num) 
			&& !exist_col(sudoku, col, num) 
			&& !exist_box(sudoku, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int sudoku[N][N], int *row, int *col) {
	for (*row = 0; *row < N; (*row)++) {
		for (*col = 0; *col < N; (*col)++) {
			if (sudoku[*row][*col] == 0) {
				return 1;
			}
		}
	}
	return 0;
}

int solve(int sudoku[N][N]) {
	
	int row = 0;
	int col = 0;
	
	if (!find_unassigned(sudoku, &row, &col)){
		return 1;
	}
	
	for (int num = 1; num <= N; num++ ) {
		
		if (safe_num(sudoku, row, col, num)) {
			sudoku[row][col] = num;
			
			if (solve(sudoku)) {
				return 1;
			}
			
			sudoku[row][col] = UNASSIGNED;
		}
	}
	
	return 0;
}

void print_sudoku(int sudoku[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			printf("%2d", sudoku[row][col]);
		}
		printf("\n");
	}
}

int main() {
	
	int sudoku[N][N] ={{0,5,0, 3,1,4, 0,6,0},
			          {8,7,0, 0,0,9, 4,0,3},
			          {6,4,3, 5,0,7, 1,9,2},
			          {0,0,7, 8,0,5, 2,1,0},
			          {4,1,0, 9,0,0, 0,0,0},
			          {0,2,5, 0,6,1, 9,0,7},
			          {7,9,0, 2,5,0, 8,4,0},
			          {0,0,4, 0,9,6, 0,0,5},
					  {0,3,0, 1,0,8, 6,7,0}};
	
	if (solve(sudoku)) {
		print_sudoku(sudoku);
		printf("Sudoku solved successfully");
	} else {
		printf("Invalid solution");
	}
	return 0;
}
