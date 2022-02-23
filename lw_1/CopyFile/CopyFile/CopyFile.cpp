// CopyFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "CopyFile.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

//1. Разобраться с nullOptional, не стоит использовать неизвестное api
std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: CopyFile.exe <input file name> <output file name>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

void CopyFile(std::ifstream& input, std::ofstream& output)
{
	char ch;
	//2. Что возвращает input.get()?
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open " << args->inputFileName << " for reading\n";
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open " << args->outputFileName << " for writing\n";
		return 1;
	}

	CopyFile(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Failed to copy text to output file\n";
		return 1;
	}

	return 0;
}
