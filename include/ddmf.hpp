/** \file
 *  \brief DDMFを計算するためのクラスを定義する。
 */

#ifndef __DDMF_HPP__
#define __DDMF_HPP__

#include <list>
#include <string>
#include <complex>

#include <assert.h>
#include <iostream>
#include <fstream>
#include <float.h>

class DDMF;
class Matrix;
class Variable;
class DDMFMgr;
class Node;
class OpCache;

/** \class DDMFMgr
 *  \brief DDMFを管理するクラス
 */
class DDMFMgr {
 private:
  /** \var static const int APPLY_AND
   *  \brief apply関数をAND演算で呼び出すための定数。
   *  \see apply()
   *
   *  apply関数の第一引数に渡し、AND演算であることを示す。
   */
  static const int APPLY_AND = 1;

  /** \var static const int APPLY_XOR
   *  \brief apply関数をXOR演算で呼び出すための定数。
   *  \see apply()
   *
   *  apply関数の第一引数に渡し、XOR演算であることを示す。
   */
  static const int APPLY_XOR = 2;

  /** \var std::list<Variable *> vars
   *  \brief DDMFで管理されている変数(Variable クラスのインスタンス)のリスト
   */
  std::list<Variable*> vars;

  /** \var int variable_counter
   *  \brief DDMFで管理されている変数の数
   */
  int variable_counter;

  /** \var int hash_size
   *  \brief DDMFで管理されているノードハッシュのサイズ
   */
  int hash_size;

  /** \var size_t hash_count
   *  \brief DDMFで管理されているノードハッシュに入っているノードの数
   */
  size_t hash_count;

  /** \var std::list<Node*>* hash_table
   *  \brief DDMFで管理されているノードハッシュ
   */
  std::list<Node*>* hash_table;

  /** \var int opCacheSize
   *  \brief DDMFで管理されている演算ハッシュのサイズ
   */
  int opCacheSize;

  /** \var OpCache** opCacheTable
   *  \brief DDMFで管理されている演算ハッシュ
   */
  OpCache** opCacheTable;

  /** \var int gc_type
   *  \brief ガベージコレクションの種別
   *
   *  ガベージコレクションの種別 : GC_TYPE_LIST_SIZE
   *                               (どこか一つのハッシュエントリに対して閾値以上のノードが挿入された場合)
   *                             : GC_TYPE_NODE_MEMSIZE
   *                               (ノードが使用するメモリ量が閾値を越えた場合)
   *                             : GC_TYPE_0LINK_SIZE
   *                               (参照リンクが0のノードが閾値を越えた場合)
   */
  int gc_type;

  /** \var size_t th_size
   *  \brief 閾値
   *
   *  ガベージコレクションが動作する際の閾値
   */
  size_t th_size;

  /** \var int th_ratio
   *  \brief 閾値の割合
   *
   *  ガベージコレクションが動作する際の閾値の割合。gc_type =
   *  GC_TYPE_NODE_MEMSIZE のとき、ガベージコレクションが動作する際
   *  の閾値は、\f$th\_size \times th\_ratio / 100\f$ となる。th_ratioは最
   *  初 90 で、ガベージコレクションによりノード数が減らない場合には
   *  1 増える。ガベージコレクションによりノード数が減ると 90 に戻る。
   *  th_ratio が 100 を越えると例外が発生する。
   */
  int th_ratio;

  /** \var size_t zero_node_counter
   *  \brief 参照リンク数が0となっているノードの数
   */
  size_t zero_node_counter;

  /** \var int gc_stopper
   *  \brief ガベージコレクション再帰実行数
   *
   *  ガベージコレクションが必要以上に再帰実行されること防ぐ。
   */
  int gc_stopper;

  /** \fn Node* getNode(Variable* var, Node* node1, Node* node0, Matrix matrix1)
   *  \brief ノードを生成する。
   *  \param var [in]     生成するノードのトップの変数
   *  \param node1 [in]   生成するノードの1-枝のノード
   *  \param node0 [in]   生成するノードの0-枝のノード
   *  \param matrix1 [in] 生成するノードの1-枝の行列
   *  \return 生成されたノード
   *
   *  指定された、トップの変数、1-枝のノード、0-枝のノード、1-枝の行列
   *  を持つノードを生成する。既にノードハッシュに存在するときは、
   *  そのノードへのポインタを返す。
   */
  Node* getNode(Variable* var, Node* node1, Node* node0, Matrix matrix1);

  /** \fn void deleteNode(Node* node)
   *  \brief 指定されたノードをノードハッシュから削除する
   *  \param node [in] 削除するノード
   */
  void deleteNode(Node* node);

  /** \fn unsigned int calcHash(char* hash_string, int string_length) const
   *  \brief ハッシュ値の計算(引数は、ハッシュを計算する文字列と文字長)
   *  \param hash_string [in] ハッシュを求める文字列
   *  \param string_length [in] ハッシュを求める文字列の長さ
   *  \return ハッシュ値
   *
   *  指定された文字列からハッシュ値を計算する
   */
  unsigned int calcHash(char* hash_string, int string_length) const;

  /** \fn DDMF apply(int op, const DDMF& ddmf1, const DDMF& ddmf2)
   *  \brief DDMF間の演算を行う
   *  \param op [in] 演算種別を指定する
   *  \param ddmf1 [in] 演算の左辺
   *  \param ddmf2 [in] 演算の右辺
   *  \return 演算結果
   *
   *  ddmf1, ddmf2を指定された演算種別で演算し、結果を返す。
   */
  DDMF apply(int op, const DDMF& ddmf1, const DDMF& ddmf2);

  /** \fn bool opCache(int op, const DDMF& ddmf1, const DDMF& ddmf2, DDMF&
   *ret_ddmf) const
   *  \brief 演算キャッシュに存在すれば true, なければ false.
   *存在する場合は結果を返す
   *  \param op [in] 演算種別
   *  \param ddmf1 [in] 演算の左辺
   *  \param ddmf2 [in] 演算の右辺
   *  \param ret_ddmf [out] 演算結果
   *  \return 演算が存在するかどうか
   *
   *  ddmf1, ddmf2を指定された演算種別で演算した結果が演算キャッシュ
   *  に存在するかどうか。
   */
  bool opCache(int op, const DDMF& ddmf1, const DDMF& ddmf2,
               DDMF& ret_ddmf) const;

  /** \fn void opCacheRegister(int op, const DDMF& ddmf1, const DDMF& ddmf2,
   *DDMF& regist_ddmf)
   *  \brief 演算キャッシュに演算結果を登録
   *  \param op [in] 演算種別
   *  \param ddmf1 [in] 演算の左辺
   *  \param ddmf2 [in] 演算の右辺
   *  \param regist_ddmf [in] 演算結果
   *
   *  演算種別、ddmf1, ddmf2、指定された演算種別で演算した結果を演算
   *  キャッシュに登録する。
   */
  void opCacheRegister(int op, const DDMF& ddmf1, const DDMF& ddmf2,
                       DDMF& regist_ddmf);

  /** \fn void opCacheClear()
   *  \brief 演算キャッシュをすべてクリア(無効に)する。
   */
  void opCacheClear();

 public:
  /** \fn int garbageCollection()
   *  \brief ガベージコレクションを行う
   *  \return 削除されたノード数
   *
   *  gc_type に従い、ノード生成時、あるいはノード削除時にガベージコ
   *  レクションを行う。
   */
  int garbageCollection();

  /** \fn DDMFMgr(int size, int opSize, int _gc_type, int _th_size)
   *  \brief
   * コンストラクタ。ノードハッシュサイズ、演算キャッシュサイズ、ガベージコレクション種別、閾値を指定
   *  \param size [in] ノードハッシュのサイズ
   *  \param opSize [in] 演算キャッシュのサイズ
   *  \param _gc_type [in] ガベージコレクションの種別
   *  \param _th_size [in] 閾値
   */
  DDMFMgr(int size, int opSize, int _gc_type, int _th_size);

  /** \fn DDMF ddmfVar()
   *  \brief 1変数のDDMFを返す
   *  \return 生成されたDDMF
   *
   *  1変数のDDMFを返す。新しい変数を生成し、その変数をトップの変数、
   *  1-枝のノードを行列 I、0-枝のノードを行列 I、1-枝の行列を N とする
   *  DDMFを生成し、そのDDMFを返す。
   */
  DDMF ddmfVar();

  /** \var static const int GC_TYPE_LIST_SIZE
   *  \brief ガベージコレクションの種別 :
   * どこか一つのハッシュエントリに対して閾値以上のノードが挿入された場合
   */
  static const int GC_TYPE_LIST_SIZE = 0;

  /** \var static const int GC_TYPE_NODE_MEMSIZE
   *  \brief ガベージコレクションの種別 :
   * ノードが使用するメモリ量が閾値を越えた場合
   */
  static const int GC_TYPE_NODE_MEMSIZE = 1;

  /** \var static const int GC_TYPE_0LINK_SIZE
   *  \brief ガベージコレクションの種別 :
   * 参照リンクが0のノードが閾値を越えた場合
   */
  static const int GC_TYPE_0LINK_SIZE = 2;
  friend class DDMF;
  friend class Node;
};

/** \class Matrix
 *  \brief 行列クラス
 *
 *  行列クラス
 */
class Matrix {
 private:
  /** \var int type
   *  \brief 行列の値 I, N, V, V\f$^{-1}\f$, とG の4種類
   */
  int type;

  /** \var std::complex type
   *  \brief 行列の各要素。ただし, type とは同期しない
   */
  std::complex<double> a[2][2];

  /** \fn int getFingerPrint() const
   *  \brief 行列のハッシュ値を返す
   *  \return ハッシュ値
   */
  int getFingerPrint() const;

 public:
  /** \fn Matrix& operator=(const Matrix& matrix)
   *  \brief コピー代入演算の定義
   *  \param matrix [in] コピー元の行列
   *  \return 行列
   */
  Matrix& operator=(const Matrix& matrix);

  /** \fn Matrix(const Matrix & matrix)
   *  \brief コピーコンストラクタ
   *  \param matrix [in] コピー元の行列
   */
  Matrix(const Matrix& matrix);

  /** \fn Matrix(int mtype)
   *  \brief コンストラクタ type 指定
   *  \param mtype [in] 行列種別
   *
   *  行列種別を指定して、行列クラスのインスタンスを生成する。
   */
  Matrix(int mtype);

  /** \fn Matrix()
   *  \brief コンストラクタ
   *
   *  行列 I を生成する。
   */
  Matrix();

  /** \fn Matrix(double a, double b, double c, double d)
   *  \brief コンストラクタ
   *
   *  (e1,e2,e3,e4)を要素とする行列を生成する。
   */
  Matrix(double e1, double e2, double e3, double e4);

  /** \fn Matrix(std::complex<double> e1, std::complex<double> e2,
   *std::complex<double> e3, std::complex<double> e4)
   *  \brief コンストラクタ
   *
   *  (a,b,c,d)を要素とする行列を生成する。
   */
  Matrix(std::complex<double> e1, std::complex<double> e2,
         std::complex<double> e3, std::complex<double> e4);

  /** \fn void print(std::ostream& os, std::string nest) const
   *  \brief 行列のタイプを表示
   *  \param os [in] 出力ストリーム
   *  \param nest [in] 接頭文字列
   *
   *  先頭に接頭文字列を出力する。
   */
  void print(std::ostream& os, std::string nest) const;

  /** \fn void print_qo(std::ostream& os) const
   *  \brief 行列の内容をqoファイルフォーマットの
   *  \brief General Gate用に出力
   *  \param os [in] 出力ストリーム
   *
   */
  void print_qo(std::ostream& os) const;

  /** \fn DDMF operator*(const DDMF& ddmf) const
   *  \brief (行列) \f$\times\f$ (DDMF) の演算を行う。
   *  \param ddmf [in] 演算を行う DDMF
   *  \return 演算結果
   */
  DDMF operator*(const DDMF& ddmf) const;

  /** \fn bool operator==(const Matrix& matrix) const
   *  \brief 行列同士の同値性を判定する
   *  \param matrix [in] 行列
   *  \return 同値かどうかのブール値
   */
  bool operator==(const Matrix& matrix) const;

  /** \fn Matrix operator*(const Matrix& matrix) const
   *  \brief (行列) \f$\times\f$ (行列) の演算を行う。
   *  \param matrix [in] 演算を行う行列
   *  \return 演算結果
   */
  Matrix operator*(const Matrix& matrix) const;

  /** \fn Matrix operator~() const
   *  \brief 逆行列を返す
   *  \return 逆行列
   */
  Matrix operator~() const;

  /** \var static const int TYPE_I
   *  \brief 行列 I を表す定数
   */
  static const int TYPE_I = 0;

  /** \var static const int TYPE_V
   *  \brief 行列 V を表す定数
   */
  static const int TYPE_V = 1;

  /** \var static const int TYPE_N
   *  \brief 行列 N を表す定数
   */
  static const int TYPE_N = 2;

  /** \var static const int TYPE_VI
   *  \brief 行列 V\f$^{-1}\f$ を表す定数
   */
  static const int TYPE_VI = 3;

  /** \var static const int TYPE_G
   *  \brief 任意の行列を表す定数
   */
  static const int TYPE_G = 4;
  friend class DDMFMgr;
};

/** \class DDMF
 *  \brief DDMFクラス
 *
 *  DDMFクラス
 */
class DDMF {
 private:
  /** \var DDMFMgr *mgr
   *  \brief 属している DDMFMgr クラスへのポインタ
   */
  DDMFMgr* mgr;

  /** \var Matrix matrix
   *  \brief 最上位ノードにかかっている行列
   */
  Matrix matrix;

  /** \var Node* node
   *  \brief 最上位ノード
   */
  Node* node;

  /** \fn void printMatrix(std::ostream& os, std::list<Variable *>* vars,
   *std::list<Variable *>::iterator iter, std::string values, Matrix matrix,
   *Node *node) const;
   *  \brief DDMFの内容表示
   *  \param os [in] 出力ストリーム
   *  \param vars [in] 変数リスト
   *  \param iter [in] イテレータ
   *  \param values [in] 変数文字列
   *  \param matrix [in] 行列
   *  \param node [in] ノード
   *  \see print()
   *
   *  printからのみ呼び出される。
   */
  void printMatrix(std::ostream& os, std::list<Variable*>* vars,
                   std::list<Variable*>::iterator iter, std::string values,
                   Matrix matrix, Node* node) const;

  /** \fn DDMF(DDMFMgr *_mgr, Variable *var)
   *  \brief コンストラクタ。変数で指定された DDMF を生成
   *  \param _mgr [in] DDMFMgrへのポインタ
   *  \param var  [in] 指定する変数へのポインタ
   *
   *  1変数のDDMFを返す。指定された変数をトップの変数、1-枝のノード
   *  を行列 I、0-枝のノードを行列 I、1-枝の行列を N とするDDMFを生
   *  成し、そのDDMFを返す。
   */
  DDMF(DDMFMgr* _mgr, Variable* var);

  /** \fn DDMF(DDMFMgr *_mgr, Matrix _matrix, Node *_node)
   *  \brief 行列と最上位ノードで指定された DDMF を生成
   *  \param _mgr [in] DDMFMgrへのポインタ
   *  \param _matrix [in] 指定する行列へのポインタ
   *  \param _node [in] 指定するノードへのポインタ
   *
   *  コンストラクタ。行列と、最上位ノードで指定された DDMF を生成する。
   */
  DDMF(DDMFMgr* _mgr, Matrix _matrix, Node* _node);

 public:
  /** \fn DDMF& operator=(const DDMF& ddmf)
   *  \brief コピー代入演算
   *  \param ddmf [in] コピー元のDDMF
   *  \return DDMF
   */
  DDMF& operator=(const DDMF& ddmf);

  /** \fn DDMF(const DDMF & ddmf)
   *  \brief コピーコンストラクタ
   *  \param ddmf [in] コピー元のDDMF
   */
  DDMF(const DDMF& ddmf);

  /** \fn DDMF(const DDMF & ddmf)
   *  \brief コンストラクタ
   */
  DDMF(DDMFMgr& DDMFmgr);

  /** \fn DDMF()
   *  \brief コンストラクタ
   */
  // DDMF();

  /** \fn ~DDMF()
   *  \brief デストラクタ
   */
  ~DDMF();

  /** \fn void print(std::ostream& os) const
   *  \brief DDMFの表示
   *  \param os [in] 出力ストリーム
   */
  void print(std::ostream& os) const;

  /** \fn DDMF operator*(const DDMF& ddmf) const
   *  \brief DDMF同士の AND 演算を行う
   *  \param ddmf [in] 演算を行うDDMF
   *  \return 演算結果
   */
  DDMF operator*(const DDMF& ddmf) const;

  /** \fn DDMF operator^(const DDMF& ddmf) const
   *  \brief DDMF同士の XOR 演算を行う
   *  \param ddmf [in] 演算を行うDDMF
   *  \return 演算結果
   */
  DDMF operator^(const DDMF& ddmf) const;

  /** \fn DDMF operator!() const
   *  \brief DDMFを反転する
   *  \return 反転されたDDMF
   */
  DDMF operator!() const;

  /** \fn DDMF operator*(const Matrix& _matrix) const
   *  \brief DDMFと行列をかけたものを返す
   *  \param _matrix [in] 行列
   *  \return 演算結果
   */
  DDMF operator*(const Matrix& _matrix) const;

  /** \fn   DDMF MatrixMultFromLeft(const Matrix& _matrix) const;
   *  \brief DDMFに行列を左からかけたものを返す
   *  \param _matrix [in] 行列
   *  \return 演算結果
   */
  DDMF MatrixMultFromLeft(const Matrix& _matrix) const;

  /** \fn bool operator==(const DDMF& ddmf) const
   *  \brief DDMF同士の同値性を判定する
   *  \param ddmf [in] DDMF
   *  \return 同値かどうかのブール値
   */
  bool operator==(const DDMF& ddmf) const;

  /** \fn void change_order(int var_no) const
   *  \brief var_noに対応する変数とvar_no+1に対応する変数を入れ替える
   *  \param var_no [in] 入れ替える変数の番号
   */
  void change_order(int var_no) const;

  /** \fn void change_order(int var_no1, int var_no2) const
   *  \brief DDMFのvar_no1とvar_no2に対応する変数を入れ替える
   *  \param var_no1 [in] 入れ替える変数の番号
   *  \param var_no2 [in] 入れ替える変数の番号
   */
  void change_order(int var_no1, int var_no2) const;

  friend class DDMFMgr;
  friend class Node;
  friend class OpCache;
  friend class Matrix;
};

/** \class Node
 *  \brief ノードクラス
 *
 *  ノードクラス
 */
class Node {
 private:
  /** \var DDMFMgr *mgr
   *  \brief DDMFMgrへのポインタ
   */
  DDMFMgr* mgr;

  /** \var Variable *var
   *  \brief ノードのトップの変数
   */
  Variable* var;

  /** \var Node *node1
   *  \brief 1-枝のノード
   */
  Node* node1;

  /** \var Node *node0
   *  \brief 0-枝のノード
   */
  Node* node0;

  /** \var Matrix matrix1
   *  \brief 1-枝の行列
   */
  Matrix matrix1;

  /** \var int link_count
   *  \brief ノードへの参照数
   */
  int link_count;

  /** \fn Node(DDMFMgr *_mgr, Variable* _var, Node* _node1, Node* _node0, Matrix
   * _matrix1)
   *  \brief コンストラクタ
   *  \param _mgr [in] 所属するDDMFMgrへのポインタ
   *  \param _var [in] トップの変数
   *  \param _node1 [in] 1-枝のノード
   *  \param _node0 [in] 0-枝のノード
   *  \param _matrix1 [in] 1-枝の行列
   */
  Node(DDMFMgr* _mgr, Variable* _var, Node* _node1, Node* _node0,
       Matrix _matrix1);

  /** \fn void print(std::ostream& os, std::string nest) const
   *  \brief 表示する
   *  \param os [in] 出力ストリーム
   *  \param nest [in] 接頭文字列
   *
   *  出力ストリームにノード情報を出力する。
   */
  void print(std::ostream& os, std::string nest) const;

  /** \fn ~Node()
   *  \brief デストラクタ
   */
  ~Node();

  /** \fn int inc_link()
   *  \brief 参照数をカウントアップ
   *  \return 現在(カウントアップ後)の参照数
   */
  int inc_link();

  /** \fn int dec_link()
   *  \brief 参照数をカウントダウン
   *  \return 現在(カウントダウン後)の参照数
   */
  int dec_link();

  /** \fn Node& operator=(const Node& node)
   *  \brief コピー代入演算
   *  \param node [in] コピー元のノード
   *  \return ノード
   */
  Node& operator=(const Node& node);

  /** \fn Node(const Node & node)
   *  \brief コピーコンストラクタ
   *  \param node [in] コピー元のノード
   */
  Node(const Node& node);

 public:
  bool operator==(const Node& node) const;
  friend class DDMFMgr;
  friend class DDMF;
  friend class OpCache;
};

/** \class Variable
 *  \brief 変数クラス
 *
 *  変数クラス
 */
class Variable {
 private:
  /** \fn int no
   *  \brief 変数番号
   */
  int no;

  /** \fn Variable(int var_no)
   *  \brief コンストラクタ
   *  \param var_no [in] 変数番号
   *
   *  変数番号を指定して呼び出す。
   */
  Variable(int var_no);

  /** \fn void print(std::ostream& os, std::string nest) const
   *  \brief 表示
   *  \param os [in] 出力ストリーム
   *  \param nest [in] 接頭文字列
   *
   *  変数を表示。先頭に接頭文字列を出力する。
   */
  void print(std::ostream& os, std::string nest) const;

  /** \fn bool operator==(const Variable& var) const
   *  \brief 変数同士の同値性を判定する
   *  \param var [in] 変数
   *  \return 同値かどうかのブール値
   */
  bool operator==(const Variable& var) const;

  /** \fn bool operator<(const Variable& var) const
   *  \brief 変数同士の大小関係を判定する
   *  \param var [in] 変数
   *  \return 左辺が小さいかどうかのブール値
   */
  bool operator<(const Variable& var) const;

  /** \fn Variable& operator=(const Variable& var)
   *  \brief コピー代入演算
   *  \param var [in] コピー元の変数
   *  \return ノード
   */
  Variable& operator=(const Variable& var);

  /** \fn Variable(const Variable & var)
   *  \brief コピーコンストラクタ
   *  \param var [in] コピー元の変数
   */
  Variable(const Variable& var);

 public:
  friend DDMF DDMFMgr::ddmfVar();
  friend class DDMFMgr;
  friend class Node;
  friend class DDMF;
};

/** \class DDMFErr
 *  \brief 例外クラス
 *
 *  例外クラス
 */
class DDMFErr {
 private:
  /** \var const char * str
   *  \brief エラーメッセージ
   */
  const char* str;

  /** \fn DDMFErr(const char * s) : str(s)
   *  \brief コンストラクタ
   *  \param s [in] エラーメッセージ
   *
   *  エラーメッセージを持つDDMFErrクラスのインスタンスを生成するコンストラクタ
   */
  DDMFErr(const char* s) : str(s){};

  /** \fn DDMFErr& operator=(const DDMFErr& err)
   *  \brief コピー代入演算
   *  \param err [in] コピー元のDDMFErr
   *  \return ノード
   */
  DDMFErr& operator=(const DDMFErr& err);

  /** \fn DDMFErr(const DDMFErr & err)
   *  \brief コピーコンストラクタ
   *  \param err [in] コピー元のDDMFErr
   */
  DDMFErr(const DDMFErr& err);

 public:
  /** \fn const char * get() const
   *  \brief エラーメッセージを取得する
   *  \return エラーメッセージ
   */
  const char* get() const { return str; };
  friend class DDMF;
  friend class DDMFMgr;
  friend class Matrix;
};

/** \class OpCache
 *  \brief 演算ハッシュクラス
 *
 *  演算ハッシュクラス
 */
class OpCache {
 private:
  /** \var int op
   *  \brief 演算の種類
   */
  int op;

  /** \var Node *ddmf1_node
   *  \brief 演算の右辺のDDMFのノードへのポインタ
   */
  Node* ddmf1_node;

  /** \var Matrix ddmf1_matrix
   *  \brief 演算の右辺のDDMFの行列
   */
  Matrix ddmf1_matrix;

  /** \var Node *ddmf2_node
   *  \brief 演算の左辺のDDMFのノードへのポインタ
   */
  Node* ddmf2_node;

  /** \var Matrix ddmf2_matrix
   *  \brief 演算の左辺のDDMFの行列
   */
  Matrix ddmf2_matrix;

  /** \var DDMF result_ddmf
   *  \brief 演算結果
   */
  DDMF result_ddmf;

  /** \fn OpCache(int _op, const DDMF& _ddmf1, const DDMF& _ddmf2, DDMF&
   * _result_ddmf)
   *  \brief コンストラクタ
   *  \param _op [in] 演算種別
   *  \param _ddmf1 [in] 演算子の左辺のDDMF
   *  \param _ddmf2 [in] 演算子の右辺のDDMF
   *  \param _result_ddmf [in] 演算結果のDDMF
   */
  OpCache(int _op, const DDMF& _ddmf1, const DDMF& _ddmf2, DDMF& _result_ddmf);

  /** \fn OpCache& operator=(const OpCache& opCache)
   *  \brief コピー代入演算
   *  \param opCache [in] コピー元の演算ハッシュクラス
   *  \return ノード
   */
  OpCache& operator=(const OpCache& opCache);

  /** \fn OpCache(const OpCache & opCache)
   *  \brief コピーコンストラクタ
   *  \param opCache [in] コピー元の演算ハッシュクラス
   */
  OpCache(const OpCache& opCache);
  friend class DDMFMgr;
};

#endif /* __DDMF_HPP__ */
