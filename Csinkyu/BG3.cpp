/*
   - BG3.cpp -
*/
#include "BG3.h"

#include "Global.h"
#include <cmath>

//初期化.
void BG3::Init() {
    angle = 0.0;
    pulse = 0.0;

    // ランダム配置
    for (int i = 0; i < POINT_NUM; i++)
    {
        point[i].x = GetRand(4000) - 2000;
        point[i].y = GetRand(4000) - 2000;
        point[i].z = GetRand(3000) + 100;

        point[i].oldZ = point[i].z;
    }
}

//更新.
void BG3::Update() {

    angle += 0.002;
    pulse += 0.04;

    // ワープ速度
    constexpr double SPEED = 18.0;

    for (int i = 0; i < POINT_NUM; i++)
    {
        point[i].oldZ = point[i].z;

        point[i].z -= SPEED;

        // 手前へ来たら奥へ戻す
        if (point[i].z < 50)
        {
            point[i].x = GetRand(4000) - 2000;
            point[i].y = GetRand(4000) - 2000;
            point[i].z = 3000;

            point[i].oldZ = point[i].z;
        }
    }
}

//描画(通常時)
void BG3::DrawNor(double modeAlpha, double count) {
    DrawCommon(modeAlpha, { 80, 180, 255 });
}

//描画(反射モード)
void BG3::DrawRef(double modeAlpha, double count) {
    DrawCommon(modeAlpha, { 255, 80, 200 });
}

//描画(共通)
void BG3::DrawCommon(double modeAlpha, MY_COLOR mainColor) {

    const DBL_XY center =
    {
        WINDOW_WID / 2.0,
        WINDOW_HEI / 2.0
    };

    //==============================
    // 疑似3D ワープライン
    //==============================
    constexpr double FOV = 500.0;

    for (int i = 0; i < POINT_NUM; i++)
    {
        WarpPoint& p = point[i];

        // 奥すぎる場合は描画しない
        if (p.z <= 1.0)
            continue;

        //--------------------------------
        // 回転
        //--------------------------------
        double c = cos(angle * 0.3);
        double s = sin(angle * 0.3);

        double rx = p.x * c - p.y * s;
        double ry = p.x * s + p.y * c;

        //--------------------------------
        // 現在座標
        //--------------------------------
        double scale = FOV / p.z;

        DBL_XY now =
        {
            center.x + rx * scale,
            center.y + ry * scale
        };

        //--------------------------------
        // 前フレーム座標
        //--------------------------------
        double oldScale = FOV / p.oldZ;

        DBL_XY old =
        {
            center.x + rx * oldScale,
            center.y + ry * oldScale
        };

        //--------------------------------
        // 画面外ならスキップ
        //--------------------------------
        if (now.x < -100 || now.x > WINDOW_WID + 100)
            continue;

        if (now.y < -100 || now.y > WINDOW_HEI + 100)
            continue;

        //--------------------------------
        // 線の太さ
        //--------------------------------
        double thick = 1.0 + (3000.0 - p.z) / 800.0;

        if (thick > 5.0)
            thick = 5.0;

        //--------------------------------
        // 描画
        //--------------------------------
        Line line;
        line.stPos = old;
        line.edPos = now;
        line.color = mainColor;
        line.thick = thick;

        DrawMode::Exe(
            DrawModeID::None, DrawBlendModeID::Alpha, _int(255 * modeAlpha),
            [&]() {
                DrawLineKR(line, true);
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