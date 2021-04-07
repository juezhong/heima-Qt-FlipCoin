#ifndef LEVELCHOOSESCENE_H
#define LEVELCHOOSESCENE_H

#include <QMainWindow>
#include "playscene.h"

class LevelChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelChooseScene(QWidget *parent = nullptr);
    // 重写 paintEvent 事件 画背景图
    void paintEvent(QPaintEvent *ev);

private:
    PlayScene *play_scene = nullptr;

signals:
    // 写一个自定义的信号，告诉主场景点击了返回按钮
    void click_back_button();

};

#endif // LEVELCHOOSESCENE_H
