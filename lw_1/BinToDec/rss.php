#include <iostream>
#include <optional>
#include <string>

const int BINARY_COUNT = 32;
const int ASCII_DIGIT_OFFSET = 48;

//1. Если аргумент один, можно не использовать структуру
struct Args
{
	std::string binaryNumber;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: BinToDec.exe <binary number>\n";
		return std::nullopt;
	}

	Args args;
	args.binaryNumber = argv[1];

	return args;
}

std::optional<int> BinaryToDecimal(std::string binaryNumber)
{
	int result = 0;

	for (int i = 0; i < binaryNumber.length(); i++)
	{
		//Подумать как можно использовать безопасные варианты кастов
		int digit = (int)binaryNumber[i] - ASCII_DIGIT_OFFSET;

		if (digit != 0 && digit != 1)
		{
			//3. Предлагаю отделить логику от вывода (можно использовать лямба функцию или колбек) 
			// (можно попробовать выбросить исключение и поймать его там где вызывается функция)
			std::cout << "It is not a binary number\n";
			return std::nullopt;
		}

		result = result << 1;
		result += digit;
	}

	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	//2. Попробуй вынести в отдельную функцию
	if (args->binaryNumber.length() >= BINARY_COUNT)
	{
		std::cout << "Too long binary number\n";
		return 1;
	}

	auto decimal = BinaryToDecimal(args->binaryNumber);
	if (!decimal)
	{
		return 1;
	}
	
	// 2.(Доп) Попробуй вынести в отдельную функцию
	std::cout << decimal.value();

	return 0;
}
