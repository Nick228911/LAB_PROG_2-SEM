#include <iostream>
#include <vector>

using namespace std;


template<class T>
bool lesss(T a, T b) {
    if (a < b) return true;
    else return false;
}


template<class iterator, class pred>
bool all_of(iterator l, iterator r, pred p) {
    for (l; l != r; ++l) {
        if (p(*l)) return false;
    }
    return true;
}


template<class iterator, class T>
bool any_of(iterator l, iterator r, bool (&func)(T, T), T comp) {
    for (l; l != r; ++l) {
        if (func(*l, comp)) return true;
    }
    return false;
}


template<class iterator, class T>
bool none_of(iterator l, iterator r, bool (&func)(T, T), T comp) {
    for (l; l != r; ++l) {
        if (func(*l, comp)) return false;
    }
    return true;
}


template<class iterator, class T>
bool ant_of(iterator l, iterator r, bool (&func)(T, T), T comp) {
    int count = 0;
    for (l; l != r; ++l) {
        if (func(*l, comp)) ++count;
    }

    if (count == 1) return true;
    return false;
}


template<class iterator, class T>
bool is_sorted(iterator l, iterator r, bool (&func)(T, T)) {
    if (func(*l, *r)) {
        for (l; prev(l) != r; ++l) {
            if (!func(*l, *next(l))) return false;
        }
        return true;
    }
    if (!func(*l, *r)) {
        for (l; pref(l) != r; ++l) {
            if (func(*l, *next(l))) return false;
        }
        return true;
    }
}


template<class iterator, class T>
iterator find_not(iterator l, iterator r, T comp) {
    for (l; l != r; l++) {
        if (*l != comp) return l;

    }
    return r;
}


template<class iterator, class T>
bool MY_is_partitioned_MY(iterator l, iterator r, bool (&func)(T, T)) {
    int kk = 0;
    for (l; l != r; l++) {
        kk++;
        if (kk == 3) {
            break;
        }
    }

    if (kk < 3) return true;

    iterator ll, lr, rl, rr;
    ll = l;
    rr = r;
    l++;
    for (l; l != prev(r); l++) {
        int chl = 0;
        int ccl = 0;
        int chr = 0;
        int ccr = 0;
        lr = l;
        rl = l;

        for (ll; ll != lr; ll++) {
            if (func(*ll, *lr)) {
                chl = 1;
            } else {
                ccl = 1;
            }
            if (chl == ccl) return false;


        }
        for (rl; rl != rr; r--) {
            if (!func(*rr, *rl)) {
                chl = 1;
            } else {
                ccr = 1;
            }
            if (chr == ccr) return false;
        }


        if (chl == chr or ccl == ccr) {
            return true;
        } else {
            return false;
        }
    }
}


template<class iterator, class T>
bool is_partitioned(iterator l, iterator r, T p) {
    for (l; l != r; ++l)
        if (!p(*l))
            break;
    for (l; l != r; ++l)
        if (p(*l))
            return false;
    return true;
}


template<class iterator, class T>
iterator find_backward(iterator l, iterator r, T comp) {
    if (l == r) return l;
    if (l == prev(l)){
        if(*r == comp) return r;
        if(*l == comp) return l;
    }
    iterator nNn;
    for (l; l != r; l++){
        if (*l == comp){
            nNn = l;
        }
    }
   return nNn;
//    Я ПРОШЕЛСЯ ПО ВСЕМ ЭЛЕМЕНТАМ И НАШЕЛ
//    ПОСЛЕДНИЙ С НЧАЛА, ЧТО ЕСТЬ ПЕРВЫЙ С КОНЦА ЭЛЕМЕНТ
}



//template<class iterator, class T>
//bool rice_of(iterator l, iterator r){
//    for (l; next(l) != r; l++){
//        if (*l >= *next(l)) return false;
//    }
//    return true;
//}



template<class iterator, class T>
bool is_palindrome(iterator l, iterator r, bool (&func)(T, T), T comp) {
    int lc = 0, rc = 0;
    if (l == r) return true;
    if (l == prev(r)) return true;
    for (r; r != l; l++, r--) {
//        lc++;
//        rc++;
        if (next(l) == prev(r) or next(l) == prev(r, 2)) {
            if (*l != *prev(r)) return false;
            break;
        } else {

            if (*l != *prev(r)) return false;

        }


//    int count = 0;
//    iterator lr = l;
//    iterator rr = r;
//    for (l; l != r; ++r) {
//        ++count;
//    }
//    l = lr;
//    if (count % 2 == 1){
//        while (r != l){
//            if (!lesss(*next(l), *l) and !lesss(*pref(r), *r)) return false;
//            l++;
//            r--;
//        }
//    } else {
//        while (next(l) != pref(pref(r))){
//            if (!lesss(*next(l), *l) and !lesss(*pref(r), *r)) return false;
//            l++;
//            r--;
//        }
//    }
//    return true;
    }
    return true;
}


int main() {
    vector<int> a = {1, 3, 2, 2};


    return 0;
}
