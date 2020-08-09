#include "logging.h"

Logging::Logging()
{

}

void Logging::user_log(std::string s){
    std::string *log = new std::string;
    log->append("Пользователь ");
    log->append(s);
    qDebug() << QString::fromStdString(*log);

    std::ofstream fout;
    fout.open("../log.txt", std::ios_base::app);
    if(!fout.is_open()){
        qDebug() << "Файл для записи лога не может быть открыт!";
        return;
    }
    fout << *log << std::endl;
    fout.close();
}

void Logging::hero_log(std::string s){
    std::string *log = new std::string;
    log->append("Герой ");
    log->append(s);
    qDebug() << QString::fromStdString(*log);

    std::ofstream fout;
    fout.open("../log.txt", std::ios_base::app);
    if(!fout.is_open()){
        qDebug() << "Файл для записи лога не может быть открыт!";
        return;
    }
    fout << *log << std::endl;
    fout.close();
}
