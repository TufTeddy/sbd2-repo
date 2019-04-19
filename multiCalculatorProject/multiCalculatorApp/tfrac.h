#ifndef TFRAC_H
#define TFRAC_H
#include "tanumber.h"
#include <cmath>

class TFrac : public TANumber
{
public:
    explicit TFrac() : numerator(0), denominator(1){}
    TFrac(std::string fractionString);
    TFrac(int _numerator, int _denominator);

    std::unique_ptr<TANumber> clone() override{
        return std::make_unique<TFrac>(*this);
    }

    std::unique_ptr<TANumber> summ(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> substract(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> mult(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> divide(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> square() override;
    bool equal(std::unique_ptr<TANumber> second) override;
    bool not_equal(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> copy() override;

    void reduction();
    void unary();
    int gcd(int a, int b);
    void reroll();

    int getNumerator() const;
    void setNumerator(int value);
    int getDenominator() const;
    void setDenominator(int value);
    std::string getNumString();
    std::string getDenString();
    std::string getNumberAsString() override;
    void setNumberString(std::string str);

private:
    int numerator;
    int denominator;
};

#endif // TFRAC_H
