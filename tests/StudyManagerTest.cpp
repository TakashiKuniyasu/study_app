#include <iostream>
#include <gtest/gtest.h>
#include <filesystem>
#include "StudyManager.hpp"
#include "StudyManagerTest.hpp"

TEST(StudyManagerTest, AddRecord){
    std::filesystem::remove("test_record.csv");
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60);

    EXPECT_EQ(manager.getRecordCount(), 1);

    manager.addRecord("Docker", "2026/8/29", 80);
 
    EXPECT_EQ(manager.getRecordCount(), 2);

    std::filesystem::remove("test_record.csv");
    return;
}
TEST(StudyManagerTest, Deleterecord){
    std::filesystem::remove("test_record.csv");

    StudyManager manager("test_record.csv");

    manager.addRecord("C++", "2026/8/28", 60);
    manager.addRecord("Docker", "2026/8/29", 80);

    manager.deleteRecord(2);
    EXPECT_EQ(manager.getRecordCount(), 1);
    EXPECT_NE(manager.findRecordByID(1), nullptr);
    EXPECT_EQ(manager.findRecordByID(2), nullptr);
}
TEST(StudyManagerTest, Editrecord){
    std::filesystem::remove("test_record.csv");
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
TEST(StudyManagerTest, Saveandloadrecord){
    std::filesystem::remove("test_record.csv");
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
TEST(StudyManagerTest, Deleteinvalidid){
    std::filesystem::remove("test_record.csv");
    StudyManager manager("test_record.csv");
    manager.addRecord("C++", "2026/8/28", 60);

    manager.deleteRecord(2);
    EXPECT_EQ(manager.getRecordCount(), 1);
}
TEST(StudyManagerTest, Editinvalidid){
    std::filesystem::remove("test_record.csv");
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
TEST(StudyManagerTest, Loadtwice){
    std::filesystem::remove("test_record.csv");
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