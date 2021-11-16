---
title: 新しいmacを買ったら最初にやること
tags: Mac
author: marimori
slide: false
---

# この記事は何？
最近新しいmacを買ったので備忘録を兼ねて自分なりの最低限の設定を記事にした。

- 引用：(https://qiita.com/marimori/items/5feb210edbbb07e1a15b)

## ほんとの最初に入れるソフト

|名前|これはなに？|
|----|----|
|Google Chrome|webブラウザ|
|Alfred|アプリランチャー。このためにmacを使ってるといっても過言ではない|
|Google 日本語入力|IME.ことりえ使いづらい|
|Karabiner-Elements|US配列だと言語切替が辛いのでこれで⌘に割り当てる|


## 黒い画面

### iTerm2をインストール
https://www.iterm2.com/
標準のターミナルよりも使いやすさ/カスタマイズ性ともに優秀

### HomeBrewをインストール
これがないと何も始まらない
https://brew.sh/index_ja

#### 標準シェルをfishにする
`fish` is 便利・わかりやすい・かわいい

```shell
brew install fish
which fish | sudo tee -a /etc/shells
chsh -s /usr/local/bin/fish
```
このあとiTerm2を再起動すれば標準シェルがfishになってる。

#### fisher man
fishのパッケージマネージャー

```shell
curl https://git.io/fisher --create-dirs -sLo ~/.config/fish/functions/fisher.fish
```

#### テーマの変更
[bobthefish](https://github.com/oh-my-fish/oh-my-fish/blob/master/docs/Themes.md#bobthefish)がお気に入り

```shell
fisher add oh-my-fish/theme-bobthefish
```
で導入完了

#### Hack Nerd Font のインストール
上のテーマでアイコンなどが文字化けすることがあるので、対応してるフォントを入れる
https://github.com/ryanoasis/nerd-fonts/tree/master/patched-fonts/Hack
フォントをインストールしたらiTerm2のフォント設定を変えるのを忘れずに。


#### いろんなパッケージを入れる
```shell
brew install peco ghq emacs wget
```

|なまえ|これはなに？|
|---|---|
|peco|標準入力をインクリメンタルサーチして出力してくれるすごい子|
|ghq|gitリポジトリを管理するためのツール|
|emacs|catalinaからemacsが標準で入ってないので|
|wget|wget.なんで標準で入ってないんですかね|


#### fish config
fishは `~/.bash_profile` じゃなくて、 `~/.config/fish/config.fish`を読む

```bash:~/.config/fish/config.fish
## peco-history
function fish_user_key_bindings
  bind \cr peco_select_history
end

## alias
alias g="cd (ghq root)/(ghq list | peco)"
alias gs="git status"
```

```shell
fisher add oh-my-fish/plugin-peco
```

`peco-history` はctrl+Rでコマンド履歴をインクリメンタルサーチする設定
`g` はghqで管理しているリポジトリをインクリメンタルサーチし、移動するためのエイリアス


## git
```shell
git config --global user.email hoge@example.com
git config --global user.name "Foo Bar"
git config --global core.editor "emacs -nw"
git config --global push.default simple
```

## SSH
```shell
ssh-keygen -t rsa
cat ~/.ssh/id_rsa.pub | pbcopy  #クリップボードに公開鍵をコピー
```
あとはGitHubに登録したり、サーバーに登録したりする。

#### GitHubの疎通確認
```shell
ssh -T git@github.com
```

#### サーバーに公開鍵を登録
公開鍵をサーバーの `~/.ssh/authorized_keys` に追記する

ローカルマシンに以下の設定をしておくと、`ssh myserver` だけで接続できるようになる。

```~/.ssh/config
Host myserver
  HostName example.com
  IdentityFile ~/.ssh/id_rsa
  User foo
```

## Docker
https://docs.docker.com/docker-for-mac/install/

## 各言語設定
とりあえずanyenvを入れて **envの管理をする

```shell
brew install anyenv
anyenv install --init
```
以下を追記

```~/.config/fish/config.fish
## anyenv
eval (anyenv init -| source)
```

### python
※僕はanacondaよりもpyenv派です


```shell
anyenv install pyenv
exec $SHELL -l
pyenv versions
pyenv install --list  # インストール可能なpythonバージョンの確認
pyenv install 3.6.9
pyenv global 3.6.9 && pyenv rehash
pip install -U pip
```


## エディタ
### emacs
すでにbrewでいれてある。
起動すると`Warning (initialization): Unable to access user-emacs-directory`みたいなエラーメッセージが出てくるのでパーミッションを変更する。

```shell
sudo chown -R $USER .emacs.d/
```



### VS code
https://code.visualstudio.com/

#### `code` コマンドを使えるようにする
⌘+Shfit+P > `Shell Command: Install 'code' command in PATH` を実行するとcodeコマンドが使えるようになる。
ターミナルから直接ファイルやプロジェクトを開くときに便利

#### settings
⌘+Shfit+P > Open Settings (JSON)
以下を追記

```settings.json
{
    // ...
    "terminal.integrated.shell.osx": "/usr/local/bin/fish",
    "terminal.integrated.fontFamily": "Hack",
    "files.autoSave": "afterDelay"
}
```


#### Extensions
|なまえ|これはなに？|
|---|----|
|Bracket Pair Colorizer|括弧をカラフルに装飾してくれるので、対応関係がわかりやすくなる|
|GitLens|git blameのすごいやつ。この行の過去編集した人を突き止められる|
|indent-rainbow|インデントをカラフルにしてくれるので、対応関係がわかりやすい。特にpythonistにはおすすめ|
|Material Icon Theme|ファイルアイコンを可愛くしてくれるやつ|
|Path Intellisense|ファイルパスを自動補完してくれる|
|Prettier|コードフォーマッター|
|TODO Highlight|vscodeは標準でアノテーションコメントをハイライトしてくれないので、その対処法|
|Trailing Spaces|文末の余計なSpaceをハイライトしてくれる|


## ディスプレイの表示領域を拡張
Retinaディスプレイなのにmacだとその巨大な画面を活かせないので、[Display Menu](https://apps.apple.com/jp/app/display-menu/id549083868)を使って拡張する。

