
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <iomanip>

#define MATRIX_SIZE 3

struct Args
{
	std::string matrix1FileName;
	std::string matrix2FileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: CopyFile.exe <input file name> <output file name>\n";
		return std::nullopt;
	}

	Args args;
	args.matrix1FileName = argv[1];
	args.matrix2FileName = argv[2];

	return args;
}

int ReadMatrix(std::string matrix1FileName, double** matrix)
{
	std::ifstream fileStream;

	//1. попробуй отделить проверку от чтения
	fileStream.open(matrix1FileName);
	if (!fileStream.is_open())
	{
		//2.вывод лучше сделать в одном месте
		std::cout << "Failed to open " << matrix1FileName << " for reading\n";
		return 1;
	}

	//3. можно тоже выделить в отдельную функцию
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		matrix[i] = new double[MATRIX_SIZE];
		if (matrix[i] == NULL)
		{
			return 1;
		}
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			//4. добавить проверку на строку
			fileStream >> matrix[i][j];
		}
	}

	//3. тоже бы выделить

	//5. разделить ошибки для удобства дебагинга
	if (fileStream.bad() || fileStream.eof())
	{
		std::cout << "Failed to read data from file matrix\n";
		return 1;
	}
	return 0;
}

void MultiplyMatrix(double** matrix1, double** matrix2, double** multipliedMatrix)
{
	//могут быть проблемы с передачей аргументов через указатели
	//размер матрицы передавать в параметрах
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		multipliedMatrix[i] = new double[MATRIX_SIZE]{ 0 };
	}

	for (int i = 0; i < MATRIX_SIZE; i++)
	{

		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			for (int k = 0; k < MATRIX_SIZE; k++)
			{
				multipliedMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

void PrintMatrix(double** matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << std::setprecision(3) << std::fixed << matrix[i][j];
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	double** matrix1;
	matrix1 = new double*[MATRIX_SIZE];
	if (ReadMatrix(args->matrix1FileName, matrix1))
	{
		return 1;
	};

	double** matrix2;
	matrix2 = new double*[MATRIX_SIZE];
	if (ReadMatrix(args->matrix2FileName, matrix2))
	{
		return 1;
	};
	
	double** multipliedMatrix;
	multipliedMatrix = new double*[MATRIX_SIZE];
	MultiplyMatrix(matrix1, matrix2, multipliedMatrix);
	
	PrintMatrix(multipliedMatrix);
	
	return 0;
}
