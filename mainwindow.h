#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include "connection.h"
#include "QSqlQuery"
#include <QSqlError>
#include "login.h"
#include "mailing.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSeConnecter_clicked();

    void on_pushButton_ENR_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_supp_up_clicked();

    void on_pushButtonRetour_clicked();

    void on_pushButtonRetourMPrincipale_clicked();

    void on_pushButtonmdpoubliee_clicked();

private:
    Ui::MainWindow *ui;
    login L;
};
#endif // MAINWINDOW_H
