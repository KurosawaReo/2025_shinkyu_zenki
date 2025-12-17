<!-- 
   GitHubの表示を基準にするため、VScode上での表示とは異なる点に注意
-->

<p align="center">
  <img src="_readme_img/logo_all_black.png" width="500"><br>
</p>

---
## 操作説明
**キーボード**
<img src="_readme_img/lore_keyboard.png">
**Xboxコントローラ**
<img src="_readme_img/lore_xbox_controller.png">
<br>

---
## ゲーム概要
<img src="_readme_img/game_image.png">
<table>
    <tr>
        <th>ジャンル</th>
        <td>反撃型回避アクション</td>
    </tr>
    <tr>
        <th>操作端末</th>
        <td>キーボード / コントローラ</td>
    </tr>
    <tr>
        <th>プレイ人数</th>
        <td>1人</td>
    </tr>
    <tr>
        <th>開発期間</th>
        <td>2025年4月 ～ 現在</td>
    </tr>
    <tr>
        <th>開発人数</th>
        <td>2人</td>
    </tr>
    <tr>
        <th>使用技術</th>
        <td>C++ / DxLib</td>
    </tr>
</table>

## ルール
以下のサイクルをゲームオーバーになるまで繰り返すエンドレスゲームです。
最終スコアでハイスコアを競います。

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule1_sakeru.gif" width=200>
  <div>
    <b>1. 避ける</b><br>
    レーザーや隕石などの障害物に1回でも当たるとゲームオーバー。<br>
    <font color=00ffff>青いもの</font>が障害物のサインです。
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule2_toru.gif" width=200>
  <div>
    <b>2. 取る</b><br>
    画面上部からアイテムが降ってきます。<br>
    アイテムを取ると、反射モードへ変化します。<br>
    プレイヤーが<font color=ff00ff>ピンク色</font>になったら、反射モードのサインです。
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule3_hansya.gif" width=200>
  <div>
    <b>3. 反射</b><br>
    反射モード中は、レーザーにわざと当たりに行くことで反射することができます。<br>
    ただし、反射モードには制限時間があるため、切れる前に逃げることも重要です。<br>
    ※レーザーのみ当たってもOKで、無敵ではありません
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule4_kowasu.gif" width=200>
  <div>
    <b>4. 壊す</b><br>
    反射したレーザーは、近くの隕石に向かって自動で追尾します。<br>
    レーザーが隕石に衝突すると破壊され、スコアを得ることができます。
  </div>
</div>
<br>

これらのルールは、ゲーム本編の『**チュートリアル**』モードからでも確認できます。
<img src="_readme_img/menu_tutorial.png">

## こだわりポイント

> ### ネオン風のデザイン

本作は「きれい × かっこいい」をテーマとした世界観で作りました。
<font color=00ffff>青色</font>と<font color=ff00ff>ピンク色</font>の対比で、目を惹くデザインが特徴的です。


<div style="display: flex; flex-wrap: wrap;">
  <p style="width: 45%; margin: 1%;">
    <font color=00ffff><b>通常モード</b></font>
    <img src="_readme_img/color_blue.png">
  </p>
  <p style="width: 45%; margin: 1%;">
    <font color=ff00ff><b>反射モード</b></font>
    <img src="_readme_img/color_pink.png">
  </p>
</div>

> ### "動き" を作るアニメーション
本作ではオブジェクトやUIなど、至る所にアニメーションを入れています。
常に何かが動いているため、ゲーム全体の迫力が増しています。

▼`背景アニメーション`

<img src="_readme_img/anim_bg.gif">
<br>

▼`レベルアップアニメーション`

<img src="_readme_img/anim_levelup.gif">
<br>

> ### 隕石
形と線の数は、独自のアルゴリズムでランダムに生成しています。
1. 隕石の線の数を抽選
2. 隕石の中心から、頂点をどのくらいの距離離すかを抽選

<img src="_readme_img/meteor1.png"> <img src="_readme_img/meteor2.png"> <img src="_readme_img/meteor3.png">

また、隕石が壊れた時の演出にもこだわり、壊した時の気持ち良さが出るよう工夫しました。

<img src="_readme_img/anim_break_meteor.gif">
<br>

> ### KrLib
ゲーム開発を効率化することを目的とした、自作ラッパーライブラリです。

こちらをクリックすると、ライブラリのソースへ移動します。

・[KrLib - DXライブラリ用](https://github.com/KurosawaReo/2025_shinkyu_zenki/tree/main/Csinkyu/KrLib_Dx)<br>
・[KrLib - C++用](https://github.com/KurosawaReo/2025_shinkyu_zenki/tree/main/Csinkyu/KrLib_cpp)<br>