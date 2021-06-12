#pragma once

#include <iostream>
#include <iterator>
#include <initializer_list>

template <class T>
class Buffer {
private:
    T *element = nullptr;
    size_t Bamount = 0;
    size_t Bcapacity = 0;

public:

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *BDat = nullptr;

    public:

        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        difference_type operator-(const iterator &something) const {
            return BDat - something.BDat;
        }

        explicit iterator(T* Begin) {
            BDat = Begin;
        }
        iterator(const iterator& num) {
            BDat = num.BDat;
        }
        ~iterator() = default;

        T &operator*() {
            return *BDat;
        }
        T *operator->() {
            return BDat;
        }

        iterator operator++() {
            ++BDat; return *this;
        }
        iterator operator--() {
            --BDat; return *this;
        }
        iterator operator+(int x) {
            BDat = BDat + x; return *this;
        }
        iterator operator-(int x) {
            BDat = BDat - x; return *this;
        }

        bool operator==(const iterator &something) const {
            return BDat == something.BDat;
        }
        bool operator!=(const iterator &something) const {
            return BDat != something.BDat;
        }
        bool operator<(const iterator &something) const {
            return BDat < something.BDat;
        }
        bool operator<=(const iterator &something) const {
            return BDat <= something.BDat;
        }
        bool operator>(const iterator &something) const {
            return BDat > something.BDat;
        }
        bool operator>=(const iterator &something) const {
            return BDat >= something.BDat;
        }

    };


    explicit Buffer(size_t capacity) {
        Bcapacity = capacity;
        element = new T[Bcapacity];
    }
    Buffer(const Buffer& other) :
            Bamount(other.Bamount),
            Bcapacity(other.Bcapacity),
            element(other.data) {
    };
    ~Buffer() {
        delete element;
    }


    iterator begin() const {
        return iterator(element);
    }
    iterator end() const {
        return iterator(element + Bamount);
    }
    // Получение капасити и размера массива
    [[nodiscard]] size_t capacity() const {
        return this->Bcapacity;
    }
    [[nodiscard]] size_t size() const {
        return this->Bamount;
    }


    void push_front(T x);
    void pop_front();
    void push_back(T x);
    void pop_back();
    void insert(size_t ind, T x);
    void ret_index(size_t ind);
    void ret_index(iterator ind);
    void insert(iterator ind, T x);
    void remove(size_t ind);
    void resize(size_t new_capacity);
    void infoBuff();


    T operator[] (size_t ind) {
        return element[ind % Bcapacity];
    }

    Buffer& operator=(std::initializer_list<T> list) {
        Bcapacity = list.size();
        element = new T[list.size()];
        for (auto it = list.begin(); it != list.end(); ++it)
            push_back(*it);
        return *this;
    }


};