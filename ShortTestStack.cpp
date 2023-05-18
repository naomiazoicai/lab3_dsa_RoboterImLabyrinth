#include "ShortTestStack.h"
#include "Stack.h"
#include <assert.h>
using namespace std;
#include <iostream>

void test_all_stack()
{
    cout << "Test create stack!" << endl;
    test_createStack();
    test_pushStack();
    test_popStack();
    testMixStack();
    test_quantityStack();
}

void test_createStack()
{
    cout << "test create stack" << endl;
    Stack s;
    assert(s.isEmpty() == true);
    try {
        s.top();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    try {
        s.pop();
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
}

void test_pushStack()
{
    cout<<"test push stack"<<endl;
    Stack s;
    for (int i = 0; i < 10; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);
    for (int i = -10; i < 20; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);
    for (int i = -100; i < 100; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);

    for (int i = 10000; i > -10000; i--) {
        s.push(i);
    }
    assert(s.isEmpty() == false);
    assert(s.top() != 0);
    assert(s.top() == -9999);

    assert(s.pop() == -9999);
    assert(s.top() == -9998);
}

void test_popStack() {
    cout << "test pop stack" << endl;
    Stack s;
    for (int i = 0; i < 10; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);
    for (int i = -10; i < 20; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);
    for (int i = -100; i < 100; i++) {
        s.push(i);
    }
    assert(s.isEmpty() == false);

    for (int i = 10000; i > -10000; i--) {
        s.push(i);
    }
    assert(s.isEmpty() == false);


    for (int i = -9999; i <= 10000 ; i++) {
        assert(s.pop() == i);
    }
    assert(s.isEmpty() == false);
    for (int i = 99; i >= -100; i--) {
        assert(s.pop() == i);
    }
    assert(s.isEmpty() == false);
    for (int i = 19; i >= -10; i--) {
        assert(s.pop() == i);
    }
    assert(s.isEmpty() == false);

    for (int i = 9; i >= 0; i--) {
        assert(s.pop() == i);
    }
    assert(s.isEmpty() == true);
}

void testMixStack() {
    Stack stack;
    stack.push(1);
    assert(stack.top() == 1);
    stack.push(2);
    assert(stack.top() == 2);
    cout<<"test top stack"<<endl;

}

void test_quantityStack() {
    cout << "test quantity stack" << endl;
    Stack s;
    for (int i = 1; i <= 6; i++) {
        for (int j = 30000; j >= -3000; j--) {
            s.push(i + j);
        }
    }

    for (int i = 6; i >= 1; i--) {
        for (int j = -3000; j <= 30000; j++) {
            assert(s.pop() == i + j);
        }
    }
}