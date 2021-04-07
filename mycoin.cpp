#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString button_img)
{
    QPixmap pixmap;
    bool isLoad = pixmap.load(button_img);
    if (!isLoad)
    {
        qDebug() << QString("图片%1加载失败").arg(button_img);
        return;
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border: 0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    // 初始化定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    // 监听 正面（金） 翻 反面（银） 的信号 并翻转金币
    this->connect(this->timer1, &QTimer::timeout, this, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border: 0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));

        // 如果翻完了
        if (this->min > this->max)
        {
            this->min = 1;
            this->isAnimation = false;
            this->timer1->stop();
        }
    });

    // 监听 反面（银） 翻 正面（金） 的信号 并翻转金币
    this->connect(this->timer2, &QTimer::timeout, this, [=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border: 0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));

        // 如果翻完了
        if (this->max < this->min)
        {
            this->max = 8;
            this->isAnimation = false;
            this->timer2->stop();
        }
    });
}

MyCoin::MyCoin(int init)
{
    // Gold :/res/Coin0001.png
    // Silver :/res/Coin0008.png
    QPixmap pixmap;
    QString button_img = nullptr;
    if (1 == init)
    {
        button_img = ":/res/Coin0001.png";
    }
    else
    {
        button_img = ":/res/Coin0008.png";
    }
    bool isLoad = pixmap.load(button_img);
    if (!isLoad)
    {
        qDebug() << QString("图片%1加载失败").arg(button_img);
        return;
    }
    this->setFixedSize(pixmap.width(), pixmap.height());
    this->setStyleSheet("QPushButton{border: 0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(), pixmap.height()));

    // 初始化定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    // 监听 正面 翻 反面 的信号 并翻转金币
    this->connect(this->timer1, &QTimer::timeout, this, [=](){

    });
}

void MyCoin::changeflag()
{
    if (true == this->flag)
    {
        this->timer1->start(30);
        this->isAnimation = true;
        this->flag = false;
    }
    else
    {
        this->timer2->start(30);
        this->isAnimation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *ev)
{
    if (this->isAnimation || this->isWin) // 胜利后标志，屏蔽点击
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(ev);
    }
}
