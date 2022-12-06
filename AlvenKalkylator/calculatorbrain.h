#ifndef CALCULATORBRAIN_H
#define CALCULATORBRAIN_H
#include <QString>
#include <map>
#include <iostream>
#include <functional>

enum class Key{
    zero = 0,
    one,two,three,four,five,six,seven,eight,nine,
    sign,decimal,
    radians,degrees,
    sin,cos,tan,
    asin,acos,atan,
    sqrt,exp10,exp,pow,
    square,log,ln,
    plus,minus,times,div,equal,
    noop //no operation
};

inline int intFromKey(Key key){
    return int(key);
}

inline bool isDigit(Key key){
    return intFromKey(key)<=9;
}

inline QString digitstringFromKey(Key key){
    QString digit;
    digit.setNum(intFromKey(key),10);
    return digit;
}

class Calculatorbrain
{


public:

    Calculatorbrain();

    QString processKey(Key key);

    static bool selfTest();

    void applyUnaryOperation(const Key key);
    double radiansFromUserunit(double angle) const;
    double userunitFromRadians(double radians) const;

    void applyPendingInfixOperation();
    void changeSign();
    void insertDecimalDot();
    double valueOfDisplay() const;

    void setDisplayFromValue(double v);
private:
    bool isInfixOperator(Key key) const;
    bool isUnaryOperation(Key key) const;

    QString _strDisplay;
    bool _isTypingNumber=false;
    bool _isCalculatingInDegrees;
    Key _pendingOperation=Key::noop;
    double _pendingValue;


    std::map<Key, std::function<double(double)> > _unaryopFromKey;
    std::map<Key, std::function<double(double,double)> > _infixopFromKey;

};

#endif // CALCULATORBRAIN_H
