#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pixmap;
    bool isLoad = pixmap.load(normalImg);
    if (!isLoad)
    {
        qDebug() << "pixmap load failed!!";
    }
    // 设置图片固定大小
    this->setFixedSize(pixmap.width(), pixmap.height());
    // 设置不规则图片样式
    this->setStyleSheet("QPushButton{border :0px;}");
    // 设置图标
    this->setIcon(pixmap);
    // 设置图标大小
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));
}

void MyPushButton::down()
{
    // 创建一个动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    // 设置动画的时间间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 执行这个动效
    animation->start();
}

void MyPushButton::uppr()
{
    // 创建一个动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    // 设置动画的时间间隔
    animation->setDuration(200);
    // 起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    // 结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    // 设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 执行这个动效
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if (this->pressImgPath != "")
    {
        QPixmap pixmap;
        bool isLoad = pixmap.load(this->pressImgPath);
        if (!isLoad)
        {
            qDebug() << "pixmap load failed!!";
        }
        // 设置图片固定大小
        this->setFixedSize(pixmap.width(), pixmap.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border :0px;}");
        // 设置图标
        this->setIcon(pixmap);
        // 设置图标大小
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    // 上面拦截完之后还要让父类执行其他内容
    return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->pressImgPath != "")
    {
        QPixmap pixmap;
        bool isLoad = pixmap.load(this->normalImgPath);
        if (!isLoad)
        {
            qDebug() << "pixmap load failed!!";
        }
        // 设置图片固定大小
        this->setFixedSize(pixmap.width(), pixmap.height());
        // 设置不规则图片样式
        this->setStyleSheet("QPushButton{border :0px;}");
        // 设置图标
        this->setIcon(pixmap);
        // 设置图标大小
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    // 上面拦截完之后还要让父类执行其他内容
    return QPushButton::mouseReleaseEvent(event);
}
