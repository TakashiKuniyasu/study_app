#pragma once
#include <string>

class StudyRecord{
private:
    int ID;
    std::string date;
    std::string content;
    int minute;
public:
    StudyRecord(
        int id,
        std::string content,
        std::string date,
        int minutes
    )
        :ID(id),
         content(content),
         date(date),
         minute(minutes){}

    void input(int id);
    void show() const;
    int getMinutes() const;
    int getID() const;
    std::string getDate() const;
    std::string getContent() const;
};