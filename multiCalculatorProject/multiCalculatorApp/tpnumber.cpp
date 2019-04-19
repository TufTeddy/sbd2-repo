#include "tpnumber.h"
#include <stdexcept>
#include <cmath>

TPNumber::TPNumber(double number, int base, int precision)
{
    if (base >= 2 && base <= 16 && precision >= 0) {
        _number = number;
        _base = base;
        _precision = precision;
    }
    else {
        _number = 0.0;
        _base = 10;
        _precision = 0;
    }
}

TPNumber::TPNumber(const std::string &number, const std::string &base, const std::string &precision)
{
    try {
        _base = std::stoi(base);
        _precision = std::stoi(precision);

        if (_base >= 2 && _base <= 16 && _precision >= 0) {
            _number = strtod(number);
        }
        else {
            throw std::invalid_argument("Wrong base or precision");
        }
    }
    catch (...) {
        _number = 0.0;
        _base = 10;
        _precision = 0;
    }
}

std::unique_ptr<TANumber> TPNumber::summ(std::unique_ptr<TANumber> second)
{
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    this->setNumber(firstArg+secondArg);
    this->setBase(dynamic_cast<TPNumber*>(second.get())->getBase());
    return this->clone();
}

std::unique_ptr<TANumber> TPNumber::substract(std::unique_ptr<TANumber> second)
{
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    this->setNumber(firstArg-secondArg);
    this->setBase(dynamic_cast<TPNumber*>(second.get())->getBase());
    return this->clone();
}

std::unique_ptr<TANumber> TPNumber::mult(std::unique_ptr<TANumber> second)
{
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    this->setNumber(firstArg*secondArg);
    this->setBase(dynamic_cast<TPNumber*>(second.get())->getBase());
    return this->clone();
}

std::unique_ptr<TANumber> TPNumber::divide(std::unique_ptr<TANumber> second)
{
    if(dynamic_cast<TPNumber*>(second.get())->getNumber() - 0 <= DBL_EPSILON){
        throw new std::exception("div by 0");
    }
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    this->setNumber(firstArg/secondArg);
    this->setBase(dynamic_cast<TPNumber*>(second.get())->getBase());
    return this->clone();
}

std::unique_ptr<TANumber> TPNumber::square()
{
    double firstArg = this->getNumber();
    this->setNumber(firstArg*firstArg);
    return this->clone();
}

bool TPNumber::equal(std::unique_ptr<TANumber> second)
{
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    if(fabs(firstArg-secondArg) <= DBL_EPSILON) {
        return true;
    }
    else {
        return false;
    }
}

bool TPNumber::not_equal(std::unique_ptr<TANumber> second)
{
    double firstArg = this->getNumber();
    double secondArg = dynamic_cast<TPNumber*>(second.get())->getNumber();
    if(fabs(firstArg-secondArg) <= DBL_EPSILON) {
        return false;
    }
    else {
        return true;
    }
}

std::unique_ptr<TANumber> TPNumber::copy()
{
    return this->clone();
}

std::string TPNumber::getNumberAsString()
{
    std::string num;
    bool minusFlag = false;
    bool zeroFlag = false;
    if(_number < 0){
        _number*=-1;
        minusFlag = true;
    }


    auto intPart = (int)_number;
    if (!intPart) zeroFlag = true;

    double fracPart = _number - intPart;

    while (intPart) {
        auto digit = (char)(intPart % _base);

        digit += digit < 10 ? '0' : -10 + 'A';

        num.insert(num.begin(), digit);

        intPart /= _base;
    }

    if(zeroFlag) num.insert(num.begin(), '0');
    if(minusFlag) num.insert(num.begin(), '-');

    std::string fracString = "";
    if (fracPart != 0) {
        fracString += '.';

        for (int exp = 1; exp < _precision; ++exp) {
            auto digit = (char)(fracPart *= _base);

            fracString += (char)(digit < 10 ? '0' + digit : 'A' + digit - 10);

            fracPart -= digit;
        }
        auto digit = (char)round(fracPart * _base);
        if (digit == _base) {
            digit--;
        }

        fracString += (char)(digit < 10 ? '0' + digit : 'A' + digit - 10);
    }

    if(!fracString.empty()){
        while(fracString.back() == '0'){
            fracString.pop_back();
        }
    }

    num += fracString;

    return num.empty() ? "0" : num;
}

void TPNumber::setNumberString(std::string str, int base)
{
    try {
        _base = base;

        if (_base >= 2 && _base <= 16 && _precision >= 0) {
            _number = strtod(str);
        }
        else {
            throw std::invalid_argument("Wrong base or precision");
        }
    }
    catch (...) {
        _number = 0.0;
        _base = 10;
        _precision = 0;
    }
}

void TPNumber::inv()
{
    this->_number = 1 / this->_number;
}

int TPNumber::getPrecision() const
{
    return _precision;
}

void TPNumber::setPrecision(int value)
{
    _precision = value;
}

int TPNumber::getBase() const
{
    return _base;
}

void TPNumber::setBase(int value)
{
    if (value < 2 || value > 16) {
        throw std::invalid_argument("Wrong base");
    }

    _base = value;
}

double TPNumber::getNumber() const
{
    return _number;
}

void TPNumber::setNumber(double value)
{
    _number = value;
}

std::string TPNumber::getPrecisionAsString()
{
    return std::to_string(_precision);
}

std::string TPNumber::getBaseAsString()
{
    return std::to_string(_base);
}

double TPNumber::strtod(const std::string &num)
{
    size_t pos = num.find('.');
    int posWithMinus = 0;
    if(num[0] == '-') posWithMinus = 1;
    int intPart = std::stoi(num.substr(posWithMinus, pos), nullptr, _base);
    double fracPart = 0;

    if (pos != std::string::npos) {
        std::string fracSubstr = num.substr(pos + 1);

        fracPart = std::stoi(fracSubstr, nullptr, _base);

        while (fracPart >= 1) {
            fracPart /= _base;
        }

        for (int idx = 0; fracSubstr[idx] == '0'; ++idx) {
            fracPart /= _base;
        }
    }

    if(!posWithMinus) {
        return (double)intPart + fracPart;
    }
    else {
        return (double)(-intPart) - fracPart;
    }
}

char TPNumber::fromIntToChar(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}

char TPNumber::fromCharToInt(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}

std::string TPNumber::from10(double number, int curBase)
{
    int intPart = static_cast<int>(number);
    double fracPart = number - intPart;

    std::string answer;

    while (intPart > 0)
    {
        answer.push_back(fromIntToChar(intPart % curBase));
        intPart /= curBase;
    }
    std::reverse(answer.begin(), answer.end());
    int tempInt = 0;
    int index = 0;
    if (fracPart!= 0) answer.push_back('.');
    while (fracPart > 0)
    {
        tempInt = fracPart * curBase;
        answer.push_back(fromIntToChar(tempInt));
        fracPart = fracPart * curBase;
        fracPart -= tempInt;
        index++;
    }
    while(answer.back() == '0'){
        answer.pop_back();
    }
    return answer;
}
