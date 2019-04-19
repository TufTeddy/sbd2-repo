#include <QtTest>

// add necessary includes here

class tcomplextest : public QObject
{
    Q_OBJECT

public:
    tcomplextest();
    ~tcomplextest();

private slots:
    void test_case1();

};

tcomplextest::tcomplextest()
{

}

tcomplextest::~tcomplextest()
{

}

void tcomplextest::test_case1()
{

}

QTEST_APPLESS_MAIN(tcomplextest)

#include "tst_tcomplextest.moc"
