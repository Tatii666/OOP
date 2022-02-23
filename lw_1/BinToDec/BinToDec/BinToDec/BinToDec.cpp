#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string binaryNumber;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: bin2dec.exe <binary number>\n";
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
		int digit = (int)binaryNumber[i] - 48;

		if (digit != 0 && digit != 1)
		{
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

	if (args->binaryNumber.length() >= 32)
	{
		std::cout << "Too big binary number\n";
		return 1;
	}

	std::optional<int> decimal = BinaryToDecimal(args->binaryNumber);
	if (!decimal)
	{
		return 1;
	}
	
	std::cout << decimal.value();

	return 0;
}
