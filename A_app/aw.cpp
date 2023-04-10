#include "aw.h"
#include "ui_aw.h"
#include <QTimer>
#include <QDateTime>

#include "windows.h"

aW::aW(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::aW)
{
    ui->setupUi(this);
    //共享内存
    m_screen_width=GetSystemMetrics(SM_CXSCREEN);
    m_screen_height=GetSystemMetrics(SM_CYSCREEN);
    m_memoryInfo=new MemoryInfo;
    m_shared_memory=new QSharedMemory;
    m_shared_memory->setKey(SHARED_MEMORY_KEY);
    m_shared_memory->create(sizeof (m_memoryInfo),QSharedMemory::ReadWrite);
    const char*shared_info_a="shared memory A ! ";
    m_memoryInfo->status=1;
    m_memoryInfo->width=m_screen_width;
    m_memoryInfo->height=m_screen_height;
    memcpy(m_memoryInfo->buffer,shared_info_a,strlen(shared_info_a));
    m_shared_memory->lock();
    memcpy(m_shared_memory->data(),m_memoryInfo,sizeof (MemoryInfo));
    m_shared_memory->unlock();

    //程序框嵌
    setFixedSize(QSize(450,300));
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[&](){
        m_shared_memory->lock();
        m_memoryInfo=(MemoryInfo *)m_shared_memory->constData();
        m_shared_memory->unlock();
        QString dt;
        if(m_memoryInfo->status==1){
           dt=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        }
        else if(m_memoryInfo->status==2){
           dt=QDateTime::currentDateTime().toString("hh:mm:ss yyyy-MM-dd");
        }
            ui->label->setText(dt);
            });
    timer->start(1000);
}

aW::~aW()
{
    m_shared_memory->detach();
    delete m_shared_memory;
    delete m_memoryInfo;
    delete ui;
}

