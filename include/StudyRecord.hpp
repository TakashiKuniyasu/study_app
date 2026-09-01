#pragma once
#include <string>
#include <sstream>

enum class Month{
    January=1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};
class StudyRecord{
private:
    int ID;
    std::string date;
    std::string content;
    int minute;
    bool convertStringToInt(std::string, int&);
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
    bool checkDate(std::string);
    bool checkDateYear(std::stringstream&, int&);
    bool checkDateMonth(std::stringstream&, int&);
    bool checkDateDay(std::stringstream&, int&);
    bool judgeExistDay(int, int, int);
};