#ifndef OBSERVER_H
#define OBSERVER_H
#include <iostream>
#include <vector>
using namespace std;

class Observer {
    public:
        Observer(); 
        virtual void notify() = 0; 
        virtual ~Observer() = default;
};

#endif
