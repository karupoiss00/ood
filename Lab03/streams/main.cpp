#include <iostream>
#include <vector>
#include <optional>
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "OutputStreamDecorator.h"
#include "InputStreamDecorator.h"
#include "DecompressInputData.h"
#include "DecryptInputData.h"
#include "CompressOutputData.h"
#include "CryptOutputData.h"

using namespace std;

constexpr streamsize BUFFER_SIZE = 32;

struct Command
{
	string name;
	char* argument;
};

struct Args
{
	vector<Command> commands;
	string inputFileName;
	string outputFileName;
};

void HandleUserCommands(IInputDataStreamPtr& input, IOutputDataStreamPtr& output, vector<Command> const& commands);
optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	
	if (!args)
	{
		return 1;
	}
	
	IInputDataStreamPtr inputFileStream(new CFileInputStream(args->inputFileName));
	IOutputDataStreamPtr outputFileStream(new CFileOutputStream(args->outputFileName));

	HandleUserCommands(inputFileStream, outputFileStream, args->commands);

	char buf[BUFFER_SIZE];
	streamsize size;

	while (!inputFileStream->IsEOF())
	{
		size = inputFileStream->ReadBlock(&buf, BUFFER_SIZE);

		if (size)
		{
			outputFileStream->WriteBlock(&buf, size);
		}
	}

	return 0;
}

bool HasCommandArgument(string const& command)
{
	return (command == "--encrypt") || (command == "--decrypt");
}

optional<vector<Command>> ParseCommands(int argc, char* argv[])
{
	vector<Command> parsedCommands;
	for (int i = 1; i < argc - 3; i++)
	{
		Command command;
		command.name = argv[i];

		if (HasCommandArgument(argv[i]))
		{
			bool argumentAvailable = (i + 1) < (argc - 3);
			if (argumentAvailable)
			{
				command.argument = argv[i + 1];
			}
			else
			{
				cout << "Used command without argument!" << endl;
				return nullopt;
			}
		}
		parsedCommands.push_back(command);
	}

	return parsedCommands;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		string filePath = string(argv[0]);
		string fileName = filePath.substr(filePath.find_last_of('/'));

		cout << "Invalid arguments count" << endl;
		cout << "Usage: " << fileName << " [commands] <input file> <output file>" << endl;

		return nullopt;
	}

	auto parsedCommands = ParseCommands(argc, argv);

	if (!parsedCommands)
	{
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];
	args.commands = *parsedCommands;

	return args;
}

IInputDataStreamPtr DecorateInput(IInputDataStreamPtr&& stream, Command const& command)
{
	if (command.name == "--decompress")
	{
		CDecompressInputData* decompressor = new CDecompressInputData(move(stream));
		return move(unique_ptr<CDecompressInputData>(decompressor));
	}

	if (command.name == "--decrypt")
	{
		CDecryptInputData* decryptor = new CDecryptInputData(move(stream), atoi(command.argument));
		return (unique_ptr<CDecryptInputData>(decryptor));
	}

	return move(stream);
}


IOutputDataStreamPtr DecorateOutput(IOutputDataStreamPtr&& stream, Command const& command)
{
	if (command.name == "--compress")
	{
		CCompressOutputData* compressor = new CCompressOutputData(move(stream));
		return move(unique_ptr<CCompressOutputData>(compressor));
	}

	if (command.name == "--encrypt")
	{
		CCryptOutputData* encryptor = new CCryptOutputData(move(stream), atoi(command.argument));
		return move(unique_ptr<CCryptOutputData>(encryptor));
	}

	return move(stream);
}

void HandleUserCommands(IInputDataStreamPtr& input, IOutputDataStreamPtr& output, vector<Command> const& commands)
{
	for (auto command : commands)
	{
		bool isCommandForOutput = command.name == "--compress" || command.name == "--encrypt";
		bool isCommandForInput = command.name == "--decompress" || command.name == "--decrypt";
		
		if (isCommandForOutput)
		{
			output = DecorateOutput(move(output), command);
		}

		if (isCommandForInput)
		{
			input = DecorateInput(move(input), command);
		}
	}
}