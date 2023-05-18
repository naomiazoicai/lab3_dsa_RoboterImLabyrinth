#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Stack
{
private:
    TElem * nodesStack;          // array of nodes
    int* nextPosStack;           // array of the next positions
    int tail;
    int sizeStack;
    int capacityStack;           // the capacity
    int firstEmptyStack;         // index of the first empty node in the array
public:
    Stack();

    //pushes an element on top of the stack
    void push(TElem e);

    //returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem top() const;

    //removes and returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem pop();

    //checks if the stack is empty
    bool isEmpty() const;

    // destructor
    ~Stack();


    void resize_up();

    void resize_down();
};
