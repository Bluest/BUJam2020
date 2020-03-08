#include "Engine.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<Core> core = Core::init(200, 200, 60.0f);
    core->run();
    
    return 0;
}
