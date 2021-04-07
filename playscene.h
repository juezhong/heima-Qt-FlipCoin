#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    // 重写 paintEvent 事件 画背景图
    void paintEvent(QPaintEvent *ev);

private:
    int Level_Index;
    int gameArray[4][4]; // 二维数组维护每个关卡的具体数据
    MyCoin *coins[4][4]; // 维护创建的每个金币
    bool isWin; // 判断胜利标志

signals:
    // 写一个自定义的信号，告诉主场景点击了返回按钮
    void click_back_button();

};

#endif // PLAYSCENE_H
