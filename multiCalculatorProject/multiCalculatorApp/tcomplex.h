#ifndef TCOMPLEX_H
#define TCOMPLEX_H
#define _USE_MATH_DEFINES
#include "tanumber.h"
#include <cmath>

class TComplex : public TANumber
{
public:
    explicit TComplex() : real(0), imaginary(0) {}

    TComplex(double real, double imaginary) : real(real), imaginary(imaginary)
    {}

    TComplex(std::string complexString)
    {
        try {
            size_t pos = complexString.find("+i*");
            int k = 1;
            if (pos == std::string::npos) {
                pos = complexString.find("-i*");
                k = -1;
            }
            if (pos == std::string::npos) {
                real = std::stod(complexString);
                imaginary = 0;
            }
            else {
                real = std::stod(complexString.substr(0, pos));
                imaginary = std::stod(complexString.substr(pos + 3)) * k;
            }
        }
        catch (...) {
            real = 0;
            imaginary = 0;
        }
    }

    ~TComplex() override = default;

    std::unique_ptr<TANumber> clone() override{
        return std::make_unique<TComplex>(*this);
    }

    std::unique_ptr<TANumber> summ(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> substract(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> mult(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> divide(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber>square() override;
    bool equal(std::unique_ptr<TANumber> second) override;
    bool not_equal(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> copy() override;

    void power(int index);
    void reverse();
    double angleDegrees();
    double angleRadians();
    double absolute();
    bool convertStringToComplex(std::string complexString);

    void setNumberString(std::string str);
    std::string getNumberAsString() override;
    std::string getRealStr();
    void setRealStr(std::string str);
    std::string getImaginaryStr();
    void setImaginaryStr(std::string str);

    double getRealDouble() const;
    void setRealDouble(double value);

    double getImaginaryDouble() const;
    void setImaginaryDouble(double value);


private:
    double real;
    double imaginary;
};

#endif // TCOMPLEX_H
