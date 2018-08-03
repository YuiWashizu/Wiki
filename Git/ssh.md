# ssh接続
## Make Key 
ホームディレクトリにて<br>
```
$ cd .ssh
```
で鍵を入れるディレクトリに移動<br>
鍵の生成は以下のよう<br>
```:input
$ ssh-keygen -t rsa
```

```:output
$ ssh-keygen -t rsa
Generating public/private rsa key pair.
Enter file in which to save the key (/Users/(username)/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
```

output関しては、全てEnterキーを押すのでOK<br>
id_rsaとid_rsa_pubの2つの鍵が生成される<br>
1度生成したことがある場合、2度目からは上書きされてしまうので注意する<br>
- id_rsa：秘密鍵
- id_rsa_pub：公開鍵
```
$ cd
$ cat .ssh/id_rsa.pub
```
でid_rsa_puの中身を確認してコピー<br>
コピーする時には以下のようにしてもいい<br>
```:Macの場合
$ pbcopy < ~/.ssh/id_rsa.pub
```


## gitHub up
以下のリンクから公開鍵の設定ができる<br>
[Sign in to GitHub · GitHub](https://github.com/settings/ssh)
画面右上の「Add SSH Key」をクリック<br>

「title」に公開鍵名、「key」に公開鍵の中身を入れて「Add Key」をクリック<br>
ここで、間違えて秘密鍵を入力してしまうと、<br>
```
Key is invalid. It must begin with 'ssh-ed25519', 'ssh-rsa', 'ssh-dss', 'ecdsa-sha2-nistp256', 'ecdsa-sha2-nistp384', or 'ecdsa-sha2-nistp521'. Check that you're copying the public half of the key
```
のようなエラーが出るので注意する。


## Connect to gitHub
接続を確かめるにはホームディレクトリにて
```:input
$ ssh -T git@github.com
```
と入力し、
```:output
Hi [UserName]! You've successfully authenticated, but GitHub does not provide shell access.
```
と返ってきたらOK<br>

もっと楽に接続するためには<br>

- MacOSの場合
```
$ sudo emacs /etc/ssh/ssh_config
```
- それ以外のOS：新しくスクリプトを作る
```
$ emacs /.ssh/config
```

の中身にどこでもいいので、
```:/etc/ssh/ssh_config
Host git
     User git
     HostName github.com
     IdentityFile ~/.ssh/id_rsa
```

を追加すると、
```
$ ssh -T git
```
で接続できるようになる。<br>
と思ったが、この後、`push`を行うときに、パスワード入力が必要だった。<br>
リポジトリに対応するディレクトリに移動し、<br>
```
$ git remote -v
origin  https://github.com/YuiWashizu/log.git (fetch)
origin  https://github.com/YuiWashizu/log.git (push)
```
なのを確認し、以下のように変更する。<br>
```
$ git remote set-url origin git@github.com
$ git remote -v
origin  git@github.com: (fetch)
origin  git@github.com: (push)
```
これで、パスワード入力なしで`push`できるようになったはず。