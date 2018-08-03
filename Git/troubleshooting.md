# git on server
サーバー上のGitについてのトラブルシューティング
## git push error
今回起こったこと(2018/08/03)
サーバー上での`git add`を行うに当たって
```
git init
git add somefile.cpp
git commit -m "new add file"
git remote add origin https://YuiWashizu/ComputingSummerSchool2018.git
git add origin master
```
を行うと、以下のようなエラーが出た
```
error: The requested URL returned error: 403 Forbidden while accessing https://github.com/YuiWashizu/ComputingSummerSchool2018.git/info/refs

fatal: HTTP request failed
```
ググるとgitのバージョンが古いなど書いてあったので、サーバー上のgitをアップデートしようとしたがめんどすぎたのでやめた。（しかも関係なかった）
以下の方法で解決したのでそれを記す。
```
git init
git add somefile.cpp
git commit -m "add new file"
git remote set-url origin https://YuiWashizu@github.com/YuiWashizu/ComputingSummerSchool2018.git
git add origin master
```
URLの部分にアカウント名を入れた方がいいらしい
これで無事`add`できたことを確認した。