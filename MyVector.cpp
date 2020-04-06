#include "MyVector.h"

MyVector::MyVector(size_t size, ResizeStrategy, float coef) {
    _data = new ValueType[size];
}


MyVector::MyVector(size_t size, ValueType value, ResizeStrategy, float coef) {
    _data = new ValueType[size];
}

MyVector::MyVector(const MyVector& copy) {
    for (int i = 0; i<_size; i++) {
        _data[i] = copy._data[i];
    }
}

MyVector& MyVector::operator=(const MyVector& copy) {
    ValueType* eqVector = new ValueType[copy._size];
    for (size_t i = 0; i<_size; i++) {
        eqVector[i] = copy._data[i];
    }
    delete[] _data;
    this->_data = eqVector;
    this->_size = copy._size;
    return *this;
}

MyVector::~MyVector() {
    delete _data;
    _size = 0;
    _capacity = 0;
}

size_t MyVector:: capacity() const {
    return _capacity;
}

size_t MyVector:: size() const {
    return _size;
}

float MyVector:: loadFactor() {
    return _size/_capacity;
}


MyVector::iterator MyVector::begin() const {
    return MyVector::iterator{this, 0};
}

MyVector::iterator MyVector::end() const{
    return MyVector::iterator{this, static_cast<int>(_size)};
}

ValueType& MyVector:: operator[](const size_t i) const {
    if (i >= _size) {
        std::cout<<"error"<<std::endl;
    }
    return _data[i];
}

void MyVector:: pushBack(const ValueType& value) {
    ValueType* puVector = new ValueType[_size+1];
    for (size_t i = 0; i<_size; i++) {
        puVector[i] = _data[i];
    }
    puVector[_size] = value;
    delete[] _data;
    this->_data = puVector;
    this->_size += 1;
}

void MyVector:: insert(const size_t i, const ValueType& value) {
    auto inVector = new ValueType[_size+i];
    for (auto idx = 0; idx < _size; ++idx) {
        inVector[idx] = _data[idx];
    }
    delete[] _data;
    this->_data = inVector;
    _data[i] = value;
    this->_size += 1;
}

void MyVector:: insert(const size_t i, const MyVector& value) {
    auto inVector = new ValueType[_size+value.size()];
    for (auto idx = 0; idx<i; ++idx) {
        inVector[idx] = _data[idx];
    }
    size_t j = 0;
    for(auto idx = i; idx<i + value.size(); ++idx) {
        inVector[idx] = value[j];
        j++;
    }
    for (auto idx = i + value.size(); idx<_size+value.size(); ++idx) {
        size_t k = i;
        inVector[idx] = _data[k];
        k++;
    }
    delete[] _data;
    this->_data = inVector;
    this->_size += value.size();
}


void MyVector:: popBack() {
    ValueType* popVector = new ValueType[_size-1];
    for (size_t i = 0; i<_size-1; i++) {
        popVector[i] = _data[i];
    }
    delete[] _data;
    this->_data = popVector;
    this->_size -= 1;
}

void MyVector:: erase(const size_t i) {
    ValueType* erVector = new ValueType[_size-1];
    for (size_t j = 0; j<i; j++) {
        erVector[j] = _data[j];
    }
    for (size_t j = i; j<_size-1; j++) {
        erVector[j] = _data[j+1];
    }
    delete[] _data;
    this->_data = erVector;
    this->_size -= 1;
}

void MyVector:: erase(const size_t i, const size_t len) {
    ValueType* erVector2 = new ValueType[_size-len];
    for (size_t j = 0; j<i; j++) {
        erVector2[j] = _data[j];
    }
    for (size_t j = i; j<_size-len; j++) {
        erVector2[j] = _data[j+len];
    }
    delete[] _data;
    this->_data = erVector2;
    this->_size -= len;
}

long long int MyVector:: find(const ValueType& value, bool isBegin) const {
    if (isBegin == true) {
        size_t i = 0;
        while (_data[i] != value ) {
            i++;
        }
        return i+1;
    }
    else {
        size_t i = _size-1;
        while (_data[i] != value ) {
            i--;
        }
        return i-1;
    }
    return -1;
}

void MyVector:: reserve(const size_t capacity) {
    _capacity = capacity;
}


void MyVector:: resize(const size_t size, const ValueType) {
    if (size>_size) {
        ValueType* reVector = new ValueType[size];
        for (size_t i = 0; i<_size; i++) {
            reVector[i] = _data[i];
        }
        delete[] _data;
        this->_data = reVector;
        this->_size = size;
    }
    else {
        ValueType* reVector = new ValueType[size];
        for (size_t i = 0; i<size; i++) {
            reVector[i] = _data[i];
        }
        delete[] _data;
        this->_data = reVector;
        this->_size = size;
    }
}

void MyVector:: clear() {
    _size = 0;
}

void MyVector:: print() {
    for (size_t i = 0; i<_size; i++) {
        std::cout<<_data[i]<<std::endl;
    }
}







