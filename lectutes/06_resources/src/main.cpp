#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QLibraryInfo>
#include "mainwindow.h"

// Helper function to install Qt's base translations
static bool installQtBaseTranslator(QTranslator &tr, const QLocale &loc)
{
    const QString dir = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
    const QString full = QStringLiteral("qtbase_%1").arg(loc.name());
    const QString shortCode = QStringLiteral("qtbase_%1").arg(loc.name().section('_', 0, 0));
    return (tr.load(full, dir) || tr.load(shortCode, dir));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Qt's base translator for standard dialogs, etc.
    static QTranslator qtTr; // Static to ensure it lives as long as the app
    const QLocale loc = QLocale::system();

    if (installQtBaseTranslator(qtTr, loc)) {
        app.installTranslator(&qtTr);
        qDebug() << "Qt base translations installed for" << loc.name();
    } else {
        qDebug() << "No Qt base translations for" << loc.name();
    }

    // Set the default locale for the application.
    // This is crucial for QLocale::system() and tr() calls to pick up the correct language initially.
    QLocale::setDefault(loc);

    // The app-specific translator will be managed by MainWindow::changeLanguage.
    // Initialize the main window.
    MainWindow w;
    w.show();

    return app.exec();
}
