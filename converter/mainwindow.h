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
#include "tpnumber.h"
#include "history.h"
#include "tpnumberconverter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
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

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getCurrentBase() const;
    void setCurrentBase(int value);

    double getNumber() const;
    void setNumber(double number);

    int getPrecision() const;
    void setPrecision(int precision);

    void setViewOfMainWindow();
    void checkButtonsToBase();

    int getNumbersAfterDivSign() const;
    void setNumbersAfterDivSign(int numbersAfterDivSign);

public slots:
    void sliderEventSlot(int base);
    void digitButtonPushed(QString digitString);
    void backSpaceButtonSlot();
    void transformButtonSlot();
    void clearAllButtonSlot();
    void dotButtonSlot();
    void lineEditChangedSlot();

private:
    QWidget *window;

    QSignalMapper * digitButtonsMapper;
    QGridLayout *wholeLayout;
    QLineEdit *pNumberLineEdit;
    QLineEdit *precisionLineEdit;
    QLabel *precisionLabel;
    QSlider *pBaseSlider;
    QVector <QPushButton*> vectorOfButtons;
    QLabel *currentBaseLabel;

    QPushButton *transformButton;
    QPushButton *backSpaceButton;
    QPushButton *clearAllButton;
    QPushButton *dotButton;

    QValidator *validatorLineEdit;
    QValidator *validatorPrecisionLineEdit;
    double _number = 0;
    int _currentBase = 2;
    int _fromBase = 2;
    int _precision = 0;
    int _numbersAfterDivSign = 0;
    bool divSignPressed = false;

    //TPNumberEditor *editorObject;
    TPNumberConverter *converter;
    History *historyObject;


};

#endif // MAINWINDOW_H
