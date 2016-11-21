QC (Quantum Circuit)
==============
This program is quantum circuit simulator.

Requirements
---------------
* g++ 6.2.0 or later
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
###### "qc/bit.hpp"
量子ビットを実装しているクラス．
  
派生クラスとして，***qc::CBit*** と ***qc::TBit*** がある．
それぞれ，コントロールビットとターゲットビットに対応している．

```cpp
auto cbit = qc::CBit(0_bit, true);
auto tbit = qc::TBit(1_bit);
```

qc::Bit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|no_|ビット番号 (private member variable)|
|get_no|ビット番号を取得する (public member function)|

qc::CBit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|polarity_|コントロールビットの極性 (private member variable)|
|get_polarity|極性を取得する (public member function)|
|invert_polarity|極性を反転する (public member function)|

### qc::Gate クラス
###### "qc/gate.hpp", "qc/gate/library.hpp"
量子ゲートを実装しているクラス．
  
ゲートの機能を提供する ***qc::GateKernel*** **抽象**クラスをポインタで保持している．
qc::GateKernel は qc::CBit と qc::TBit の集合を保持している．
  
qc::GateKernel の派生クラスを用いて各量子ゲート (e.g., H, X) のカーネルを実装している．
各ゲートに対応するクラスは，qc::Gate を継承している．
また，qc::Gate への暗黙的な型変換が可能．

```cpp
auto x = qc::X(cbit, tbit);
auto gate = static_cast<qc::Gate>(x);
```

以下のような例に注意する必要がある．

```cpp
auto h = qc::H(tbit);
auto x = qc::X(cbit, tbit);
h = x; // error
```

qc::X から qc::H など，異なる種類のゲート間の型変換はできない．
同様に qc::Gate から qc::X などへの型変換もできない．
異なる種類のゲートを同列に扱う場合，各ゲートを qc::Gate オブジェクトとして扱うべきである．

```cpp
auto h = static_cast<qc::Gate>(qc::H(tbit));
auto x = static_cast<qc::Gate>(qc::X(cbit, tbit));
h = x; // ok
```

上記の例では，qc::H (qc::X) の一時オブジェクトが生成されている．
一時オブジェクトを生成せずに，直接 qc::Gate オブジェクトを生成する場合は，***qc::Gate::make()*** を利用する．

```cpp
auto x = qc::Gate::make<X>(cbit, tbit);
```

ゲート名の文字列からゲートを生成する場合は，***qc::make_gate()*** を利用する．
ゲート名にはエイリアスも使用可能．
また，大文字小文字を区別しない．

```cpp
auto x = qc::make_gate("X", cbit, tbit);
auto x = qc::make_gate("NOT", cbit, tbit);
```

実装済みのゲートは以下の通り．
(括弧内の斜体はエイリアス)

* ***I*** (単位行列)
* ***H*** (***Hadamard***)
* ***X*** (パウリ行列, ***NOT***, ***Toffoli***, ***MCT***, ***MPMCT***)
* ***Y*** (パウリ行列)
* ***Z*** (パウリ行列)
* ***V*** (Rx(pi/2))
* ___V*___ (***V+***, ***VDagger***, ***VPlus***)
* ***W*** (Rx(pi/4))
* ___W*___ (***W+***, ***WDagger***, ***WPlus***)
* ***S*** (Rz(pi/2), ***P***)
* ___S*___ (***S+***, ***SDagger***, ***SPlus***)
* ***T*** (Rz(pi/4))
* ___T*___ (***T+***, ***TDagger***, ***TPlus***)
* ***Swap***

qc::Gate クラスの主なメンバ関数を以下にまとめる．

|members|description|
|---|---|
|cbits_|コントロールビットのリスト (private member variable)|
|tbits_|ターゲットビットのリスト (private member variable)|
|get_type_name|ゲート名を取得する (public member function)|
|get_cbits|コントロールビットの集合を取得する (public member function)|
|get_tbits|ターゲットビットの集合を取得する (public member function)|
|set_cbits|コントロールビットの集合をセットする (public member function)|
|set_tbits|ターゲットビットの集合をセットする (public member function)|
|add_cbit|コントロールビットを追加する (public member function)|
|add_tbit|ターゲットビットを追加する (public member function)|
|has_bit|ビットを含んでいるか確認する (public member function)|
|has_cbit|コントロールビットを含んでいるか確認する (public member function)|
|has_tbit|ターゲットビットを含んでいるか確認する (public member function)|
|erase_bit|ビットを削除する (public member function)|
|collect_bits|使用しているビット番号の集合を生成する (public member function)|
|is_controlled|制御ゲートか確認する (public member function)|
|is_single_controlled|1-制御ゲートか確認する (public member function)|
|is_multi_controlled|n-制御ゲートか確認する (public member function)|
|is_single_target|1-標的ゲートか確認する (public member function)|
|is_multi_target|n-標的ゲートか確認する (public member function)|
|is_single_qubit_rotation|1量子ビット回転ゲートか確認する (public member function)|
|is_all_positive|全てのコントロールビットの極性が正か確認する (public member function)|
|print|ストリームに出力する (public member function)|

### qc::Circuit クラス
###### "qc/circuit.hpp"
量子回路を実装しているクラス．
  
qc::Gate をリストで保持している．

```cpp
auto circuit = qc::Circuit();
circuit.add_gate(x);
```

qc::Circuit クラスの主なメンバ関数を以下にまとめる．

|members|description|
|---|---|
|description_|説明文 (private member variable)|
|gates_|ゲートのリスト (private member variable)|
|get_description|説明文を取得する (public member function)|
|set_description|説明文をセットする (public member function)|
|get_gates|ゲートのリストを取得する (public member function)|
|set_gates|ゲートのリストをセットする (public member function)|
|add_gate|ゲートを末尾に追加する (public member function)|
|insert_gate|ゲートを任意の位置に挿入する (public member function)|
|erase_gate|指定した位置のゲートを削除する (public member function)|
|remove_gate|ゲートを削除する (public member function)|
|remove_gate_if|条件を満たすゲートを削除する (public member function)|
|move_gate|ゲートを移動する (public member function)|
|swap_gate|ゲートを入れ替える (public member function)|
|begin_gates|ゲートのリストの先頭のイテレータを取得する (public member function)|
|end_gates|ゲートのリストの末尾のイテレータを取得する (public member function)|
|cbegin_gates|ゲートのリストの先頭のイテレータ (const) を取得する (public member function)|
|cend_gates|ゲートのリストの末尾のイテレータ (const) を取得する (public member function)|
|extend|連結する (public member function)|
|clear|ゲートを全て削除する (public member function)|
|empty|ゲートが存在しないか確認する (public member function)|
|get_gate_count|ゲート数を取得する (public member function)|
|collect_bits|使用しているビット番号の集合を生成する (public member function)|
|print|ストリームに出力する (public member function)|

### qc::Group クラス
###### "qc/gate/group.hpp"
複数の qc::Gate をグループとして扱うためのクラス．
  
qc::Gate をリストで保持しており，qc::Circuit と同様のメンバを持っている．
qc::Group 自体も qc::Gate を継承しており，qc::Circuit のゲートのリストの要素として扱うことが可能．

```cpp
auto group = qc::Group(x);
group.add_gate(h);
circuit.add_gate(group);
```

直接 qc::Gate オブジェクトを生成する場合は，qc::Gate::make() または，***qc::Group::make()*** を利用する．

```cpp
auto group = qc::Group::make();
group.add_gate(h);
```

上記の例で，qc::Gate オブジェクトに対して add_gate() が呼べていることに注意すべきである．
これは，qc::Gate が qc::Circuit と同様のメソッドを持っているためである．
そのため，以下のようなコードのコンパイルは通ってしまう．

```cpp
auto x = qc::X(tbit);
x.add_gate(x); // コンパイルは通る
```

しかし，このようなコードは実行時に (NODEBUG マクロを定義していなければ) アサーションが発生する．
qc::Gate オブジェクトに対して add_gate() などのメソッドを呼ぶときには，***qc::is_group()*** を使うべきである．

```cpp
if(qc::is_group(gate)) gate.add_gate(x);
```

### アルゴリズム
###### "qc/algorithm.hpp"
量子回路に関するアルゴリズムを実装した関数がまとめられている．

|functions|description|
|---|---|
|get_cbit|1-制御ゲートのコントロールビットを取得する|
|get_tbit|1-標的ゲートのターゲットビットを取得する|
|add_gate_front|回路やグループの先頭にゲートを追加する|
|add_gate_back|回路やグループの末尾にゲートを追加する|
|insert_gate_before|回路やグループの pos の直前にゲートを挿入する|
|insert_gate_after|回路やグループの pos の直後にゲートを挿入する|
|decomp_to_single_target_gates|全てのゲートを1-標的ゲートに分解する|
|collect_cbits|コントロールビットのビット番号の集合を生成する|
|collect_tbits|ターゲットビットのビット番号の集合を生成する|
|is_mct_circuit|MCT (Multi-Control Toffoli) のみで構成された回路か確認する|
|is_esop_circuit|ESOP (Exclusive Sum-of-Products) 形式に変換可能な回路か確認する|
|get_mct_cost|[MCT のコスト][arXiv:quant-ph/0403053]を取得する|
|calculate_mct_circuit_cost|MCT 回路の総コストを計算する|
|sort_gates_by_cbits|コントロールビットで回路をソートする|
|sort_gates_by_tbits|ターゲットビットで回路をソートする|
|sort_gates|回路をソートする|
|decomp_to_single_target_circuits|1-出力回路に分解する|
|is_group|ゲートがグループか確認する|
|has_group|回路やグループ内にグループが存在するか確認する|
|remove_empty_groups|回路やグループ内の空のグループを全て削除する|
|expand_groups|回路やグループ内のグループを展開する|

### 入出力
###### "qc/io.hpp"
***qc::io*** に IO 関連の機能がまとめられている．

```cpp
auto circuit = qc::io::open(filename);
qc::io::input(circuit, filename);
qc::io::output(circuit, filename);
```
拡張子からファイル形式を判断する．
  
対応しているファイル形式は以下の通り．
* qo
* esop
* [blif][blif] (入力は nand2 のみ)

[cmake]: https://cmake.org/
[blif]: https://www.cse.iitb.ac.in/~supratik/courses/cs226/spr16/blif.pdf
[arXiv:quant-ph/0403053]: https://arxiv.org/pdf/quant-ph/0403053v1.pdf
