#include <iostream>
#include <optional>
#include "Picture.h"
#include "PictureController.h"
#include "SVGCanvas.h"

using namespace std;
using namespace shapes;
using namespace std::placeholders;

struct Args
{
	string outputFilename;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	Picture picture;
	SVGCanvas canvas(argv[1]);
	PictureController controller(picture, canvas, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << endl << "> ";

		try
		{
			if (!controller.HandleCommand())
			{
				cout << "Unknown command!" << endl;
			}
		}
		catch (std::exception const& e)
		{
			cout << e.what() << endl;
		}
	}

	canvas.Save();

	return 0;
}	

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Invalid arguments format" << endl;
		cout << "Usage: program.exe <output file name>" << endl;
		return nullopt;
	}

	Args args;
	args.outputFilename = argv[1];

	return args;
}