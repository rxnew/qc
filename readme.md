QC (Quantum Circuit)
==============
This program is quantum circuit simulator.

Requirements
---------------
* g++ 5.3 or later
* [CMake][cmake] 2.8 or later

How to install
---------------
```
$ cd build
$ cmake [-DCMAKE_INSTALL_PREFIX=<dir>] [-DCMAKE_BUILD_TYPE=(Debug|Release)] ..
$ make install
```

How to use
---------------
### qc::Bit クラス
量子ビットを実装しているクラス．
  
派生クラスとして，**qc::Cbit** と **qc::Tbit** がある．
それぞれ，コントロールビットとターゲットビットに対応している．

```
auto cbit = Cbit(0, true);
auto tbit = Tbit(1);
```

qc::Bit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|bitno_|ビット番号 (public member variable)|

qc::Cbit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|polarity_|コントロールビットの極性 (public member variable)|
|invertPolarity|極性を反転する (public member function)|

### qc::Gate クラス
量子ゲートを実装している**抽象**クラス．
Cbit と Tbit をリストで保持している．
  
派生クラスで各量子ゲート (e.g., X, T) を実装している．

```
auto gate = std::make_unique<X>(cbit, tbit);
```

qc::Gate クラスの主なメンバ関数を以下にまとめる．

|members|description|
|---|---|
|cbits_|コントロールビットのリスト (private member variable)|
|tbits_|ターゲットビットのリスト (private member variable)|
|clone|複製を生成する (public member function)|
|getCbitList|コントロールビットのリストを取得する (public member function)|
|getTbitList|ターゲットビットのリストを取得する (public member function)|
|addCbit|コントロールビットを追加する (public member function)|
|addTbit|ターゲットビットを追加する (public member function)|
|isIncluded|ビットを含んでいるか確認する (public member function)|
|eraseBit|ビットを削除する (public member function)|
|print|ストリームに出力する (public member function)|

### qc::Circuit クラス
量子回路を実装しているクラス．
量子ゲートの**ポインタ**をリストで保持している．

```
auto circuit = qc::Circuit();
circuit.addGate(gate);
```

qc::Circuit クラスの主なメンバ関数を以下にまとめる．

|members|description|
|---|---|
|gates_|ゲートのリスト (private member variable)|
|description_|説明文 (private member variable)|
|getGateList|ゲートのリストを取得する (public member function)|
|addGate|ゲートを末尾に追加する (public member function)|
|insertGate|ゲートを任意の位置に挿入する (public member function)|
|eraseGate|ゲートを削除する (public member function)|
|swapGate|ゲートを入れ替える (public member function)|
|append|連結する (public member function)|
|clear|ゲートを全て削除する (public member function)|
|getGateCount|ゲート数を取得する (public member function)|
|collectUsedBits|使用しているビットのリストを生成する (public member function)|
|simulate|ユニタリ変換をシミュレートする (public member function)|
|print|ストリームに出力する (public member function)|

### 入出力
qc::io に IO 関連の機能がまとめられている．

```
auto circuit = qc::io::open(filename);
qc::io::input(circuit, filename);
qc::io::output(circuit, filename);
```
拡張子からファイル形式を判断する．
  
対応しているファイル形式は以下の通り．
* qo
* esop
* blif (入力は nand2 のみ)

[cmake]: https://cmake.org/
