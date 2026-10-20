#include <iostream>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "CsvManager.hpp"

class CsvManagerTest : public ::testing::Test
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
void expectOnlyLinuxRecord(const std::vector<StudyRecord>& records){
    ASSERT_EQ(records.size(),1);
    EXPECT_EQ(records[0].getID(),2);
    EXPECT_EQ(records[0].getContent(),"Linux");
    EXPECT_EQ(records[0].getDate(),"2026/10/20");
    EXPECT_EQ(records[0].getMinutes(),75);
}
};
TEST_F(CsvManagerTest,LoadCsvTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/10/19,60\n";
    }

    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile("test_record.csv",records));
    ASSERT_EQ(records.size(),1);
    EXPECT_EQ(records[0].getID(),1);
    EXPECT_EQ(records[0].getContent(),"C++");
    EXPECT_EQ(records[0].getDate(),"2026/10/19");
    EXPECT_EQ(records[0].getMinutes(),60);
}
TEST_F(CsvManagerTest,LoadCsvFailedTest){
    std::vector<StudyRecord> records;
    EXPECT_FALSE(CsvManager::loadFromFile("not_exist_directory/test_record.csv",records));
}
TEST_F(CsvManagerTest,LoadEmptyCsvTest){
    {
        std::ofstream file("test_record.csv");        
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile("test_record.csv",records));
    EXPECT_TRUE(records.empty());
}
TEST_F(CsvManagerTest,LoadRecordsCsvTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++基礎,2026/10/18,45\n2,Linux,2026/10/20,80\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile("test_record.csv",records));
    ASSERT_EQ(records.size(),2);
    EXPECT_EQ(records[0].getID(),1);
    EXPECT_EQ(records[0].getContent(),"C++基礎");
    EXPECT_EQ(records[0].getDate(),"2026/10/18");
    EXPECT_EQ(records[0].getMinutes(),45);
    EXPECT_EQ(records[1].getID(),2);
    EXPECT_EQ(records[1].getContent(),"Linux");
    EXPECT_EQ(records[1].getDate(),"2026/10/20");
    EXPECT_EQ(records[1].getMinutes(),80);
}
TEST_F(CsvManagerTest,SaveAndLoadTest){
    std::vector<StudyRecord> records{
        StudyRecord(1,"C++","2026/10/19",60),
        StudyRecord(2,"Linux","2026/10/20",45)
    };
    CsvManager::saveToFile("test_record.csv",records);
    std::vector<StudyRecord> loadRecords;
    EXPECT_TRUE(CsvManager::loadFromFile("test_record.csv",loadRecords));
    ASSERT_EQ(loadRecords.size(),records.size());
    EXPECT_EQ(loadRecords[0].getID(),records[0].getID());
    EXPECT_EQ(loadRecords[0].getContent(),records[0].getContent());
    EXPECT_EQ(loadRecords[0].getDate(),records[0].getDate());
    EXPECT_EQ(loadRecords[0].getMinutes(),records[0].getMinutes());
    EXPECT_EQ(loadRecords[1].getID(),records[1].getID());
    EXPECT_EQ(loadRecords[1].getContent(),records[1].getContent());
    EXPECT_EQ(loadRecords[1].getDate(),records[1].getDate());
    EXPECT_EQ(loadRecords[1].getMinutes(),records[1].getMinutes());
}
TEST_F(CsvManagerTest,LoadCsvInvalidIdTest){
    {
        std::ofstream file("test_record.csv");
        file << "abc,C++,2026/10/19,60\n"
                "2,Linux,2026/10/20,75\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}
TEST_F(CsvManagerTest,LoadCsvInvalidDateTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,abc,60\n"
                "2,Linux,2026/10/20,75\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}
TEST_F(CsvManagerTest,LoadCsvInvalidMinutesTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/10/19,abc\n"
                "2,Linux,2026/10/20,75\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}
TEST_F(CsvManagerTest,LoadCsvMissingColumnTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/10/19\n"
                "2,Linux,2026/10/20,75\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}
TEST_F(CsvManagerTest,LoadCsvOverColumnTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/10/19,60,abc\n"
                "2,Linux,2026/10/20,75\n";
    }
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}
TEST_F(CsvManagerTest,LoadCsvExtraEmptyColumnTest){
    {
        std::ofstream file("test_record.csv");
        file << "1,C++,2026/10/19,60,\n"
                "2,Linux,2026/10/20,75\n";
    } 
    std::vector<StudyRecord> records;
    EXPECT_TRUE(CsvManager::loadFromFile
        ("test_record.csv",records));
    expectOnlyLinuxRecord(records);
}