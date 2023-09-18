#include <iostream>
#include <thread>
#include "Picture.h"
#include "PictureController.h"
#include "Canvas.h"

using namespace std;
using namespace shapes;
using namespace std::placeholders;

int main()
{
	Picture picture;
	Canvas canvas;
	PictureController controller(picture, canvas, cin, cout);

	thread inputThread([&controller] {
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
	});

	canvas.Run();

	return 0;
}	