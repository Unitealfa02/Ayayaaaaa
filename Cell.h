// Cell.h
#pragma once

class Cell {
public:
    Cell() : state(false) {}

    bool getState() const { return state; }
    void setState(bool newState) { state = newState; }

private:
    bool state;
};
