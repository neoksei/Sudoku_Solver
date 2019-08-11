#include <iostream>
#include <cstdlib>
#include <ctime>

struct int_pair {
	int i;
	int j;
};

void print_matrix(int** matrix) {
	for (int i = 0; i < 9; i++) {

		std::cout << std::endl;

		for (int j = 0; j < 9; j++) {
			std::cout << matrix[i][j] << " ";
		}
	}

	std::cout << "\n_________________\n";
}

int_pair find_free_cell(int** matrix) { // return a free cell
	int_pair cell;
	cell.i = 666;
	cell.j = 666;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (matrix[i][j] == 0) { // find a free cell
				cell.i = i;
				cell.j = j;
				return cell;
			}
		}
	return cell; // if there isn't a free cell, returns special value

void find_fit_digits(int** matrix, int_pair cell, int* digits) { // resulting digits will be returned in array
	
	for (int i = 0; i < 9; i++) {
		digits[i] = i + 1; // all digits fit first
	}
	
	for (int j = 0; j < 9; j++) { // chech rows
		if (matrix[cell.i][j] != 0) { // if there is some digit
			digits[matrix[cell.i][j] - 1] = 0; // it doesnt fit
		}
	}

	for (int i = 0; i < 9; i++) { // check column
		if (matrix[i][cell.j] != 0) {
			digits[matrix[i][cell.j] - 1] = 0;
		}
	}

	for (int i = cell.i / 3 * 3; i < cell.i / 3 * 3 + 3; i++) // check square
		for (int j = cell.j / 3 * 3; j < cell.j / 3 * 3 + 3; j++) {
			if (matrix[i][j] != 0) {
				digits[matrix[i][j] - 1] = 0;
			}
		} // Now there are only suitable digits in our array
}

int** create_matrix() { 
	int** A;
	if (!(A = (int**)malloc(sizeof(int*) * 9))) {
		std::cout << "Error allocation memory (Row)" << std::endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 9; i++) {
		if (!(A[i] = (int*)malloc(sizeof(int) * 9))) {
			std::cout << "Error allocation memory (Column)" << std::endl;
		}
	}

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			A[i][j] = 0; // All cells a free by default
		}

	return A;
}

void solve(int** matrix) {
	static bool solution_was_found = false;
	int_pair cell = find_free_cell(matrix); 

	if (cell.i == 666) { // it means there isn't a free cell
		solution_was_found = true; // So solution was found
		return;
	}

	int digits[9];

	find_fit_digits(matrix, cell, digits);

	for (int i = 0; i < 9; i++) {
		if (solution_was_found) { // Must check it for each iteration
			return; // It will collapse all functions
		}
		if (digits[i] != 0) {
			matrix[cell.i][cell.j] = digits[i]; // It's our prediction
			solve(matrix); // step of a recursion
		}
	}
	
	if (solution_was_found) { // If we leave cycle when solution was found
		return; // We collapse our function
	}
	else {
		matrix[cell.i][cell.j] = 0; // If solution was not found, it's important to leave matrix unchanged
	}

}

int main()
{
	int** matrix = create_matrix();

	for (int i = 0; i < 9; i++)

		for (int j = 0; j < 9; j++) {
			std::cin >> matrix[i][j];
		}

	unsigned int start_time = clock();
	solve(matrix);
	unsigned int end_time = clock();
	print_matrix(matrix);
	unsigned int search_time = end_time - start_time;
	std::cout << "\nElapsed time in milliseconds: " << search_time << std::endl;
	return 0;
}
