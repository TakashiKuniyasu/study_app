# 学習記録管理アプリ
## 1.できること
・学習記録を記録する（学習内容、学習日、学習時間）  
・学習内容一覧を見る  
・学習内容を削除する  
・学習記録を検索する  
・学習記録を編集する  
・日付を並べ替える  
・学習記録時間を並べ替える  
・学習内容ごとの学習時間を出力する  
・学習期間内での学習内容ごとの学習時間を出力する  

## 2.ビルド方法  
study_app直下で
``` bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 3.実行方法
study_app直下で
``` bash
cd build
./study_app
```

## 4.テスト方法
study_app直下で
``` bash
cd build
ctest --output-on-failure
```
