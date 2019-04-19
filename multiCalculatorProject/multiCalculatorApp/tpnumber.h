#ifndef TPNUMBER_H
#define TPNUMBER_H
#include "tanumber.h"

class TPNumber : public TANumber
{
public:
    TPNumber(){}
    explicit TPNumber(double number, int base, int precision);
    explicit TPNumber(const std::string &number, const std::string &base = "10", const std::string &precision = "7");

    std::unique_ptr<TANumber> clone() override{
        return std::make_unique<TPNumber>(*this);
    }

    std::unique_ptr<TANumber> summ(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> substract(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> mult(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> divide(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> square() override;
    bool equal(std::unique_ptr<TANumber> second) override;
    bool not_equal(std::unique_ptr<TANumber> second) override;
    std::unique_ptr<TANumber> copy() override;

    virtual std::string getNumberAsString() override;
    void setNumberString(std::string str, int base);
    void inv();

    int getPrecision() const;
    void setPrecision(int value);

    int getBase() const;
    void setBase(int value);

    double getNumber() const;
    void setNumber(double value);

    std::string getPrecisionAsString();
    std::string getBaseAsString();

private:
    double strtod(const std::string &num);
    char fromIntToChar(int num);
    char fromCharToInt(char c);
    std::string from10(double number, int curBase);

    double _number;
    int _base;
    int _precision;
};

#endif // TPNUMBER_H
