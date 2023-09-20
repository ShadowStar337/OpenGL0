#pragma once
#include <vector>
#include <cstdint>
#include <iostream>

class Matrix {
public:
    Matrix();
    void init(uint32_t rows, uint32_t columns);
    void setData(const std::vector<float>& newData);
    void clear();
    bool equals(const Matrix &otherMatrix) const;
    void setToIdentity();
    Matrix multiply(const Matrix& otherMatrix) const;

    inline float getRows() const;
    inline float getColumns() const;
    inline const std::vector<float>& getData() const;
    inline std::vector<float> getDataCopy() const;
private:
    uint32_t rows;
    uint32_t columns;
    std::vector<float> data;
};

std::ostream& operator<<(std::ostream& outputStream, const Matrix& matrix);

inline float Matrix::getRows() const
{
    return rows;
}

inline float Matrix::getColumns() const
{
    return columns;
}

inline const std::vector<float> &Matrix::getData() const
{
    return data;
}

inline std::vector<float> Matrix::getDataCopy() const
{
    return data;
}