#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "styles.h"

#include <QFileDialog>
#include <QClipboard>
#include <QFile>

#include <fstream>

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

    ui->up_clear->setSpacing(1);
    ui->down_clear->setSpacing(1);

    clear_up_place = new OrientablePushButton();
    clear_up_place->setOrientation(OrientablePushButton::VerticalBottomToTop);
    clear_up_place->setMinimumSize(SIZE * 2, SIZE * 10);
    clear_up_place->setMaximumSize(SIZE * 2, SIZE * 10);
    clear_up_place->setStyleSheet("font-size: 12px;");
    ui->horizontalLayout_6->addWidget(clear_up_place, 0);
    connect(clear_up_place, &QPushButton::clicked, this, [=](){
        for(int i{0}; i < 64; i++){
            for(int j{0}; j < 8; j++){
                paint_place[i][j]->setText("f");

                paint_place[i][j]->setStyleSheet(white_btn_style);
            }
        }
    });

    clear_down_place = new OrientablePushButton();
    clear_down_place->setOrientation(OrientablePushButton::VerticalBottomToTop);
    clear_down_place->setMinimumSize(SIZE * 2, SIZE * 10);
    clear_down_place->setMaximumSize(SIZE * 2, SIZE * 10);
    clear_down_place->setStyleSheet("font-size: 12px;");
    ui->horizontalLayout_8->addWidget(clear_down_place, 0);
    connect(clear_down_place, &QPushButton::clicked, this, [=](){
        for(int i{0}; i < 64; i++){
            for(int j{0}; j < 8; j++){
                paint_place[i + 64][j]->setText("f");

                paint_place[i + 64][j]->setStyleSheet(white_btn_style);
            }
        }
    });

    if(QLocale::languageToString(QLocale::system().language()) == "Russian") set_ru();
    else set_en();

    for(int i{0}; i < 64; i++){
        for(int j{0}; j < 8; j++){
            paint_place[i][j] = new QPushButton;

            paint_place[i][j]->setMinimumSize(QSize(SIZE, SIZE));
            paint_place[i][j]->setMaximumSize(QSize(SIZE, SIZE));

            paint_place[i][j]->setText("f");

            paint_place[i][j]->setStyleSheet(white_btn_style);

            connect(paint_place[i][j], &QPushButton::clicked, [=](){
                if(paint_place[i][j]->text() == "f"){
                    paint_place[i][j]->setText("t");

                    paint_place[i][j]->setStyleSheet(black_btn_style);
                }
                else{
                    paint_place[i][j]->setText("f");

                    paint_place[i][j]->setStyleSheet(white_btn_style);
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

            paint_place[i + 64][j]->setStyleSheet(white_btn_style);

            connect(paint_place[i + 64][j], &QPushButton::clicked, [=](){
                if(paint_place[i + 64][j]->text() == "f"){
                    paint_place[i + 64][j]->setText("t");

                    paint_place[i + 64][j]->setStyleSheet(black_btn_style);
                }
                else{
                    paint_place[i + 64][j]->setText("f");

                    paint_place[i + 64][j]->setStyleSheet(white_btn_style);
                }
            });

            ui->down_grid->addWidget(paint_place[i + 64][j], j, i);
        }
    }

    for(int i{0}; i < 64; i++){
        clear_column[i] = new QPushButton;

        clear_column[i]->setMinimumSize(SIZE, SIZE);
        clear_column[i]->setMaximumSize(SIZE, SIZE);

        clear_column[i]->setText(QString::number(i + 1, 10));

        clear_column[i]->setStyleSheet("font-size: 8px;");

        connect(clear_column[i], &QPushButton::clicked, this, [=](){
            QString column = "";
            for(int j{0}; j < 8; j++){
                column += paint_place[i][j]->text();
            }
            if(column == "ffffffff"){
                for(int j{0}; j < 8; j++){
                    paint_place[i][j]->setText("t");

                    paint_place[i][j]->setStyleSheet(black_btn_style);
                }
            }
            else{
                for(int j{0}; j < 8; j++){
                    paint_place[i][j]->setText("f");

                    paint_place[i][j]->setStyleSheet(white_btn_style);
                }
            }
        });

        ui->up_clear->addWidget(clear_column[i], i);
    }

    for(int i{0}; i < 64; i++){
        clear_column[i + 64] = new QPushButton;

        clear_column[i + 64]->setMinimumSize(SIZE, SIZE);
        clear_column[i + 64]->setMaximumSize(SIZE, SIZE);

        clear_column[i + 64]->setText(QString::number(i + 65, 10));

        clear_column[i + 64]->setStyleSheet("font-size: 8px;");

        connect(clear_column[i + 64], &QPushButton::clicked, this, [=](){
            QString column = "";
            for(int j{0}; j < 8; j++){
                column += paint_place[i + 64][j]->text();
            }
            if(column == "ffffffff"){
                for(int j{0}; j < 8; j++){
                    paint_place[i + 64][j]->setText("t");

                    paint_place[i + 64][j]->setStyleSheet(black_btn_style);
                }
            }
            else{
                for(int j{0}; j < 8; j++){
                    paint_place[i + 64][j]->setText("f");

                    paint_place[i + 64][j]->setStyleSheet(white_btn_style);
                }
            }
        });

        ui->down_clear->addWidget(clear_column[i + 64], i);
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
    clear_up_place->setText("Очистить верхнюю часть");
    clear_down_place->setText("Очистить нижнюю часть");
    ui->save_btn->setText("Сохранить");
    ui->load_btn->setText("Загрузить");
    ui->set_file_name_btn->setText("...");
    ui->clear_btn->setText("Очистить");
    ui->fill_btn->setText("Заполнить");
    ui->copy_btn->setText("Скопировать");
    ui->lang_btn->setText("English");
    ui->about_btn->setText("Справка");
    ui->exit_btn->setText("Выход");
}

void MainWindow::set_en(){
    clear_up_place->setText("Clean the top");
    clear_down_place->setText("Clear the bottom");
    ui->save_btn->setText("Save");
    ui->load_btn->setText("Load");
    ui->set_file_name_btn->setText("...");
    ui->clear_btn->setText("Clean");
    ui->fill_btn->setText("Fill in");
    ui->copy_btn->setText("Copy");
    ui->lang_btn->setText("Русский");
    ui->about_btn->setText("About");
    ui->exit_btn->setText("Exit");
}

void MainWindow::save_paint(){
    if(ui->lineEdit->text() == "") this->get_exit_file();
    else if(ui->lineEdit->text().mid(ui->lineEdit->text().length() - 3, 3) != "txt") this->get_exit_file();

    if(ui->lineEdit->text() == "") return;

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
            if(i == 15 || i == 31 || i == 47 || i == 63 || i == 79 || i == 95 || i == 111) {
                tmp_arr += '\n';
                tmp_arr += ' ';
            }
        }
    }

    QFile exit_file(ui->lineEdit->text());

    exit_file.open(QIODevice::ReadWrite | QIODevice::Truncate);

    exit_file.write("{");
    exit_file.write(tmp_arr.toUtf8());
    exit_file.write("};");

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

    while(1){
        if(tmp.at(0) == '{' || tmp.at(0) == '0' || tmp.at(0) == '1') break;
        tmp = exit_file.readLine();
    }
    if(tmp.at(0) == '{') {
        int hex_char = 0;

        QString tmp_hex;

        while(hex_char != 128){
            for(int i{0}; i < tmp.length(); i++){
                if(tmp.at(i) == 'x'){
                    tmp_hex = QString(tmp.at(i + 1)) + QString(tmp.at(i + 2));
                    tmp_hex = QString::number(tmp_hex.toInt(NULL, 16), 2);

                    while(tmp_hex.length() != 8) tmp_hex = "0" + tmp_hex;

                    for(int j{7}; j >= 0; j--){
                        if(tmp_hex.at(7 - j) == '1') paint_place[hex_char][j]->clicked();
                    }

                    hex_char++;
                }
            }

            tmp = exit_file.readLine();
        }
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

                paint_place[i][j]->setStyleSheet(white_btn_style);
            }
        }
    }
}

void MainWindow::fill_in(){
    for(int i{0}; i < 128; i++){
        for(int j{0}; j < 8; j++){
            if(paint_place[i][j]->text() == "f"){
                paint_place[i][j]->setText("t");

                paint_place[i][j]->setStyleSheet(black_btn_style);
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

    data->setText("{" + tmp_arr + "};");
}

void MainWindow::change_lang(){
    if(ui->lang_btn->text() == "English") set_en();
    else set_ru();
}
