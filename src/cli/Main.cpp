#include <Precompiled.hpp>
#include <core/Engine.hpp>

int main()
{
    std::cout << "Starting engine." << std::endl;
    
    eng::Engine().execute();
    
    std::cout << "Terminating engine." << std::endl;
    return 0;
}
