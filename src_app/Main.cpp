#include <Precompiled.hpp>
#include <core/Engine.hpp>

int main()
{
    std::cout << "Starting engine." << std::endl;
    
    eng::Engine engine;
    engine.execute();
    
    std::cout << "Terminating engine." << std::endl;
    return 0;
}
