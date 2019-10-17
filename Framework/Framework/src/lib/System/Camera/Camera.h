#pragma once

#include "Collision\Collision.h"
#include "NonCopyable\NonCopyable.hpp"
#include "System\System.h"
/**
*@file Camera.h
*@brief Camera Class
*@author kanekona
*@data 2019/03/11
*@details 
*/

/**
*@brief Camera2D Class
*@details camera行列を扱う
*@details Scene１つに１cameraの生成を行う
*/
class CCamera2D : private CNonCopyable
{
	//!	実際位置
	CBox2D cameraPos;
	//!	位置
	CVec2 position;
	//! サイズ
	CVec2 scale;
	//! 投影行列を保存しておく配列
	GLfloat projectionMatrix[16];
	//! 判定用
	CCircleCollider collision;
	//! Collider値
	CTransform transform;
	/**
	*@brief	投影行列を登録する
	*@param[in] float left 左
	*@param[in] float right 右
	*@param[in] float buttom 下
	*@param[in] float top 上
	*@param[in] float nearVal 手前
	*@param[in] float farVal 奥
	*/
	void SetProjectionMatrix(
		const float left, const float right,
		const float buttom, const float top,
		const float nearVal, const float farVal);
public:
	/**
	*@brief	constructor
	*/
	explicit CCamera2D();
	/**
	*@brief	constructor
	*@param[in]	const Box2D& b 位置とサイズ
	*/
	explicit CCamera2D(const CBox2D& b);
	/**
	*@brief	destructor
	*/
	virtual ~CCamera2D();
	/**
	*@brief	初期化処理
	*@param[in]	const Box2D& b 位置とサイズ
	*/
	void Initialize(const CBox2D& b);
	/**
	*@brief	更新処理
	*/
	void Update();
	/**
	*@brief	位置を移動させる
	*@param[in] const Vec2& move 移動値
	*/
	void MovePos(const CVec2& move);
	/**
	*@brief	位置を設定する
	*@param[in]	const Vec2& pos 位置
	*/
	void SetPos(const CVec2& pos);
	/**
	*@brief	サイズを設定する
	*@param[in]	const Vec2& size 大きさ
	*/
	void SetSize(const CVec2& size);
	/**
	*@brief	サイズを動かす
	*@param[in]	const Vec2& move 移動値
	*/
	void MoveSize(const CVec2& move);
	/**
	*@brief	カメラ位置のX座標を設定する
	*@param[in]	float x 座標値
	*/
	void SetPos_x(const float& x);
	/**
	*@brief	カメラ位置のY座標を設定する
	*@param[in]	float y 座標値
	*/
	void SetPos_y(const float& y);
	/**
	*@brief	カメラの横サイズを変える
	*@param[in]	float w 横サイズ
	*/
	void SetSize_w(const float& w);
	/**
	*@brief	カメラの縦サイズを変える
	*@param[in]	float w 縦サイズ
	*/
	void SetSize_h(const float& h);
	/**
	*@brief	カメラの位置を返す
	*@return Vec2 カメラ位置
	*/
	const CVec2& GetPos() const;
	/**
	*@brief	カメラのサイズを返す
	*@return Vec2 カメラの大きさ
	*/
	const CVec2& GetSize() const;
	/**
	*@brief	投影行列を取得する
	*@return GLfloat* 投影行列
	*/
	const GLfloat* GetProjectionMatrix() const;
	/**
	*@brief Camera判定を取得
	*@return CollisionCircle* 判定
	*/
	const CCircleCollider* GetCollision() const;
	/**
	*@brief 上下反転カメラ行列を取得する
	*@param[out] GLfloat* out 投影行列
	*/
	void ReverseProjectionMatrix(GLfloat* out);
};