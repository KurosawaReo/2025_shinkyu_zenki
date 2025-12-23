/*
   - Stage_Endless.h -

   ステージ: 耐久モード.
*/
#pragma once

//耐久モード.[継承不可]
class EndlessStage final
{
//▼実体関係.
public:
	static EndlessStage& GetInst() {
		static EndlessStage inst; //自身のインスタンス.
		return inst;
	}

//▼変数.
private:
	
//▼関数.
private:
	//constructor(新規作成をできなくする)
	EndlessStage(){}

public:
	void Init();
	void Reset();
	void Update();
	void Draw();

	void UpdateObjects();
	void DrawObjects();

	//使用禁止.
	EndlessStage(const EndlessStage&) = delete;
	EndlessStage& operator=(const EndlessStage&) = delete;
};