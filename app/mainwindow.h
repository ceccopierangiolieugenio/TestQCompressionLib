#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int appendLog(const QString &s);

signals:
    void addLog(const QString &text);

public slots:
    void setInFile();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
