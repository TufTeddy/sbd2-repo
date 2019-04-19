#include "tfrac.h"
#include <stdexcept>

TFrac::TFrac(std::string fractionString)
{
    std::size_t pos = fractionString.find("/");

    if (pos != std::string::npos) {
        this->numerator = atol(fractionString.substr(0, pos).c_str());
        this->denominator = atol(fractionString.substr(pos + 1).c_str());
    } else {
        this->numerator = atol(fractionString.c_str());
        this->denominator = 1;
    }
    if(!this->denominator){
        throw new std::runtime_error("div by 0");
    }
}

TFrac::TFrac(int _numerator, int _denominator)
{
    if(!_denominator){
        throw new std::runtime_error("div by 0");
    }
    numerator = _numerator;
    denominator = _denominator;
}

std::unique_ptr<TANumber> TFrac::summ(std::unique_ptr<TANumber> second)
{
    int denominatorTemp = this->denominator * dynamic_cast<TFrac*>(second.get())->denominator;
    int firstNumerator = this->numerator * dynamic_cast<TFrac*>(second.get())->denominator;
    int secondNumerator = dynamic_cast<TFrac*>(second.get())->numerator * this->denominator;

    if(!this->numerator) return dynamic_cast<TFrac*>(second.get())->clone();
    if(!dynamic_cast<TFrac*>(second.get())->numerator) return this->clone();
    if(!(firstNumerator + secondNumerator)){
        this->numerator = 0;
        this->denominator = 1;
        return this->clone();
    }

    this->numerator = firstNumerator + secondNumerator;
    this->denominator = denominatorTemp;
    this->reduction();
    return this->clone();
}

std::unique_ptr<TANumber> TFrac::substract(std::unique_ptr<TANumber> second)
{
    int denominatorTemp = this->denominator * dynamic_cast<TFrac*>(second.get())->denominator;
    int firstNumerator = this->numerator * dynamic_cast<TFrac*>(second.get())->denominator;
    int secondNumerator = dynamic_cast<TFrac*>(second.get())->numerator * this->denominator;

    if(!this->numerator) return dynamic_cast<TFrac*>(second.get())->clone();
    if(!dynamic_cast<TFrac*>(second.get())->numerator) return this->clone();
    if(!(firstNumerator - secondNumerator)){
        this->numerator = 0;
        this->denominator = 1;
        return this->clone();
    }

    this->numerator = firstNumerator - secondNumerator;
    this->denominator = denominatorTemp;
    this->reduction();
    return this->clone();
}

std::unique_ptr<TANumber> TFrac::mult(std::unique_ptr<TANumber> second)
{
    this->numerator *= dynamic_cast<TFrac*>(second.get())->numerator;
    this->denominator *= dynamic_cast<TFrac*>(second.get())->denominator;
    if(!numerator) {
        this->numerator = 0;
        this->denominator = 1;
    }
    this->reduction();
    return this->clone();
}

std::unique_ptr<TANumber> TFrac::divide(std::unique_ptr<TANumber> second)
{
    int secondNum = dynamic_cast<TFrac*>(second.get())->numerator,
            secondDen = dynamic_cast<TFrac*>(second.get())->denominator;

    if(!secondNum || !secondDen){
        throw new std::runtime_error("div by 0");
    }

    this->numerator *= secondDen;
    this->denominator *= secondNum;
    if(!numerator) {
        this->numerator = 0;
        this->denominator = 1;
    }

    this->reduction();
    return this->clone();
}

std::unique_ptr<TANumber> TFrac::square()
{
    this->numerator *= this->getNumerator();
    this->denominator *= this->getDenominator();
    if(!denominator || !numerator) {
        this->numerator = 0;
        this->denominator = 1;
    }
    this->reduction();
    return this->clone();
}

void TFrac::reduction()
{
    int temp = gcd(this->numerator, this->denominator);

    this->numerator /= temp;
    this->denominator /= temp;
}

int TFrac::gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void TFrac::reroll()
{
    int tmp;
    tmp = this->numerator;
    this->setNumerator(this->denominator);
    this->setDenominator(tmp);
    this->reduction();
}

int TFrac::getNumerator() const
{
    return numerator;
}

void TFrac::setNumerator(int value)
{
    numerator = value;
}

int TFrac::getDenominator() const
{
    return denominator;
}

void TFrac::setDenominator(int value)
{
    denominator = value;
}

std::string TFrac::getNumString()
{
    char tmp[10];
    _itoa_s(this->numerator, tmp, 10);
    std::string str = tmp;
    return str;
}

std::string TFrac::getDenString()
{
    char tmp[10];
    _itoa_s(this->denominator, tmp, 10);
    std::string str = tmp;
    return str;
}

bool TFrac::equal(std::unique_ptr<TANumber> second)
{
    if((this->numerator == dynamic_cast<TFrac*>(second.get())->numerator)
            && (this->denominator == dynamic_cast<TFrac*>(second.get())->denominator)){
        return true;
    }else{
        return false;
    }
}

bool TFrac::not_equal(std::unique_ptr<TANumber> second)
{
    if((this->numerator == dynamic_cast<TFrac*>(second.get())->numerator)
            && (this->denominator == dynamic_cast<TFrac*>(second.get())->denominator)){
        return false;
    }else{
        return true;
    }
}

std::unique_ptr<TANumber> TFrac::copy()
{
    return this->clone();
}

void TFrac::unary()
{
    this->numerator *= -1;
}

std::string TFrac::getNumberAsString()
{
    if (!this->denominator) return std::string("nan");

    char tmp[10];
    _itoa_s(this->numerator, tmp, 10);
    std::string str = tmp;
    str += '/';
    _itoa_s(this->denominator, tmp, 10);
    str += tmp;
    return str;
}

void TFrac::setNumberString(std::string str)
{
    std::size_t pos = str.find("/");

    if (pos != std::string::npos) {
        this->numerator = atol(str.substr(0, pos).c_str());
        this->denominator = atol(str.substr(pos + 1).c_str());
    } else {
        this->numerator = atol(str.c_str());
        this->denominator = 1;
    }
    if(!this->denominator){
        throw new std::runtime_error("div by 0");
    }
}

