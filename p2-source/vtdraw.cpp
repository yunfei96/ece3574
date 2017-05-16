#include <QApplication>
#include "main_window.hpp"
int main(int argc, char * argv[])
{
    
    QApplication app(argc, argv);
    if(argc == 2)
    {
        MainWindow widget(argv[1]);
        widget.show();
        return app.exec();
    }
    if(argc == 1)
    {
        MainWindow widget;
        widget.show();
        return app.exec();
    }
    cout << "Error: argument number not right" << endl;
}
