#ifndef WIDGET_H
#define WIDGET_H

#define SHARED_MEMORY_KEY "shared_memory_a"

#include <QWidget>
#include <QProcess>

#include <QSharedMemory>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


typedef struct {
    int status;
    int width;
    int height;
    char buffer[1024];
}MemoryInfo;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    QProcess *aW_app;

    QSharedMemory *m_shared_memory;
    MemoryInfo *m_memoryInfo;
};
#endif // WIDGET_H
