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

int_pair find_free_cell(int** matrix) { // ищет свободную клетку
	int_pair cell;
	cell.i = 666;
	cell.j = 666;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (matrix[i][j] == 0) { // свободной считается зануленная клетка
				cell.i = i;
				cell.j = j;
				return cell;
			}
		}
	return cell; // если свободных клеток не осталось, возвращается клетка со специальным значением
}

void find_fit_digits(int** matrix, int_pair cell, int* digits) { // по клетке ищет возможные цифры
	// возвращает возможные цифры в массиве digits
	for (int i = 0; i < 9; i++) {
		digits[i] = i + 1; // изначально считаем, что любая цифра подходит
	}					   // цифры смещены на единицу относительно индекса

	for (int j = 0; j < 9; j++) { // сначала смотрим на строку
		if (matrix[cell.i][j] != 0) { // 
			digits[matrix[cell.i][j] - 1] = 0; // не забываем про смещение
		}
	}

	for (int i = 0; i < 9; i++) { // теперь на столбец
		if (matrix[i][cell.j] != 0) {
			digits[matrix[i][cell.j] - 1] = 0;
		}
	}

	for (int i = cell.i / 3 * 3; i < cell.i / 3 * 3 + 3; i++) // теперь на квадрант
		for (int j = cell.j / 3 * 3; j < cell.j / 3 * 3 + 3; j++) {
			if (matrix[i][j] != 0) {
				digits[matrix[i][j] - 1] = 0;
			}
		} // теперь в массиве только подходящие цифры и нули
}

int** create_matrix() { // стандартный такой create_matrix
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
			A[i][j] = 0; // изначально любая клетка свободна
		}

	return A;
}

void solve(int** matrix) {
	static bool solution_was_found = false;
	int_pair cell = find_free_cell(matrix); // свободная клетка

	if (cell.i == 666) { // свободных клеток не осталось
		solution_was_found = true; // решение было найдено
		return;
	}

	int digits[9];

	find_fit_digits(matrix, cell, digits); // нашли подходящие цифры

	for (int i = 0; i < 9; i++) { // перебираем их в цикле
		if (solution_was_found) { // если решение было найдено ранее
			return; // сворачиваем функцию
		}
		if (digits[i] != 0) { // если есть подходящая цифра
			matrix[cell.i][cell.j] = digits[i]; //подставляем ее в матрицу
			solve(matrix); // шаг рекурсии
		} // если цифр не оказалось (решение зашло в тупик), матрица остается без изменений
	}     // а функция просто покидается
	
	if (solution_was_found) { //если на последней итерации цифра оказалось подходящей
		return; // важно выйти без зануления
	}
	else {
		matrix[cell.i][cell.j] = 0; // иначе в финальной матрице будут встречаться рандомные нули
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