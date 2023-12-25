我們的檔案分成兩種版本，一種是CPP版本，一種是GUI版本
CPP版本可執行「指令檔模式」及「輸入指令模式」
GUI僅能執行GUI
兩者都有Board File, Random Count, Random Rate等載入盤面模式

GUI版本的程式碼由qmake編譯
開啟終端機並執行以下指令
qmake位置\qmake.exe MineSweeper.pro -tp vc
例：C:\Qt\5.15.2\msvc2019_64\bin\qmake.exe MineSweeper.pro -tp vc

===================================================================================================

CPP版本：
以終端機執行Group5_P1_ver1/exe/CPP/MineSweeper.exe，並依照以下指令進行操作

1.指令檔模式 : MineSweeper.exe CommandFile <輸入指令檔> <輸出檔>
2.輸入指令模式 : MineSweeper.exe CommandInput

載入盤面檔：Load BoardFile <盤面檔相對路徑>
指定地雷數量：Load RandomCount <M> <N> <炸彈數量>
指定地雷生成機率：Load RandomRate <M> <N> <炸彈生成機率>
開始遊戲：StartGame
印出資訊：Print <資訊名> (GameBoard, GameState, GameAnswer, BombCount, FlagCount, OpenBlankCount, RemainBlankCount)
開啟格子：LeftClick <row> <col>
標註旗幟/問號/回復無標註：RightClick <row> <col>
重新遊玩：Replay
關閉程式：Quit

===================================================================================================

GUI版本：
執行Group5_P1_ver1\exe\GUI\MineSweeper_DEMO.exe即可開始遊玩

1.Load Mode 下拉清單可選擇載入盤面的模式
  2.1.Board File 模式可指定載入盤面檔的路徑
  2.2.Random Count 模式可指定盤面大小(下限1*1，上限50*50)及炸彈數量
  2.3.Random Rate 模式可指定盤面大小(下限1*1，上限50*50)及炸彈生成機率(0~1)

2.Load 按鈕可載入盤面

3.StartGame 按鈕開始遊戲，開始遊戲時會自動播放BGM

4.GameState會顯示在下方status bar

5.上方工具列的Print選單可以選擇要印出的資料，資料將會輸出在終端機
  5.1.GameBoard 資訊在載入盤面後才可印出
  5.2.GameState 資訊隨時皆可以被印出
  5.3.GameAnswer 資訊在載入盤面後才可印出
  5.4.BombCount 資訊不可在Standby階段印出
  5.5.FlagCount 資訊不可在Standby階段印出
  5.6.OpenBlankCount 資訊不可在Standby階段印出
  5.7.RemainBlankCount 資訊不可在Standby階段印出

6.開始遊玩後，比照經典踩地雷規則，開啟格子及踩到炸彈會播放音效

7.遊戲結束後可選擇Replay或Quit