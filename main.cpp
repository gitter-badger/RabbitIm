#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QCamera>
#include "Widgets/FrmVideo/CaptureVideoFrame.h"
#include "Widgets/FrmVideo/FrmPlayer.h"
#include <QVideoProbe>
#include "Tool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CTool::SetFFmpegLog();

    QString locale = QLocale::system().name();

    //本地化QT资源
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    //本地化程序资源
    QTranslator myappTranslator;
    myappTranslator.load("app_" + locale, a.applicationDirPath());
    a.installTranslator(&myappTranslator);

    /*
    MainWindow w;
    w.show();//*/

    //*以下为视频捕获、显示测试代码
    QList<QByteArray> device = QCamera::availableDevices();
    QList<QByteArray>::iterator it;
    for(it = device.begin(); it != device.end(); it++)
    {
        qDebug("Camera:%s", qPrintable(QCamera::deviceDescription(*it)));
    }

    QCamera camera;
    CCaptureVideoFrame captureVideoFrame;
    camera.setCaptureMode(QCamera::CaptureVideo);
    CFrmPlayer player;
    if(captureVideoFrame.setSource(&camera))
    {
        player.connect(&captureVideoFrame, SIGNAL(CaptureFrame(QVideoFrame)),
                       SLOT(present(QVideoFrame)));
    }

    player.show();
    player.activateWindow();
    camera.start();//*/

    return a.exec();
}
