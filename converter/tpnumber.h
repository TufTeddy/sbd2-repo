#ifndef TPNUMBER_H
#define TPNUMBER_H

#include <string>

class TPNumber {
public:
    explicit TPNumber(double number, int base, int precision);

    explicit TPNumber(std::string number,std::string base, std::string precision);

    TPNumber& operator=(const TPNumber &sec);

    TPNumber operator+(const TPNumber& sec);

    TPNumber operator-(const TPNumber& sec);

    TPNumber operator*(const TPNumber& sec);

    TPNumber operator/(const TPNumber& sec);

    TPNumber sqr();

    TPNumber inv();

    double getNumber();

    std::string getNumberAsString();

    int getBase();

    std::string getBaseAsString();

    void setBase(int base);

    void setBase(const std::string &base);

    int getPrecision();

    std::string getPrecisionAsString();

    void setPrecision(int precision);

    void setPrecision(const std::string &precision);

private:
    double strtod(const std::string &num);

    double _number;
    int _base;
    int _precision;
};

#endif // TPNUMBER_H
