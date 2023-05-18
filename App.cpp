#include "Queue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "ShortTestStack.h"
#include "Labyrinth.h"
#include <iostream>

using namespace std;

int main()
{

    testAll();
    testAllExtended();
    test_all_stack();
//
//     Labyrinth
//    Labyrinth l("false.txt");
      Labyrinth l("beispiel.txt");
    l.printLabyrinth();
    cout << l.pathExistenceCheck() << endl;
    l.shortestPath();

}