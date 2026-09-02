#include <iostream>
#include <cassert>
#include "StudyRecord.hpp"

int main(){
    // 日付チェック
    assert(StudyRecord::checkDate("2024/2/29") == true);
    assert(StudyRecord::checkDate("1999/1/1") == false);
    assert(StudyRecord::checkDate("2027/1/1") == false);
    assert(StudyRecord::checkDate("2026/1/1") == true);
    assert(StudyRecord::checkDate("2000/1/1") == true);
    assert(StudyRecord::checkDate("2026/0/1") == false);
    assert(StudyRecord::checkDate("2026/13/1") == false);
    assert(StudyRecord::checkDate("2026/1/32") == false);
    assert(StudyRecord::checkDate("2026/1/0") == false);
    assert(StudyRecord::checkDate("2026/2/29") == false);
    assert(StudyRecord::checkDate("2026/4/31") == false);
    assert(StudyRecord::checkDate("2026/6/31") == false);
    assert(StudyRecord::checkDate("2026/9/31") == false);
    assert(StudyRecord::checkDate("2026/11/31") == false);
    assert(StudyRecord::checkDate("2026/12/31") == true);

    // 学習時間チェック
    assert(StudyRecord::checkMinute(-1) == false);
    assert(StudyRecord::checkMinute(0) == false);
    assert(StudyRecord::checkMinute(1) == true);

    //コンストラクタ＋getter
    StudyRecord record(
        1,
        "C++",
        "2026/8/28",
        60
    );

    assert(record.getID() == 1);
    assert(record.getContent() == "C++");
    assert(record.getDate() == "2026/8/28");
    assert(record.getMinutes() == 60);

    //update
    record.update("Docker","2026/8/29",80);

    assert(record.getID() == 1);
    assert(record.getContent() == "Docker");
    assert(record.getDate() == "2026/8/29");
    assert(record.getMinutes() == 80);

    std::cout << "全テスト成功" << std::endl;

    return 0;
}
