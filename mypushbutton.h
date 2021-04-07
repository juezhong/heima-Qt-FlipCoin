#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    // 正常显示的图片，按下后的图片 pressImg 默认为空
    MyPushButton(QString normalImg, QString pressImg = "");

    // 弹跳的特效
    void down(); // 图片向下
    void uppr(); // 图片向上

    // 关卡选择界面返回按钮
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QString normalImgPath;
    QString pressImgPath;

signals:

};

#endif // MYPUSHBUTTON_H
