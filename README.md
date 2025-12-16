<!-- 
   GitHubの表示を基準にするため、VScode上での表示とは異なる点に注意
-->

<p align="center">
  <img src="_readme_img/logo_all_black.png" width="500"><br>
</p>

---
## 操作説明
**キーボード**
<img src="_readme_img/操作説明_キーボード.png">
**Xboxコントローラ**
<img src="_readme_img/操作説明_xboxコントローラ.png">
<br>

---
## ゲーム概要
<img src="_readme_img/ゲーム画面.png">
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
  <img src="_readme_img/rule1_避ける.gif" width=200>
  <div>
    <b>1. 避ける</b><br>
    レーザーや隕石などの障害物に1回でも当たるとゲームオーバー。<br>
    <font color=00ffff>青いもの</font>が障害物のサインです。
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule2_取る.gif" width=200>
  <div>
    <b>2. 取る</b><br>
    画面上部からアイテムが降ってきます。<br>
    アイテムを取ると、反射モードへ変化します。<br>
    プレイヤーが<font color=ff00ff>ピンク色</font>になったら、反射モードのサインです。
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule3_反射.gif" width=200>
  <div>
    <b>3. 反射</b><br>
    反射モード中は、レーザーにわざと当たりに行くことで反射することができます。<br>
    ただし、反射モードには制限時間があるため、切れる前に逃げることも重要です。<br>
    ※レーザーのみ当たってもOKで、無敵ではありません
  </div>
</div>
<br>

<div style="display:flex; align-items:center; gap:16px;">
  <img src="_readme_img/rule4_壊す.gif" width=200>
  <div>
    <b>4. 壊す</b><br>
    反射したレーザーは、近くの隕石に向かって自動で追尾します。<br>
    レーザーが隕石に衝突すると破壊され、スコアを得ることができます。
  </div>
</div>
<br>

これらのルールは、ゲーム本編の『**チュートリアル**』モードからでも確認できます。
<img src="_readme_img/メニュー_チュートリアル.png">

### こだわりポイント

> ### 視認性と演出を両立したビジュアル

「きれい × かっこいい」をテーマに、線や図形を主体とした目を惹くデザインにしました。

アニメーションやサウンドにもこだわり、見ていて飽きない**動き**のあるゲームデザインを目指しました。

▼`背景アニメーション`

<img src="_readme_img/背景アニメ.gif">
<br>

▼`Levelアニメーション`

<img src="_readme_img/Levelアニメ.gif">
<br>

> ### 隕石
形と線の数は独自のアルゴリズムでランダム生成しています。
また、壊した時の演出にこだわり、壊した時の気持ち良さを感じるよう工夫しました。

<img src="_readme_img/隕石破壊アニメ.gif">
<br>

> ### プログラム設計への工夫

* 管理クラスを中心としたシングルトン設計
* エフェクト専用の EffectManager による演出管理
* 隕石形状をランダム生成するアルゴリズム
* DxLib向け自作ライブラリ **KrLib** による開発効率化
<br>

> ### KrLib
ゲーム開発をスムーズにすることを目的とした、自作ラッパーライブラリです。

こちらをクリックすると、ライブラリのソースへ移動します。

・[KrLib - DXライブラリ用](https://github.com/KurosawaReo/2025_shinkyu_zenki/tree/main/Csinkyu/KrLib_Dx)<br>
・[KrLib - C++用](https://github.com/KurosawaReo/2025_shinkyu_zenki/tree/main/Csinkyu/KrLib_cpp)<br>