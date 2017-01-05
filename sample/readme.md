QC sample project
==============
This program is a sample project using qc library.

Requirements
---------------
* g++ 6.2.0 or later
* [CMake][cmake] 3.2 or later
* [graphc][graphc] v1.0 or later
* [json11][json11] v1.3 or later
* [qc][qc]

How to build
---------------
QC ライブラリを利用するプロジェクトのサンプルです．  
依存ライブラリが見つからない場合，自動でダウンロードされ，ビルドディレクトリにインストールされます．  
依存ライブラリのインストール場所を指定する場合やインストール先を変更する場合は，***INSTALL_EXTERNAL_PROJECTS_PREFIX*** を設定します．

```
$ cd sample/build
$ cmake [-DINSTALL_EXTERNAL_PROJECTS_PREFIX=<dir>] [-DCMAKE_BUILD_TYPE=(Debug|Release)] ..
$ make
```

How to run
---------------
```
$ ./bin/main
```

[cmake]: https://cmake.org/
[graphc]: https://github.com/rxnew/graph.git
[json11]: https://github.com/ngc-developers/json11.git
[qc]: https://github.com/rxnew/qc.git
