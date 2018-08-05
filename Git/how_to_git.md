# Gitの基本的な使い方を快適に
## Gitの基本的な用語
- リポジトリ：履歴管理を行う場所
	- リモートリポジトリ：サーバー上にあるリポジトリ
	- ローカルリポジトリ：自分のPC内にあるリポジトリ
- ブランチ：履歴管理を枝分かれさせてるもの
- クローン：リモートリポジトリをコピーしてローカルリポジトリを作成すること
- コミット：インデックスに登録してある変更対象をローカルリポジトリに反映
- プッシュ：ローカルリポジトリの変更をリモートリポジトリに反映させること
- プル：リモートシポジトリの変更をローカルリポジトリに反映させること
- マージ：異なるブランチの変更を反映させること

## とりあえずGitをインストールする
すでにインストール済みの場合はスキップ可能<br>
バージョン確認をしてみると
```
$ git --version
git version 1.7.1
```
と出てくる.以下gitは1.7.1以上のバージョンを想定する.<br>
初期設定を行う
```
$ git config --global user.name 'YuiWashizu'
$ git config --global user.email '[your email address]'
```
を以上で初期設定完了.ちなみに現在の設定を確認するには以下のよう.
```
$ git config --list
user.name=YuiWashizu
user.email=[your email address]
```

## GitHubの登録
GitHubでアカウントを登録する.

## Gitの基本的な使い方
最低限これができていれば、なんとなくGitを使える.<br>
まずは、作業場所とするローカルリポジトリを作成する.
```
$ mkdir test_repo
$ cd test_repo/
$ git init
Initialized empty Git repository in /data/washizu/test_repo/.git/
$ ls -a
. .. .git
```
`git init`で作業ディレクトリtest_repoに対応するローカルリポジトリが作成される.`ls -a `コマンドで.gitのディレクトリが作成されていることが確認できればOK.<br>
今回はディレクトリtest_repo内で、testcode.pyを作成し、それをGitHubにあげることで、Gitの基本的な使い方を確認する.
```
$ ls 
testcode.py
$ git add testcom.py
$ git commit -m "add new file"
$ git remote add origin https://YuiWashizu@github.com/YuiWashizu/test-repo.git
$ git push origin master
```
で完了するはず.`push`する際には、パスワード入力を求められる.（めんどくさいので、後で直す）<br>
```
$ git remote add origin https://YuiWashizu@github.com/YuiWashizu/test-repo.git
```
この行は、pushするとき毎回入力する必要はなさそう.確認してみる.
```
$ git add testcode2.py
$ it commit -m "add new file"
[master 07dc36f] add new file
 0 files changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 testcode2.py
$ git push origin master
Counting objects: 3, done.
Delta compression using up to 24 threads.
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 242 bytes, done.
Total 2 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://YuiWashizu@github.com/YuiWashizu/test-repo.git
   ff6b8ec..07dc36f  master -> master
```
ちなみに、`git push`の時に
```
$ git push -u origin master
```
とすると、次回以降`git push`だけでリモートリポジトリの`origin`に`master`でプッシュできるようになる.<br>

## ssh接続設定
`git push`の時など、毎度パスワードを入力するのが面倒なので、ssh接続に設定しておくといい.
### 鍵の生成 
ホームディレクトリにて<br>
```
$ cd .ssh
```
で鍵を入れるディレクトリに移動<br>
鍵の生成は以下のよう<br>
```:input
$ ssh-keygen -t rsa
```

```
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


### GitHubに公開鍵を登録
以下のリンクから公開鍵の設定ができる<br>
[Sign in to GitHub · GitHub](https://github.com/settings/ssh)
画面右上の「Add SSH Key」をクリック<br>

「title」に公開鍵名、「key」に公開鍵の中身を入れて「Add Key」をクリック<br>
ここで、間違えて秘密鍵を入力してしまうと、<br>
```
Key is invalid. It must begin with 'ssh-ed25519', 'ssh-rsa', 'ssh-dss', 'ecdsa-sha2-nistp256', 'ecdsa-sha2-nistp384', or 'ecdsa-sha2-nistp521'. Check that you're copying the public half of the key
```
のようなエラーが出るので注意する。


### GitHubと接続
接続を確かめるにはホームディレクトリにて
```
$ ssh -T git@github.com
```
と入力し、
```
Hi [UserName]! You've successfully authenticated, but GitHub does not provide shell access.
```
と返ってきたらOK<br>

＊もっと楽に接続するためには<br>

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
これで、パスワード入力なしで`push`できるようになったはず。<br>
これでもエラーが出る場合は以下のようにもう一度設定し直すといい。<br>
```
$ git remote set-url origin git:YuiWashizu/[リポジトリ名].git
```
