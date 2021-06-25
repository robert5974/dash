#include <QApplication>
#include <QStringList>
#include <QProcess>
#include <QWindow>

#include "app/window.hpp"
// Support for Rotary Encoder (KY-040)
void monitor-volume(){
	// instantiate dynamically to avoid stack unwinding before the process terminates
    QProcess* process = new QProcess(); 

    // catch data output
    QObject::connect(process, &QProcess::readyRead, [process] () {
        QByteArray a = process->readAll();
        qDebug() <<  a;
    });

    // delete process instance when done, and get the exit status to handle errors.
    QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                     [=](int exitCode, QProcess::ExitStatus /*exitStatus*/){
        qDebug()<< "process exited with code " << exitCode;
        process->deleteLater();
    });

    // start the process after making signal/slots connections 
    process->start("python3 monitor-volume.py");
}
int main(int argc, char *argv[])
{
    QApplication dash(argc, argv);

    dash.setOrganizationName("openDsh");
    dash.setApplicationName("dash");

    QStringList args = dash.arguments();
    bool use_fixed_size = (args.size() > 2);

    QSize size = dash.primaryScreen()->size();
    if (use_fixed_size)
        size = QSize(args.at(1).toInt(), args.at(2).toInt());

    QPixmap pixmap(QPixmap(":/splash.png").scaledToHeight(size.height()/2));
    QSplashScreen splash(pixmap);
    splash.setMask(pixmap.mask());
    splash.show();
    dash.processEvents();

    Window window;
    window.setWindowIcon(QIcon(":/logo.png"));
    window.setWindowFlags(Qt::FramelessWindowHint);
    if (!use_fixed_size)
        window.setWindowState(Qt::WindowFullScreen);

    // force to either screen or custom size
    window.setFixedSize(size);
    window.show();
    splash.finish(&window);

    return dash.exec();
}
