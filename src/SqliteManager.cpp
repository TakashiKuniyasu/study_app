#include<iostream>
#include "SqliteManager.hpp"

bool SqliteManager::databaseOpen(const std::string& filename){
    if(sqlite3_open(filename.c_str(), &db) != SQLITE_OK){
        if(db != nullptr){
            std::cout << "データベースOPEN失敗" 
                        << sqlite3_errmsg(db) 
                        << std::endl; 
            sqlite3_close(db);
            db = nullptr;
        }
        return false;
    }
    return true;
}
bool SqliteManager::databaseClose(){
    if(db == nullptr){
        return true;
    }
    int result = sqlite3_close(db);

    if(result != SQLITE_OK){
        std::cout << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    db = nullptr;
    return true;
}
bool SqliteManager::createTable(){
    sqlite3_stmt* create_stmt = nullptr;
    const char* create_sql =
        "CREATE TABLE IF NOT EXISTS study_records"
        " (id INTEGER PRIMARY KEY,"
        " content TEXT NOT NULL," 
        " date TEXT NOT NULL, "
        " minutes INTEGER NOT NULL);";
    
    int result = sqlite3_prepare_v2(db,
                                create_sql,
                                -1,
                                &create_stmt,
                                nullptr);
    if(result != SQLITE_OK){
        std::cout << "テーブル作成準備失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        return false;
    }
    result = sqlite3_step(create_stmt);
    if(result != SQLITE_DONE){
        std::cout << "テーブル作成失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(create_stmt);
        return false;        
    }
    sqlite3_finalize(create_stmt);
    return true;
}
bool SqliteManager::insertRecord(const std::string& content,
                    const std::string& date,
                    int minutes){
    sqlite3_stmt* insert_stmt = nullptr;
    const char* insert_sql =
                "INSERT INTO study_records"
                " (content, date, minutes)"
                " VALUES(?, ?, ?);";
    int result = sqlite3_prepare_v2(db,
                                insert_sql,
                                -1,
                                &insert_stmt,
                                nullptr);
    if(result != SQLITE_OK){
        std::cout << "レコード追加準備失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        return false;
    }
    result = sqlite3_bind_text
                (insert_stmt, 
                    1, 
                    content.c_str(), 
                    -1, 
                    SQLITE_TRANSIENT);
    if(result != SQLITE_OK){
        std::cout << "学習内容の追加失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(insert_stmt);
        return false;
    }
    result = sqlite3_bind_text
                (insert_stmt, 
                    2, 
                    date.c_str(), 
                    -1, 
                    SQLITE_TRANSIENT);
    if(result != SQLITE_OK){
        std::cout << "日付の追加失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(insert_stmt);
        return false;
    }
    result = sqlite3_bind_int
                (insert_stmt, 3, minutes);
    if(result != SQLITE_OK){
        std::cout << "学習時間の追加失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(insert_stmt);
        return false;
    }
    result = sqlite3_step(insert_stmt);
    if(result != SQLITE_DONE){
        std::cout << "レコード追加処理失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(insert_stmt);
        return false;
    }
    sqlite3_finalize(insert_stmt);
    return true;
}
bool SqliteManager::selectAllRecords(std::vector<StudyRecord>& records){
    std::vector<StudyRecord> records_local;
    sqlite3_stmt* select_stmt;
    const char* select_sql =
        "SELECT id, content, date, minutes"
        " FROM study_records;";
    int result = sqlite3_prepare_v2(db,
                                select_sql,
                                -1,
                                &select_stmt,
                                nullptr);
    if(result != SQLITE_OK){
        std::cout << "一覧表示準備失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        return false;
    }
    while((result = sqlite3_step(select_stmt)) == SQLITE_ROW){
        StudyRecord record(sqlite3_column_int(select_stmt, 0),
                        reinterpret_cast<const char*>(sqlite3_column_text(select_stmt,1)),
                        reinterpret_cast<const char*>(sqlite3_column_text(select_stmt,2)),
                        sqlite3_column_int(select_stmt,3));
        records_local.push_back(record);
    }
    if(result != SQLITE_DONE){
        std::cout << "一覧表示処理失敗" 
                << sqlite3_errmsg(db)
                << std::endl;
        sqlite3_finalize(select_stmt);
        return false;
    }else{
        records = std::move(records_local);
    }
    sqlite3_finalize(select_stmt);
    return true;
}