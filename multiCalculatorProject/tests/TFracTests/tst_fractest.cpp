#include <QtTest>

// add necessary includes here

class fractest : public QObject
{
    Q_OBJECT

public:
    fractest();
    ~fractest();

private slots:
    void test_case1();

};

fractest::fractest()
{

}

fractest::~fractest()
{

}

void fractest::test_case1()
{

}

QTEST_APPLESS_MAIN(fractest)

#include "tst_fractest.moc"
