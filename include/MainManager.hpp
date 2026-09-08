#pragma once
#include <string>

enum class menu{
    Record =1,
    Watch,
    Delete,
    Search,
    Edit,
    Sort,
    SumtimeByContents,
    SumtimeByDate,
    Exit
};

class MainManager{
public:
menu userInput();
void inputStudyRecord(std::string&,
                     std::string&,
                     int&);
int inputID(const std::string&);
std::string inputSearchContent();
int inputSortMinutesMethod();
void showTotalMinutesByContents(const std::map<std::string,int>&);
void inputSortByDateStartAndEnd(std::string&, std::string&);
void outputSortByDateStartAndEnd(int);
};