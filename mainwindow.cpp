#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QClipboard>
#include <QFile>

#include <QDebug>

#define SIZE 18

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Runline");
    this->setWindowIcon(QIcon(":/images/images/runner.png"));

    ui->up_grid->setSpacing(1);
    ui->down_grid->setSpacing(1);

    if(QLocale::languageToString(QLocale::system().language()) == "Russian") set_ru();
    else set_en();

    for(int i{0}; i < 64; i++){
        for(int j{0}; j < 8; j++){
            paint_place[i][j] = new QPushButton;

            paint_place[i][j]->setMinimumSize(QSize(SIZE, SIZE));
            paint_place[i][j]->setMaximumSize(QSize(SIZE, SIZE));

            paint_place[i][j]->setText("f");

            paint_place[i][j]->setStyleSheet("QPushButton{"
                                             "background-color:white;"
                                             "color:white;"
                                             "border:1px solid #808080;"
                                             "}"
                                             "QPushButton:hover{"
                                             "background-color: #808080;"
                                             "color:#808080;"
                                             "border-color:black;"
                                             "}"
                                             "QPushButton:pressed{"
                                             "background-color:black;"
                                             "color:black;"
                                             "border-color:white;"
                                             "}");

            connect(paint_place[i][j], &QPushButton::clicked, [=](){
                if(paint_place[i][j]->text() == "f"){
                    paint_place[i][j]->setText("t");

                    paint_place[i][j]->setStyleSheet("QPushButton{"
                                                     "background-color:black;"
                                                     "color:black;"
                                                     "border:1px solid #808080;"
                                                     "}"
                                                     "QPushButton:hover{"
                                                     "background-color: #808080;"
                                                     "color:#808080;"
                                                     "border-color:white;"
                                                     "}"
                                                     "QPushButton:pressed{"
                                                     "background-color:white;"
                                                     "color:white;"
                                                     "border-color:black;"
                                                     "}");
                }
                else{
                    paint_place[i][j]->setText("f");

                    paint_place[i][j]->setStyleSheet("QPushButton{"
                                                     "background-color:white;"
                                                     "color:white;"
                                                     "border:1px solid #808080;"
                                                     "}"
                                                     "QPushButton:hover{"
                                                     "background-color: #808080;"
                                                     "color:#808080;"
                                                     "border-color:black;"
                                                     "}"
                                                     "QPushButton:pressed{"
                                                     "background-color:black;"
                                                     "color:black;"
                                                     "border-color:white;"
                                                     "}");
                }
            });

            ui->up_grid->addWidget(paint_place[i][j], j, i);
        }
    }

    for(int i{0}; i < 64; i++){
        for(int j{0}; j < 8; j++){
            paint_place[i + 64][j] = new QPushButton;

            paint_place[i + 64][j]->setMinimumSize(QSize(SIZE, SIZE));
            paint_place[i + 64][j]->setMaximumSize(QSize(SIZE, SIZE));

            paint_place[i + 64][j]->setText("f");

            paint_place[i + 64][j]->setStyleSheet("QPushButton{"
                                             "background-color:white;"
                                             "color:white;"
                                             "border:1px solid #808080;"
                                             "}"
                                             "QPushButton:hover{"
                                             "background-color: #808080;"
                                             "color:#808080;"
                                             "border-color:black;"
                                             "}"
                                             "QPushButton:pressed{"
                                             "background-color:black;"
                                             "color:black;"
                                             "border-color:white;"
                                             "}");

            connect(paint_place[i + 64][j], &QPushButton::clicked, [=](){
                if(paint_place[i + 64][j]->text() == "f"){
                    paint_place[i + 64][j]->setText("t");

                    paint_place[i + 64][j]->setStyleSheet("QPushButton{"
                                                     "background-color:black;"
                                                     "color:black;"
                                                     "border:1px solid #808080;"
                                                     "}"
                                                     "QPushButton:hover{"
                                                     "background-color: #808080;"
                                                     "color:#808080;"
                                                     "border-color:white;"
                                                     "}"
                                                     "QPushButton:pressed{"
                                                     "background-color:white;"
                                                     "color:white;"
                                                     "border-color:black;"
                                                     "}");
                }
                else{
                    paint_place[i + 64][j]->setText("f");

                    paint_place[i + 64][j]->setStyleSheet("QPushButton{"
                                                     "background-color:white;"
                                                     "color:white;"
                                                     "border:1px solid #808080;"
                                                     "}"
                                                     "QPushButton:hover{"
                                                     "background-color: #808080;"
                                                     "color:#808080;"
                                                     "border-color:black;"
                                                     "}"
                                                     "QPushButton:pressed{"
                                                     "background-color:black;"
                                                     "color:black;"
                                                     "border-color:white;"
                                                     "}");
                }
            });

            ui->down_grid->addWidget(paint_place[i + 64][j], j, i);
        }
    }

    connect(ui->save_btn, &QPushButton::clicked, this, &MainWindow::save_paint);
    connect(ui->load_btn, &QPushButton::clicked, this, &MainWindow::load_paint);
    connect(ui->set_file_name_btn, &QPushButton::clicked, this, &MainWindow::get_exit_file);
    connect(ui->clear_btn, &QPushButton::clicked, this, &MainWindow::clear_all);
    connect(ui->fill_btn, &QPushButton::clicked, this, &MainWindow::fill_in);
    connect(ui->copy_btn, &QPushButton::clicked, this, &MainWindow::copy_arr);
    connect(ui->lang_btn, &QPushButton::clicked, this, &MainWindow::change_lang);
    connect(ui->exit_btn, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_exit_file(QString filename){
    ui->lineEdit->setText(filename);
}

void MainWindow::set_ru(){
    ui->save_btn->setText("Сохранить");
    ui->load_btn->setText("Загрузить");
    ui->set_file_name_btn->setText("...");
    ui->clear_btn->setText("Очистить");
    ui->fill_btn->setText("Заполнить");
    ui->copy_btn->setText("Скопировать");
    ui->lang_btn->setText("English");
    ui->exit_btn->setText("Выход");
}

void MainWindow::set_en(){
    ui->save_btn->setText("Save");
    ui->load_btn->setText("Load");
    ui->set_file_name_btn->setText("...");
    ui->clear_btn->setText("Clear");
    ui->fill_btn->setText("Fill in");
    ui->copy_btn->setText("Copy");
    ui->lang_btn->setText("Русский");
    ui->exit_btn->setText("Exit");
}

void MainWindow::save_paint(){
    if(ui->lineEdit->text() == "") this->get_exit_file();
    else if(ui->lineEdit->text().mid(ui->lineEdit->text().length() - 3, 3) != "txt") this->get_exit_file();

    if(ui->lineEdit->text() == "") return;

    QString paint_str = "";
    QString tmp_arr = "";

    for(int i{0}; i < 128; i++){
        QString tmp_str = "";

        for(int j{7}; j >= 0; j--){
            if(paint_place[i][j]->text() == "t") tmp_str += "1";
            else tmp_str += "0";
        }

        paint_str += tmp_str + "   ";

        tmp_str = QString::number(tmp_str.toInt(NULL, 2), 16);

        if(tmp_str.length() == 1) tmp_str = "0x0" + tmp_str;
        else tmp_str = "0x" + tmp_str;

        paint_str += tmp_str + "\n";

        tmp_arr += tmp_str;

        if(i != 127){
            tmp_arr += ", ";
            if(i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111) tmp_arr += "\n";
        }
    }

    QFile exit_file(ui->lineEdit->text());

    exit_file.open(QIODevice::ReadWrite | QIODevice::Truncate);

    exit_file.write(paint_str.toUtf8());
    exit_file.write("\n{");
    exit_file.write(tmp_arr.toUtf8());
    exit_file.write("}");



    exit_file.close();
}

void MainWindow::load_paint(){
    if(ui->lang_btn->text() == "English"){
        ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "", "(*.txt)"));
        if(ui->lineEdit->text() == "") ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "", "(*.txt)"));
        else if(ui->lineEdit->text().mid(ui->lineEdit->text().length() - 3, 3) != "txt") ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Выберите файл", "", "(*.txt)"));
    }
    else{
        ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Choose file", "", "(*.txt)"));
        if(ui->lineEdit->text() == "") ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Choose file", "", "(*.txt)"));
        else if(ui->lineEdit->text().mid(ui->lineEdit->text().length() - 3, 3) != "txt") ui->lineEdit->setText(QFileDialog::getOpenFileName(0, "Choose file", "", "(*.txt)"));
    }

    if(ui->lineEdit->text() == "") return;

    QFile exit_file(ui->lineEdit->text());

    exit_file.open(QIODevice::ReadOnly);

    clear_all();

    QString tmp = exit_file.readLine();

    if(tmp.at(0) == '{') {

    }
    else {
        for(int i{0}; i < 128; i++){
            for(int j{7}; j >= 0; j--){
                if(tmp.at(1) == 'x') tmp = tmp.mid(5, 8);

                if(tmp.at(7 - j) == '1') paint_place[i][j]->clicked();
            }

            tmp = exit_file.readLine();
        }
    }

    exit_file.close();
}

void MainWindow::get_exit_file(){
    if(ui->lang_btn->text() == "English"){
        set_exit_file(QFileDialog::getSaveFileName(this, "Выберите файл", QString(), "(*.txt)"));
    }
    else{
        set_exit_file(QFileDialog::getSaveFileName(this, "Choose file", QString(), "(*.txt)"));
    }
}

void MainWindow::clear_all(){
    for(int i{0}; i < 128; i++){
        for(int j{0}; j < 8; j++){
            if(paint_place[i][j]->text() == "t"){
                paint_place[i][j]->setText("f");

                paint_place[i][j]->setStyleSheet("QPushButton{"
                                                 "background-color:white;"
                                                 "color:white;"
                                                 "border:1px solid #808080;"
                                                 "}"
                                                 "QPushButton:hover{"
                                                 "background-color: #808080;"
                                                 "color:#808080;"
                                                 "border-color:black;"
                                                 "}"
                                                 "QPushButton:pressed{"
                                                 "background-color:black;"
                                                 "color:black;"
                                                 "border-color:white;"
                                                 "}");
            }
        }
    }
}

void MainWindow::fill_in(){
    for(int i{0}; i < 128; i++){
        for(int j{0}; j < 8; j++){
            if(paint_place[i][j]->text() == "f"){
                paint_place[i][j]->setText("t");

                paint_place[i][j]->setStyleSheet("QPushButton{"
                                                 "background-color:black;"
                                                 "color:black;"
                                                 "border:1px solid #808080;"
                                                 "}"
                                                 "QPushButton:hover{"
                                                 "background-color: #808080;"
                                                 "color:#808080;"
                                                 "border-color:white;"
                                                 "}"
                                                 "QPushButton:pressed{"
                                                 "background-color:white;"
                                                 "color:white;"
                                                 "border-color:black;"
                                                 "}");
            }
        }
    }
}

void MainWindow::copy_arr(){
    QString tmp_arr = "";

    for(int i{0}; i < 128; i++){
        QString tmp_str = "";

        for(int j{7}; j >= 0; j--){
            if(paint_place[i][j]->text() == "t") tmp_str += "1";
            else tmp_str += "0";
        }

        tmp_str = QString::number(tmp_str.toInt(NULL, 2), 16);

        if(tmp_str.length() == 1) tmp_str = "0x0" + tmp_str;
        else tmp_str = "0x" + tmp_str;

        tmp_arr += tmp_str;

        if(i != 127){
            tmp_arr += ", ";
            if(i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111) tmp_arr += "\n";
        }
    }

    QClipboard *data = QApplication::clipboard();

    data->setText("{" + tmp_arr + "}");
}

void MainWindow::change_lang(){
    if(ui->lang_btn->text() == "English") set_en();
    else set_ru();
}
