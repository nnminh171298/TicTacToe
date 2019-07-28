QT += quick svg
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

RC_ICONS = $$PWD/images/NomiT3-icon.ico
VERSION = 2.0.1

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

HEADERS += \
    scr/algo.h \
    scr/algo_fillblank.h \
    scr/algo_minimax.h \
    scr/algo_random.h \
    scr/backend.h \
    scr/board.h \
    scr/gameengine.h \
    scr/gamenode.h \
    scr/gametreegenerator.h

SOURCES += \
    scr/algo.cpp \
    scr/algo_fillblank.cpp \
    scr/algo_minimax.cpp \
    scr/algo_random.cpp \
    scr/backend.cpp \
    scr/board.cpp \
    scr/gameengine.cpp \
    scr/gamenode.cpp \
    scr/gametreegenerator.cpp \
    scr/main.cpp

RESOURCES += \
    images.qrc \
    qml.qrc
