#include <iostream>
#include "Picture.h"
#include "PictureController.h"
#include "MockCanvas.h"

using namespace std;
using namespace shapes;

int main()
{
	Picture picture;
	MockCanvas canvas;
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

	return 0;
}	