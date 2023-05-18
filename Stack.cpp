//
// Created by naomi on 5/4/2023.
//
#include "Stack.h"


///constructor
///complexity:O(n), worst case: Θ(n) , average case: Θ(n), best case: Θ(n)
Stack::Stack()
{
    this->capacityStack = 2;
    this->sizeStack = 0;
    nodesStack = new TElem [capacityStack];
    nextPosStack = new int[capacityStack];
    tail = -1;
    firstEmptyStack = 0;
    for (int i = 0; i < capacityStack-1; ++i)
    {
        nextPosStack[i] = i+1;
    }
    nextPosStack[capacityStack -1] = -1;    //end of stack
}

///pushes an element on top of the stack
///complexity:O(capacityStack), worst case: Θ(capacityStack) , average case: Θ(1) (kleine Wahrscheinlichkeit fur resize), best case: Θ(1)
void Stack::push(TElem e)
{
    if (firstEmptyStack == -1)      //if the stack is full
        resize_up();
    sizeStack++;
    if (isEmpty())
    {
        //if the stack is empty, we assign e to the first position and update firstEmpty & tail
        int currentElemPosition = firstEmptyStack;
        tail = currentElemPosition;
        nodesStack[currentElemPosition] = e;
        firstEmptyStack = nextPosStack[firstEmptyStack];
        nextPosStack[currentElemPosition] = -1;
    }
    else
    {
        //if the stack isn't empty, we assign e to the first empty position and update firstEmpty & nextPos & tail
        int currentElemPosition = firstEmptyStack;
        firstEmptyStack = nextPosStack[firstEmptyStack];
        nextPosStack[currentElemPosition] = tail;
        nodesStack[currentElemPosition] = e;
        tail = currentElemPosition;
    }
}

///returns the element from the top of the stack
///throws exception if the stack is empty
///complexity: Θ(1) worst, average and best
TElem Stack::top() const
{
    if (isEmpty())
        throw exception();
    // int topPos = nextPosStack[tail];
    int topPos = tail;
    return nodesStack[topPos];
}

///removes and returns the element from the top of the stack
///throws exception if the stack is empty
///complexity: Θ(1) worst, average and best
TElem Stack::pop()
{
    if (isEmpty())
        throw exception();
    int popPos = tail;
    tail = nextPosStack[tail];
    nextPosStack[popPos] = firstEmptyStack;
    firstEmptyStack = popPos;       //updating firstEmpty to the position of the removed element
    int returnElem = nodesStack[popPos];
    sizeStack--;
    if (sizeStack == capacityStack/4)
    {
        resize_down();
    }
    return returnElem;

}

///checks if the stack is empty
///complexity: Θ(1) worst, average and best
bool Stack::isEmpty() const
{
    //if (tail == 0)
    if (tail == -1)
        return true;
    return false;
}

///destructor
///complexity: Θ(1) worst, average and best
Stack::~Stack() {
    delete[] this->nodesStack;
    delete[] this->nextPosStack;
}

///auxiliary method for resizing up if needed
///complexity:O(oldCapacity), worst case: Θ(oldCapacity) , average case: Θ(oldCapacity), best case: Θ(1)
void Stack::resize_up() {
    int oldCapacity = capacityStack;
    capacityStack *= 2;
    int* auxNodes = new TElem[capacityStack];
    int* auxNextPos = new int[capacityStack];
    // Copy old arrays
    for (int i = 0; i < oldCapacity; ++i)
    {
        auxNodes[i] = nodesStack[i];
        auxNextPos[i] = nextPosStack[i];
    }
    // Initialise the rest of the auxNextPos
    for (int i = oldCapacity; i < capacityStack-1; ++i)
    {
        auxNextPos[i] = i+1;
    }
    auxNextPos[capacityStack-1] = -1;
    // Finish
    firstEmptyStack = oldCapacity;
    delete[] nodesStack;
    delete[] nextPosStack;
    nodesStack = auxNodes;
    nextPosStack = auxNextPos;
}

///auxiliary method for deallocating space if needed
///complexity:O(n), worst case: Θ(n) , average case: Θ(n) n - number of elements in queue, best case: Θ(1)
void Stack::resize_down()
{
    if (capacityStack < 2)
        return;
    capacityStack /= 2;
    int* auxNodes = new TElem[capacityStack];
    int* auxNextPos = new int[capacityStack];
    // Copy elements
    int indexOldContainers = tail;
    int indexNewContainers = 0;
    while (indexOldContainers != -1)
    {
        if (nextPosStack[indexOldContainers] != -1)
            auxNextPos[indexNewContainers] = indexNewContainers + 1;
        else
            auxNextPos[indexNewContainers] = -1;
        auxNodes[indexNewContainers] = nodesStack[indexOldContainers];
        indexOldContainers = nextPosStack[indexOldContainers];
        indexNewContainers++;
    }
    if (tail != -1)
        tail = 0;
    // Initialise nex pos
    firstEmptyStack = indexNewContainers;
    while (indexNewContainers < capacityStack - 1)
    {
        auxNextPos[indexNewContainers] = indexNewContainers + 1;
        indexNewContainers++;
    }
    auxNextPos[capacityStack - 1] = -1;

    // Finish
    delete[] nodesStack;
    delete[] nextPosStack;
    nodesStack = auxNodes;
    nextPosStack = auxNextPos;
}