/*
 * This file is part of mg-package-manager
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (C) 2013 Timo Hannukkala <timo.hannukkala@nomovok.com>
 *
 * Contact: Kyösti Ranto <kyosti.ranto@digia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <QGuiApplication>
#include "packagemanager.h"
#include "iconprovider.h"

#include <QObject>
#include <QString>
#include <QMainWindow>
#include <QQuickView>
#include <QGraphicsObject>

#include <QDebug>
#include <QtQml>
#include <QQmlContext>
#include <QQmlEngine>
#include <QGuiApplication>

#include "package.h"
#include "packagegroup.h"
#include "packagemarkings.h"
#include "repository.h"
#include "packagemodel.h"
#include "filterpackagemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView viewer;

    PackageManager *pm = new PackageManager(&viewer);

    QQmlContext *context = viewer.rootContext();
    context->setContextProperty("initialstate", "mainview");
    context->setContextProperty("mainWindow", &viewer);
    viewer.engine()->addImageProvider(QLatin1String("icons"), new IconProvider);
    viewer.engine()->addImportPath("/usr/lib/qt5/imports");

    qmlRegisterType<Package>("Package", 1,0, "Package");
    qmlRegisterType<PackageGroup>("Package", 1,0, "PackageGroup");
    qmlRegisterType<PackageMarkings>("Package", 1, 0, "PackageMarkings");
    qmlRegisterType<Repository>("Repository", 1,0, "Repository");
    qmlRegisterType<FilterPackageModel>("FilterPackageModel", 1,0, "FilterPackageModel");

    viewer.setSource(QUrl("qrc:/qml/main.qml"));

    viewer.showFullScreen();

    return app.exec();
}
