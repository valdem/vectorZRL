#include "MyVector.h"
#include <iostream>

int main() {
    MyVector vector;
    vector.insert(0,2.3);
    vector.insert(1,5.6);
    vector.insert(2,1.8);
    vector.print();
    vector.sortedSquares(vector, SortedStrategy::decrease);
    vector.print();
}
