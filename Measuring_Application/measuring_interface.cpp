#include "measuring_interface.h"
#include "./ui_measuring_interface.h"
int64_t COUNT=100000;
const QString RED_COLOR="color: rgb(255,0,0);",
              GREEN_COLOR="color: rgb(0,255,0);";
#define MEASURE_INT(entered_operation,max_number,time_value)         \
the_logger.Start();                                                  \
for (int i=0; i<COUNT; ++i)                                          \
{                                                                    \
int the_value;                                                       \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
the_value=the_generator.bounded(1,max_number)entered_operation       \
the_generator.bounded(1,max_number);                                 \
}                                                                    \
the_logger.Stop<time_value>(#entered_operation,"int",COUNT*10)
#define MEASURE_TYPE(entered_operation,entered_type,max_number,time_value)   \
the_logger.Start();                                                          \
for (int i=0; i<COUNT; ++i)                                                  \
{                                                                            \
entered_type the_value;                                                      \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
the_value=entered_type(the_generator.bounded(1,max_number))entered_operation \
entered_type(the_generator.bounded(1,max_number));                           \
}                                                                            \
the_logger.Stop<time_value>(#entered_operation,#entered_type,COUNT*10)
#define APPLY_CHOICE(time_value)                                    \
the_logger.SetTime(duration_cast<time_value>(the_end-               \
                                               the_begin).count()); \
MEASURE_INT(+,255,time_value);                                      \
MEASURE_INT(-,255,time_value);                                      \
MEASURE_INT(*,255,time_value);                                      \
MEASURE_INT(/,255,time_value);                                      \
MEASURE_TYPE(+,double,255,time_value);                              \
MEASURE_TYPE(-,double,255,time_value);                              \
MEASURE_TYPE(*,double,255,time_value);                              \
MEASURE_TYPE(/,double,255,time_value);                              \
MEASURE_TYPE(+,char,255,time_value);                                \
MEASURE_TYPE(-,char,255,time_value);                                \
MEASURE_TYPE(*,char,255,time_value);                                \
MEASURE_TYPE(/,char,255,time_value);                                \
MEASURE_TYPE(+,long,255,time_value);                                \
MEASURE_TYPE(-,long,255,time_value);                                \
MEASURE_TYPE(*,long,255,time_value);                                \
MEASURE_TYPE(/,long,255,time_value);                                \
MEASURE_TYPE(+,float,255,time_value);                               \
MEASURE_TYPE(-,float,255,time_value);                               \
MEASURE_TYPE(*,float,255,time_value);                               \
MEASURE_TYPE(/,float,255,time_value);
Measuring_Interface::Measuring_Interface(
        QWidget *the_widget):QMainWindow(the_widget),
        ui(new Ui::Measuring_Interface)
{
    ui->setupUi(this);
    ui->Save->setDisabled(true);
}
void TimeLogger::SetTime(
int64_t entered_empty_cycle_time)
{
the_empty_cycle_time=entered_empty_cycle_time;
}
void TimeLogger::Start()
{
the_begin_point=steady_clock::now();
}
template<typename Time>
void TimeLogger::Stop(const std::string &the_operation,
                            const std::string &the_type,
                            int64_t the_count_of_iterations)
{
the_end_point=steady_clock::now();
int64_t the_time=duration_cast<Time>(
the_end_point-the_begin_point).count()-the_empty_cycle_time;
double speed=double(the_count_of_iterations)/double(the_time);
the_database[the_operation][the_type]=
std::make_pair(the_count_of_iterations,speed);
}
std::multimap<double,std::tuple<std::string,std::string,
double>> &&TimeLogger::GetData()
{
for (const auto &[the_operation,the_type]:the_database)
for (const auto &[the_key,the_values]:the_type)
the_table.insert(
{the_values.second,{the_operation,the_key,the_values.second}});
double the_factor=double(100)/the_table.rbegin()->first;
decltype(the_table) the_updated_table;
for (auto &[the_speed,the_data]:the_table)
    the_updated_table.insert({the_speed*the_factor,std::move(the_data)});
the_table=std::move(the_updated_table);
return std::move(the_table);
}
void Measuring_Interface::Check()
{
if (ui->Count->text().toInt()<10000)
    ui->Count->setText(
    QString::fromStdString(std::to_string(10000)));
}
void Measuring_Interface::Generate()
{
    COUNT=ui->Count->text().toInt();
    auto the_begin=steady_clock::now();
    for (int i=0; i<COUNT; ++i) {}
    auto the_end=steady_clock::now();
    TimeLogger the_logger;
    if (ui->Choice->currentText()=="Milliseconds")
    {
        APPLY_CHOICE(milliseconds);
        the_choice="мілісекунду";
    }
    else if (ui->Choice->currentText()=="Microseconds")
    {
        APPLY_CHOICE(microseconds);
        the_choice="мікросекунду";
    }
    else
    {
        APPLY_CHOICE(nanoseconds);
        the_choice="наносекунду";
    }
    the_result=std::move(the_logger.GetData());
    ui->Save->setDisabled(false);
    ui->Generate->setDisabled(true);
    ui->Status->setStyleSheet(GREEN_COLOR);
    ui->Status->setText("Дані згенеровано!");
}
void Measuring_Interface::Save()
{
    QString the_path=the_dialog.getSaveFileUrl(nullptr,QString(),
                                               QUrl(),"html",
                                               nullptr,
                                               QFileDialog::Options(),
                                               QStringList()).path();
    if (the_path.isEmpty()) return;
    the_path+=".html";
    the_path.erase(the_path.begin(),std::next(the_path.begin()));
    the_file.setFileName(the_path);
    the_file.open(QIODeviceBase::WriteOnly);
    the_file.write("<!DOCTYPE HTML>\n"
                   "<html>\n"
                   "<link rel=\"stylesheet\" href=\"Table.css\">\n"
                   "<body>\n"
                   "<table>\n");
    the_file.write("<tr>\n");
    the_headers[2]+=the_choice;
    for (const auto &the_header:the_headers)
    {
    the_file.write(QString("<th>"+the_header+"</th>\n").toUtf8());
    }
    the_file.write("</tr>\n");
    for (auto the_iterator=the_result.rbegin();
         the_iterator!=the_result.rend(); ++the_iterator)
    {
    the_file.write("<tr>\n");
    the_file.write(QString("<td>"+
    QString::fromStdString(std::get<0>(the_iterator->second))+"</td>\n<td>"+
    QString::fromStdString(std::get<1>(the_iterator->second))+"</td>\n<td>"+
    QString::fromStdString(std::to_string(
    std::get<2>(the_iterator->second)))+"</td>\n<td>"+
    QString::fromStdString(std::to_string(the_iterator->first))+
                           "%</td>\n").toUtf8());
    the_file.write("</tr>\n");
    }
    the_file.write("</table>\n"
                   "</body>\n"
                   "</html>");
    the_headers[2].erase(
                the_headers[2].constBegin()+22,
                 the_headers[2].constEnd());
    the_file.close();
    ui->Save->setDisabled(true);
    ui->Generate->setDisabled(false);
    ui->Status->setStyleSheet(GREEN_COLOR);
    ui->Status->setText("Дані збережені до "+the_path+"!");
}
Measuring_Interface::~Measuring_Interface()
{
    delete ui;
}

