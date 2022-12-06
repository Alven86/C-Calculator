#include "alvenmainwindow.h"
#include "ui_alvenmainwindow.h"
#include "calculatorbrain.h"
#include <QDebug>
AlvenMainWindow::AlvenMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlvenMainWindow)
{
    ui->setupUi(this);
    _keyFrombuttonpointer = {
        {ui->btn0, Key::zero},
        {ui->btn1, Key::one},
        {ui->btn2, Key::two},
        {ui->btn3, Key::three},
        {ui->btn4, Key::four},
        {ui->btn5, Key::five},
        {ui->btn6, Key::six},
        {ui->btn7, Key::seven},
        {ui->btn8, Key::eight},
        {ui->btn9, Key::nine},
        {ui->btnEqual, Key::equal},
        {ui->btnDiv, Key::div},
        {ui->btnTimes, Key::times},
        {ui->btnMinus, Key::minus},
        {ui->btnPlus, Key::plus},
        {ui->btnSin, Key::sin},
        {ui->btnTan, Key::tan},
        {ui->btnCos, Key::cos},
        {ui->btnSqrt, Key::sqrt},
        {ui->btnExp10, Key::exp10},
        {ui->btnExp, Key::exp},
        {ui->btnDeg, Key::degrees},
        {ui->btnRad, Key::radians},
        {ui->btnDecimal, Key::decimal},
        {ui->btnSign, Key::sign},

        {ui->btnPow, Key::pow}
    };

      _keyInvertetd={
        {Key::sin, Key::asin},
        {Key::cos, Key::acos},
        {Key::tan, Key::atan},
        {Key::sqrt, Key::square},
        {Key::exp10, Key::log},
        {Key::exp, Key::ln}
    };

      _stringFromFunctionKey={
        {Key::sin, "sin"},
        {Key::cos, "cos"},
        {Key::tan, "tan"},
        {Key::acos, "acos"},
        {Key::asin, "asin"},
        {Key::atan, "atan"},
        {Key::sqrt, "sqrt"},
        {Key::exp10, "exp10"},
        {Key::exp, "exp"},
        {Key::square, "x^2"},
        {Key::log, "log"},
        {Key::ln, "ln"}

    };
      for(QObject* child: ui->centralWidget->children()){
          QPushButton *button=dynamic_cast<QPushButton*>(child);
          if(button){
              connect(button,SIGNAL(clicked(bool)),this,SLOT(someButtonWasClicked()));
          }
      }
}


AlvenMainWindow::~AlvenMainWindow()
{
    delete ui;
}

void AlvenMainWindow::someButtonWasClicked(){
    const QAbstractButton *theButton = dynamic_cast<QAbstractButton*>(sender());

    const bool isInverted = ui->btnInv->isChecked();

    if(theButton==ui->btnInv){

        const bool nextState = isInverted;
        ui->btnInv->setChecked(nextState);
        changeTextOnFunctionButtons(nextState);
    }
    else{
        Key key = keyFromButton(theButton,isInverted);

        const QString result = _brain.processKey(key);


        ui->display->setText(result);
        if(isInverted){
            ui->btnInv->setChecked(false);
            changeTextOnFunctionButtons(false);

        }
    }
}
Key AlvenMainWindow::changeTextOnFunctionButtons(bool invert){
    for(QObject* widget : ui->centralWidget->children()){
        QAbstractButton* btn = dynamic_cast<QAbstractButton*>(widget);
        Key key = keyFromButton(btn, invert);
        if(_stringFromFunctionKey.find(key)!=_stringFromFunctionKey.end()){
            QString btnText = _stringFromFunctionKey[key];
            btn->setText(btnText);

        }
    }
}
Key AlvenMainWindow::keyFromButton(const QAbstractButton* button, bool invert){
    Key key = _keyFrombuttonpointer[button];
    if(invert && _keyInvertetd.find(key)!=_keyInvertetd.end()){
        return _keyInvertetd[key];

    }
    return key;
}
