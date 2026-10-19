#pragma once
#include <string>
#include <vector>
#include "StudyRecord.hpp"
class CsvManager{
public:
static void saveToFile(const std::string&, 
    const std::vector<StudyRecord>&);
static bool loadFromFile(const std::string& fileName,
    std::vector<StudyRecord>& recorrds);
private:
static bool csvIdCheck(const std::string& ,int& idNum);
static bool csvMinutesCheck(const std::string&, int&);
static bool parseCsvRecord(std::string& id,
                           std::string& content,
                           std::string& date,
                           std::string& minutes,
                           const std::string& line);
};