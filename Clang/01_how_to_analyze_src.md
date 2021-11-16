cscope でソースコード解析
===

cscope とは
---

c, c++, java, go 対応のタグ作成ツール

インストール方法
---

### linux

```sh
% yum install cscope
```

インデックス作成方法
---

```sh
% pwd
want/to/somewhere/to/make/index
% cscope-indexer -r
% cscope -bR
```

検索方法
---

```sh
% vim example.c
< vim の画面で >
[esc キー]
:cs find g xxxxx # 関数定義検索
:cs find s xxxxx # シンボル検索
:cs find e xxxxx # egrep 検索
:cs find f xxxxx # file 検索
```


