#pragma once
#include <iostream>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

enum class SortedStrategy {
    decrease,
    increase
};

// тип значений в векторе
// потом будет заменен на шаблон
using ValueType = double;

class MyVector
{
public:
    MyVector(size_t size = 0, ResizeStrategy strategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    MyVector(size_t size, ValueType value, ResizeStrategy strategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    
    MyVector(const MyVector& copy);
    MyVector& operator=(const MyVector& copy);

    ~MyVector();

    // для умненьких — реализовать конструктор и оператор для перемещения

    size_t capacity() const;
    size_t size() const;
    float loadFactor();
    
    class iterator
    {
    public:
        iterator(const MyVector* vector, int index):iVector(),index(){
            
        }
        const ValueType& operator*() const {
            return iVector->operator[](index);
        }
        ValueType& operator*() {
            return iVector->operator[](index);
        }
        const ValueType operator->() const{
            return iVector->operator[](index);
        }
        ValueType operator->() {
            return iVector->operator[](index);
        }
        iterator &operator++() {
            ++index;
            return *this;
        }
        bool operator!=(const iterator& other) {
            return index != other.index;
        }
        bool operator==(const iterator& other) {
            return index == other.index;
        }
    private:
        const MyVector* iVector;
        int index = -1;
    };
    
    iterator begin() const;
    iterator end() const;
    
    // доступ к элементу,
    // должен работать за O(1)
    ValueType& operator[](const size_t i) const;

    // добавить в конец,
    // должен работать за amort(O(1))
    void pushBack(const ValueType& value);
    // вставить,
    // должен работать за O(n)
    void insert(const size_t i, const ValueType& value);    // версия для одного значения
    void insert(const size_t i, const MyVector& value);        // версия для вектора

    // удалить с конца,
    // должен работать за amort(O(1))
    void popBack();
    // удалить
    // должен работать за O(n)
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);            // удалить len элементов начиная с i

    // найти элемент,
    // должен работать за O(n)
    // если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
    // если искомого элемента нет, вернуть -1
    long long int find(const ValueType& value, bool isBegin = true) const;

    // зарезервировать память (принудительно задать capacity)
    void reserve(const size_t capacity);

    // изменить размер
    // если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
    // если меньше - обрезаем вектор
    void resize(const size_t size, const ValueType = 0.0);

    // очистка вектора, без изменения capacity
    void clear();
    
    void print();
    
    MyVector sortedSquares(const MyVector& vec, SortedStrategy strategy) {
        if (strategy == SortedStrategy::increase) {
            for (size_t i = 0; i<_size; i++) {
                _data[i] *= _data[i];
            }
            ValueType temp = 0;
            for (size_t i = 0; i<_size-1; ++i) {
                for (size_t j = 0; j<_size-1; ++j) {
                    if (_data[j+1] < _data[j]) {
                        temp = _data[j+1];
                        _data[j+1] = _data[j];
                        _data[j] = temp;
                    }
                }
            }
        }
        else if (strategy == SortedStrategy::decrease) {
            for (size_t i = 0; i<_size; i++) {
                _data[i] *= _data[i];
            }
            ValueType temp = 0;
            for (size_t i = 0; i<_size-1; ++i) {
                for (size_t j = 0; j<_size-1; ++j) {
                    if (_data[j+1] > _data[j]) {
                        temp = _data[j+1];
                        _data[j+1] = _data[j];
                        _data[j] = temp;
                    }
                }
            }
        }
        return vec;
    }
    
private:
    ValueType* _data = nullptr;
    size_t _size = 0;
    size_t _capacity;
};
