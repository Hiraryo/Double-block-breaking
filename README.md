<h3 align="center">普通じゃない『ブロック崩し』</h3>
<h1 align="center">取扱説明書</h1>
<h2 align="center">ごあいさつ</h2>
このたびはMac OS専用ゲームソフト「普通じゃない『ブロック崩し』」をお求めいただきまして、誠にありがとうございます。<br>
ご使用前に、この「取扱説明書」をよくお読みいただき、正しい使用方法でご愛用ください。なお、この「取扱説明書」は大切に保管してください。

# CONTENTS
- [ご使用いただく前に]()
- [使用方法]()
- [操作方法]()
- [対応OS]()
- [著作権について]()
- [免責事項]()
- [クレジット（順不同）]()

## ご使用いただく前に
- [はじめに]()
- [安全に使用していただくために・・・]()
- [セット内容]()

<h2 align="center">はじめに</h2>

**本作の特徴**
- 大学1回生の基礎プログラミング演習の自由制作課題で作ったゲーム作品です。
- 見た目はよくあるブロック崩しですが、遊び方は普通ではありません。
- 独自のゲームロジックです。

<h2 align="center">安全に使用していただくために・・・</h2>

-  **健康上のご注意（必ずお読みください） 健康上の安全のため、ご使用にあたって特に次の点にご注意ください。**
1.  健康のため、ゲームをお楽しみになるときは、部屋を明るくして使用してください。特に小さなお子様が遊ばれるときは、保護者の方の目の届くところで遊ばせるようにしてください。<br><br>
2.  疲れた状態での使用、連続して長時間にわたる使用は、健康上好ましくありませんので避けてください。また、ゲームをするときは適度に休憩をとってください。目安として1時間ごとに10〜15分の小休憩をおすすめします。<br><br>
3.  ごくまれに、強い光の刺激や、点滅を受けたり、テレビの画面などを見たりしているときに、一時的に筋肉のけいれんや意識の喪失などを経験する人がいます。こうした症状を経験した人は、ゲームをする前に必ず医師と相談してください。また、ゲーム中にこのような症状が起きた場合には、直ちにゲームを中止し、医師の診察を受けてください。<br><br>
4.  ゲーム中にめまい・吐き気・疲労感・乗り物酔いに似た症状などを感じたり、目や手・腕に疲労、不快や痛みを感じたときは、直ちにゲームを中止してください。その後も不快感が続いている場合は医師の診察を受けてください。それを怠った場合、長期にわたる障害を引き起こす可能性があります。<br><br>
5.  他の要因により、手や腕の一部に障害が認められたり、疲れている場合は、ゲームをすることによって、症状が悪化する可能性があります。そのような場合は、ゲームをする前に医師に相談してください。<br><br>
6.  ステレオヘッドホンを使用して大音量で長時間聞いていると難聴になる恐れがあります。呼びかけられて返事ができるくらいの音量で使用してください。もし、耳の疲労や耳鳴りのような異常に気づいたら一旦使用を中止し、その後も耳鳴りのような異常が続いている場合は医師の診察を受けてください。<br><br>

<h2 align="center">セット内容</h2>

root/<br>
　┣━ Graphics/　←本作で使用する画像ファイルが入っています。<br>
　┣━ Scripts/　←本作のプログラムファイルが入っています。<br>
　┣━ Sounds/　←本作で使用する音楽ファイルが入っています。<br>
　┣━ StageDatas/　←ブロックの配置を記述したファイルが入っています。<br>
　┗━ README.md　←本作の取扱説明書です。

## 使用方法
- ゲームの流れ

- ゲームの始め方
- ミスとゲームオーバー
- ゲームの終了方法

## 操作方法
|アクション|キー| 
|:----:|:----:|
|開始 or 決定|スペースキー|
|終了|Qキー|
|画面下のバーを右に移動させる|Jキー|
|画面下のバーを左に移動させる|Fキー| 

## 対応OS
Mac OS<br>
Handy Graphic (version 0.8.3)は、IntelおよびApple M1に対応しています。<br>
Handy Graphicの詳細については[こちら](http://www.cc.kyoto-su.ac.jp/~ogihara/Hg/)をご覧ください。

## 著作権について
本作に使用している素材やデータ等には全て著作権があります。素材やデータ等の改造、転載及び流用、二次配布等を禁止します。<br>
ただし、フリー素材に関しては各著作者の利用規約に従えば使用可能な場合があります。

## 免責事項
本作の利用にあたって、何らかの不具合やトラブルが生じたとしても、平井崚太は一切の責任を負いません。<br>
自己責任でご利用ください。

## クレジット（順不同）
- メインプログラミング
    - 平井　崚太

- ゲームプログラミング
    - 平井　崚太

- BGM提供
    - [DOVA-SYNDROME](https://dova-s.jp/) 様
    - まっすー 様

- SE制作
    - 平井　崚太

- 画像制作
    - 平井　崚太


## ブロックの2次元配列と表示手法について
![Secondary array](https://user-images.githubusercontent.com/60394438/122278895-65e0c880-cf22-11eb-946b-17ed224001a3.png)
```C
//ブロック表示
layerID_block = HgLSwitch(&layers_block);
HgLClear(layerID_block);
for(i = 0; i < block_no; i ++){
    for(j = 0; j< block_no; j ++){
        if (block_array[i][j] != 0){
            HgWSetFillColor(layerID_block,HG_RED);
            HgWSetColor(layerID_block,HG_WHITE);
            HgWSetWidth(layerID_block,2.0);
            HgWBoxFill(layerID_block,(j+1) * BLOCK_X_START + block_space_w, (i+1) * BLOCK_Y_START + block_space_h - (460 * i),BLOCK_WIDTH,BLOCK_HEIGHT,1);
        }
    }
}
```
#### 描画のための設定について
##### 線の太さ
>何も指定しない場合、図形の線の太さは１画素分ですが、これを変更することができます。いったん太さを変更すると、別の指定があるまではその値が使われます。
<br>＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/<br>
int HgSetWidth(double t)<br>
<u>引数</u>　　t:　線の太さ<br>
<u>返り値</U>　0: 　正常、  -1:　異常
<br>＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/<br>
線の太さの指定は、直線、円、長方形などの図形に共通して有効です。

[Handy Graphicユーザーズガイド](http://www.cc.kyoto-su.ac.jp/~ogihara/Hg/products/guide0.80.pdf)より引用

##### 図形の色の指定
>図形を描くのに使われる色を指定することができます。色はhgcolor型というデータ型で指定しますが、よく使われる色はマクロで定義されています（[表１](https://github.com/Hiraryo/Double-block-breaking/blob/develop/README.md#%E8%A1%A8%EF%BC%91%E8%89%B2%E3%81%AE%E3%83%9E%E3%82%AF%E3%83%AD%E5%AE%9A%E7%BE%A9)）。
描かれる線の色を指定するには次の関数を使います。いったん色を指定すると、別の色を指定するまで同じ色が使われます。一度も指定しない場合は黒で描かれます。
<br>＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/<br>
int HgSetColor(hgcolor clr)<br>
<u>引数</u>　 clr:　色の指定<br>
<u>返り値</U>　0: 　正常、  -1:　異常
<br>＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/＿/<br><br>
下で説明する円や長方形では内部を塗りつぶすことができます。このような図形を**塗りつぶし図形**と呼びますが、塗りつぶしに使う線を描くための色とは別に、次の関数を使って指定します。いったん色を指定すると、別の色を指定するまで同じ色が使われます。一度も指定しない場合は白で塗りつぶされます。
<br>・・・・・・・・・・・・・・・・・・・<br>
int HgSetFillColor(hgcolor clr)<br>
<u>引数</u>　 clr:　色の指定<br>
<u>返り値</U>　0: 　正常、  -1:　異常
<br>・・・・・・・・・・・・・・・・・・・

[Handy Graphicユーザーズガイド](http://www.cc.kyoto-su.ac.jp/~ogihara/Hg/products/guide0.80.pdf)より引用

#### 表１：色のマクロ定義
> |色|マクロ名|色|マクロ名|色|マクロ名|色|マクロ名|
> |:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
> |白|HG_WHITE|赤|HG_RED|シアン|HG_CYAN|空色|HG_SKYBLUE
> |黒|HG_BLACK|緑|HG_GREEN|オレンジ|HG_ORANGE|濃赤色|HG_DRED
> |灰色|HG_GRAY|青|HG_BLUE|ピンク|HG_PINK|濃緑色|HG_DGREEN
> |淡灰色|HG_LGRAY|黄|HG_YELLOW|マゼンタ|HG_MAGENTA|濃青色|HG_DBLUE|
> |濃灰色|HG_DGRAY|紫|HG_PURPLE|茶|HG_BROWN|透明|HG_CLEAR|
[Handy Graphicユーザーズガイド](http://www.cc.kyoto-su.ac.jp/~ogihara/Hg/products/guide0.80.pdf)より引用
<br>
#### 描画関数について
##### 長方形
>int HgBoxFill(double x, double y, double w, double h, int stroke)<br>
<u>引数</u>　　x,y:　左下隅の座標　　w,h:　幅と高さ　　stroke:　周囲を描くかどうか<br>
<u>返り値</U>　0: 　正常、  -1:　異常<br>------------------------------------------------------------------------------<br>
HgBoxFill()は、座標(x,y)を左下隅とする幅w、高さhの塗りつぶされた長方形を描きます。塗りつぶしにはHgSetFillColor()で指定した色が使われます。引数strokeが0の場合は周囲に長方形を描きません。0以外の値(例えば1)の場合、他の線図形と同じ太さ、同じ色の線で長方形を描きます。<br>
左下隅の座標はウィンドウの外部の点でも構いません。幅と高さは w ≥ 0.0, h ≥ 0.0の実数値です。

[Handy Graphicユーザーズガイド](http://www.cc.kyoto-su.ac.jp/~ogihara/Hg/products/guide0.80.pdf)より引用

## 座標と変数について
![Coordinates and variables](https://user-images.githubusercontent.com/60394438/122274121-2d8abb80-cf1d-11eb-9a67-fb557f011995.png)

## ブロックの当たり判定について
```C
//ブロックの当たり判定
if (ball_y >= 500){
    block_line_x = ((ball_y % 500) / 40);   //ボールが今何列目にあるのかを計算
}
if (ball_x >= 100){
    block_line_y = (ball_x / 100 - 1);    //ボールが今何行目にあるのかを計算
}
if (ball_y >= BLOCK_Y_START && ball_y <= (BLOCK_HEIGHT * block_no) + (block_space_h * (block_no - 1)) + BLOCK_Y_START){    //ブロックの上またはブロックの下に当たった場合
    if (block_line_x <= 5 && block_line_y <= 5){
        if (block_array[block_line_x][block_line_y] != 0){
            ball_dy *= -1;
            block_array[block_line_x][block_line_y] = 0;
            score += 100;
            block_num -= 1;
            HgSoundPlay(SE_1);
        }
    }
}
```
本作の当たり判定は、ブロックの2次配列の値とボールのXY座標の値で判定を行なっております。

## 📷 Screenshot
## タイトル画面
![title](https://user-images.githubusercontent.com/60394438/106357876-3f900700-634c-11eb-9cb7-9a76f136693e.gif)

## ゲーム画面
![main](https://user-images.githubusercontent.com/60394438/121796143-e87f3480-cc51-11eb-823f-e8ad1aca1d5c.gif)

## エンディング画面
![ending](https://user-images.githubusercontent.com/60394438/121797040-94c41980-cc58-11eb-8a05-406b0b5d83c6.gif)
