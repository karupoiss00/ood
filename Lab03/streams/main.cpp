#include <iostream>
#include <vector>
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "OutputStreamDecorator.h"
#include "InputStreamDecorator.h"
#include "DecompressInputData.h"
#include "DecryptInputData.h"
#include "CompressOutputData.h"
#include "CryptOutputData.h"

using namespace std;

const streamsize BUFFER_SIZE = 32;

IInputDataStreamPtr DecorateInput(IInputDataStreamPtr&& stream, const string& command, int32_t arg = 0);
IOutputDataStreamPtr DecorateOutput(IOutputDataStreamPtr&& stream, const string& command, int32_t arg = 0);
void HandleUserCommand(IInputDataStreamPtr& input, IOutputDataStreamPtr& output, char* commands[], uint32_t commandCount);

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << endl << "Invalid arguments count" << endl
			<< "Usage: transform.exe [options] <input file> <output file>" << endl;
		return 1;
	}

	string inputFileName = argv[argc - 2];
	string outputFileName = argv[argc - 1];

	IInputDataStreamPtr inputFileStream(new CFileInputStream(inputFileName));
	IOutputDataStreamPtr outputFileStream(new CFileOutputStream(outputFileName));

	HandleUserCommand(inputFileStream, outputFileStream, argv + 1, argc - 3);

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

void HandleUserCommand(IInputDataStreamPtr& input, IOutputDataStreamPtr& output, char* commands[], uint32_t commandCount)
{
	uint32_t handledCount = 0;

	while (handledCount < commandCount)
	{
		if (string(commands[handledCount]) == "--compress")
		{
			output = DecorateOutput(move(output), commands[handledCount]);
			++handledCount;
		}
		else if (string(commands[handledCount]) == "--decompress")
		{
			input = DecorateInput(move(input), commands[handledCount]);
			++handledCount;
		}
		else if (string(commands[handledCount]) == "--encrypt")
		{
			int32_t arg = atoi(commands[handledCount + 1]);
			output = DecorateOutput(move(output), commands[handledCount], arg);
			handledCount += 2;
		}
		else if (string(commands[handledCount]) == "--decrypt")
		{
			int32_t arg = atoi(commands[handledCount + 1]);
			input = DecorateInput(move(input), commands[handledCount], arg);
			handledCount += 2;
		}
	}
}

IInputDataStreamPtr DecorateInput(IInputDataStreamPtr&& stream, const string& command, int32_t arg)
{
	if (command == "--decompress")
	{
		CDecompressInputData* decompressor = new CDecompressInputData(move(stream));
		return move(unique_ptr<CDecompressInputData>(decompressor));
	}

	if (command == "--decrypt")
	{
		CDecryptInputData* decryptor = new CDecryptInputData(move(stream), arg);
		return (unique_ptr<CDecryptInputData>(decryptor));
	}

	return move(stream);
}


IOutputDataStreamPtr DecorateOutput(IOutputDataStreamPtr&& stream, const string& command, int32_t arg)
{
	if (command == "--compress")
	{
		CCompressOutputData* compressor = new CCompressOutputData(move(stream));
		return move(unique_ptr<CCompressOutputData>(compressor));
	}

	if (command == "--encrypt")
	{
		CCryptOutputData* encryptor = new CCryptOutputData(move(stream), arg);
		return move(unique_ptr<CCryptOutputData>(encryptor));
	}

	return move(stream);
}