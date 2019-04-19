#include <QtTest>

// add necessary includes here

class proctests : public QObject
{
    Q_OBJECT

public:
    proctests();
    ~proctests();

private slots:
    void test_case1();

};

proctests::proctests()
{

}

proctests::~proctests()
{

}

void proctests::test_case1()
{

}

QTEST_APPLESS_MAIN(proctests)

#include "tst_proctests.moc"
