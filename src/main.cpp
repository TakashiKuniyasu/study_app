#include <iostream>
#include <map>
#include "StudyManager.hpp"
#include "MainManager.hpp"

int main(){
    MainManager user;
    StudyManager manager("study_records.csv");
    manager.loadFromFile();

    while(true){

        menu menu_num = user.userInput();

        switch (menu_num)
        {
        case menu::Record:
        {
            std::string content;
            std::string date;
            int minute;

            user.inputStudyRecord(content, date, minute);
            manager.addRecord(content, date, minute);
            break;
        }
        case menu::Watch:
        {
            manager.showRecords();
            manager.showTotalMinutes();   
            break;
        }
        case menu::Delete:
        {
            int  id = user.inputID("削除したいIDを入力してください");
            manager.deleteRecord(id);
            break;
        }
        case menu::Search:
        {
            std::string word = user.inputSearchContent();
            auto records = manager.searchContent(word);
            manager.showResultSearchContent(records);
            break;
        }
        case menu::Edit:
        {
            int id = user.inputID("編集したいIDを入力してください");

            std::string content;
            std::string date;
            int minute;

            user.inputStudyRecord(content, date, minute);

            manager.editPrevData(id, content, date, minute);
            break;
        }
        case menu::SortByDate:
        {
            auto ascdesc = user.inputSortMethod();
            if(ascdesc == ascdesc::desc){
                manager.sortDateDesc();
            }else{
                manager.sortDateAsc();
            }
            break;
        }
        case menu::SortByMinutes:
        {
            auto ascdesc = user.inputSortMethod();
            if(ascdesc == ascdesc::desc){
                manager.sortMinutesDesc();
            }else{
                manager.sortMinutesAsc();
            }
            break;
        }
        case menu::SumtimeByContents:
        {
            std::map<std::string,int>sumtime;
            sumtime = manager.totalSumTimeContents();
            user.showTotalMinutesByContents(sumtime);
            break;
        }
        case menu::SumtimeByDate:
        {
            std::string start;
            std::string end;
            int minutes;
            user.inputSumtimeByDateStartAndEnd(start, end);
            minutes = manager.getTotalMinutesInPeriod(start, end);
            user.outputSumtimeByDateStartAndEnd(minutes);
            break;
        }
        case menu::SumtimeByContentsInPeriod:
        {
            std::string start;
            std::string end;
            user.inputSumtimeByDateStartAndEnd(start, end);
            auto sumtime = manager.SumtimeByContentsInPeriod(start, end);
            user.outputSumtimeByContentsInPeriod(sumtime);
            break;
        }
        case menu::Exit:
        {
            std::cout << "処理を終了します\n" << std::endl;
            return 0;
            break;
        }
        }
    }
    return 0;
}