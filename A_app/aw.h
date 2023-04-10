#ifndef AW_H
#define AW_H

#define SHARED_MEMORY_KEY "shared_memory_a"

#include <QWidget>
#include <QSharedMemory>
QT_BEGIN_NAMESPACE
namespace Ui { class aW; }
QT_END_NAMESPACE


typedef struct {
    int status;
    int width;
    int height;
    char buffer[1024];
}MemoryInfo;

class aW : public QWidget
{
    Q_OBJECT

public:
    aW(QWidget *parent = nullptr);
    ~aW();

private:
    Ui::aW *ui;
    QSharedMemory *m_shared_memory;
    MemoryInfo *m_memoryInfo;
    int m_screen_width;
    int m_screen_height;

};
#endif // AW_H
