# Terminal Setup
ホームディレクトリから以下へアクセス
## .bashrc
  ```
  emacs .bashrc 
  ```
### alias
aliasを作成することで、コマンドを設定することができる。
```
alias [自分で決めたコマンド]="もとのコマンド"
```
「=」の両端にスペースは空けない

### /etc/ssh/ssh_config
アカウント名を省略することができる
```
Host [コマンド名]
  User メールアドレスの@以前
  HostName メールアドレス@以下
  ServerAliveInterval 120
  TCPKeepAlive yes
```
設定しておくとscpなどを行うときに便利
gitの公開鍵を設定する際には
```
Host git
  User git
  HostName github.com
  IdentityFile ~/.ssh/id_rsa
```
このように設定すると
```
ssh -T git
```
で接続可能になる