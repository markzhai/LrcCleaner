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

private slots:
    void on_halfBracketCheck_clicked();
    void on_fullBracketCheck_clicked();
    void on_squareBracketCheck_clicked();
    void on_heavyBracketCheck_clicked();
    void on_bigBracketCheck_clicked();
    void on_angelBracketCheck_clicked();
    void on_openButton_clicked();
    void on_saveButton_clicked();

private:
    void loadText();
    void processText();
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    Ui::MainWindow *ui;
    QString filename;
    QString text;
    QString processedText;
};

#endif // MAINWINDOW_H
