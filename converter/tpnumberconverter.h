#ifndef TPNUMBERCONVERTER_H
#define TPNUMBERCONVERTER_H
#include "tpnumber.h"
#include <QString>
#include <cstdlib>
#include <QDebug>

class TPNumberConverter
{
public:
    explicit TPNumberConverter();
    TPNumber from10(TPNumber number, int needBase);
    TPNumber to10(TPNumber number, int curBase);

    TPNumber number() const;
    void setNumber(const TPNumber &number);

    int precision() const;
    void setPrecision(int precision);
    char fromIntToChar(int num);
    char fromCharToChar(char c);


private:
    int _currentBase;
    int _neededBase;
    int _precision;
};

#endif // TPNUMBERCONVERTER_H
