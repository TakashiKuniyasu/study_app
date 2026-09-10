#pragma once
#include <string>

class CsvManager{
public:
static bool csvIdCheck(const std::string& ,int& idNum);
static bool csvMinutesCheck(const std::string&, int&);
static bool parseCsvRecord(std::string& id,
                           std::string& content,
                           std::string& date,
                           std::string& minutes,
                           const std::string& line);
};