#pragma once

#include <iostream>
#include "buff_e.h"
using namespace std;

template<class T>
struct element {
    T val;
    bool is_end = false;
    element *prev;
    element *next;
};

template<class T>
class buffer_iterator
        : public iterator<random_access_iterator_tag, T> {
public:
    buffer_iterator() = delete;

    buffer_iterator(element<T> *p) : ptr_(p) {}

    buffer_iterator(const buffer_iterator<T> &it) : ptr_(it.ptr_) {}

    inline buffer_iterator<T> &operator=(const T &value) {
        ptr_ = *value;
        return *this;
    }

    inline buffer_iterator<T> &operator=(T *ptr) {
        ptr_ = ptr;
        return *this;
    }

    inline buffer_iterator<T> &operator=(const buffer_iterator<T> &it) {
        ptr_ = it.ptr_;
        return *this;
    }


    inline T *operator->() const {
        return *(ptr_->val);
    }

    inline T &operator*() const {
        return ptr_->val;
    }

    inline buffer_iterator<T> &operator+=(const int &val) {
        for (int i = 0; i < val; i++)
            ptr_ = ptr_->next;
        return *this;
    }

    inline buffer_iterator<T> &operator-=(const int &val) {
        for (int i = val; i > 0; i--)
            ptr_ = ptr_->prev;
        return *this;
    }

    friend inline int operator+(const buffer_iterator<T> &it1, const buffer_iterator<T> &it2) {
        buffer_iterator<T> it = it1;
        int result1 = 0;
        while (!it.ptr_->prev->is_end) {
            it--;
            result1++;
        }

        it = it2;
        int result2 = 0;
        while (!it.ptr_->prev->is_end) {
            it--;
            result2++;
        }

        return result1 + result2;
    }

    friend inline int operator-(buffer_iterator<T> it1, buffer_iterator<T> it2) {
        buffer_iterator<T> it = it1;
        int result1 = 0;
        while (!it.ptr_->prev->is_end) {
            it--;
            result1++;
        }

        it = it2;
        int result2 = 0;
        while (!it.ptr_->prev->is_end) {
            it--;
            result2++;
        }

        return result1 - result2;
    }

    friend inline buffer_iterator<T> operator+(const buffer_iterator<T> &it, const int &val) {
        return buffer_iterator(it + val);
    }

    friend inline buffer_iterator<T> operator-(const buffer_iterator<T> &it, const int &val) {
        return buffer_iterator(it - val);
    }

    friend inline bool operator==(const buffer_iterator<T> &it1, const buffer_iterator<T> &it2) {
        return it1.ptr_ == it2.ptr_;
    }

//    inline bool operator==(T *it) {
//        return ptr_ == it;
//    }

    inline bool operator!=(const buffer_iterator<T> &it) {
        return ptr_ != it.ptr_;
    }

//    inline bool operator!=(T *it) {
//        return ptr_ != it;
//    }

    friend inline bool operator>(const buffer_iterator<T> &it1, const buffer_iterator<T> &it2) {
        buffer_iterator<T> it = it1;

        while (it != it2) {
            if (it.ptr_->is_end)
                return true;
            it++;
        }
        return false;
    }


    friend inline bool operator<(const buffer_iterator<T> &it1, const buffer_iterator<T> &it2) {
        return it2 > it1;
    }

private:
    element<T> *ptr_;
};


template<class T>
class buffer {
private:
    unsigned capacity_;
    element<T> *l;
    element<T> *r;
public:
    template<class V>
    friend
    class buffer_iterator;

    friend struct element<T>;

    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<const T> const_iterator;

    buffer(unsigned capacity = 100)
            : capacity_(capacity) {
        if (capacity == 0)
            throw Overflow_Buff();
        l = new element<T>();
        r = l;
        element<T> *cur = l;
        for (int i = 1; i < capacity; i++) {
            cur->next = new element<T>();
            cur->next->prev = cur;
            cur = cur->next;
        }
        cur->next = new element<T>;
        cur->next->is_end = true;
        cur->next->next = l;
        cur->next->prev = cur;
        l->prev = cur->next;
    }

    buffer(const buffer<T> &other)
            : capacity_(other.capacity_) {
        l = new element<T>();

        element<T> *cur = l;
        element<T> *other_cur = other.l;

        bool content_end = other.r == other.l;
        for (int i = 0; i < capacity_; i++) {
            if (!content_end)
                cur->val = other_cur->val;

            if (other_cur == other.r) {
                r = cur;
                content_end = true;
            }
            cur->val = other_cur->val;

            cur->next = new element<T>();
            cur->next->prev = cur;

            cur = cur->next;
            other_cur = other_cur->next;
        }
        cur->next = new element<T>();
        cur->is_end = true;
        cur->next->prev = cur;
        cur->next->next = l;
    }

    ~buffer() {
        element<T> *cur = l->next;
        while (cur != l) {
            element<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        delete l;
    }

    void push_back(T value) {
        if (r->is_end) {
            l = l->next;
            r->is_end = false;
            r->next->is_end = true;
        }

        r = r->next;

        r->prev->val = value;
    }

    T pop_back() {
        if (r == l)
            throw Overflow_Buff();
        r = r->prev;
        return r->val;
    }

    void push_front(T a) {
        if (r == l) {
            r = l->next;
            l->val = a;
            return;
        } else if (l->prev == r) {
            r->is_end = false;
            r = r->prev;
            r->is_end = true;
        }

        l->prev->is_end = false;
        l->prev->prev->is_end = true;
        l->prev->val = a;
        l = l->prev;
    }

    T pop_front() {
        if (r == l)
            throw Overflow_Buff();

        T value = l->val;

        l->prev->is_end = false;
        l = l->next;
        l->prev->is_end = true;

        return value;
    }

    T &front() {
        if (r == nullptr)
            throw Index();
        return l->val;
    }

    T &back() {
        return r->prev->val;
    }

    int size() {
        if (r == nullptr)
            return 0;
        element<T> *cur = l;
        int size = 0;
        while (cur != r) {
            size++;
            cur = cur->next;
        }
        return size;
    }

    unsigned capacity() {
        return capacity_;
    }

    bool empty() {
        return r == nullptr;
    }

    bool full() {
        return r->is_end;
    }

    T &operator[](unsigned ind) const {
        if (ind > capacity_ || r == nullptr)
            throw Index();

        element<T> *cur = l;
        for (int i = 0; i < ind; i++) {
            if (cur == r)
                throw Index();
            cur = cur->next;
        }
        if (cur == r)
            throw Index();

        return cur->val;
    };

    void resize(unsigned new_capacity) {
        if (new_capacity == 0) {
            throw Overflow_Buff();
        } else if (new_capacity < capacity_) {
            for (int cur_capacity = capacity_; cur_capacity > new_capacity; cur_capacity--) {
                l->prev->prev->prev->next = l->prev;
                element<T> *del_el = l->prev->prev;
                if (del_el == r)
                    r = l->prev;
                l->prev->prev = l->prev->prev->prev;
                delete del_el;
            }
        } else {
            for (int cur_capacity = capacity_; cur_capacity < new_capacity; cur_capacity++) {
                l->prev->prev->next = new element<T>();
                l->prev->prev->next->prev = l->prev->prev;
                l->prev->prev->next->next = l->prev;
                l->prev->prev = l->prev->prev->next;
                if (l->prev == r)
                    r = l->prev->prev;
            }
        }
        capacity_ = new_capacity;
    }

    iterator begin() {
        return iterator(l);
    }

    iterator end() {
        return iterator(r);
    }

    const_iterator begin() const {
        return const_iterator(l);
    }

    const_iterator end() const {
        return const_iterator(r);
    }

    friend istream &operator>>(istream &in, buffer<T> &buffer) {
        T value;
        in >> value;
        buffer.push_back(value);
        return in;
    }

    friend ostream &operator<<(ostream &out, buffer<T> &buffer) {
        out << buffer.pop_front() << "\n";
        return out;
    }

    void info() {
        if (r == l) {
            cout << "number of elements is Zero" << "\n";
            return;
        }
        element<T> *cur = l;
        do {
            if (cur == r)
                cout << "buffer ended";
            if (cur->is_end)
                cout << "end";
            if (!cur->is_end && cur != r)
                cout << cur->val << "\n";

            cout << " ";
            cout.flush();
            cur = cur->next;
        } while (cur != l);
        cout << ", size = " << size() << endl;
    }
};