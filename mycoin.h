#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString button_img);
    MyCoin(int init);

    // 金币的其他属性
    int posX; // X 坐标
    int posY; // Y 坐标
    bool flag; // 正反的标志
    bool isAnimation = false; // 执行动画的标志
    bool isWin = false; // 判断胜利标志

    void changeflag(); // 改变标志执行翻转效果
    void mousePressEvent(QMouseEvent *ev) override;

private:
    QTimer *timer1; // 正面（金） -> 反面（银）
    QTimer *timer2; // 反面（银） -> 正面（金）
    int min = 1;
    int max = 8;

signals:

};

#endif // MYCOIN_H
