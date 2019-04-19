#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QVector>
#include <QLabel>
#include <QSignalMapper>
#include <QDebug>
#include <QRegExpValidator>
#include <QRegExp>
#include <QValidator>
#include <QMenu>
#include <QMenuBar>
#include <QLayout>
#include <QMessageBox>
#include "tctrl.h"
#include "tfrac.h"
#include "tcomplex.h"
#include "tpnumber.h"
#include "history.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    enum numbersInt: int
    {
        zero = 0,
        one = 1,
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        nine = 9,
        A = 10,
        B = 11,
        C = 12,
        D = 13,
        E = 14,
        F = 15,
        sixteen = 16
    };
    enum calcMode : int
    {
        complex = 1,
        pnumber = 2,
        frac = 3
    };
    int currentBase() const;
    void setCurrentBase(int currentBase);

    int currentBaseToOperate() const;
    void setCurrentBaseToOperate(int currentBaseToOperate);

public slots:
    void showHistory();
    void digitButtonPushed(QString digitString);
    void complexModButtonPushed();
    void pnumberModButtonPushed();
    void fracModButtonPushed();
    void sliderEventSlot(int base);
    void checkButtonsToBase();
    void plusButtonPushed();
    void minusButtonPushed();
    void mulButtonPushed();
    void divButtonPushed();
    void resultButtonPushed();
    void changeModeComplex();
    void changeModeFrac();
    void memoryLoad();
    void memorySave();
    void clearAll();
    void clearEntry();
    void transformPnumber();
    void dotButtonPushed();
    void backSpaceButtonPushed();

private:
    QWidget *window;
    QSignalMapper * digitButtonsMapper;
    QGridLayout *wholeLayout;
    QLineEdit *entryLineEdit;
    QLabel *memoryLabel;
    //QLineEdit *precisionLineEdit;
    //QLabel *precisionLabel;
    QSlider *pBaseSlider;
    QVector <QPushButton*> vectorOfButtons;
    QLabel *currentBaseLabel;

    QMenuBar *menubar;
    QMenu *menu;

    QPushButton *backSpaceButton;
    QPushButton *clearAllButton;
    QPushButton *clearEntryButton;
    QPushButton *dotButton;
    QPushButton *memLoadButton;
    QPushButton *memSaveButton;
    QPushButton *changeSignButton;
    QPushButton *plusButton;
    QPushButton *minusButton;
    QPushButton *divButton;
    QPushButton *mulButton;
    QPushButton *resultButton;
    QPushButton *complexPartButton;
    QPushButton *fracPartButton;

    QPushButton *complexModeButton;
    QPushButton *pnumberModeButton;
    QPushButton *fracModeButton;

    QVBoxLayout *verticLayout;
    QValidator *validatorLineEdit;
    QValidator *validatorPrecisionLineEdit;

    int _currentBase = numbersInt::A;
    int _currentBaseToOperate = numbersInt::A;
    bool lrComplex = false;
    bool lrFrac = false;
    TCtrl *ctrlunit;
    History *historyObject;
    TANumber *_number;
    calcMode mode = calcMode::complex;
    QString toHistoryString = "";


    void setCurrentValidator();
    void setViewOfSlider();
    void setViewOfMainWindow();
    void setViewOfMenu();
    void setViewOfMemoryBlock();
    void setViewOfLineEdit();
    void setViewOfDigitButtons();
    void setViewOfOperationButtons();
    void insertingInLayout();
};


#endif // MAINWINDOW_H
