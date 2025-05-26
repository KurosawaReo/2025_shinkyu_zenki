
#pragma once

class Item
{
private:

	BOOL   pos;
	BOOL   active; //有効か.
	

	double itemX, itemY;
    int itemFlag;
	int itemW, itemH, itemGraph;
	int itemCounter;

public:
	void Init();
	void Update();
	void Draw();
	void ItemMove(); //アイテム.


};