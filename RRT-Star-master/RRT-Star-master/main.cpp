#include "RRTStar.hpp"
#include "Graph.hpp"
//#include "AirSimTest.hpp"
// Memory Leak Check
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

void singleRRT() {
    Coord start = Coord(20, 40, 1);
    Coord end = Coord(-20, -40, 5);
    BiRRTStar brrt = BiRRTStar(start, end);
    brrt.CallRRTStar();

    //for (auto& it : brrt.getPath()) {
    //    it->printNode();
    //}
    for (auto& it : brrt.getPath()) {
        std::cout << it->node_number << " ";
    }
    std::cout << std::endl;
    
}

int main()
{
    //srand((unsigned)time(NULL));
    srand(SEED);
    singleRRT();
    //droneTest();


    _CrtDumpMemoryLeaks();
    return 0;
}