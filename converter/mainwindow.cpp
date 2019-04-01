#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //editorObject = new TPNumberEditor();
    tpnumberObject = new TPNumber(_number, _currentBase, _numbersAfterDivSign);
    setViewOfMainWindow();
    checkButtonsToBase();
    QObject::connect(pBaseSlider, &QSlider::valueChanged,
                     this, &MainWindow::sliderEventSlot);
    //QObject::connect(, &QPushButton::clicked, this, &MainWindow::buttonPushed);
    QObject::connect(transformButton, &QPushButton::clicked, this, &MainWindow::transformButtonSlot);
    QObject::connect(backSpaceButton, &QPushButton::clicked, this, &MainWindow::backSpaceButtonSlot);
    QObject::connect(clearAllButton, &QPushButton::clicked, this, &MainWindow::clearAllButtonSlot);
    QObject::connect(dotButton, &QPushButton::clicked, this, &MainWindow::dotButtonSlot);
}

MainWindow::~MainWindow()
{

}

void MainWindow::sliderEventSlot(int base)
{
    currentBaseLabel->setText(QStringLiteral("Current base: %1").arg(base));
    setCurrentBase(base);
    checkButtonsToBase();
}

void MainWindow::digitButtonPushed(QString digitString)
{
    QString tempString;
    tempString = pNumberLineEdit->text().toUtf8();
    pNumberLineEdit->setText(tempString+digitString);
    if (divSignPressed)
        _numbersAfterDivSign ++;
}

void MainWindow::backSpaceButtonSlot()
{
    if (_numbersAfterDivSign > 0){
        if (_numbersAfterDivSign == 1) {
            _numbersAfterDivSign--;
            divSignPressed = false;
        }
        _numbersAfterDivSign--;
    }
    QString tempString;
    tempString = pNumberLineEdit->text().toUtf8();
    pNumberLineEdit->setText(tempString.remove(tempString.size()-1, 1));
}

void MainWindow::transformButtonSlot()
{

}

void MainWindow::clearAllButtonSlot()
{
    pNumberLineEdit->clear();
    divSignPressed = false;
    _numbersAfterDivSign = 0;
}

void MainWindow::dotButtonSlot()
{
    if(!divSignPressed)
    {
        _numbersAfterDivSign = 1;
        divSignPressed = true;

        QString tempString;
        tempString = pNumberLineEdit->text().toUtf8();
        pNumberLineEdit->setText(tempString+'.');
    }
}

int MainWindow::getNumbersAfterDivSign() const
{
    return _numbersAfterDivSign;
}

void MainWindow::setNumbersAfterDivSign(int numbersAfterDivSign)
{
    _numbersAfterDivSign = numbersAfterDivSign;
}

void MainWindow::setViewOfMainWindow()
{
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    setFixedSize(400, 250);

    wholeLayout = new QGridLayout();

    pBaseSlider = new QSlider(Qt::Orientation::Horizontal);
    pBaseSlider->setMinimum(numbersInt::two);
    pBaseSlider->setTickInterval(numbersInt::one);
    pBaseSlider->setTickPosition(QSlider::TicksBelow);
    pBaseSlider->setMaximum(numbersInt::sixteen);

    transformButton = new QPushButton("Transform");
    transformButton->setFixedHeight(40);
    backSpaceButton = new QPushButton("BS");
    clearAllButton = new QPushButton("Clear All");
    dotButton = new QPushButton(".");
    pNumberLineEdit = new QLineEdit();
    precisionLineEdit = new QLineEdit();
    precisionLineEdit->setFixedWidth(95);
    precisionLabel = new QLabel("Precision: ");
    currentBaseLabel = new QLabel(QStringLiteral("Current base: %1").arg(this->getCurrentBase()));

    wholeLayout->addWidget(pNumberLineEdit, 0, 0, 1, 4);
    wholeLayout->addWidget(pBaseSlider, 1, 0, 1, 4);
    wholeLayout->addWidget(currentBaseLabel, 2, 0, 1, 4);
    wholeLayout->addWidget(precisionLabel, 3,0,1,1);
    wholeLayout->addWidget(precisionLineEdit, 3, 1, 1, 1);
    wholeLayout->addWidget(transformButton, 3, 3, 2, 1);

    int c = 0;
    for (int i = 5; i < 9; ++i){
        for (int j = 0; j < 4; ++j){
            if (c > numbersInt::nine){
                QPushButton *temp = new QPushButton(QString('A' + c - numbersInt::A));
                QObject::connect(temp, &QPushButton::clicked,[this, temp](){digitButtonPushed(temp->text());});
                vectorOfButtons.push_back(temp);
                wholeLayout->addWidget(temp, i, j);
            }else{
                QPushButton *temp = new QPushButton(QString::number(numbersInt::zero+c));
                QObject::connect(temp, &QPushButton::clicked,[this, temp](){digitButtonPushed(temp->text());});
                vectorOfButtons.push_back(temp);
                wholeLayout->addWidget(temp, i, j);
            }
            c++;
        }
    }
    wholeLayout->addWidget(dotButton, 9, 0);
    wholeLayout->addWidget(backSpaceButton, 9, 1);
    wholeLayout->addWidget(clearAllButton, 9, 2, 1, 2);

    window = new QWidget();
    setCentralWidget(window);
    window->setLayout(wholeLayout);

}

void MainWindow::checkButtonsToBase()
{
    for (auto it : vectorOfButtons){
        it->setEnabled(false);
    }
    for (int i = 0; i < _currentBase; ++i)
    {
        vectorOfButtons[i]->setEnabled(true);
    }

    QString rxLineEditString = QString("^[0-%1]*\\.[0-%1]*$").arg(_currentBase-1);
    if(_currentBase > numbersInt::nine)
        rxLineEditString = QString("^([0-%1]*[A-%2]*)*\\.([0-%1]*[A-%2]*)*")
                .arg(numbersInt::nine)
                .arg(QString('A' + _currentBase - numbersInt::B));
    //qDebug() << rxLineEditString << endl;
    QRegExp rxLineEdit(rxLineEditString);
    validatorLineEdit = new QRegExpValidator(rxLineEdit, this);
    pNumberLineEdit->setValidator(validatorLineEdit);

}

double MainWindow::getNumber() const
{
    return _number;
}

void MainWindow::setNumber(double number)
{
    _number = number;
}

int MainWindow::getCurrentBase() const
{
    return _currentBase;
}

void MainWindow::setCurrentBase(int value)
{
    _currentBase = value;
}

