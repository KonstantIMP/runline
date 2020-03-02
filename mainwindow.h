#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton *paint_place[128][8];

    void set_exit_file(QString);

    void set_ru();
    void set_en();

private slots:
    void save_paint();
    void load_paint();
    void get_exit_file();
    void clear_all();
    void fill_in();
    void copy_arr();
    void change_lang();
};
#endif // MAINWINDOW_H
