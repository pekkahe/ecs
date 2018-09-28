#include <Precompiled.hpp>
#include <core/Engine.hpp>

int main()
{
	int exitCode = 0;
	std::cout << "Starting engine." << std::endl;
	
	eng::Engine engine;
	engine.execute();

	//try
	//{ 
	//}
	//catch (const std::exception& e)
	//{ 
	//	std::cout << e.what() << std::endl;
	//	exitCode = 1;
	//}

	std::cout << "Terminating engine." << std::endl;
    return exitCode;
}

