/*
   - BG3.cpp -
*/
#include "BG3.h"

#include <cmath>
#include <cstdlib>

//=========================================
// 定数
//=========================================

//六角形サイズ.
constexpr float HEX_SIZE = 70.0f;

//グリッド数.
constexpr int GRID_X = 18;
constexpr int GRID_Z = 18;

//高さ.
constexpr float HEIGHT_MIN = 5.0f;
constexpr float HEIGHT_MAX = 40.0f;

//配置間隔.
constexpr float HEX_X_SPACING = HEX_SIZE * 1.75f;
constexpr float HEX_Z_SPACING = HEX_SIZE * 1.50f;

//色.
constexpr int COLOR_DARK_R = 10;
constexpr int COLOR_DARK_G = 25;
constexpr int COLOR_DARK_B = 30;

constexpr int COLOR_LIGHT_R = 40;
constexpr int COLOR_LIGHT_G = 80;
constexpr int COLOR_LIGHT_B = 90;

//発光色.
constexpr int GLOW_R = 50;
constexpr int GLOW_G = 255;
constexpr int GLOW_B = 255;


//=========================================
// 六角形頂点取得
// centerX, centerZ : 中心座標
// radius           : 六角形サイズ
// y                 : 高さ
//=========================================
static void CreateHexVertices(
	VECTOR outVertices[6],
	float centerX,
	float centerZ,
	float radius,
	float y
)
{
	for (int i = 0; i < 6; i++)
	{
		//60度ずつ回転.
		float angle = DX_PI_F / 180.0f * (60.0f * i);

		//円周上に頂点配置.
		float x = centerX + cosf(angle) * radius;
		float z = centerZ + sinf(angle) * radius;

		outVertices[i] = VGet(x, y, z);
	}
}


//=========================================
// 六角形上面描画
//=========================================
static void DrawHexTop(
	const VECTOR topVertices[6],
	int color
)
{
	//中心点.
	VECTOR center = VGet(0, 0, 0);

	for (int i = 0; i < 6; i++)
	{
		center.x += topVertices[i].x;
		center.y += topVertices[i].y;
		center.z += topVertices[i].z;
	}

	center.x /= 6.0f;
	center.y /= 6.0f;
	center.z /= 6.0f;

	//扇状三角形で描画.
	for (int i = 0; i < 6; i++)
	{
		int next = (i + 1) % 6;

		DrawTriangle3D(
			center,
			topVertices[i],
			topVertices[next],
			color,
			TRUE
		);
	}
}


//=========================================
// 側面描画
//=========================================
static void DrawHexSides(
	const VECTOR topVertices[6],
	float bottomY,
	int color
)
{
	for (int i = 0; i < 6; i++)
	{
		int next = (i + 1) % 6;

		//上面頂点.
		VECTOR topA = topVertices[i];
		VECTOR topB = topVertices[next];

		//下面頂点.
		VECTOR bottomA = VGet(
			topA.x,
			bottomY,
			topA.z
		);

		VECTOR bottomB = VGet(
			topB.x,
			bottomY,
			topB.z
		);

		//四角形を三角形2枚で描画.
		DrawTriangle3D(
			topA,
			topB,
			bottomA,
			color,
			TRUE
		);

		DrawTriangle3D(
			bottomA,
			topB,
			bottomB,
			color,
			TRUE
		);
	}
}


//=========================================
// 発光ライン
//=========================================
static void DrawGlow(
	float x,
	float y,
	float z,
	float anim
)
{
	//脈動.
	float scale =
		0.8f +
		sinf(anim + (x + z) * 0.01f) * 0.2f;

	int alpha =
		(int)(
			120 +
			sinf(anim + (x * 0.02f)) * 60
		);

	alpha = max(0, min(alpha, 255));

	//疑似ブルーム.
	for (int i = 0; i < 4; i++)
	{
		float size =
			40.0f +
			i * 15.0f;

		DrawBillboard3D(
			VGet(x, y + 5.0f, z),
			0.5f,
			0.5f,
			size * scale,
			0.0f,
			-1,
			GetColor(
				GLOW_R - i * 10,
				GLOW_G,
				GLOW_B
			),
			TRUE
		);
	}
}


//=========================================
// 初期化
//=========================================
void BG3::Init()
{
	m_hexList.clear();

	//乱数固定.
	srand(0);

	//六角形生成.
	for (int z = 0; z < GRID_Z; z++)
	{
		for (int x = 0; x < GRID_X; x++)
		{
			HexData data{};

			//奇数行を半マスずらす.
			float offsetX =
				(z % 2) ?
				HEX_X_SPACING * 0.5f :
				0.0f;

			//配置.
			data.x =
				(x * HEX_X_SPACING)
				+ offsetX
				- 800.0f;

			data.z =
				(z * HEX_Z_SPACING)
				- 600.0f;

			//==========================
			// 高さ生成
			// ランダムだと汚いので
			// sin/cosで自然な凹凸
			//==========================
			float noise =
				sinf(x * 0.45f) +
				cosf(z * 0.38f);

			noise *= 0.5f;
			noise += 0.5f;

			data.height =
				HEIGHT_MIN +
				noise *
				(HEIGHT_MAX - HEIGHT_MIN);

			//一部だけ発光.
			data.isGlow =
				(rand() % 100) < 25;

			m_hexList.push_back(data);
		}
	}
}

//=========================================
// 更新
//=========================================
void BG3::Update()
{
	//発光アニメ用時間.
	m_glowAnim += 0.03f;
}


//=========================================
// 描画
//=========================================
void BG3::Draw()
{
	//==================================================
	// 仮カメラ
	// 少し下から見上げる角度
	//==================================================
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f, 250.0f, -650.0f),
		VGet(0.0f, 40.0f, 100.0f)
	);

	//背景色.
	ClearDrawScreen();

	//==================================================
	// 六角形描画
	//==================================================
	for (const auto& hex : m_hexList)
	{
		//----------------------------------------
		// 六角形頂点生成
		//----------------------------------------
		VECTOR topVertices[6];

		CreateHexVertices(
			topVertices,
			hex.x,
			hex.z,
			HEX_SIZE,
			hex.height
		);

		//----------------------------------------
		// 色決定
		//----------------------------------------
		int baseColor;

		//高さによって少し明るさ変更.
		float brightness =
			hex.height / HEIGHT_MAX;

		int r =
			COLOR_DARK_R +
			(int)(
				(COLOR_LIGHT_R - COLOR_DARK_R)
				* brightness
				);

		int g =
			COLOR_DARK_G +
			(int)(
				(COLOR_LIGHT_G - COLOR_DARK_G)
				* brightness
				);

		int b =
			COLOR_DARK_B +
			(int)(
				(COLOR_LIGHT_B - COLOR_DARK_B)
				* brightness
				);

		baseColor = GetColor(r, g, b);

		//----------------------------------------
		// 側面描画
		//----------------------------------------
		DrawHexSides(
			topVertices,
			-100.0f,
			baseColor
		);

		//----------------------------------------
		// 上面描画
		//----------------------------------------
		DrawHexTop(
			topVertices,
			baseColor
		);

		//----------------------------------------
		// 発光
		//----------------------------------------
		if (hex.isGlow)
		{
			DrawGlow(
				hex.x,
				hex.height,
				hex.z,
				m_glowAnim
			);
		}
	}
}


//=========================================
// ポーズ
//=========================================
void BG3::Pause()
{

}


//=========================================
// ポーズ解除
//=========================================
void BG3::PauseEnd()
{

}