#include <iostream>
#include <gtest/gtest.h>
#include <filesystem>
#include "StudyRecord.hpp"

TEST(StudyRecordTest, CheckDate){
    EXPECT_EQ(StudyRecord::checkDate("2024/2/29"), true);
    EXPECT_EQ(StudyRecord::checkDate("1999/1/1"), false);
    EXPECT_EQ(StudyRecord::checkDate("2027/1/1"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/1/1"), true);
    EXPECT_EQ(StudyRecord::checkDate("2000/1/1"), true);
    EXPECT_EQ(StudyRecord::checkDate("2026/0/1"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/13/1"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/1/32"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/1/0"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/2/29"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/4/31"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/6/31"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/9/31"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/11/31"), false);
    EXPECT_EQ(StudyRecord::checkDate("2026/12/31"), true);
}
TEST(StudyRecordTest, CheckMinutes){
    EXPECT_EQ(StudyRecord::checkMinute(-1), false);
    EXPECT_EQ(StudyRecord::checkMinute(0), false);
    EXPECT_EQ(StudyRecord::checkMinute(1), true);
}
TEST(StudyRecordTest, CheckGetter){
    StudyRecord record(
        1,
        "C++",
        "2026/8/28",
        60
    );

    EXPECT_EQ(record.getID(), 1);
    EXPECT_EQ(record.getContent(), "C++");
    EXPECT_EQ(record.getDate(), "2026/8/28");
    EXPECT_EQ(record.getMinutes(), 60);
}
TEST(StudyRecordTest, CheckUpdate){
    StudyRecord record(1,"","",0);
    record.update("Docker","2026/8/29",80);

    EXPECT_EQ(record.getID(), 1);
    EXPECT_EQ(record.getContent(), "Docker");
    EXPECT_EQ(record.getDate(), "2026/8/29");
    EXPECT_EQ(record.getMinutes(), 80);
}
