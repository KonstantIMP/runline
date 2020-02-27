#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#define SIZE 15

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Runline");
    this->setWindowIcon(QIcon(":/images/images/runner.png"));

    ui->up_grid->setSpacing(0);
    ui->down_grid->setSpacing(0);

    if(QLocale::languageToString(QLocale::system().language()) == "Russian"){
        set_ru();
    }
    else{
        set_en();
    }

    for(int i{0}; i < 64; i++){
        for(int j{0}; j < 8; j++){
            paint_place[i][j] = new QPushButton;

            paint_place[i][j]->setMaximumSize(QSize(SIZE, SIZE));

            ui->up_grid->addWidget(paint_place[i][j], j, i);
        }
    }

    for(int i{0}; i < 64; i++){
        for(int j{0}; j < 8; j++){
            paint_place[i + 64][j] = new QPushButton;

            paint_place[i + 64][j]->setMaximumSize(QSize(SIZE, SIZE));

            ui->down_grid->addWidget(paint_place[i + 64][j], j, i);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::set_en(){}
