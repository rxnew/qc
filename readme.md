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
  
派生クラスとして，***qc::Cbit*** と ***qc::Tbit*** がある．
それぞれ，コントロールビットとターゲットビットに対応している．

```
auto cbit = Cbit(0, true);
auto tbit = Tbit(1);
```

qc::Bit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|no_|ビット番号 (private member variable)|
|get_no|ビット番号を取得する (public member function)|

qc::Cbit クラスの主なメンバを以下にまとめる．

|members|description|
|---|---|
|polarity_|コントロールビットの極性 (private member variable)|
|get_polarity|極性を取得する (public member function)|
|invert_polarity|極性を反転する (public member function)|

### qc::Gate クラス
量子ゲートを実装しているクラス．
ゲートの機能を提供する ***qc::GateKernel*** **抽象**クラスをポインタで保持している．
qc::GateKernel は qc::Cbit と qc::Tbit の集合を保持している．
  
qc::GateKernel の派生クラスを用いて各量子ゲート (e.g., X, T) を実装している．実装済みのゲートは以下の通り．

* ***U*** (任意のユニタリ行列)
* ***I*** (単位行列)
* ***H*** (***Hadamard***)
* ***X*** (パウリ行列, ***NOT***, ***Toffoli***, ***MCT***, ***MPMCT***)]
* ***Y*** (パウリ行列)
* ***Z*** (パウリ行列)
* ***V*** (Rx(pi/2))
* ___V*___ (***V+***, ***VDagger***, ***VPlus***)
* ***S*** (Rz(pi/2), ***P***)
* ___S*___ (***S+***, ***SDagger***, ***SPlus***)
* ***T*** (Rz(pi/4))
* ___T*___ (***T+***, ***TDagger***, ***TPlus***)
* ***Swap***

```
auto gate = qc::X(cbit, tbit);
```

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
|collect_bits|使用しているビットの集合を生成する (public member function)|
|is_controlled|制御ゲートか確認する (public member function)|
|is_single_controlled|1-制御ゲートか確認する (public member function)|
|is_multi_controlled|n-制御ゲートか確認する (public member function)|
|is_single_target|1-標的ゲートか確認する (public member function)|
|is_multi_target|n-標的ゲートか確認する (public member function)|
|is_single_qubit_rotation|1量子ビット回転ゲートか確認する (public member function)|
|is_all_positive|全てのコントロールビットの極性が正か確認する (public member function)|
|print|ストリームに出力する (public member function)|

### qc::Circuit クラス
量子回路を実装しているクラス．
qc::Gate をリストで保持している．

```
auto circuit = qc::Circuit();
circuit.add_gate(gate);
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
|collect_bits|使用しているビットの集合を生成する (public member function)|
|print|ストリームに出力する (public member function)|

### 入出力
***qc::io*** に IO 関連の機能がまとめられている．

```
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
