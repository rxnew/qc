QC (Quantum Circuit)
==============
This program is quantum circuit simulator.

Requirements
---------------
* g++ 4.9 or later
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
  
派生クラスとして，qc::Cbit と qc::Tbit がある．
それぞれ，コントロールビットとターゲットビットに対応している．

```
auto cbit = Cbit(0, true);
auto tbit = Tbit(1);
```

### qc::Gate クラス
量子ゲートを実装している**抽象**クラス．
Cbit と Tbit をリストで保持している．
  
派生クラスで各量子ゲート (e.g., X, T) を実装している．

```
auto gate = new X(cbit, tbit);
```

### qc::Circuit クラス
量子回路を実装しているクラス．
量子ゲートの**ポインタ**をリストで保持している．

```
auto circuit = qc::Circuit();
circuit.addGate(gate);
```

[cmake]: https://cmake.org/
