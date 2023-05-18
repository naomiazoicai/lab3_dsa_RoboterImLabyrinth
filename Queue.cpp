#include "Queue.h"
#include <exception>

using namespace std;


///queue constructor
///complexity:Θ(n), worst case: Θ(n) , average case: Θ(n), best case: Θ(n)
Queue::Queue()
{
    this->capacity = 2;
    this->size = 0;
    nodes = new TElem [capacity];
    nextPos = new int[capacity];
    head = -1;
    tail = -1;
    firstEmpty = 0;
    for (int i = 0; i < capacity-1; ++i)
    {
        nextPos[i] = i+1;
    }
    nextPos[capacity-1] = -1;
}

///pushes an element to the end of the queue
///complexity:O(n), worst case: Θ(n) , average case: Θ(1) (kleine Wahrscheinlichkeit fur resize), best case: Θ(1)
void Queue::push(TElem elem)
{
    if (firstEmpty == -1)
        resize_up();
    size++;
    if (isEmpty())
    {
        int currentElemPosition = firstEmpty;
        head = firstEmpty;
        tail = firstEmpty;
        nodes[currentElemPosition] = elem;
        firstEmpty = nextPos[firstEmpty];
        nextPos[currentElemPosition] = -1;
    }
    else
    {
        int currentElemPosition = firstEmpty;
        nextPos[tail] = currentElemPosition;
        nodes[currentElemPosition] = elem;
        firstEmpty = nextPos[firstEmpty];
        nextPos[currentElemPosition] = -1;
        tail = currentElemPosition;
    }

}

///returns the element from the front of the queue
///throws exception if the queue is empty
///complexity: Θ(1) worst, average and best
TElem Queue::top() const
{
    if (isEmpty())
        throw exception();
    return nodes[head];
}

///removes and returns the element from the front of the queue
///throws exception if the queue is empty
///complexity: Θ(1) worst, average and best
TElem Queue::pop()
{
    if (isEmpty())
        throw exception();

    int popPos = head;
    TElem toPopElement = nodes[popPos];
    head = nextPos[head];
    nextPos[popPos] = firstEmpty;
    firstEmpty = popPos;
    size--;
    if (size == capacity/4)
        resize_down();
    return toPopElement;
}

///checks if the queue is empty
///complexity: Θ(1) worst, average and best
bool Queue::isEmpty() const
{
    if (head == -1)
        return true;
    return false;
}

///destructor
///complexity: Θ(1) worst, average and best
Queue::~Queue()
{
    delete[] this->nodes;
    delete[] this->nextPos;
}

///auxiliary method for allocating more space if needed
///complexity:O(oldCapacity), worst case: Θ(oldCapacity) , average case: Θ(1) (kleine Wahrscheinlichkeit fur resize), best case: Θ(1)
void Queue::resize_up()
{
    int oldCapacity = capacity;
    capacity *= 2;
    int* auxNodes = new TElem[capacity];
    int* auxNextPos = new int[capacity];

    // Copy old arrays
    for (int i = 0; i < oldCapacity; ++i)
    {
        auxNodes[i] = nodes[i];
        auxNextPos[i] = nextPos[i];
    }

    // Initialise the rest of the auxNextPos
    for (int i = oldCapacity; i < capacity-1; ++i)
    {
        auxNextPos[i] = i+1;
    }
    auxNextPos[capacity-1] = -1;

    // Finish
    firstEmpty = oldCapacity;
    delete[] nodes;
    delete[] nextPos;
    nodes = auxNodes;
    nextPos = auxNextPos;
}

///auxiliary method for deallocating space if needed
///complexity:O(n), worst case: Θ(n) , average case: Θ(n) n - number of elements in queue, best case: Θ(1)
void Queue::resize_down()
{
    if (capacity < 2)
        return;
    capacity /= 2;
    int* auxNodes = new TElem[capacity];
    int* auxNextPos = new int[capacity];
    // Copy elements
    int indexOldContainers = head;
    int indexNewContainers = 0;
    while (indexOldContainers != -1)
    {
        if (nextPos[indexOldContainers] != -1)
            auxNextPos[indexNewContainers] = indexNewContainers + 1;
        else
            auxNextPos[indexNewContainers] = -1;
            auxNodes[indexNewContainers] = nodes[indexOldContainers];
            indexOldContainers = nextPos[indexOldContainers];
            indexNewContainers++;
    }
    if (head != -1)
        head = 0;
    // Initialise nex pos
    firstEmpty = indexNewContainers;
    while (indexNewContainers < capacity - 1)
    {
        auxNextPos[indexNewContainers] = indexNewContainers + 1;
        indexNewContainers++;
    }
    auxNextPos[capacity - 1] = -1;

    // Finish
    delete[] nodes;
    delete[] nextPos;
    nodes = auxNodes;
    nextPos = auxNextPos;
}

///copy-constructor
///complexity:O(n), worst case: Θ(n) , average case: Θ(n) n - number of elements in queue, best case: Θ(1)
Queue::Queue(const Queue &q)
{
    capacity = q.capacity;
    size = q.size;
    head = q.head;
    firstEmpty = q.firstEmpty;
    nodes = new TElem [capacity];
    nextPos = new int [capacity];
    for (int i = 0; i < size; ++i)
    {
        nodes[i] = q.nodes[i];
    }
    for (int i = 0; i < capacity; ++i)
    {
        nextPos[i] = q.nextPos[i];
    }
}

///assignment operator
///complexity:O(n), worst case: Θ(n) , average case: Θ(n) n - number of elements in queue, best case: Θ(1)
Queue &Queue::operator=(const Queue &q){
    if (this == &q)
        return *this;
    capacity = q.capacity;
    size = q.size;
    head = q.head;
    firstEmpty = q.firstEmpty;
    nodes = new TElem [capacity];
    nextPos = new int [capacity];
    for (int i = 0; i < size; ++i)
    {
        nodes[i] = q.nodes[i];
    }
    for (int i = 0; i < capacity; ++i)
    {
        nextPos[i] = q.nextPos[i];
    }
    return *this;
}