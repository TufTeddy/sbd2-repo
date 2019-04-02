#include "tpnumberconverter.h"

TPNumberConverter::TPNumberConverter()
{
}

TPNumber TPNumberConverter::from10(TPNumber number, int needBase)
{
    _neededBase = needBase;
    qDebug() << QString::fromStdString(number.getNumberAsString()) << " " << needBase;
    int intPart = static_cast<int>(number.getNumber());
    double fracPart = number.getNumber() - intPart;
    fracPart *= 10000000;
    std::string intPartString = std::to_string(intPart);
    std::string fracPartString = std::to_string(static_cast<int>(fracPart));


    std::string answer;
    std::string temp;


    while (intPart > 0)
    {
        answer.push_back(fromIntToChar(intPart % needBase));
        intPart /= needBase;
    }
    //qDebug() << QString::fromUtf8(answer.c_str());
    std::reverse(answer.begin(), answer.end());
    int temp;
    int index = 0;

    while (fracPart > 0)
    {
        if (index >= _precision)
            break;
        temp = fracPart * needBase;
        answer.push_back(fromIntToChar(temp));
        fracPart -= temp;
        index++;
    }

    //qDebug() << QString::fromUtf8(answer.c_str());
    return TPNumber(answer, std::to_string(needBase), number.getPrecisionAsString());
}

TPNumber TPNumberConverter::to10(TPNumber number, int curBase)
{
    _currentBase = curBase;
    _precision = number.getPrecision();

    double tempNumber = number.getNumber();
    int intPart = static_cast<int>(tempNumber);
    double fracPart = tempNumber - intPart;

    std::string answer;
    std::string temp;
    temp = std::to_string(intPart);
    int len = temp.length();
    int power = 1; // Initialize power of base
    int num = 0;  // Initialize result
    int i;

    for (i = len - 1; i >= 0; i--)
    {
        // A digit in input number must be
        // less than number's base
        num += fromCharToChar(temp[i]) * power;
        power = power * curBase;
    }
    answer = std::to_string(num);

    fracPart *= 10000000;
    temp = std::to_string(fracPart);

    qDebug() << fracPart <<QString::fromStdString(temp);
    len = temp.length();
    power = -1;
    num = 0;
    int c = 0;
    for (i = len-1; i >=0; i--){
        num += fromCharToChar(temp[i]) * power;
        power = power / curBase;
        c++;
        if (c >= _precision)
            break;
    }
    num/=10000000;
    answer = answer + "." + std::to_string(num);
    qDebug() << QString::fromStdString(answer);
    return TPNumber(answer, std::to_string(10), number.getPrecisionAsString());
}

int TPNumberConverter::precision() const
{
    return _precision;
}

void TPNumberConverter::setPrecision(int precision)
{
    _precision = precision;
}

char TPNumberConverter::fromIntToChar(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}

char TPNumberConverter::fromCharToChar(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;

}
