/*
   - MenuManager.h -
   メニューシーン.
*/
#pragma once

/*------------------------------------------*/
//【編集】メニューのデザインを変えたい時はここをいじる.

//メニュー設定(レイアウト)
struct MenuLayout
{
	DBL_XY   menuPos       = {370, 280};					//モード枠の位置.
	DBL_XY   menuSize      = {400,  70};					//モード枠のサイズ.
	int      menuSpace     = 100;							//モード枠の配置間隔.
	int      loreInner     = 15;							//説明文が内側にどれだけずれるか.
	int      loreLineSpace = 30;							//説明文の行間.
	DBL_XY   imgPos        = {WINDOW_WID-510, 410};			//サムネ画像の基準位置.
};
//メニュー設定(色)
struct MenuColor 
{
	UINT text    = GetColor(255, 255, 255);	//テキスト色.
	UINT frame   = GetColor(  0, 255, 255);	//枠色.
	UINT normal  = GetColor(150, 150, 150);	//未選択色.
	UINT select1 = GetColor(100, 255, 255);	//カーソル表.
	UINT select2 = GetColor( 50, 150, 255);	//カーソル裏.
	UINT line    = GetColor(  0, 255, 255);	//線の色.
};
/*------------------------------------------*/

class GameData;

//メニュー.[継承不可]
class MenuManager final
{
//▼実体関係.
public:
	static MenuManager& GetInst() {
		static MenuManager inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	GameData* p_data{};           //GameDataのポインタ.

	Font      fontMenu[2]{};      //メニュー用フォント.

	int       selectedIndex = 0;  //カーソルの選択位置 | 0:ゲーム開始 | 1:チュートリアル | 2:タイトルに戻る |
	float     counter = 0;        //経過時間.

	//点滅アニメーション.
	Timer     tmBlink = Timer(TimerMode::CountDown, 0.1f); //点滅間隔.
	Timer     tmTitle = Timer(TimerMode::CountDown, 2.5f); //タイトルアニメ用.
	bool      isBlink = 0;                                 //点滅させる用.

	/*
	//電気アニメーション.
	double    electrRate = 0.0;  //電気が線の何割まで進んだか.
	Line      electr{};          //電気用の線.
	*/
	//描画用設定.
	const MenuLayout mLayout;
	const MenuColor  mColor;

//関数.
private:
	//constructor(新規作成をできなくする)
	MenuManager(){}

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void OnCursorMove(); //カーソル移動時の処理.
	
	//使用禁止.
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator=(const MenuManager&) = delete;
};