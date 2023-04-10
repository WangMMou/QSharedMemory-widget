#include "widget.h"
#include "ui_widget.h"

#include <QWindow>
#include "windows.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QProcess>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    /*
    aW_app=new QProcess;
    aW_app->close();
    QString program="./A/A_app.exe";
    aW_app->setWorkingDirectory("./A");
    aW_app->start(program,NULL);
    Sleep(3000);
    */
    //bool isProcessOk=aW_app->waitForFinished();
    //bool isProcessOk1=aW_app->waitForStarted();

    m_shared_memory=new QSharedMemory;
    m_shared_memory->setKey(SHARED_MEMORY_KEY);
    m_shared_memory->attach(QSharedMemory::ReadWrite);
    m_shared_memory->lock();
    m_memoryInfo=(MemoryInfo *)m_shared_memory->constData();
    qDebug()<<m_memoryInfo->status<<m_memoryInfo->width<<m_memoryInfo->height<<m_memoryInfo->buffer;
    m_shared_memory->unlock();

    WId winId=(WId)FindWindow(NULL,L"aW");
    QWindow *window=QWindow::fromWinId(winId);
    QWidget *widget=QWidget::createWindowContainer(window);
    QWidget *container=new QWidget(this);
    //container->setContentsMargins(10,10,10,10);
    container->setMinimumSize(QSize(450,300));
    QVBoxLayout *layout=new QVBoxLayout(container);
    layout->addWidget(widget);
    layout->addWidget(ui->pushButton);
    layout->addWidget(ui->pushButton_2);
    container->show();

}

Widget::~Widget()
{
    aW_app->close();
    m_shared_memory->detach();
    delete m_shared_memory;
    delete aW_app;
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    m_shared_memory->lock();
    m_memoryInfo->status=1;
    memcpy(m_shared_memory->data(),m_memoryInfo,sizeof (MemoryInfo));
    m_shared_memory->unlock();
}

void Widget::on_pushButton_2_clicked()
{
    m_shared_memory->lock();
    m_memoryInfo->status=2;
    memcpy(m_shared_memory->data(),m_memoryInfo,sizeof (MemoryInfo));
    m_shared_memory->unlock();
}
