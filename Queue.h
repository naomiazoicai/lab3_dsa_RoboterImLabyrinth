#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
    TElem* nodes; // array of nodes
    int* nextPos; //array of next positions
    int head;
    int tail;
    int capacity;
    int size;
    int firstEmpty; // index of the first empty position

    void resize_up();
    void resize_down();

public:
    Queue();

    // Copy constructor
    Queue(const Queue &q);

    // Assigment operator
    Queue& operator=(const Queue &q);

    //pushes an element to the end of the queue
    void push(TElem e);

    //returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem top() const;

    //removes and returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem pop();

    //checks if the queue is empty
    bool isEmpty() const;

    //destructor
    ~Queue();
};
