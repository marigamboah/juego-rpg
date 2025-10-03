#include <QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "ui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    // Música de fondo (Qt 6)
    auto *audioOutput = new QAudioOutput(&w);
    audioOutput->setVolume(0.5);                 // 0.0 .. 1.0

    auto *music = new QMediaPlayer(&w);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/assets/audio/music_bg.wav")); // resources.qrc
    music->setLoops(QMediaPlayer::Infinite);     // repetir en bucle
    music->play();

    w.show();
    return a.exec();
}
