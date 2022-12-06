#ifndef ALVENMAINWINDOW_H
#define ALVENMAINWINDOW_H

#include <QMainWindow>
#include <QAbstractButton>
#include <map>
#include "calculatorbrain.h"


namespace Ui {
class AlvenMainWindow;
}

class AlvenMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlvenMainWindow(QWidget *parent = 0);
    Key keyFromButton(const QAbstractButton* button, bool invert);
    Key changeTextOnFunctionButtons(bool invert);
    ~AlvenMainWindow();

private:
    Ui::AlvenMainWindow *ui;
    std::map<const QObject*, Key> _keyFrombuttonpointer;
    std::map<Key, Key> _keyInvertetd;
    std::map<Key, QString> _stringFromFunctionKey;
    Calculatorbrain _brain;
private slots:
    void someButtonWasClicked();
};

#endif // ALVENMAINWINDOW_H
