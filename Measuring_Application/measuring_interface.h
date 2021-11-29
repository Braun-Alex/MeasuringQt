#ifndef MEASURING_INTERFACE_H
#define MEASURING_INTERFACE_H
#include <QMainWindow>
#include <QRandomGenerator>
#include <QFile>
#include <QFileDialog>
#include <chrono>
using namespace std::chrono;
QT_BEGIN_NAMESPACE
namespace Ui { class Measuring_Interface; }
QT_END_NAMESPACE
class TimeLogger
{
public:
void SetTime(int64_t entered_empty_cycle_time);
void Start();
template<typename Time>
void Stop(const std::string &the_operation,const std::string &the_type,
          int64_t the_count_of_operations);
std::multimap<double,std::tuple<std::string,
std::string,double>> &&GetData();
private:
int64_t the_empty_cycle_time;
time_point<steady_clock,duration<int64_t,
std::ratio<1,1000000000>>> the_begin_point,the_end_point;
std::map<std::string,std::map<std::string,
std::pair<int64_t,double>>> the_database;
std::multimap<double,std::tuple<std::string,std::string,
double>> the_table;
};
class Measuring_Interface:public QMainWindow
{
Q_OBJECT
public:
Measuring_Interface(QWidget *the_widget=nullptr);
~Measuring_Interface();
private slots:
void Check();
void Generate();
void Save();
private:
QString the_choice;
std::array<char,4> the_operations={'+','-','*','/'};
QRandomGenerator the_generator;
QFile the_file;
QFileDialog the_dialog;
std::array<QString,4> the_headers={"Операція","Тип",
                                   "Кількість операцій за ",
                                   "Порівняльна швидкість"};
std::multimap<double,std::tuple<std::string,std::string,
double>> the_result;
Ui::Measuring_Interface *ui;
};
#endif
