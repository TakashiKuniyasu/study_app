#pragma once
#include <string>

enum class menu{
    Record =1,
    Watch,
    Delete,
    Search,
    Edit,
    Exit
};

class MainManager{
public:
menu userInput();
void inputStudyRecord(std::string&,
                     std::string&,
                     int&);
int inputID();
static std::string inputEditContent();
};