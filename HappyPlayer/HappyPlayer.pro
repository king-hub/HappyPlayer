#-------------------------------------------------
#
# Project created by QtCreator 2016-08-14T08:09:23
#
#-------------------------------------------------

QT       += core gui avwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HappyPlayer
TEMPLATE = app


SOURCES += main.cpp\
        MainView.cpp \
    Button/ButtonForStatusBar.cpp \
    View/TitleBar.cpp \
    View/PlayControlView.cpp \
    VideoPlayerVew/VideoPlayerView.cpp \
    VideoPlayerVew/Button/ButtonPlay.cpp \
    VideoPlayerVew/Slider/SliderControlPos.cpp

HEADERS  += MainView.h \
    Button/ButtonForStatusBar.h \
    Button/buttonheaderfile.h \
    View/TitleBar.h \
    View/PlayControlView.h \
    VideoPlayerVew/VideoPlayerView.h \
    VideoPlayerVew/Button/ButtonPlay.h \
    VideoPlayerVew/Slider/SliderControlPos.h

RESOURCES += \
    Button/buttonresources.qrc \
    View/view.qrc \
    VideoPlayerVew/Slider/slidercontrolpos.qrc

DISTFILES += \
    VideoPlayerVew/Slider/Res/SliderControlSlider
