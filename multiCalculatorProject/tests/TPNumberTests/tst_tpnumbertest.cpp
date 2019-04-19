#include <QtTest>
#include "tpnumber.h"

class tpnumbertest : public QObject
{
    Q_OBJECT

public:
    tpnumbertest();
    ~tpnumbertest();

private slots:
    void constructor_data();
    void stringConstructor_data();
    void summ_data();
    void substract_data();
    void mult_data();
    void divide_data();
    void getNumberAsString_data();

    void constructor();
    void stringConstructor();
    void summ();
    void substract();
    void mult();
    void divide();
    void getNumberAsString();
};

tpnumbertest::tpnumbertest()
{

}

tpnumbertest::~tpnumbertest()
{

}

void tpnumbertest::constructor_data()
{
    QTest::addColumn<double>("number");
    QTest::addColumn<int>("base");
    QTest::addColumn<int>("precision");
    QTest::addColumn<double> ("answer");

    QTest::newRow("constructor") << 0.0 << 0 << 0 << 0.0;
    QTest::newRow("constructor") << 2.5 << 2 << 2 << 2.5;
    QTest::newRow("constructor") << -2.5 << 2 << 2 << -2.5;
    QTest::newRow("constructor") << 1001.0 << 2 << 2 << 1001.0;
    QTest::newRow("constructor") << 23.0 << 10 << 2 << 23.0;
}

void tpnumbertest::constructor()
{
    QFETCH(double, number);
    QFETCH(int, base);
    QFETCH(int, precision);
    QFETCH(double, answer);

    TANumber *obj = new TPNumber(number, base, precision);
    QCOMPARE(dynamic_cast<TPNumber*>(obj)->getNumber(), answer);
}

void tpnumbertest::stringConstructor_data()
{
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("base");
    QTest::addColumn<QString>("precision");
    QTest::addColumn<double>("answer");

    QTest::newRow("constructorString") << "0" << "0" << "0" << 0.0;
    QTest::newRow("constructorString") << "2.5" << "10" << "2" << 2.5;
    QTest::newRow("constructorString") << "-1.1" << "2" << "2" << -1.50;
    QTest::newRow("constructorString") << "1001" << "2" << "2" << 9.0;
    QTest::newRow("constructorString") << "AB" << "16" << "0" << 171.0;
}

void tpnumbertest::stringConstructor()
{
    QFETCH(QString, number);
    QFETCH(QString, base);
    QFETCH(QString, precision);
    QFETCH(double, answer);

    TANumber *obj = new TPNumber(number.toStdString(), base.toStdString(), precision.toStdString());
    QCOMPARE(dynamic_cast<TPNumber*>(obj)->getNumber(), answer);

}

void tpnumbertest::getNumberAsString_data()
{
    QTest::addColumn<QString>("number");
    QTest::addColumn<QString>("base");
    QTest::addColumn<QString>("precision");
    QTest::addColumn<QString> ("answer");

    QTest::newRow("getNumbString") << "0" << "0" << "0" << "0";
    QTest::newRow("getNumbString") << "2.5" << "6" << "2" << "2.5";
    QTest::newRow("getNumbString") << "-2.50" << "10" << "2" << "-2.5";
    QTest::newRow("getNumbString") << "1001" << "2" << "2" << "1001";
    QTest::newRow("getNumbString") << "AB" << "16" << "0" << "AB";
    QTest::newRow("getNumbString") << "-AB.AB" << "16" << "3" << "-AB.AB";

}

void tpnumbertest::getNumberAsString()
{
    QFETCH(QString, number);
    QFETCH(QString, base);
    QFETCH(QString, precision);
    QFETCH(QString, answer);

    TANumber *obj = new TPNumber(number.toStdString(), base.toStdString(), precision.toStdString());
    QCOMPARE(QString::fromStdString(dynamic_cast<TPNumber*>(obj)->getNumberAsString()), answer);
}

void tpnumbertest::summ_data()
{
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("firstNumBase");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("secondNumBase");
    QTest::addColumn<QString>("answer");

    QTest::newRow("summ") << "0" << "2" << "0" << "10" << "0";
    QTest::newRow("summ") << "10" << "2" << "4" << "10" << "6";
    QTest::newRow("summ") << "4" << "10" << "10" << "2" << "110";
    QTest::newRow("summ") << "AB.BA" << "16" << "-10" << "10" << "161.7265625";
    QTest::newRow("summ") << "-AB.BA" << "16" << "20" << "3" << "-20010.2011212";

}

void tpnumbertest::summ()
{
    QFETCH(QString, firstNum);
    QFETCH(QString, firstNumBase);
    QFETCH(QString, secondNum);
    QFETCH(QString, secondNumBase);
    QFETCH(QString, answer);

    TANumber *first = new TPNumber(firstNum.toStdString(), firstNumBase.toStdString());
    TANumber *second = new TPNumber(secondNum.toStdString(), secondNumBase.toStdString());
    first->summ(second->clone());
    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void tpnumbertest::substract_data()
{
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("firstNumBase");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("secondNumBase");
    QTest::addColumn<QString>("answer");

    QTest::newRow("sub") << "0" << "2" << "0" << "10" << "0";
    QTest::newRow("sub") << "10" << "2" << "4" << "10" << "-2";
    QTest::newRow("sub") << "4" << "10" << "10" << "2" << "10";
    QTest::newRow("sub") << "AB.BA" << "16" << "-10" << "10" << "181.7265625";
    QTest::newRow("sub") << "-AB.BA" << "16" << "20" << "3" << "-20120.2011212";
}

void tpnumbertest::substract()
{
    QFETCH(QString, firstNum);
    QFETCH(QString, firstNumBase);
    QFETCH(QString, secondNum);
    QFETCH(QString, secondNumBase);
    QFETCH(QString, answer);

    TANumber *first = new TPNumber(firstNum.toStdString(), firstNumBase.toStdString());
    TANumber *second = new TPNumber(secondNum.toStdString(), secondNumBase.toStdString());
    first->substract(second->clone());
    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}


void tpnumbertest::mult_data()
{
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("firstNumBase");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("secondNumBase");
    QTest::addColumn<QString>("answer");

    QTest::newRow("mult") << "0" << "2" << "0" << "10" << "0";
    QTest::newRow("mult") << "10" << "2" << "4" << "10" << "8";
    QTest::newRow("mult") << "4" << "10" << "10" << "2" << "1000";
    QTest::newRow("mult") << "AB.BA" << "16" << "-10" << "10" << "-1717.265625";
    QTest::newRow("mult") << "-AB.BA" << "16" << "20" << "3" << "-1102011.1002002";
}
void tpnumbertest::mult()
{
    QFETCH(QString, firstNum);
    QFETCH(QString, firstNumBase);
    QFETCH(QString, secondNum);
    QFETCH(QString, secondNumBase);
    QFETCH(QString, answer);

    TANumber *first = new TPNumber(firstNum.toStdString(), firstNumBase.toStdString());
    TANumber *second = new TPNumber(secondNum.toStdString(), secondNumBase.toStdString());
    first->mult(second->clone());
    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}

void tpnumbertest::divide_data()
{
    QTest::addColumn<QString>("firstNum");
    QTest::addColumn<QString>("firstNumBase");
    QTest::addColumn<QString>("secondNum");
    QTest::addColumn<QString>("secondNumBase");
    QTest::addColumn<QString>("answer");

    //QTest::newRow("div") << "0" << "2" << "0" << "10" << "0";
    QTest::newRow("div") << "10" << "2" << "4" << "10" << "0.5";
    QTest::newRow("div") << "4" << "10" << "10" << "2" << "10";
    //QTest::newRow("div") << "AB.BA" << "16" << "-10" << "10" << "-17.1726562";
    QTest::newRow("div") << "-AB.BA" << "16" << "20" << "3" << "-1001.1212022";
}

void tpnumbertest::divide()
{
    QFETCH(QString, firstNum);
    QFETCH(QString, firstNumBase);
    QFETCH(QString, secondNum);
    QFETCH(QString, secondNumBase);
    QFETCH(QString, answer);

    TANumber *first = new TPNumber(firstNum.toStdString(), firstNumBase.toStdString());
    TANumber *second = new TPNumber(secondNum.toStdString(), secondNumBase.toStdString());
    first->divide(second->clone());
    QCOMPARE(QString::fromStdString(first->getNumberAsString()), answer);
}


QTEST_APPLESS_MAIN(tpnumbertest)

#include "tst_tpnumbertest.moc"
