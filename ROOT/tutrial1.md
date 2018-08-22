# tutrial1
## ROOTとは
  一般に我々が実験を行う場合は, 以下のようなワークフローになる：
  1. 何か測定したい対象がある→検出器・システムを構築する
  2. そのシステムからの情報を収集・加工・保存する
  3. そのデータを解析し, 結果を得る
  
  ROOTとは, ここでのデータの加工や保存、解析に用いるツール. ROOTは多くのライブラリ（用途ごとにクラスをまとめたもの）から構成されていて, これらのクラス を呼び出し使用する. 例えば, データ解析においては, ヒストグラム（TH1, TH2, etc）やグラフ（TGraph, TGraphErrors, etc）,フィッティング（TF1,etc）などのクラスを使用する.<br>
  さて, このページでは以下の項目について実際にROOTを動かして行く:
  * ヒストグラムの生成と描画
  * TTree生成と利用

## 環境設定
  自分でROOTをインストールすつ場合はマニュアルに従って設定する.（[Download](https://root.cern.ch/downloading-root), [Building ROOT](https://root.cern.ch/building-root)）ROOTを起動すると,
  ```
  $ root
   ------------------------------------------------------------
  | Welcome to ROOT 6.04/14                http://root.cern.ch |
  |                               (c) 1995-2014, The ROOT Team |
  | Built for linuxx8664gcc                                    |
  | From tag v6-04-14, 3 February 2016                         |
  | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q' |
   ------------------------------------------------------------
   root[0]
   ```
   まず, "Hello,World!"を出力してみる.
   ```
   root[0] std::cout << "Hello World!" << std::endl;
   Hello World!
   ```
## ヒストグラムの生成と描画
  早速ヒストグラムを生成してみる.
  ```
  $ root -l #-lはrootのロゴを表示させないコマンド
  root[0] TH1F* myhist = new TH1F("myhist", "My first histogram", 10, 0., 10.);
  ```
  ここでは"TH1F"というクラスを使用している. TH1Fのコンストラクタは
  ```
  TH1F::TH1F(const char* name, const char* title, Int_t nbins, Double_t xlow, Double_t xup)
  Create a 1-Dim histogram with fix bins of type float
  Parameters
    name : name of histogram
    title: histogram title.
    nbins: number of bins
    xlow : low edge of first bin
    xup  : upper edge of last bin
  ```
  Float型の1次元ヒストグラムとわかる. ヒストグラムの名前, タイトル, ビン数, ビンの下限と上限を設定している.<br>
  さらに, TH1Fは以下のようなクラス継承がある.<br>
  
  - TH1F
    - TArrayF
      - TArray
    - TH1
      - TAttMarker
      - TAttFill
      - TAttLine
      - TNamed
        - TObject
  
  基本となるTH1クラスには様々なメンバ関数が定義されている. その多くは関数の名前から機能が想像できる. 例えば, ヒストグラムに値を詰める場合には, `Fill()`という関数、ヒストグラムに描画するには`Draw()`という関数を使う. 実際にx=3.4という値をヒストグラムに詰めて描画する.
  ```
  root[1] myhist->Fill(3.4);
  root[2] myhist->Draw();
  ```
  
## TTreeの生成と利用方法
  実験データは一般的に数多くの情報を持っている.
  - エネルギー, 運動量, 位置, 電荷, ...などの粒子ごとの情報
  - これらは自称ごとには独立, でも1事象内は結びついている
  例えば, 以下のようなテーブルを表すことができる：

  | 荷電粒子の軌跡No. | 運動量[MeV] | 座標z[mm] | 電荷 |
  |:----------:|:-----------:|:------------:|:--------:|
  | 0 | 3200.43 | 7643 | -1 |
  | 1 | 2893.22 | 9834 | 1 |
  | 2 | 3603.90 | 11232 | 1 |
  | 3 | 9899.14 | 10232 | -1 |
  | 4 | 5674.32 | 8092 | 1 |
