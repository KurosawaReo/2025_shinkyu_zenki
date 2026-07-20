/*
   - BG3.cpp -
   3Dの背景は画面酔いするリスクがあることに注意。
*/
#include "BG3.h"

//依存関係.
#include "Global.h"
#include "GameData.h"
#include <cmath>
//参照.
static GameData* gameData;

/* ===== 定数 ===== */
constexpr double MOVE_SPEED   = 4.0;     //前に移動する速度.
constexpr double ROT_SPEED    = 0.002;   //回転する速度.
constexpr double POINT_LEN    = 18.0;    //飛んでくる線の長さ.
constexpr double Z_MIN        = 50.0;    //一番手前のz座標.
constexpr double Z_MAX        = 3000.0;  //一番奥のz座標.
constexpr double HEX_INTERVAL = 180.0;
constexpr double FOV          = 500.0;
/* ================ */

//初期化.
void BG3::Init() {

    //参照取得.
    gameData = ManagerInsts::Get<GameData>();

    angle = 0.0;

    //初期位置.
    for (auto& i : point)
    {
        i.x = Calc::RandNum(-2000.0, 2000.0);
        i.y = Calc::RandNum(-2000.0, 2000.0);
        i.z = Calc::RandNum( 100.0,  Z_MAX);

        i.oldZ = i.z;
    }
    for (int i = 0; i < HEX_NUM; i++)
    {
        hex[i].z = Z_MIN + i * HEX_INTERVAL;
    }
}

//更新.
void BG3::Update() {

    angle += ROT_SPEED * gameData->speedRate;

    for (auto& i : point)
    {
        //移動.
        i.z -= MOVE_SPEED * gameData->speedRate;
        i.oldZ = i.z + POINT_LEN;

        //手前へ来たら奥へ戻す.
        if (i.z < Z_MIN)
        {
            i.x = Calc::RandNum(-2000.0, 2000.0);
            i.y = Calc::RandNum(-2000.0, 2000.0);
            i.z = Z_MAX;

            i.oldZ = i.z;
        }
    }
    for (auto& i : hex)
    {
        //移動.
        i.z -= MOVE_SPEED * gameData->speedRate;

        //手前へ来たら奥へ戻す.
        if (i.z < Z_MIN) {
            i.z += HEX_NUM * HEX_INTERVAL;
        }
    }
}

//描画(通常時)
void BG3::DrawNor(double modeAlpha) {

    DrawHexagons(modeAlpha, COLOR_MODE_NOR);
    DrawPoints  (modeAlpha, COLOR_MODE_NOR);
}

//描画(反射モード)
void BG3::DrawRef(double modeAlpha) {
    
    DrawHexagons(modeAlpha, COLOR_MODE_REF);
    DrawPoints  (modeAlpha, COLOR_MODE_REF);
}

//描画(線)
void BG3::DrawPoints(double modeAlpha, MY_COLOR mainColor) {

    const DBL_XY center = App::GetWindowRect().GetMid().ToDbl();

    //==============================
    // 疑似3D ワープライン
    //==============================

    for (auto& i : point)
    {
        //奥すぎる場合は描画しない.
        if (i.z <= 1.0) {
            continue;
        }

        //--------------------------------
        // 回転
        //--------------------------------
        double c = cos(angle * 0.3);
        double s = sin(angle * 0.3);

        double rx = i.x * c - i.y * s;
        double ry = i.x * s + i.y * c;

        //--------------------------------
        // 現在座標
        //--------------------------------
        double scale = FOV / i.z;

        DBL_XY now =
        {
            center.x + rx * scale,
            center.y + ry * scale
        };

        //画面外なら描画しない.
        if (now.x < -100 || now.x > WINDOW_WID + 100) {
            continue;
        }
        if (now.y < -100 || now.y > WINDOW_HEI + 100) {
            continue;
        }

        //--------------------------------
        // 前フレーム座標
        //--------------------------------
        double oldScale = FOV / i.oldZ;

        DBL_XY old =
        {
            center.x + rx * oldScale,
            center.y + ry * oldScale
        };

        //--------------------------------
        // 線の太さ
        //--------------------------------
        float thick = _flt(1.0 + (Z_MAX - i.z) / 800.0);

        if (thick > 5.0) {
            thick = 5.0;
        }

        //--------------------------------
        // 描画
        //--------------------------------
        Line line;
        line.stPos = old;
        line.edPos = now;
        line.color = mainColor;
        line.thick = thick;

        //透明度を計算(奥ほど薄くする)
        const double alpha = 160 * (1.0 - i.z / Z_MAX) * modeAlpha;

        DrawMode::Exe(
            DrawModeID::None, DrawBlendModeID::Alpha, _int(alpha),
            [&]() {
                DrawLineKR(line, true);
            }
        );
    }
}

//描画(六角形)
void BG3::DrawHexagons(double modeAlpha, MY_COLOR color)
{
    constexpr double FOV = 5000;

    double cx = WINDOW_WID / 2.0;
    double cy = WINDOW_HEI / 2.0;

    for (auto& h : hex)
    {
        double scale = FOV / h.z;

        double radius = scale * 80;
        if (radius < 3) {
            continue;
        }

        //ポリゴンの作成.
        KR::Polygon poly;
        poly.color = color;
        poly.thick = 2;

        for (int i = 0; i < 6; i++)
        {
            double a = angle + i * M_PI / 3;

            double x = cx + cos(a) * radius;
            double y = cy + sin(a) * radius;

            poly.points.push_back({x, y});
        }

        //透明度を計算(奥ほど薄くする)
        const double alpha = 80 * (1.0 - h.z / Z_MAX) * modeAlpha;

        DrawMode::Exe(
            DrawModeID::None, DrawBlendModeID::Alpha, _int(alpha),
            [&]()
            {
                DrawPolygonKR(poly, true, true);
            }
        );
    }
}

//ポーズする.
void BG3::Pause() {
}

//ポーズ解除.
void BG3::PauseEnd() {
}