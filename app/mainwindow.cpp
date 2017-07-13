#include <QFileDialog>
#include <QDebug>
#include <QTime>


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "test_lzma.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( this, SIGNAL(addLog(const QString &)), this->ui->logText, SLOT(appendPlainText(const QString &)));
    connect( this->ui->pushButtonInFile, SIGNAL(clicked()), this, SLOT(setInFile()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::appendLog(const QString &s){
    emit addLog(s);
    return 1;
}

void MainWindow::setInFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "*.xz");
    if (fileName == "") return;

    this->ui->labelFileName->setText(fileName);

    QString inFile  = fileName;
    QString outFile = fileName.section('.',0,-2);

    qDebug() << " inFile:" << inFile;
    qDebug() << "outFile:" << outFile;

    QTime time;

    qDebug () << "Testing LZMA";
    Test_Lzma lzma;
    lzma.info();

    time.start();
    bool ret = lzma.test(inFile,outFile);
    int ms = time.elapsed();

    qDebug () << "ret = " << ret;
    qDebug () << "Time: " << ms << " ms.";
}

