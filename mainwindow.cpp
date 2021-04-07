#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
//#include <QSound> // 使用前需要先  pro 文件中加入 QT += multimedia
// 制作时Qt6 中没有，所以没有添加

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 配置主场景
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("CoinFlip Main Window");
    // 设置退出按钮
    // mac 全局菜单不显示 Quit
    // 测试发现是与系统的重复，故不显示，更换名字解决
    this->connect(ui->actionClickQuit, &QAction::triggered, this, [=](){
        this->close();
    });

    // 实例化选择关卡场景
    this->level_Choose_Scene = new LevelChooseScene;

    // 准备开始按钮的音效
//    QSound *start_sound = QSound(":/res/TapButtonSound.wav", this);
    // 播放在 42 行
    // 选择关卡，返回按钮，翻金币，胜利同样有音效，暂时不再添加

    // 添加开始按钮
    MyPushButton *startButton = new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    int button_width = this->width() * 0.5 - startButton->width() * 0.5;
    startButton->move(button_width, this->height() * 0.5);
    this->connect(startButton, &QPushButton::clicked, this, [=](){
//        qDebug() << "click start button.";
        // 播放音效
//        start_sound->play();

        startButton->down();
        startButton->uppr();
        // 直接点击就切换，没有时间显示动画
        // 延迟
        QTimer::singleShot(500, this, [=](){
            // 设置选择场景的位置
            level_Choose_Scene->setGeometry(this->geometry());

            // 将当前界面隐藏
            this->hide();
            // 进入到选择关卡场景中
            this->level_Choose_Scene->show();
        });

    });
    // 添加监听返回信号的槽函数
    this->connect(level_Choose_Scene, &LevelChooseScene::click_back_button, this, [=](){
        // 设置返回时的位置
        this->setGeometry(level_Choose_Scene->geometry());

        this->level_Choose_Scene->hide();
        this->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *ev)
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
    // 图片太大进行缩放
    background = background.scaled(background.width() * 0.5, background.height() * 0.5);
    painter.drawPixmap(0, 0, background);
}

