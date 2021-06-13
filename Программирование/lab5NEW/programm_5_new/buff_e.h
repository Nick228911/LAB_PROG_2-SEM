#pragma once
#include <iostream>
#include <exception>


class Overflow_Buff : public std::exception {
    const char* what() const noexpect override {
        return "Buffer underflow";
    }
};

class Index : public std::exception {
    const char* what() const noexpect override {
        return "Index out of bounds";
    }
};