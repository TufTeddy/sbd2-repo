#ifndef TPNUMBEREDITOR_H
#define TPNUMBEREDITOR_H

#pragma once

#include <string>

class TPNumberEditor {
public:
    TPNumberEditor();

    bool isZero();

    std::string changeSign();

    std::string addDigit(unsigned int digit);

    std::string addZero();

    std::string backspace();

    std::string clear();

    std::string addSplit();

    void setNumber(std::string num);

    std::string getNumber() const;

    static const std::string ZERO;
    static const char DIV_SIGN;
    unsigned int getBase() const;
    void setBase(unsigned int value);

    int getPrecision() const;
    void setPrecision(int value);

private:
    std::string number;
    unsigned int base;
    int precision;
};





#endif // TPNUMBEREDITOR_H
