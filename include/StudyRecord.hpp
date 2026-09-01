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
    static bool checkDateYear(std::stringstream&, int&);
    static bool checkDateMonth(std::stringstream&, int&);
    static bool checkDateDay(std::stringstream&, int&);
    static bool judgeExistDay(int, int, int);
    static bool convertStringToInt(std::string, int&);
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
    static bool checkDate(const std::string&);
    static bool checkMinute(int minute);
};