#include <iostream>
#include "view.h"

int main(int argc, char** argv) 
{
	try 
	{
		View* view = new View();
		view->init();
		delete view;
	}
	catch(Exception* e) 
	{
		std::cerr << e->what() << std::endl;
	}

	return 0;
}
