#include "mainwindow.h"
#include "./ui_mainwindow.h" // Include the generated UI header
#include <QPixmap>
#include <QDebug>
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>
#include <QEvent> // Required for changeEvent
#include <QDir>
#include <QFileInfo>
#include <QResource>
#include <QDirIterator>

static void dumpResDir(const QString &path, int depth = 0)
{
    const QString indent(depth * 2, QLatin1Char(' '));
    QDir dir(path);
    // Показати спочатку теки, потім файли, стабільно відсортовано
    const QFileInfoList items = dir.entryInfoList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
        QDir::Name | QDir::DirsFirst | QDir::IgnoreCase);

    for (const QFileInfo &fi : items) {
        const QString resPath = fi.filePath();

        if (fi.isDir()) {
            qDebug().noquote() << indent << "[DIR] " << resPath;
            dumpResDir(resPath, depth + 1);
        } else {
            QResource res(resPath);
            const bool ok = res.isValid();
            const qint64 sz = ok ? res.size() : -1;
            qDebug().noquote() << indent << "     " << resPath
                               << (ok ? QString("(%1 bytes)").arg(sz)
                                      : QString("(invalid)"));
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Corrected image path: ":/images/qt_logo.png" is correct if resources.qrc
    // has <qresource prefix="/images"><file>qt_logo.png</file></qresource>
    QString imagePath = QStringLiteral(":/images/qt_logo.png");
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->size(),
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));
    } else {
        ui->imageLabel->setText(tr("Image not found")); // Mark for translation
        qWarning() << "Failed to load" << imagePath;
    }

    updateUiTexts();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ukrainianButton_clicked()
{
    changeLanguage(QStringLiteral("uk_UA"));
}

void MainWindow::on_englishButton_clicked()
{
    changeLanguage(QStringLiteral("en_US"));
}

// Helper function to load and install a translator
static bool installTranslator(QTranslator &translator, const QString &qmFileName)
{
    // Try loading from different possible paths
    const QStringList paths = {
        QString(":%1.qm").arg(qmFileName)  // direct path with extension
    };

    for (const QString &path : paths) {
        qDebug() << "Trying to load translation from:" << path;
        if (translator.load(path)) {
            QApplication::instance()->installTranslator(&translator);
            qDebug() << "Successfully loaded translation from:" << path;
            return true;
        }
    }
    return false;
}

void MainWindow::changeLanguage(const QString &languageCode)
{
    qDebug() << "\n=== Changing language to" << languageCode << "===";
    
    // Remove existing app translator to prevent conflicts
    static QTranslator currentAppTranslator; // Static to persist across calls
    QApplication::instance()->removeTranslator(&currentAppTranslator);

    // First try the full language code
    QString qmFileName = QStringLiteral("app_%1").arg(languageCode);
    qDebug() << "Trying full language code translation:" << qmFileName;
    
    bool success = false;
    if (installTranslator(currentAppTranslator, qmFileName)) {
        qDebug() << "Successfully loaded full language code translation";
        success = true;
    } else {
        // Try with just the language part (e.g., "en" from "en_US")
        QString shortCode = languageCode.section('_', 0, 0);
        qmFileName = QStringLiteral("app_%1").arg(shortCode);
        qDebug() << "Trying short language code translation:" << qmFileName;
        
        if (installTranslator(currentAppTranslator, qmFileName)) {
            qDebug() << "Successfully loaded short language code translation";
            success = true;
        }
    }

    if (!success) {
        qDebug() << "Failed to load any translation for" << languageCode;
        // Dump available resources to debug
        qDebug() << "\nAvailable resources:";
        //dumpResDir(":/");
    }

    QLocale::setDefault(QLocale(languageCode));
    ui->retranslateUi(this);
    updateUiTexts();
    
    qDebug() << "=== Language change completed ===\n";
}

void MainWindow::updateUiTexts()
{
    qDebug() << "updateUiTexts called with current locale:" << QLocale().name();
    
    // Use English as source strings for translation
    QString title = tr("Resource and Localization Demo");
    QString message = tr("Welcome to the application!");
    
    qDebug() << "Setting window title to:" << title;
    qDebug() << "Setting message to:" << message;
    
    setWindowTitle(title);
    ui->messageLabel->setText(message);
}
