#pragma once
#include <string>
#include <vector>
#include "StudyRecord.hpp"

class StudyManager{
private:
    std::vector<StudyRecord> records;
    std::string fileName;
    int prevID=0;
public:
    StudyManager(const std::string& fileName);
    void addRecord(const std::string&,
                    const std::string&,
                    int);
    void showRecords() const;
    void showTotalMinutes() const;
    void deleteRecord(int);
    void loadFromFile();
    void searchContent(const std::string&);
    void editPrevData(int,
                      const std::string&,
                      const std::string&,
                      int);
    std::size_t getRecordCount() const;
    const StudyRecord* findRecordByID(int id) const;
private:
    void saveToFile() const;
};