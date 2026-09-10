#pragma once
#include <string>
#include <map>

enum class menu{
    Record =1,
    Watch,
    Delete,
    Search,
    Edit,
    SortByDate,
    SortByMinutes,
    SumtimeByContents,
    SumtimeByDate,
    SumtimeByContentsInPeriod,
    Exit
};
enum class ascdesc{
    desc=0,
    asc
};
class MainManager{
public:
menu userInput();
void inputStudyRecord(std::string&,
                     std::string&,
                     int&);
int inputID(const std::string&);
std::string inputSearchContent();
enum ascdesc inputSortMethod();
void showTotalMinutesByContents(const std::map<std::string,int>&);
void inputSumtimeByDateStartAndEnd(std::string&, std::string&);
void outputSumtimeByDateStartAndEnd(int);
void inputSortByDate();
void outputSumtimeByContentsInPeriod(const std::map<std::string,int>&);
};