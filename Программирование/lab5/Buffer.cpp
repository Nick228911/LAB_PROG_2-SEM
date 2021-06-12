#include <iostream>
#include "Buffer.h"


template<typename T>


//добавление в начало
void Buffer<T>::push_front(T a) {
    if (Bamount < Bcapacity) {
        for (size_t i = Bamount; i >= 1; i--) {
            element[i] = element[i - 1];
        }
        element[0] = a;
        Bamount++;
    }
    else {
        std::cout << "\noverwrite element " << element[0] << "\n";
        for (size_t i = Bcapacity - 1; i >= 1; i--) {
            element[i] = element[i - 1];
        }
        element[0] = a;
    }
}



//добавить в конец
template<typename T>
void Buffer<T>::push_back(T a) {
    if (Bamount < Bcapacity) {
        element[Bamount] = a;
        Bamount++;
    }
    else {
        std::cout << "\ndelte element " << element[Bcapacity - 1] << "\n";
        for (size_t i = 1; i < Bcapacity; i++) {
            element[i - 1] = element[i];
        }
        element[Bcapacity - 1] = a;
    }
}




//удалить начальный элемент
template<typename T>
void Buffer<T>::pop_front() {
    std::cout << "\ndelte element " << element[0] << "\n";
    for (size_t i = 0; i < Bamount - 1; i++) {
        element[i] = element[i + 1];
    }
    Bamount--;
}




//удалить конечный элемент
template<typename T>
void Buffer<T>::pop_back() {
    if (Bamount > 0) {
        std::cout << "\ndelte element " << element[Bcapacity - 1] << "\n";
        element[Bcapacity - 1] = nullptr;
        Bamount--;
    }
    else
        std::cout << "\nthere are no items in the buffer\n";
}




template<typename T>
void Buffer<T>::ret_index(size_t ind) {
    T dd = element[ind % Bcapacity];
    return dd;
}





template<typename T>
void Buffer<T>::insert(iterator ind, T a) {
    *(begin() + (ind - begin()) % Bamount) = a;
}

template<typename T>
void Buffer<T>::remove(size_t ind) {
    for (size_t i = ind + 1; i < Bamount; i++) {
        element[(i - 1) % Bcapacity] = element[i % Bcapacity];
    }
    Bamount--;
}

template<typename T>
void Buffer<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    Bamount = std::min(Bamount, new_capacity);
    for (size_t i = 0; i < Bamount; i++) {
        new_data[i] = element[i];
    }
    delete element;
    element = new_data;
    Bcapacity = new_capacity;
}


template<typename T>
void Buffer<T>::infoBuff() {
    std::cout << "Capacity = " << capacity() << "\n";
    std::cout << "Size = " << size() << "\n";
}