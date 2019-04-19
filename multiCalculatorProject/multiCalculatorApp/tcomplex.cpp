#include "tcomplex.h"

std::unique_ptr<TANumber> TComplex::summ(std::unique_ptr<TANumber> second)
{
    this->real += dynamic_cast<TComplex*>(second.get())->real;
    this->imaginary += dynamic_cast<TComplex*>(second.get())->imaginary;
    return this->clone();
}

std::unique_ptr<TANumber> TComplex::substract(std::unique_ptr<TANumber> second)
{
    this->real -= dynamic_cast<TComplex*>(second.get())->real;
    this->imaginary -= dynamic_cast<TComplex*>(second.get())->imaginary;
    return this->clone();
}

std::unique_ptr<TANumber> TComplex::mult(std::unique_ptr<TANumber> second)
{
    double _secondReal = dynamic_cast<TComplex*>(second.get())->real,
            _secondIm = dynamic_cast<TComplex*>(second.get())->imaginary,
            _firstReal = this->real, _firstIm = this->imaginary;

    this->real = _firstReal * _secondReal - _firstIm * _secondIm;
    this->imaginary = _firstReal * _secondIm + _firstIm * _secondReal;

    return this->clone();
}

std::unique_ptr<TANumber> TComplex::divide(std::unique_ptr<TANumber> second)
{
    double _secondReal = dynamic_cast<TComplex*>(second.get())->real,
            _secondIm = dynamic_cast<TComplex*>(second.get())->imaginary,
            _firstReal = this->real, _firstIm = this->imaginary;

    this->real = (_firstReal * _secondReal + _firstIm * _secondIm) /
            (_secondReal*_secondReal + _secondIm * _secondIm);

    this->imaginary = (_secondReal * _firstIm - _firstReal * _secondIm) /
            (_secondReal * _secondReal + _secondIm * _secondIm);

    return this->clone();
}

std::unique_ptr<TANumber> TComplex::square()
{
    double tempReal = this->real, tempIm = this->imaginary;
    this->real = tempReal * tempReal - tempIm * tempIm;
    this->imaginary = tempReal * tempIm + tempReal * tempIm;
    return this->clone();
}

bool TComplex::equal(std::unique_ptr<TANumber> second)
{
    if((fabs(this->real - dynamic_cast<TComplex*>(second.get())->real) <= DBL_EPSILON) &&
            ( fabs(this->imaginary - dynamic_cast<TComplex*>(second.get())->imaginary) <= DBL_EPSILON)){
        return true;
    }else{
        return false;
    }
}

bool TComplex::not_equal(std::unique_ptr<TANumber> second)
{
    if((fabs(this->real - dynamic_cast<TComplex*>(second.get())->real) <= DBL_EPSILON) &&
            ( fabs(this->imaginary - dynamic_cast<TComplex*>(second.get())->imaginary) <= DBL_EPSILON)){
        return false;
    }else{
        return true;
    }
}

std::unique_ptr<TANumber> TComplex::copy()
{
    return this->clone();
}

void TComplex::reverse()
{
    double tempReal = this->real, tempIm = this->imaginary;

    this->real = tempReal / (tempReal * tempReal + tempIm * tempIm);
    this->imaginary = tempIm / (tempReal * tempReal + tempIm * tempIm);
}

double TComplex::angleDegrees()
{
    if (this->real > 0)
    {
        if (this->imaginary >= 0)
            return 180 / M_PI * std::atan(this->imaginary / this->real);
        else if (this->imaginary < 0)
            return  180 * M_PI - std::atan(this->imaginary / this->real);
    }
    else if (this->real < 0)
    {
        if (this->imaginary >= 0)
            return 180 - std::atan(this->imaginary / this->real);
        else if (this->imaginary < 0)
            return 180 + std::atan(this->imaginary / this->real);
    }
    else if (this->real == 0)
    {
        if (this->imaginary >= 0)
            return 90;
        else if (this->imaginary < 0)
            return 270;
    }
}

double TComplex::angleRadians()
{
    if (this->real > 0)
    {
        if (this->imaginary >= 0)
            return std::atan(this->imaginary / this->real);
        else if (this->imaginary < 0)
            return 2 * M_PI - std::atan(this->imaginary / this->real);
    }

    else if (this->real < 0)
    {
        if (this->imaginary >= 0)
            return M_PI - std::atan(this->imaginary / this->real);
        else if (this->imaginary < 0)
            return M_PI + std::atan(this->imaginary / this->real);
    }
    else if (this->real == 0)
    {
        if (this->imaginary >= 0)
            return M_PI_2;
        else if (this->imaginary < 0)
            return 3 * M_PI_2;
    }
}

double TComplex::absolute()
{
    double result = std::sqrt(this->real * this->real
        + this->imaginary * this->imaginary);
    return result;
}

void TComplex::power(int index)
{
    double fi = this->angleRadians();

    TComplex *first = new TComplex((std::pow(this->absolute(), index), 0), 0);
    TComplex *second = new TComplex(std::cos(index * fi), std::sin(index * fi));
    first->mult(second->clone());
}

std::string TComplex::getNumberAsString()
{
    std::string realTempString, imaginaryTempString;
    double tempDouble, imaginaryTemp;

    if (modf(real,&tempDouble) == 0){
        realTempString = std::to_string(static_cast<int>(tempDouble));
    }else{
        realTempString = std::to_string(real);
        while(realTempString.back() == '0'){
            realTempString.pop_back();
        }
    }

    if (imaginary < 0){
        realTempString += "-i";
        imaginaryTemp = imaginary * (-1);
    }else{
        realTempString += "+i";
        imaginaryTemp = imaginary;
    }

    if (modf(imaginaryTemp,&tempDouble) == 0){
        imaginaryTempString = std::to_string(static_cast<int>(tempDouble));
    }else{
        imaginaryTempString = std::to_string(imaginaryTemp);
        while(imaginaryTempString.back() == '0'){
            imaginaryTempString.pop_back();
        }
    }

    realTempString += imaginaryTempString;

    return realTempString;
}

double TComplex::getRealDouble() const
{
    return real;
}

void TComplex::setRealDouble(double value)
{
    real = value;
}

double TComplex::getImaginaryDouble() const
{
    return imaginary;
}

void TComplex::setImaginaryDouble(double value)
{
    imaginary = value;
}

std::string TComplex::getRealStr()
{
    return std::to_string(real);
}

void TComplex::setRealStr(std::string str)
{
    this->real = std::stod(str);
}

std::string TComplex::getImaginaryStr()
{
    return std::to_string(imaginary);
}

void TComplex::setImaginaryStr(std::string str)
{
    this->imaginary = std::stod(str);
}

bool TComplex::convertStringToComplex(std::string complexString)
{
    std::size_t pos = complexString.find("+i*") + 2;

    if (pos != std::string::npos) {
        try {
            this->real = atol(complexString.substr(0, pos).c_str());
            this->imaginary = atol(complexString.substr(pos + 1).c_str());
        }
        catch (...) {
            return false;
        }
        return (this->imaginary == 0) ? false : true;
    }
    return false;
}

void TComplex::setNumberString(std::string str)
{
    try {
        size_t pos = str.find("+i*");
        int k = 1;
        if (pos == std::string::npos) {
            pos = str.find("-i*");
            k = -1;
        }
        if (pos == std::string::npos) {
            real = std::stod(str);
            imaginary = 0;
        }
        else {
            real = std::stod(str.substr(0, pos));
            imaginary = std::stod(str.substr(pos + 3)) * k;
        }
    }
    catch (...) {
        real = 0;
        imaginary = 0;
    }
}

