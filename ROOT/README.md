# ROOT
## hist_draw_pdf
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
    
  - 文字列に任意の数字を代入する
    ```
    Form("fit_gaus_from%d_to%d.pdf", filenum_i, filenum_n)
    ```
    

  
