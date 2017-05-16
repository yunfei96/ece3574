#ifndef MSG
#define MSG
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
class QLineEdit;
class MessageWidget: public QWidget
{
Q_OBJECT
public:
    MessageWidget(QWidget * parent = nullptr);
public slots:
    void info(QString message);
    void error(QString message);
private:
    QLabel *label;
    QLineEdit * msg_lable;
};
#endif
