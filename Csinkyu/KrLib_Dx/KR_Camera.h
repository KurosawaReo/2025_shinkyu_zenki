/*
   - KR_Camera.h - (DxLib)
   ver: 2025/12/07

   カメラ機能を追加。
*/
#pragma once
//KR_Globalが入ってなければここで導入.
#if !defined DEF_KR_DX_GLOBAL
  #include "KR_Global.h"
#endif

//KrLib名前空間.
namespace KR
{
	/*
	   カメラ管理[staticクラス]

	   全ての描画関数(→KR_Draw)は、このカメラの位置を元に描画されます.
	   (UIのようにカメラに追従することも可)

	   またDrawRota関数を使うと、カメラの角度も考慮して描画されます.
	*/
	class Camera final
	{
	//▼実体関係.
	private:
		static Camera inst; //実体を入れる用.
	public:
		//使用禁止.
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	//▼変数.
	private:
		DBL_XYZ cameraPos{}; //カメラ座標.
		double  cameraAng{}; //カメラ角度(2D用)

	//▼関数.
	private:
		//constructor.
		Camera() : cameraPos(0, 0, 0), cameraAng(0) {}
		//角度補正.
		void FixAng360();

	public:
		//get.
		static DBL_XY  GetPos()   { return {inst.cameraPos.x, inst.cameraPos.y}; }
		static DBL_XYZ GetPos3D() { return inst.cameraPos; }
		static double  GetAng()   {	return inst.cameraAng; }

		//set, add.
		static void SetPos(DBL_XY _pos);
		static void SetAng(double _ang);
		static void AddPos(DBL_XY _pos, bool isLocal = false);
		static void AddAng(double _ang);

		//カメラ座標.
		static DBL_XY GetCameraPos();
	};
}