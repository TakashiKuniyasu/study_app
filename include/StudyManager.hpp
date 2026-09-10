#pragma once
#include <string>
#include <vector>
#include <map>
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
    void editPrevData(int,
                      const std::string&,
                      const std::string&,
                      int);
    std::size_t getRecordCount() const;
    const StudyRecord* findRecordByID(int id) const;
    int getTotalMinutes() const;
    std::vector<StudyRecord> searchContent(const std::string&);
    void showResultSearchContent(const std::vector<StudyRecord>&);
    void sortMinutesAsc();
    void sortMinutesDesc();
    std::map<std::string,int> totalSumTimeContents() const;
    int getTotalMinutesInPeriod(const std::string&, const std::string&)const;
    void sortDateDesc();
    void sortDateAsc();
    std::map<std::string,int> sumtimeByContentsInPeriod(const std::string&, const std::string&) const;
private:
    void saveToFile() const;
    static int dateToInt(const std::string&);
    static bool csvIdCheck(const std::string&, int&);
    static bool csvMinutesCheck(const std::string&, int&);
    static bool parseCsvRecord(std::string& id,
                               std::string& content,
                               std::string& date,
                               std::string& minutes,
                               const std::string& line);
};