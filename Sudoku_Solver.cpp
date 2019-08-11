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

int_pair find_free_cell(int** matrix) { // ���� ��������� ������
	int_pair cell;
	cell.i = 666;
	cell.j = 666;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (matrix[i][j] == 0) { // ��������� ��������� ���������� ������
				cell.i = i;
				cell.j = j;
				return cell;
			}
		}
	return cell; // ���� ��������� ������ �� ��������, ������������ ������ �� ����������� ���������
}

void find_fit_digits(int** matrix, int_pair cell, int* digits) { // �� ������ ���� ��������� �����
	// ���������� ��������� ����� � ������� digits
	for (int i = 0; i < 9; i++) {
		digits[i] = i + 1; // ���������� �������, ��� ����� ����� ��������
	}					   // ����� ������� �� ������� ������������ �������

	for (int j = 0; j < 9; j++) { // ������� ������� �� ������
		if (matrix[cell.i][j] != 0) { // 
			digits[matrix[cell.i][j] - 1] = 0; // �� �������� ��� ��������
		}
	}

	for (int i = 0; i < 9; i++) { // ������ �� �������
		if (matrix[i][cell.j] != 0) {
			digits[matrix[i][cell.j] - 1] = 0;
		}
	}

	for (int i = cell.i / 3 * 3; i < cell.i / 3 * 3 + 3; i++) // ������ �� ��������
		for (int j = cell.j / 3 * 3; j < cell.j / 3 * 3 + 3; j++) {
			if (matrix[i][j] != 0) {
				digits[matrix[i][j] - 1] = 0;
			}
		} // ������ � ������� ������ ���������� ����� � ����
}

int** create_matrix() { // ����������� ����� create_matrix
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
			A[i][j] = 0; // ���������� ����� ������ ��������
		}

	return A;
}

void solve(int** matrix) {
	static bool solution_was_found = false;
	int_pair cell = find_free_cell(matrix); // ��������� ������

	if (cell.i == 666) { // ��������� ������ �� ��������
		solution_was_found = true; // ������� ���� �������
		return;
	}

	int digits[9];

	find_fit_digits(matrix, cell, digits); // ����� ���������� �����

	for (int i = 0; i < 9; i++) { // ���������� �� � �����
		if (solution_was_found) { // ���� ������� ���� ������� �����
			return; // ����������� �������
		}
		if (digits[i] != 0) { // ���� ���� ���������� �����
			matrix[cell.i][cell.j] = digits[i]; //����������� �� � �������
			solve(matrix); // ��� ��������
		} // ���� ���� �� ��������� (������� ����� � �����), ������� �������� ��� ���������
	}     // � ������� ������ ����������
	
	if (solution_was_found) { //���� �� ��������� �������� ����� ��������� ����������
		return; // ����� ����� ��� ���������
	}
	else {
		matrix[cell.i][cell.j] = 0; // ����� � ��������� ������� ����� ����������� ��������� ����
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