#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "levelchoosescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // 重写 paintEvent 事件 画背景图
    void paintEvent(QPaintEvent *ev);

private:
    Ui::MainWindow *ui;
    LevelChooseScene *level_Choose_Scene = nullptr;
};
#endif // MAINWINDOW_H
