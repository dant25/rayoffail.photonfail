#-------------------------------------------------
#
# Project created by QtCreator 2012-05-10T12:24:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = photonfail
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagewidget.cpp \
    ../src/Transform.cpp \
    ../src/Texture.cpp \
    ../src/SpectralQuantity.cpp \
    ../src/Scene.cpp \
    ../src/Renderer.cpp \
    ../src/Material.cpp \
    ../src/Importer.cpp \
    ../src/Image.cpp \
    ../src/Container.cpp \
    ../src/Camera.cpp \
    ../src/lights/SpotLight.cpp \
    ../src/lights/QuadLight.cpp \
    ../src/lights/PointLight.cpp \
    ../src/lights/Light.cpp \
    ../src/lights/DiskLight.cpp \
    ../src/math/Vec3.cpp \
    ../src/math/Utilities.cpp \
    ../src/math/Mat4x4.cpp \
    ../src/objects/Sphere.cpp \
    ../src/objects/Object.cpp \
    ../src/objects/Mesh.cpp \
    ../src/util/image.c \
    ../src/util/tinyxml/tinyxmlparser.cpp \
    ../src/util/tinyxml/tinyxmlerror.cpp \
    ../src/util/tinyxml/tinyxml.cpp \
    ../src/util/tinyxml/tinystr.cpp

HEADERS  += mainwindow.h \
    imagewidget.h \
    ../src/Transform.h \
    ../src/Texture.h \
    ../src/SpectralQuantity.h \
    ../src/Scene.h \
    ../src/Renderer.h \
    ../src/Material.h \
    ../src/Importer.h \
    ../src/Image.h \
    ../src/Container.h \
    ../src/Camera.h \
    ../src/lights/SpotLight.h \
    ../src/lights/QuadLight.h \
    ../src/lights/PointLight.h \
    ../src/lights/Light.h \
    ../src/lights/DiskLight.h \
    ../src/math/Vec3.h \
    ../src/math/Utilities.h \
    ../src/math/Ray.h \
    ../src/math/Mat4x4.h \
    ../src/math/Intersection.h \
    ../src/objects/Sphere.h \
    ../src/objects/Object.h \
    ../src/objects/Mesh.h \
    ../src/util/image.h \
    ../src/util/tinyxml/tinyxml.h \
    ../src/util/tinyxml/tinystr.h

FORMS    += mainwindow.ui
