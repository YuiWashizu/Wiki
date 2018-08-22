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

  この1行の組をtuple（タプル）と, 複数からなるもの（表）をNtuple（エヌタプル）と呼ぶ. ROOTではこれらを扱うものにTNtuple, TTreeといったクラスがる.
  - TNtuple：基本的に数字のみ扱う.
  - TTree：数字だけでなく, 色々な情報（文字列, STL container, TObject, ...）を保持できる
  
  言葉の定義は, 縦の項目をBranch, 一行のかたまりをEntryという. 実際にこのテーブルを表現するTTreeを作る.
  ```
  void makeTree1()
{
  // 表の値を扱いやすいように配列に格納しておく
  const Int_t nentries = 5;
  Int_t    a_ntracks[nentries]  = {0, 1, 2, 3, 4};                          // 荷電粒子の軌跡No.
  Double_t a_momentum[nentries] = {3200.4, 2893.2, 3603.9, 9899.1, 5674.3}; // 運動量[MeV]
  Double_t a_position[nentries] = {7643, 9834, 11232, 10232, 8092};         // 座標 z [mm]
  Int_t    a_charge[nentries]   = {-1, 1, 1, -1, 1};                        // 電荷
 
  // ROOTファイルとTTreeを作成
  TFile *file = TFile::Open("tree.root", "RECREATE");
  TTree *tree = new TTree("tree", "tree");
 
  // Branchに対応する変数を作成
  Int_t    ntracks;
  Double_t momentum;
  Double_t position;
  Int_t    charge;
 
  // Branch関数で変数のアドレスをTTreeにセット
  tree->Branch("ntracks",  &ntracks,  "ntracks/I");
  tree->Branch("momentum", &momentum, "momentum/D");
  tree->Branch("position", &position, "position/D");
  tree->Branch("charge",   &charge,   "charge/I");
 
  // 配列から値を取得、TTreeをFill
  for (Int_t ii = 0; ii < nentries; ii++) {
    ntracks  = a_ntracks[ii];
    momentum = a_momentum[ii];
    position = a_position[ii];
    charge   = a_charge[ii];
    tree->Fill();
  }
 
  // ファイルに保存
  tree->Write();
  file->Close();
}
```
Branch関数でBranchを作成し, それに対応する変数のアドレスをセットしている. TTreeのFill()が呼ばれると、 その時の変数の値がTTreeのEntryとして増えていく. 最後にTTreeのファイルを書いて, ファイルを閉じて, 実行すると, 中身を確認できる.
