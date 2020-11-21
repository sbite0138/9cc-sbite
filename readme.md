## About
[低レイヤを知りたい人のためのCコンパイラ作成入門](https://www.sigbus.info/compilerbook)を参考に作った、C(のサブセットの)コンパイラです。  
現在使える主な機能は次のとおりです。  
- [x] for,if,whileなどの基本構文  
- [x] 変数、一次元配列、ポインタ(int/char)  
- [x] 関数定義/呼び出し  
- [x] +-/\*などの基本的な演算  
- [x] 多次元配列  

より詳しくは`test/test*.c`、`examples/*.c`をご覧ください。  

次の機能はこれから実装する予定です。  
- [ ] 構造体  
- [ ] ブロックスコープ  

## Usage
    $ make
    $ ./9cc path/to/your/code > asm.s
    $ gcc -static -o prog asm.s
    $ ./prog
または  

    $ make  
    $ ./run.sh path/to/your/code

## Examples
- 9bf.c : brain*uckのインタプリタ
- sudoku.c : 数独ソルバ
- fib.c : 再帰によってフィボナッチ数列を求めるプログラム

