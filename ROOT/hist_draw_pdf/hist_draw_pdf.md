# hist_draw_pdf
  複数のrootファイル（sc0284.root〜sc0336.root）からヒストグラムを作成.<br>
  それをある一定の範囲でガウス分布でフィットし、y軸をlogスケールにする.<br>
  作成した複数のヒストグラムを1つのpdfファイルに書き出す.
  
  - 複数のヒストグラムを1つのpdfファイルに書き込む.
  - ガウス分布でフィットする
    ```
    TF1* fit_gaus = new TF1("fit_gaus", "[0]*TMath::Gaus(x,[1],[2])", 0, 4000);
    //初期値の設定
    fit_gaus->SetParameter(0, 45);
    fit_gaus->SetParameter(1, ini_mean);
    fit_gaus->SetParameter(2, ini_sigma);
    //フィット
    adc_hist->Fit("fit_gaus", "", "", ped_min, ped_max);
    ```
    
  - 文字列に任意の数字を出力する
    ```
    Form("fit_gaus_from%d_to%d.pdf", filenum_i, filenum_n)
    ```
    | 指定子 | 対応する型 | 説明 |
    |:-----------|:------------|:------------|
    | %c | char | 1文字出力 |
    | %s | char* | 文字列を出力 |
    | %d | int | 整数を10進法で出力 |
    | %u | unsigned int | 符号なし整数を10進法で出力 |
    | %o | int, unsigned int | 整数を8進法で出力 |
    | %x | int, unsigned int | 整数を16進法で出力 |
    | %f | float | 実数を出力 |
    | %e | float | 実数を指数表示で出力 |
    | %g | float | 実数で最適な形式で出力 |
    | %ld| long | 倍精度整数を10進で出力 |
    | %lu| unsigned long | 符号なし倍精度整数を10進で出力 |
    | %lo| unsigned long | 倍精度整数を8進で出力 |

