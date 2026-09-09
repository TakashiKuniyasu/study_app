#include <iostream>
#include <string>
#include <limits>
#include <map>
#include "MainManager.hpp"
#include "StudyRecord.hpp"

menu MainManager::userInput(){
    int num;
    menu menu_num;
    std::cout << "------------------------------" << std::endl;
    std::cout << "操作を選択してください" << std::endl;
    std::cout << "１．学習を記録する" << std::endl;
    std::cout << "２．学習記録を見る" << std::endl;
    std::cout << "３．学習記録を削除する" << std::endl;
    std::cout << "４．学習記録を検索する" << std::endl;
    std::cout << "５．学習記録を編集する" << std::endl;
    std::cout << "６．日付を並び替える" << std::endl;
    std::cout << "７．学習記録を並び替える" << std::endl;
    std::cout << "８．学習内容毎の学習時間を出力する" << std::endl;
    std::cout << "９．学習期間内での学習時間を出力する" << std::endl;
    std::cout << "１０．学習期間内での学習内容ごとの学習時間を出力する" << std::endl;
    std::cout << "１１．終了" << std::endl;

    std::cin >> num;
    while((std::cin.fail())||(num < 1 || num > 11)){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "1〜11を入力してください" << std::endl;
        std::cin >> num;
    }
    menu_num = static_cast<menu>(num);
    return menu_num;
}
void MainManager::inputStudyRecord(std::string& content,
                      std::string& date,
                      int& minute){
    std::cout << "学習内容を入力してください" << std::endl;
    std::cin >> content;

    while(true){
        std::cout << "日付を入力してください" << std::endl;
        std::cin >> date; 
        if(StudyRecord::checkDate(date)){
            break;
        }
        std::cout << "正しい日付を入力してください" << std::endl;    
    }

   while(true){
        std::cout << "学習時間を入力してください" << std::endl;
        std::cin >> minute;

        if(!std::cin.fail() && StudyRecord::checkMinute(minute)){
            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "正しい学習時間を入力してください" << std::endl;
    }
}
int MainManager::inputID(const std::string& message){
    int id;
    std::string sid;

    while(true){
        std::cout << message << std::endl;
        std::cin >> sid;
        try{
            std::size_t pos;
            id = std::stoi(sid, &pos);

            if(pos != sid.size()){
                std::cout << "IDが指定の形式ではありません" << std::endl;
            }else{
                break;
            }
        }catch(...){
            std::cout << "IDが指定の形式ではありません" << std::endl;
        }
    }
    return id;
}
std::string MainManager::inputSearchContent(){
    std::string word;
    std::cout << "検索する学習内容を入力してください" << std::endl;
    std::cin >> word;

    return word;
}
enum ascdesc MainManager::inputSortMethod(){
    std::string strvalue;
    int value;

    while(true){
        try{
            std::cout << "昇順にするか降順にするか選択してください" << std::endl;
            std::cout << "１：昇順、０：降順" << std::endl;
            std::cin >> strvalue;
            std::size_t pos;
            value = stoi(strvalue, &pos);
            if(pos != strvalue.size()){
                std::cout << "入力が適切ではありません" << std::endl;
                continue;
            }
            if((value != 0)&&(value != 1)){
                std::cout << "入力が適切ではありません" << std::endl;                
                continue;
            }
        }catch(...){
            std::cout << "入力が適切ではありません" << std::endl;
            continue;
        }
        break;
    }
    return static_cast<enum::ascdesc>(value);
}
void MainManager::showTotalMinutesByContents(const std::map<std::string,int>& sumtime){
    for(const auto data : sumtime){
        std::cout << data.first << " " << data.second << "分\n";
    }
}
void MainManager::inputSumtimeByDateStartAndEnd(std::string& start, std::string& end){
    while(true){
        std::cout << "開始期間を入力してください" << std::endl;
        std::cin >> start;
        if(!StudyRecord::checkDate(start)){
            std::cout << "開始時期の入力が正しくありません" << std::endl;
            continue;
        }
        break;
    }
    while(true){
        std::cout << "終了期間を入力してください" << std::endl;
        std::cin >> end;
        if(!StudyRecord::checkDate(end)){
            std::cout << "終了時期の入力が正しくありません" << std::endl;
            continue;
        }
        break;
    }
}
void MainManager::outputSumtimeByDateStartAndEnd(int minutes){
    std::cout << "期間内の総学習時間" << " " << minutes << "分" << std::endl;
}
void MainManager::outputSumtimeByContentsInPeriod(const std::map<std::string,int>& sumtime){
    for(const auto data : sumtime){
        std::cout << data.first << " " << data.second << "分\n";
    }   
}