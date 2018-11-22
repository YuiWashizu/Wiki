# GitHubから削除する
今回はGitというディレクトリをGit上から削除することを目指す.
- ディレクトリを削除する場合：`-r`が必要
```
$ git rm -r --cache [ディレクトリ名]
```

- ファイルを削除する場合
```
$ git rm --cache [ファイル名]
```
`--cache`というコマンドを用いることで、ローカルからファイルを消すこと無く、gitの管理下からファイルを消すことができる.<br>
この時点で`git status`を行うと,
```
$ git rm -r --cache Git
Git/README.md: needs merge
rm 'Git/README.md'
rm 'Git/README.md'
rm 'Git/how_to_git.md'
$ git status
# On branch master
# Untracked files:
#   (use "git add <file>..." to include in what will be committed)
#
#	Git/
nothing added to commit but untracked files present (use "git add" to track)
```
そのあとは、以下のように
```
$ git commit -m "delete"
[master 838a95e] delete
$ git push origin master
Counting objects: 5, done.
Delta compression using up to 24 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 360 bytes, done.
Total 3 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), done.
To git:YuiWashizu/Wiki.git
   1344261..838a95e  master -> master
```
とやれば、無事にファイルがGit上から削除されていることが確認できる.
```
$ ls
Git  Python  Terminal
```
ターミナル上で`ls`をすると、ディレクトリは残っているが、GitHub上で確認すると、ディレクトリは消えている.→GitHubの管理下からは抜けていることが確認できた.
