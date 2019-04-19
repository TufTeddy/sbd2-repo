#include <QtTest>
#include "tfrac.h"
#include "tproc.h"

class proctests : public QObject
{
    Q_OBJECT

public:
    proctests();
    ~proctests();

private slots:
    void ropSet_data();
    void lopSet_data();
    void oprtnRun_data();

    void ropSet();
    void lopSet();
    void oprtnRun();
};

proctests::proctests()
{

}

proctests::~proctests()
{

}

void proctests::ropSet_data()
{
    QTest::addColumn<QString>("first");
    QTest::addColumn<QString>("answer");

    QTest::newRow("ropSet") << "1/2" << "1/2";
}

void proctests::ropSet()
{
    QFETCH(QString, first);
    QFETCH(QString, answer);

    TProc *proc = new TProc();
    TANumber *frac = new TFrac(first.toStdString());

    proc->Rop_Set(frac->clone());
    QCOMPARE(QString::fromStdString(proc->Rop_Get().get()->getNumberAsString()), answer);

}

void proctests::lopSet_data()
{
    QTest::addColumn<QString>("first");
    QTest::addColumn<QString>("answer");

    QTest::newRow("ropSet") << "3/4" << "3/4";
}

void proctests::lopSet()
{
    QFETCH(QString, first);
    QFETCH(QString, answer);

    TProc *proc = new TProc();
    TANumber *frac = new TFrac(first.toStdString());

    proc->Lop_Res_Set(frac->clone());

    QCOMPARE(QString::fromStdString(proc->Lop_Res_Get().get()->getNumberAsString()), answer);
}
void proctests::oprtnRun_data()
{
    QTest::addColumn<QString>("first");
    QTest::addColumn<QString>("second");
    QTest::addColumn<QString>("answer");

    QTest::newRow("ropSet") << "1/2" << "3/4" << "5/4";
}

void proctests::oprtnRun()
{
    QFETCH(QString, first);
    QFETCH(QString, second);
    QFETCH(QString, answer);

    TProc *proc = new TProc();
    TANumber *fracFirst = new TFrac(first.toStdString());
    TANumber *fracSecond = new TFrac(second.toStdString());

    proc->Lop_Res_Set(fracFirst->clone());
    proc->Rop_Set(fracSecond->clone());
    proc->OprtnSet(TOprtn::Add);
    proc->OprtnRun();

    QCOMPARE(QString::fromStdString(proc->Lop_Res_Get().get()->getNumberAsString()), answer);
}


QTEST_APPLESS_MAIN(proctests)

#include "tst_proctests.moc"
