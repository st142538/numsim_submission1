#include "array2d.h"

#include <cassert>
#include <iostream>

Array2D::Array2D(std::array<int,2> size) :
    size_(size)
{
    // allocate data, initialize to 0
    data_.resize(size_[0]*size_[1], 0.0);
}

//! get the size
std::array<int,2> Array2D::size() const
{
    return size_;
}

//! get the size in x direction
int Array2D::sizeX() const
{
    return size_[0];
}

//! get the size in y direction
int Array2D::sizeY() const
{
    return size_[1];
}

double &Array2D::operator()(int i, int j)
{
    const int index = j*size_[0] + i;

    // assert that indices are in range
    assert(0 <= i && i < size_[0]);
    assert(0 <= j && j < size_[1]);
    assert(j*size_[0] + i < (int)data_.size());

    return data_[index];
}

double Array2D::operator()(int i, int j) const
{
    const int index = j*size_[0] + i;

    // assert that indices are in range
    assert(0 <= i && i < size_[0]);
    assert(0 <= j && j < size_[1]);
    assert(j*size_[0] + i < (int)data_.size());

    return data_[index];
}

double Array2D::max() const
{
    double maximum = data_[0];
    for (int i = 1; i < size_[0]*size_[1]; ++i)
    {
        if (data_[i] > maximum) 
        {
            maximum = data_[i];
        }
    }
    return maximum;
}


