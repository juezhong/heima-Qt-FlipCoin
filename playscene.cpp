#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    this->Level_Index = levelNum;
    qDebug() << "进入了" << this->Level_Index << "关";

    // 配置场景
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("Level Choose Scene");

    // 创建菜单栏
    QMenuBar *mbar = menuBar();
    this->setMenuBar(mbar);
    // 添加菜单 menu
    QMenu *menu_main = mbar->addMenu("Main");
    // 添加动作 action
    QAction *action_quit = menu_main->addAction("ClickQuit");
    this->connect(action_quit, &QAction::triggered, this, [=](){
        this->close();
    });

    // 添加一个返回按钮
    MyPushButton *back_button = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    back_button->setParent(this);
    back_button->move(this->width() - back_button->width(), this->height() - back_button->height());
    // 点击返回
    this->connect(back_button, &MyPushButton::clicked, this, [=](){
//        qDebug() << "click back button.";
        // 返回功能实现（使用自定义的信号和槽）
        // 延时处理
//        QTimer::singleShot(500, this, [=](){

//        });
        // 发送一个信号，使连接信号的槽能够接收处理
        emit this->click_back_button();
    });

    // 显示当前关卡数
    QLabel *level_num_label = new QLabel(this);
    QFont level_num_font;
    level_num_font.setFamily("STHeiti");
    level_num_font.setPointSize(20);
    QString level_string = QString("Level: %1").arg(this->Level_Index);
    level_num_label->setText(level_string);
    level_num_label->setFont(level_num_font);
    level_num_label->setGeometry(30, this->height() - 50, 120, 50);

    dataConfig config;
    // 初始化每个关卡的二维数组
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            this->gameArray[i][j] = config.mData[this->Level_Index][i][j];
        }
    }

    // 胜利图片显示
    QLabel *WinLabel = new QLabel;
    QPixmap tmp_pix;
    tmp_pix.load(":/res/LevelCompletedDialogBg.png");
    WinLabel->setGeometry(0, 0, tmp_pix.width(), tmp_pix.height());
    WinLabel->setPixmap(tmp_pix);
    WinLabel->setParent(this);
    WinLabel->move((this->width() - tmp_pix.width()) * 0.5, -tmp_pix.height());

    // 显示金币的背景图案
    int init = 1;
    QString init_png = nullptr;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            // 绘制背景图片
            QLabel *coin_background = new QLabel(this);
            coin_background->setGeometry(0, 0, 50, 50);
            coin_background->setPixmap(QPixmap(":/res/BoardNode.png"));
            coin_background->move(57 + i*50, 200 + j*50);

            // 创建金币
            if (1 == this->gameArray[i][j])
            {
                init = 1;
                init_png = ":/res/Coin0001.png";
            }
            else
            {
                init = 8;
                init_png = ":/res/Coin0008.png";
            }
//            MyCoin *coin = new MyCoin(init);
            MyCoin *coin = new MyCoin(init_png);
            coin->setParent(this);
            coin->move(59 + i*50, 204 + j*50);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            // 将金币放入到维护的二维数组里，方便后面维护
            this->coins[i][j] = coin;

            // 设置按钮点击事件 进行翻转
            this->connect(coin, &MyCoin::clicked, this, [=](){
                // 点击当前金币时，禁用其他金币的点击
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        this->coins[i][j]->isWin = true;
                    }
                }

               coin->changeflag();
               // 对二维数组中的值进行改变
               this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
               // this->gameArray[i][j] = this->flag;

               // 翻转周围的金币 延迟翻转
               QTimer::singleShot(300, this, [=](){
                   if (coin->posX + 1 <= 3) // 翻转右侧
                   {
                       this->coins[coin->posX + 1][coin->posY]->changeflag();
                       this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                   }
                   if (coin->posX - 1 >= 0) // 翻转左侧
                   {
                       this->coins[coin->posX - 1][coin->posY]->changeflag();
                       this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                   }
                   if (coin->posY - 1 >= 0) // 翻转上侧
                   {
                       this->coins[coin->posX][coin->posY - 1]->changeflag();
                       this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                   }
                   if (coin->posY + 1 <= 3) // 翻转下侧
                   {
                       this->coins[coin->posX][coin->posY + 1]->changeflag();
                       this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                   }

                   // 翻转完以后解除禁用
                   for (int i = 0; i < 4; ++i) {
                       for (int j = 0; j < 4; ++j) {
                           this->coins[i][j]->isWin = false;
                       }
                   }

                   // 判断是否胜利
                   this->isWin = true;
                   for (int i = 0; i < 4; ++i) {
                       for (int j = 0; j < 4; ++j) {
                           if (this->coins[i][j]->flag == false)
                           {
                               this->isWin = false;
                           }
                       }
                   }
                   if (this->isWin == true)
                   {
                       // 胜利
                       qDebug() << "游戏胜利";
                       for (int i = 0; i < 4; ++i) {
                           for (int j = 0; j < 4; ++j) {
                               this->coins[i][j]->isWin = true;
                           }
                       }
                       // 将胜利的图片移动下来
                       QPropertyAnimation *animation = new QPropertyAnimation(WinLabel, "geometry");
                       // 设置时间间隔
                       animation->setDuration(1000);
                       // 设置开始位置
                       animation->setStartValue(QRect(WinLabel->x(), WinLabel->y(), WinLabel->width(), WinLabel->height()));
                       // 设置结束位置
                       animation->setEndValue(QRect(WinLabel->x(), WinLabel->y() + 114, WinLabel->width(), WinLabel->height()));
                       // 设置缓和曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);
                       // 执行动画
                       animation->start();
                   }
               }); // QTimer::singleShot

            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap background;
//    QPixmap background(":/res/PlayLevelSceneBg.png");
    background.load(":/res/PlayLevelSceneBg.png");
    // 这种方式按照图片原本的像素画，有可能不能铺满窗口
//    painter.drawPixmap(0, 0, background);
    // 这种方式设置图片的长宽为当前窗口的大小（拉伸）
    painter.drawPixmap(0, 0, this->width(), this->height(), background);

    // 继续画一个背景图标
//    QPixmap back_title;
    background.load(":/res/Title.png");
    painter.drawPixmap((this->width() - background.width()) * 0.5, 30, background.width(), background.height(), background);
}
