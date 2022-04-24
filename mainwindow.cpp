#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
    ui->tableViewUP->setModel(L.Afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSeConnecter_clicked()
{
    QString role;
    QString UserName = ui->lineEdit_Username->text();
    QString Password = ui->lineEdit_Password->text();
    QSqlQuery querry;
    querry.prepare("SELECT TYPE_USER FROM USERS WHERE USERNAME = '"+UserName+"' AND PASSWORD_USER = '"+Password+"'");
    //querry.bindValue(":username", UserName);
    //querry.bindValue(":password", Password);
    if (querry.exec()){
            int counter = 0;
            while (querry.next()){
                counter++;
                role = querry.value(0).toString();
            }
            if (counter<1)
                QMessageBox::critical(this, tr("Error::"), "Compte n'existe pas");


            if (counter==1){
                QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                          QObject::tr("Connecté"),
                                          QMessageBox::Ok
                                          );
            if (role=="ADMIN"){
                ui->stackedWidget->setCurrentIndex(1);
            }else if (role=="FINANCE"){

            }

            }
            if (counter >1)
                QMessageBox::critical(this, tr("Error::"), "Duplicate");

        }else{
            QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
        }
}

void MainWindow::on_pushButton_ENR_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_14_clicked()
{
    QString username = ui->lineEdit_Username_UP->text();
    QString mdp = ui->lineEdit_MDP_UP->text();
    QString email = ui->lineEdit_email_UP->text();
    QString role = ui->lineEdit_role_up->text();
    QSqlQuery querry;
    querry.prepare("insert into USERS values (USERS_SEQ.nextval, '"+role+"', '"+username+"', '"+mdp+"', '"+email+"')");
    if (querry.exec()){
        ui->tableViewUP->setModel(L.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                  QObject::tr("Compte enregistré"),
                                  QMessageBox::Ok
                                  );
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }
}

void MainWindow::on_pushButton_supp_up_clicked()
{
    QString ID = ui->lineEdit_Username_UP_sup->text();
    QSqlQuery querry;
    querry.prepare("delete from users where id_user = "+ID+" ");
    if (querry.exec()){
        ui->tableViewUP->setModel(L.Afficher());
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                  QObject::tr("Compte supprimé"),
                                  QMessageBox::Ok
                                  );
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }
}

void MainWindow::on_pushButtonRetour_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonRetourMPrincipale_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEdit_Username->setText("");
    ui->lineEdit_Password->setText("");
    ui->lineEdit_Username_mdp_oublie->setText("");
}

void MainWindow::on_pushButtonmdpoubliee_clicked()
{
    QString val = ui->lineEdit_Username_mdp_oublie->text();
    QString comboBox = ui->comboBox->currentText();
    QString password, email, username;
    QSqlQuery querry;
    if (comboBox == "Username")
    querry.prepare("select PASSWORD_USER, username, email_user from users where username = '"+val+"' ");
    if (comboBox == "Email")
    querry.prepare("select PASSWORD_USER, username, email_user from users where email_user = '"+val+"' ");
    if (querry.exec()){
        int counter = 0;
        while (querry.next()){
            counter++;
            password  = querry.value(0).toString();
            username = querry.value(1).toString();
            email =  querry.value(2).toString();
        }
        if (counter<1)
            QMessageBox::critical(this, tr("Error::"), "Compte n'existe pas");

        if (counter==1)
        {
            QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                      QObject::tr("Le compte existe"),
                                      QMessageBox::Ok
                                      );
            Mailing* mailing = new Mailing("testkhouini@gmail.com", "Trunks@2001", "smtp.gmail.com", 465);
            QString Subject = "Récupération mot de passe";
            QString Message = "Mr " + username + " Votre mot de passe est " + password ;
            mailing->sendMail("testkhouini@gmail.com", email, Subject ,Message);
            QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                      QObject::tr("Mail enovoyé"),
                                      QMessageBox::Ok
                                      );
        }
        if (counter >1)
            QMessageBox::critical(this, tr("Error::"), "Duplicate");
    }else{
        QMessageBox::critical(this, tr("Error::"), querry.lastError().text());
    }

}
