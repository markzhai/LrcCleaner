#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtGui"
#include <QTextCodecPlugin>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadText()
{
    if (filename.isEmpty())
        return;
    ui->originText->clearHistory();
    QFile inputFile(filename);
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);

    text = in.readAll();
    inputFile.close();
    ui->originText->setPlainText(text);
    processText();
}

void MainWindow::processText()
{
    int count = 0;

    processedText = text;
    if (ui->halfBracketCheck->isChecked()) {
        int n = processedText.indexOf("(", 0);
        int m = processedText.indexOf(")", 0);
        while (n != -1 && m != -1) {
            if (n == 0 || (processedText.at(n-1) != ']' && processedText.at(n-1) != ' '))
            {
                processedText.remove(n, m-n+1);
                ++ count;
            }
            n = processedText.indexOf("(", n+1);
            m = processedText.indexOf(")", n+1);
        }
    }
    if (ui->angelBracketCheck->isChecked()) {
        int n = processedText.indexOf("<", 0);
        int m = processedText.indexOf(">", 0);
        while (n != -1 && m != -1) {
            if (n == 0 || (processedText.at(n-1) != ']' && processedText.at(n-1) != ' '))
            {
                processedText.remove(n, m-n+1);
                ++ count;
            }
            n = processedText.indexOf("<", n+1);
            m = processedText.indexOf(">", n+1);
        }
    }
    if (ui->bigBracketCheck->isChecked()) {
        int n = processedText.indexOf("{", 0);
        int m = processedText.indexOf("}", 0);
        while (n != -1 && m != -1) {
            if (n == 0 || (processedText.at(n-1) != ']' && processedText.at(n-1) != ' '))
            {
                processedText.remove(n, m-n+1);
                ++ count;
            }
            n = processedText.indexOf("{", n+1);
            m = processedText.indexOf("}", n+1);
        }
    }
    if (ui->squareBracketCheck->isChecked()) {
        int n = processedText.indexOf("[", 0);
        int m = processedText.indexOf("]", 0);
        while (n != -1 && m != -1) {
            if (n == 0 || (processedText.at(n-1) != ']' && processedText.at(n-1) != ' '))
            {
                processedText.remove(n, m-n+1);
                ++ count;
            }
            n = processedText.indexOf("[", n+1);
            m = processedText.indexOf("]", n+1);
        }
    }
    ui->lcdNumber->display(count);
    ui->editedText->setText(processedText);
    return;
}

void MainWindow::on_openButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
                                            tr("supported file (*.lrc *.txt);;All files(*.*)"));
    if (!filename.isNull())
        loadText();
}

void MainWindow::on_saveButton_clicked()
{
    if (ui->editedText->toPlainText().isEmpty())
        return;
    QString outputFileName = filename;
    QFile outputFile(outputFileName);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Cannot open file for writing: "
                  << qPrintable(outputFile.errorString()) << std::endl;
        return;
    }
    QTextStream out(&outputFile);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    QString stri = ui->editedText->toPlainText();
    bom(out);
    out << stri;
    outputFile.close();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    filename = urls.first().toLocalFile();
    if (filename.isEmpty())
        return;
    loadText();
}

void MainWindow::on_halfBracketCheck_clicked()
{
    processText();
}

void MainWindow::on_fullBracketCheck_clicked()
{
    processText();
}

void MainWindow::on_squareBracketCheck_clicked()
{
    processText();
}

void MainWindow::on_heavyBracketCheck_clicked()
{
    processText();
}

void MainWindow::on_bigBracketCheck_clicked()
{
    processText();
}

void MainWindow::on_angelBracketCheck_clicked()
{
    processText();
}
