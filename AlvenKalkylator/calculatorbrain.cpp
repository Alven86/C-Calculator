#include "calculatorbrain.h"
//#include <math.h>
//#define _USE_MATH_DEFINES
//#include <cmath>
#include <QtMath>
#include <QObject>
#include <iostream>

Calculatorbrain::Calculatorbrain()
{
     _unaryopFromKey = {
        {Key::cos, [this](double w)->double{return cos(w*M_PI/180);}},
        {Key::sin, [this](double w)->double{return sin(w*M_PI/180);}},
        {Key::tan, [this](double w)->double{return tan(w*M_PI/180);}},
        {Key::acos, [this](double x)->double{return (acos(x)*180/M_PI);}},
        {Key::asin, [this](double x)->double{return (asin(x)*180/M_PI);}},
        {Key::atan, [this](double x)->double{return (atan(x)*180/M_PI);}},
        {Key::sqrt,sqrt},
        {Key::exp10,[](double v)->double{return pow(10,v);}},
        {Key::exp,exp},
        {Key::square, [](double v)->double{return v*v;}},
        {Key::log,log10},
        {Key::ln,log}

    };
     _infixopFromKey={
        {Key::plus, [](double a, double b)->double{return a+b;}},
        {Key::minus, [](double a, double b)->double{return a-b;}},
        {Key::times, [](double a, double b)->double{return a*b;}},
        {Key::div, [](double a, double b)->double{return a/b;}},
        {Key::pow, [](double a, double b)->double{return pow(a,b);}}


    };


}



QString Calculatorbrain::processKey(Key key){


    if(key==Key::degrees){
        _isCalculatingInDegrees = true;


    }

    else if(key==Key::degrees){
        _isCalculatingInDegrees = false;

    }
    else if(isDigit(key)){
        if(_isTypingNumber){
            _strDisplay += digitstringFromKey(key);
        }
        else{
            _strDisplay = digitstringFromKey(key);
            _isTypingNumber = true;
        }
    }
    else if(key==Key::sign){
        changeSign();
    }
    else if(key==Key::decimal){
        insertDecimalDot();
    }
    else if(key==Key::equal){
        applyPendingInfixOperation();
        _isTypingNumber = false;
    }
    else if(isInfixOperator(key)){
        applyPendingInfixOperation();
        _isTypingNumber = false;
        _pendingOperation = key;
        _pendingValue = valueOfDisplay();
    }
    else if (isUnaryOperation(key)){
        applyUnaryOperation(key);
        _isTypingNumber = false;
    }
    return _strDisplay;


}


double Calculatorbrain::radiansFromUserunit(double angle) const {
    return _isCalculatingInDegrees ? angle*M_PI/180
                                   : angle;
}

double Calculatorbrain::userunitFromRadians(double radians) const{
    return _isCalculatingInDegrees ? radians*180/M_PI
                                   : radians;

}

bool Calculatorbrain::isUnaryOperation(Key key) const {
    return _unaryopFromKey.find(key)!=_unaryopFromKey.end();
}

void Calculatorbrain::applyUnaryOperation(const Key key){
    double currentValue = valueOfDisplay();
    double nextValue = _unaryopFromKey[key](currentValue);
    setDisplayFromValue(nextValue);
}

bool Calculatorbrain::isInfixOperator(Key key) const {
    return _infixopFromKey.find(key)!=_infixopFromKey.end();
}

void Calculatorbrain::applyPendingInfixOperation(){
    if(_pendingOperation==Key::noop)
        return;
    double currentValue = valueOfDisplay();
    double nextValue = _infixopFromKey[_pendingOperation](_pendingValue,currentValue);
    setDisplayFromValue(nextValue);

    _pendingOperation = Key::noop;

}

void Calculatorbrain::changeSign(){
    if(_strDisplay[0]=='-'){
        _strDisplay= _strDisplay.mid(1);
    }
    else{
        _strDisplay = "-" + _strDisplay;
    }
}


void Calculatorbrain::insertDecimalDot(){
    if(!_strDisplay.contains('.'))
        _strDisplay +=".";
}

double Calculatorbrain::valueOfDisplay() const {
    return _strDisplay.toDouble();
}

void Calculatorbrain::setDisplayFromValue(double v){
    _strDisplay = QString::number(v);
}
