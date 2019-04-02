#ifndef TPNUMBERCONVERTER_H
#define TPNUMBERCONVERTER_H
//#include "tpnumber.h"
#include <QString>

class TPNumberConverter
{
public:
    TPNumberConverter();
    /*TPNumber from10(TPNumber number, int needBase, int precision);
    TPNumber to10(TPNumber number, int curBase, int precision);

    TPNumber number() const;
    void setNumber(const TPNumber &number);*/

    int precision() const;
    void setPrecision(int precision);

private:
    //TPNumber _number;
    int _precision;
};

#endif // TPNUMBERCONVERTER_H
