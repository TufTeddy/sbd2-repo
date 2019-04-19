#ifndef TMEMORY_H
#define TMEMORY_H
#pragma once
#include <string>
#include "tanumber.h"
//template <class T>
class TMemory
{
private:
    std::shared_ptr<TANumber> fNumber;
    bool fState;
public:
    TMemory() : fState(false) {}
    ~TMemory() {}

    void write(std::shared_ptr<TANumber> e) {
        fNumber = e->clone();
        fState = true;
    }
    /*std::unique_ptr<TANumber*> get() {
        fState = true;
        return fNumber;
    }*/
    bool getState() {
        return fState;
    }
    void clear() {
        fState = false;
    }
    std::string readMemoryState() {
        return fState ? std::string("_On") : std::string("_Off");
    }
    std::shared_ptr<TANumber> getFNumber() {
        return fNumber->clone();
    }
};

#endif // TMEMORY_H
