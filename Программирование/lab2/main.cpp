#include <iostream>
#include <vector>

using namespace std;

class polynom {
public:
    float *cff;
    int size_;

    polynom(int size1 = 1)
            : size_(size1) {
        this->cff = new float[size_];
        for (int i = 0; i < size_; i++) {
            cff[i] = 0;
        }
    }

    polynom(const polynom &other) {
        this->size_ = other.size_;
        this->cff = new float[other.size_];
        for (int i = 0; i < other.size_; i++) {
            this->cff[i] = other.cff[i];
        }
    }

    ~polynom() {
        delete[] cff;
    }

    void c_cin() {
        for (int i = 0; i < size_; i++) {
            cin >> cff[i];
            if (size_ > 1) {
                if (i != size_ - 1) {
                    cout << "X^" << size_ - 1 << "\n";
                }
            }
        }
    }

    polynom &operator=(const polynom &other) {
        if (&other == this) {
            return *this;
        }
        this->size_ = other.size_;
        delete[] this->cff;
        this->cff = new float[other.size_];
        for (int i = 0; i < other.size_; i++) {
            this->cff[i] = other.cff[i];
        }
        return *this;
    }

    polynom &operator+=(const polynom &pol2) {

        if (pol2.size_ > this->size_) {
//            this->size_ = pol2.size_;
            float *q = this->cff;
            this->cff = new float[pol2.size_];
            for (int i = 0; i < this->size_; ++i) {
                this->cff[i] = q[i];
            }
            delete[] q;
            this->size_ = pol2.size_;

        }
        for (int i = 0; i < pol2.size_; ++i) {
            this->cff[i] += pol2.cff[i];
        }
        return *this;
    }


    polynom &operator-=(const polynom &pol2) {
        if (pol2.size_ > this->size_) {
            this->size_ = pol2.size_;
        }
        for (int i = 0; i < pol2.size_; ++i) {
            this->cff[i] -= pol2.cff[i];
        }
        return *this;

    }


    polynom &operator*=(const float vall) {
        for (int i = 0; i < this->size_; i++) {
            this->cff[i] = this->cff[i] * vall;
        }
        return *this;
    }

    polynom &operator/=(const float vall) {
        for (int i = 0; i < this->size_; i++) {
            this->cff[i] = this->cff[i] / vall;
        }
        return *this;
    }


    friend const polynom &operator/(const polynom &pol, const float vall) {
        float dell[pol.size_];
        for (int i = 0; i < pol.size_; ++i) {
            dell[i] = pol.cff[i];
        }

        for (int i = 0; i < pol.size_; ++i) {
            dell[i] /= vall;
        }
        return reinterpret_cast<polynom &>(*dell);
    }

    friend const polynom &operator*(const polynom &pol1, const polynom &pol2) {
        float ress[pol2.size_ * pol1.size_];
        for (int i = 0; i < pol1.size_; i++) {
            for (int j = 0; j < pol2.size_; i++) {
                ress[i + j] += pol1.cff[i] * pol2.cff[i];
            }
        }
        return *ress;
    }

    float operator[](int vall) {
        return cff[vall];
    }

    friend const polynom operator+(const polynom &left, const polynom &right) {
        polynom www = left;
        www += right;
        return www;
    }

    friend const polynom operator-(const polynom &left, const polynom &right) {
        float *new_summ;
        int k = left.size_;
        int l = right.size_;
        if (k >= l) {
            for (int i = 0; i < k; i++) {
                new_summ[i] = left.cff[i];
            }
            for (int i = 0; i < l; i++) {
                new_summ[i] = new_summ[i] - right.cff[i];
            }
        } else {
            for (int i = 0; i < l; i++) {
                new_summ[i] = right.cff[i];
            }
            for (int i = 0; i < k; i++) {
                new_summ[i] = new_summ[i] - left.cff[i];
            }

        }
        return *new_summ;
    }
};


bool operator==(const polynom &pol1, const polynom &pol2) {
    if (pol1.size_ != pol2.size_) {
        return false;
    }
    for (int i = 0; i < pol1.size_; i++) {
        if (pol1.cff != pol2.cff) {
            return false;
        }
    }
}

bool operator!=(const polynom pol1, const polynom pol2) {
    return !operator==(pol1, pol2);
}

ostream &operator<<(ostream &out, const polynom &value) {
    for (int i = 0; i < value.size_; i++) {
        if (value.size_ > 1 and i != value.size_ - 1)
            out << " " << value.cff[i] << "X^" << value.size_ - 1 - i << " +";
        if (value.size_ > 0 and value.size_ < 2) {
            out << value.cff[0];
        }
        if (i == value.size_ - 1) {
            out << " " << value.cff[i];
        }
    }
    return out;
}

istream &operator>>(istream &in, polynom &value) {
    in >> value.size_;
    for (int i = 0; value.size_; i++) {

        in >> value.cff[i];
    }
}


int main() {


    return 0;
}
