#include <QtTest>
#include "../../tpnumber.h"

class TPNumberTest : public QObject
{
    Q_OBJECT

public:
    TPNumberTest();
    ~TPNumberTest();

private slots:
    void constructor();
    void ConstructorString();
    void NumberContructor();
    void StringContructor();
    void add();
    void mul();
    void substract();
    void divide();
    void square();
    void number();
    void numberString();
    void base();
    void precision();
    void setBase();
    void setPrecision();
    void setPrecisionString();
};

TPNumberTest::TPNumberTest()
{

}

TPNumberTest::~TPNumberTest()
{

}

void TPNumberTest::constructor()
{
    TPNumber num(123, 4, 3);
    QCOMPARE(123.0, num.getNumber());
}

void TPNumberTest::ConstructorString()
{
    TPNumber num("123", "4", "3");
    QCOMPARE(27.0, num.getNumber());
}

void TPNumberTest::NumberContructor()
{
    QCOMPARE(TPNumber(123, 4, 3).getNumber(), 123.0);
    QCOMPARE(TPNumber(123.5, 4, 3).getNumber(), 123.5);
}

void TPNumberTest::StringContructor()
{
    QCOMPARE(TPNumber("123", "4", "3").getNumber(), 27.0);
    QCOMPARE(TPNumber("123.2", "4", "3").getNumber(), 27.5);
}


void TPNumberTest::add()
{
    QCOMPARE(TPNumber(246, 4, 3).getNumber(), (TPNumber(123, 4, 3) + TPNumber(123, 4, 3)).getNumber());
    QCOMPARE(TPNumber(132, 4, 3).getNumber(), (TPNumber(1, 4, 3) + TPNumber(131, 4, 3)).getNumber());
}

void TPNumberTest::mul()
{
    QCOMPARE(TPNumber(2, 4, 3).getNumber(), (TPNumber(2, 4, 3) * TPNumber(1, 4, 3)).getNumber());
    QCOMPARE(TPNumber(12, 4, 3).getNumber(), (TPNumber(3, 4, 3) * TPNumber(4, 4, 3)).getNumber());
}

void TPNumberTest::substract()
{
    QCOMPARE(TPNumber(1, 4, 3).getNumber(), (TPNumber(123, 4, 3) - TPNumber(122, 4, 3)).getNumber());
    QCOMPARE(TPNumber(0, 4, 3).getNumber(), (TPNumber(131, 4, 3) - TPNumber(131, 4, 3)).getNumber());
}

void TPNumberTest::divide()
{
    QCOMPARE(TPNumber(2, 4, 3).getNumber(), (TPNumber(4, 4, 3) / TPNumber(2, 4, 3)).getNumber());
    QCOMPARE(TPNumber(1, 4, 3).getNumber(), (TPNumber(4, 4, 3) / TPNumber(4, 4, 3)).getNumber());
}

void TPNumberTest::square()
{
    QCOMPARE(TPNumber(4, 4, 3).getNumber(), TPNumber(2, 4, 3).sqr().getNumber());
    QCOMPARE(TPNumber(0.25, 4, 3).getNumber(), TPNumber(0.5, 4, 3).sqr().getNumber());
}

void TPNumberTest::number()
{
    QCOMPARE(123.0, TPNumber(123, 4, 3).getNumber());
    QCOMPARE(123.5, TPNumber(123.5, 4, 3).getNumber());

}

void TPNumberTest::numberString()
{
    QCOMPARE(0, TPNumber(27, 4, 3).getNumberAsString().compare("123"));
    QCOMPARE(0, TPNumber(27.5, 4, 3).getNumberAsString().compare("123.200"));
}

void TPNumberTest::base()
{
    QCOMPARE(4, TPNumber(123, 4, 3).getBase());
    QCOMPARE(4, TPNumber("123", "4", "3").getBase());
}

void TPNumberTest::precision()
{
    QCOMPARE(3, TPNumber(123, 4, 3).getPrecision());
    QCOMPARE(3, TPNumber("123", "4", "3").getPrecision());

}

void TPNumberTest::setBase()
{
    TPNumber pnum(123, 4, 3);
    pnum.setBase(5);
    QCOMPARE(5, pnum.getBase());
    pnum.setBase(3);
    QCOMPARE(3, pnum.getBase());

}

void TPNumberTest::setPrecision()
{
    TPNumber pnum(123, 4, 3);
    pnum.setBase("5");
    QCOMPARE(5, pnum.getBase());
    pnum.setBase("3");
    QCOMPARE(3, pnum.getBase());

}

void TPNumberTest::setPrecisionString()
{
    TPNumber pnum(123, 4, 3);
    pnum.setPrecision("4");
    QCOMPARE(4, pnum.getPrecision());
    pnum.setPrecision("2");
    QCOMPARE(2, pnum.getPrecision());
}

QTEST_APPLESS_MAIN(TPNumberTest)
#include "tpnumbertest.moc"
