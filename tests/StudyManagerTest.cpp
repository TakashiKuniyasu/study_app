#include <iostream>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "StudyManager.hpp"

class StudyManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::filesystem::remove("test_record.csv");
    }

    void TearDown() override
    {
        std::filesystem::remove("test_record.csv");
    }
};
TEST_F(StudyManagerTest, AddRecord){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60);

    EXPECT_EQ(manager.getRecordCount(), 1);

    manager.addRecord("Docker", "2026/8/29", 80);
 
    EXPECT_EQ(manager.getRecordCount(), 2);
}
TEST_F(StudyManagerTest, DeleteRecord){
    StudyManager manager("test_record.csv");

    manager.addRecord("C++", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/29", 80);

    manager.deleteRecord(2);
    EXPECT_EQ(manager.getRecordCount(), 1);
    EXPECT_NE(manager.findRecordByID(1), nullptr);
    EXPECT_EQ(manager.findRecordByID(2), nullptr);
}
TEST_F(StudyManagerTest, EditRecord){
    StudyManager manager("test_record.csv");

    manager.addRecord("C++", "2026/8/28", 60);
    manager.editPrevData(1, "CMake", "2026/8/31", 75);
    const StudyRecord* record =
        manager.findRecordByID(1);
    
    ASSERT_NE(record, nullptr);
    EXPECT_EQ(record->getID(), 1);
    EXPECT_EQ(record->getContent(), "CMake");
    EXPECT_EQ(record->getDate(), "2026/8/31");
    EXPECT_EQ(record->getMinutes(), 75);
}
TEST_F(StudyManagerTest, SaveAndLoadRecord){
    StudyManager saveManager("test_record.csv");
    saveManager.addRecord("C++","2026/8/30",90);

    StudyManager loadManager("test_record.csv");
    loadManager.loadFromFile();
    EXPECT_EQ(loadManager.getRecordCount(), 1);

    const StudyRecord* loadrecord =
        loadManager.findRecordByID(1);
    
    ASSERT_NE(loadrecord, nullptr);
    EXPECT_EQ(loadrecord->getID(), 1);
    EXPECT_EQ(loadrecord->getContent(), "C++");
    EXPECT_EQ(loadrecord->getDate(), "2026/8/30");
    EXPECT_EQ(loadrecord->getMinutes(), 90);
}
TEST_F(StudyManagerTest, DeleteInvalidId){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60);

    manager.deleteRecord(2);
    EXPECT_EQ(manager.getRecordCount(), 1);
}
TEST_F(StudyManagerTest, EditInvalidId){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60); 

    manager.editPrevData(2, "C++基礎", "2026/8/31", 90);

    const StudyRecord* editTestRecord =
        manager.findRecordByID(1);
    
    ASSERT_NE(editTestRecord, nullptr);
    EXPECT_EQ(editTestRecord->getID(), 1);
    EXPECT_EQ(editTestRecord->getContent(), "C++");
    EXPECT_EQ(editTestRecord->getDate(), "2026/8/28");
    EXPECT_EQ(editTestRecord->getMinutes(), 60);
    
}
TEST_F(StudyManagerTest, LoadTwice){
    StudyManager saveManager("test_record.csv");
    saveManager.addRecord("C++", "2026/8/28", 60); 

    StudyManager manager("test_record.csv");
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(), 1);
   manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(), 1);
    auto editTestRecord =
        manager.findRecordByID(1);
    ASSERT_NE(editTestRecord, nullptr);
    EXPECT_EQ(editTestRecord->getID(), 1);
    EXPECT_EQ(editTestRecord->getContent(), "C++");
    EXPECT_EQ(editTestRecord->getDate(), "2026/8/28");
    EXPECT_EQ(editTestRecord->getMinutes(), 60);
}
TEST_F(StudyManagerTest, TotalMinutes){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60); 
    manager.addRecord("Docker", "2026/8/29", 90);

    int total = manager.getTotalMinutes();
    EXPECT_EQ(total, 150);
}
TEST_F(StudyManagerTest, SearchContent){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++基礎", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/29", 80);
    manager.addRecord("C++応用", "2026/8/30", 90);

    auto result = manager.searchContent("C++");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getContent(), "C++基礎");   
    EXPECT_EQ(result[1].getContent(), "C++応用");
}
TEST_F(StudyManagerTest, SearchContentNotFound){
    StudyManager manager("test_record.csv");

    manager.addRecord("C++基礎", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/29", 80);

    auto result = manager.searchContent("Python");
    EXPECT_TRUE(result.empty());
}
TEST_F(StudyManagerTest, LoadInvalidId){
    {
        std::ofstream file("test_record.csv");
        file << "abc,C++,2026/8/31,60\n";
    }
    StudyManager manager("test_record.csv");
    EXPECT_NO_THROW(manager.loadFromFile());
    EXPECT_EQ(manager.getRecordCount(), 0);

    {
        std::ofstream file("test_record.csv");
        file << "1abc,C++,2026/8/31,60\n";
    }
    EXPECT_NO_THROW(manager.loadFromFile());
    EXPECT_EQ(manager.getRecordCount(), 0);
}
TEST_F(StudyManagerTest,InvalidMinutesTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/8/31,abc\n";
    }
    StudyManager manager("test_record.csv");
    EXPECT_NO_THROW(manager.loadFromFile());
    EXPECT_EQ(manager.getRecordCount(), 0);
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/8/31,60abc\n";
    }
    EXPECT_NO_THROW(manager.loadFromFile());
    EXPECT_EQ(manager.getRecordCount(), 0);
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/8/31,-10\n";
    }
    EXPECT_NO_THROW(manager.loadFromFile());
    EXPECT_EQ(manager.getRecordCount(), 0);
}
TEST_F(StudyManagerTest,InvalidRecordDoesNotAffectNextId){
    {
        std::ofstream file("test_record.csv");
        file << "100,C++,2026/8/31,abc\n";
    }
    StudyManager manager("test_record.csv");
    EXPECT_NO_THROW(manager.loadFromFile());

    manager.addRecord("Docker", "2026/9/1", 60);
    EXPECT_NE(manager.findRecordByID(1), nullptr);
}
TEST_F(StudyManagerTest, InvalidDateTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,abc,60\n";
    }
    StudyManager manager("test_record.csv");
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(), 0);
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/2/30,60\n";
    }
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(), 0);
}
TEST_F(StudyManagerTest, LoadSkipsInvalidRecord){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/8/30,60\n";
        file << "2,Docker,abc,90\n";
        file << "3,CMake,2026/9/3,90\n";
    }
    StudyManager manager("test_record.csv");
    manager.loadFromFile();

    EXPECT_EQ(manager.getRecordCount(),2);
    EXPECT_NE(manager.findRecordByID(1),nullptr);
    EXPECT_EQ(manager.findRecordByID(2),nullptr);
    EXPECT_NE(manager.findRecordByID(3),nullptr);
}
TEST_F(StudyManagerTest, LoadMissingColumn){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/8/30\n";
    }
    StudyManager manager("test_record.csv");
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(),0);
}
TEST_F(StudyManagerTest, LoadExtraColumn){
    {
        std::ofstream file("test_record.csv");
        file << "2,Docker,2026/8/31,90,abc";
    }
    StudyManager manager("test_record.csv");
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(),0);
}
TEST_F(StudyManagerTest, LoadExtraEmptyColumn){
    {
        std::ofstream file("test_record.csv");
        file << "2,Docker,2026/8/31,90,";
    }
    StudyManager manager("test_record.csv");
    manager.loadFromFile();
    EXPECT_EQ(manager.getRecordCount(),0);   
}
TEST_F(StudyManagerTest, SortMinutesDescTest){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++基礎", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/31", 120);
    manager.addRecord("CMake", "2026/9/1", 80);

    manager.sortMinutesDesc();
    std::string id;
    std::string content;
    std::string date;
    std::string minutes;
    std::ifstream file("test_record.csv");

    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n'); 
    EXPECT_EQ(id,"2");
    EXPECT_EQ(content,"Docker");
    EXPECT_EQ(date,"2026/8/31");
    EXPECT_EQ(minutes,"120");
    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n');
    EXPECT_EQ(id,"3");
    EXPECT_EQ(content,"CMake");
    EXPECT_EQ(date,"2026/9/1");
    EXPECT_EQ(minutes,"80");
    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n');
    EXPECT_EQ(id,"1");
    EXPECT_EQ(content,"C++基礎");
    EXPECT_EQ(date,"2026/8/28");
    EXPECT_EQ(minutes,"60");
}
TEST_F(StudyManagerTest, SortMinutesAscTest){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++基礎", "2026/8/28", 80);
    manager.addRecord("Docker", "2026/8/31", 120);
    manager.addRecord("CMake", "2026/9/1", 60);

    manager.sortMinutesAsc();
    std::string id;
    std::string content;
    std::string date;
    std::string minutes;
    std::ifstream file("test_record.csv");

    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n'); 
    EXPECT_EQ(id,"3");
    EXPECT_EQ(content,"CMake");
    EXPECT_EQ(date,"2026/9/1");
    EXPECT_EQ(minutes,"60");
    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n');
    EXPECT_EQ(id,"1");
    EXPECT_EQ(content,"C++基礎");
    EXPECT_EQ(date,"2026/8/28");
    EXPECT_EQ(minutes,"80");
    std::getline(file,id,',');
    std::getline(file,content,',');
    std::getline(file,date,',');
    std::getline(file,minutes,'\n');
    EXPECT_EQ(id,"2");
    EXPECT_EQ(content,"Docker");
    EXPECT_EQ(date,"2026/8/31");
    EXPECT_EQ(minutes,"120");
}
TEST_F(StudyManagerTest, TotalMinutesByContentsTest){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++基礎", "2026/8/28", 80);
    manager.addRecord("Docker", "2026/8/31", 120);
    manager.addRecord("CMake", "2026/9/1", 60);
    manager.addRecord("Docker","2026/9/4",35);
    auto totaltime = manager.totalSumTimeContents();

    EXPECT_EQ(totaltime["C++基礎"],80);
    EXPECT_EQ(totaltime["Docker"],155);
    EXPECT_EQ(totaltime["CMake"],60);
}
TEST_F(StudyManagerTest, TotalMinutesByDateTest){
    StudyManager manager("test_record.csv");
    manager.addRecord("C++基礎", "2026/8/28", 80);
    manager.addRecord("Docker", "2026/8/31", 120);
    manager.addRecord("CMake", "2026/9/1", 60);
    manager.addRecord("Docker","2026/9/4",35);

    auto result = manager.getTotalMinutesInPeriod("2026/8/28","2026/8/31");
    EXPECT_EQ(result, 200);
    result = manager.getTotalMinutesInPeriod("2026/8/31","2026/9/4");
    EXPECT_EQ(result, 215);
    result = manager.getTotalMinutesInPeriod("2026/9/5","2026/9/10");
    EXPECT_EQ(result, 0);
}