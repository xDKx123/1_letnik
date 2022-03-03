#pragma once

#include <vector>

#include "Utils.h"

class HaarTransform
{
private:
    /* data */
public:
    HaarTransform(/* args */);
    ~HaarTransform();

    static std::vector<std::vector<double>> transform(std::vector<std::vector<double>> matrix);
    static std::vector<std::vector<double>> iTransform(std::vector<std::vector<double>> matrix);
};

HaarTransform::HaarTransform(/* args */)
{

}

HaarTransform::~HaarTransform()
{
}

std::vector<std::vector<double>> HaarTransform::transform(std::vector<std::vector<double>> matrix) {
    std::vector<std::vector<double>> tmp = Utils::multiplyMatrix(Utils::transformMatrics(Utils::haarMatrics()), matrix);

    return Utils::multiplyMatrix(tmp, Utils::haarMatrics());
}

std::vector<std::vector<double>> HaarTransform::iTransform(std::vector<std::vector<double>> matrix) {
    std::vector<std::vector<double>> tmp = Utils::multiplyMatrix(Utils::haarMatrics(), matrix);

    return Utils::multiplyMatrix(tmp, Utils::transformMatrics(Utils::haarMatrics()));
}