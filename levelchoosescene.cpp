#include "levelchoosescene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QLabel>

LevelChooseScene::LevelChooseScene(QWidget *parent) : QMainWindow(parent)
{
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

    // 创建选择关卡的按钮
    for (int i = 0; i < 20; i++)
    {
        MyPushButton *level_button = new MyPushButton(":/res/LevelIcon.png");
        level_button->setParent(this);
        level_button->move(25 + i%4 * 70, 130 + i/4 * 70);
        // 设置文字使用 QLabel

        // 监听每个按钮的点击事件
        this->connect(level_button, &MyPushButton::clicked, this, [=](){
            QString str = QString("You select %1 level").arg(i+1);
            qDebug() << str;

            // 这里可以加入 if 判断
//            if (this->play_scene == nullptr)
//            {

            // 进入游戏场景
            this->hide();
            this->play_scene = new PlayScene(i + 1); // 创建游戏场景

            // 设置游戏场景的位置
            play_scene->setGeometry(this->geometry());

            this->play_scene->show();
//            }
            this->connect(play_scene, &PlayScene::click_back_button, this, [=](){
                // 设置返回时的位置
                this->setGeometry(play_scene->geometry());

                this->show();
                delete play_scene;
                play_scene = nullptr;
            });
        });

        QLabel *label = new QLabel(this);
        label->setFixedSize(level_button->width(), level_button->height());
        label->setText(QString::number(1 + i));
        label->move(25 + i%4 * 70, 130 + i/4 * 70);
        // 字体显示在左边，设置文字对齐方式
        label->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

        // 设置了 Label 相当于往 button 上盖了一层东西，button 无法获得点击事件
        // 设置鼠标穿透（传输鼠标事件）
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void LevelChooseScene::paintEvent(QPaintEvent *ev)
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
