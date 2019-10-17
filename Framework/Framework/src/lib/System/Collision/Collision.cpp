#include "Collision.h"
//--------------------------------------------------
//@:CollisionBase
//--------------------------------------------------
CCollider::CCollider(const unsigned short vertex,CTransform* t)
	:VERTEX_NUM(vertex)
{
	transform = t;
	radius = { 1,1 };
}
//--------------------------------------------------
//@:CollisionBox
//--------------------------------------------------
CBoxCollider::CBoxCollider(CTransform* t)
	:CCollider(4,t)
{
}
//矩形×矩形
bool CBoxCollider::GetHit(CBoxCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	CVec2 _ver[4] = {
		{ b->hitBase.x,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.h },
	{ b->hitBase.x,b->hitBase.h }
	};
	CVec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	//回転の適用
	KL::Rotate(angle, _v);
	KL::Rotate(b->angle, _ver);
	//どちらかの範囲内に相手の頂点が存在する場合TRUEを返す
	for (int i = 0; i < 4; ++i) {
		if ((((_v[1].x - _v[0].x)*(_ver[i].y - _v[0].y)) - ((_ver[i].x - _v[0].x)*(_v[1].y - _v[0].y))) >= 0 &&
			(((_v[2].x - _v[1].x)*(_ver[i].y - _v[1].y)) - ((_ver[i].x - _v[1].x)*(_v[2].y - _v[1].y))) >= 0 &&
			(((_v[3].x - _v[2].x)*(_ver[i].y - _v[2].y)) - ((_ver[i].x - _v[2].x)*(_v[3].y - _v[2].y))) >= 0 &&
			(((_v[0].x - _v[3].x)*(_ver[i].y - _v[3].y)) - ((_ver[i].x - _v[3].x)*(_v[0].y - _v[3].y))) >= 0)
		{
			return true;
		}
	}
	//相手オブジェクト目線でも同じく処理を行う
	for (int i = 0; i < 4; ++i) {
		if ((((_ver[1].x - _ver[0].x)*(_v[i].y - _ver[0].y)) - ((_v[i].x - _ver[0].x)*(_ver[1].y - _ver[0].y))) >= 0 &&
			(((_ver[2].x - _ver[1].x)*(_v[i].y - _ver[1].y)) - ((_v[i].x - _ver[1].x)*(_ver[2].y - _ver[1].y))) >= 0 &&
			(((_ver[3].x - _ver[2].x)*(_v[i].y - _ver[2].y)) - ((_v[i].x - _ver[2].x)*(_ver[3].y - _ver[2].y))) >= 0 &&
			(((_ver[0].x - _ver[3].x)*(_v[i].y - _ver[3].y)) - ((_v[i].x - _ver[3].x)*(_ver[0].y - _ver[3].y))) >= 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		//オブジェクトAの終点-始点の方向ベクトル
		CVec2 mainvec = _v[(i + 1) % 4] - _v[i % 4];
		for (int j = 0; j < 4; ++j)
		{
			//オブジェクトBの終点-始点の方向ベクトル
			CVec2 subvec = _ver[(j + 1) % 4] - _ver[j % 4];
			CVec2 v = _ver[j % 4] - _v[i % 4];
			//外積計算
			float crs = KL::cross(mainvec, subvec);
			if (crs == 0.0f)
			{
				//平行状態
				continue;
			}
			float crs_v1 = KL::cross(v, mainvec);
			float crs_v2 = KL::cross(v, subvec);
			float t1 = crs_v2 / crs;
			float t2 = crs_v1 / crs;
			if (t1 > 0.f && t1 < 1.f && t2 > 0.f && t2 < 1.f)
			{
				//交差してる
				return true;
			}
		}
	}
	return false;
}
//矩形×円
bool CBoxCollider::GetHit(CCircleCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	CVec2 _ver[1] = {
		{ b->hitBase.cEntry_x,b->hitBase.cEntry_y }
	};
	CVec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	//Box型の回転の適用
	KL::Rotate(angle, _v);
	//円の中に頂点が存在する場合TRUEを返す
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) >= b->hitBase.r*b->hitBase.r)
	{
		return true;
	}
	
	//円の中に線分が存在する場合TRUEを返す
	for (int i = 0; i<4; i++) {
		if (KL::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<b->hitBase.r)
			return true;
	}
	return false;
}
//矩形×点
bool CBoxCollider::GetHit(CPointCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	CVec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	KL::Rotate(angle, _v);
	for (int i = 0; i < 4; ++i)
	{
		if ((((_v[(i + 1) % 4].x - _v[i].x)*
			(b->hitBase.y - _v[i].y)) -
			((b->hitBase.x - _v[i].x)*
			(_v[(i + 1) % 4].y - _v[i].y)))
			< 0)
		{
			return false;
		}
	}
	return true;
}
//矩形×線
bool CBoxCollider::GetHit(CLineCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	return false;
}
//矩形×カプセル
bool CBoxCollider::GetHit(CCapsuleCollider* b)
{
	return false;
}
//判定生成
void CBoxCollider::CreateCollision()
{
	CVec2 scaleSize = { transform->scale.x * radius.x,transform->scale.y * radius.y };
	hitBase = {
		transform->position.x - (scaleSize.x / 2.f),
		transform->position.y - (scaleSize.y / 2.f),
		transform->position.x + (scaleSize.x / 2.f),
		transform->position.y + (scaleSize.y / 2.f)
	};
	Rotate(transform->angle);
}
//回転適用
void CBoxCollider::Rotate(const float _angle) {
	//回転の値を格納
	angle = _angle;
}
//回転取得
float CBoxCollider::Rotate() const
{
	return angle;
}
//判定
bool CBoxCollider::Hit(CCollider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionCircle
//--------------------------------------------------
CCircleCollider::CCircleCollider(CTransform* t)
	:CCollider(1,t)
{
}
//円×矩形
bool CCircleCollider::GetHit(CBoxCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	CVec2 _ver[1] = {
		{ hitBase.cEntry_x,hitBase.cEntry_y }
	};
	CVec2 _v[4] = {
		{ b->hitBase.x,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.h },
	{ b->hitBase.x,b->hitBase.h }
	};
	//Box型の回転の適用
	KL::Rotate(b->Rotate(), _v);
	//円の中に頂点が存在する場合TRUEを返す
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) >= hitBase.r*hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) >= hitBase.r*hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) >= hitBase.r*hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) >= hitBase.r*hitBase.r)
	{
		return true;
	}
	//円の中に線分が存在する場合TRUEを返す
	for (int i = 0; i<4; i++) {
		if (KL::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<hitBase.r)
			return true;
	}
	return false;
}
//円×円
bool CCircleCollider::GetHit(CCircleCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//円の範囲内に相手の円の範囲が存在する場合TRUEを返す
	if (((b->hitBase.cEntry_x - hitBase.cEntry_x)*
		(b->hitBase.cEntry_x - hitBase.cEntry_x)) +
		((b->hitBase.cEntry_y - hitBase.cEntry_y)*
		(b->hitBase.cEntry_y - hitBase.cEntry_y)) <=
			(b->hitBase.r + hitBase.r)*(b->hitBase.r + hitBase.r))
	{
		return true;
	}
	return false;
}
//円×点
bool CCircleCollider::GetHit(CPointCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	CVec2 _ver[1] = {
		{ hitBase.cEntry_x,hitBase.cEntry_y }
	};
	CVec2 _v[1] = {
		{ b->hitBase.x,b->hitBase.y },
	};
	//円の中に頂点が存在する場合TRUEを返す
	if (((_ver[0].x - _v[0].x) * (_ver[0].x - _v[0].x)) + ((_ver[0].y - _v[0].y) * (_ver[0].y - _v[0].y)) <= hitBase.r * hitBase.r)
	{
		return true;
	}
	return false;
}
//円×線
bool CCircleCollider::GetHit(CLineCollider* b)
{
	return false;
}
//円×カプセル
bool CCircleCollider::GetHit(CCapsuleCollider* b)
{
	return false;
}
//判定生成
void CCircleCollider::CreateCollision()
{
	hitBase = {
		transform->position.x,
		transform->position.y,
		(transform->scale.x * radius.x) / 2.f
	};
}
//判定
bool CCircleCollider::Hit(CCollider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionPointer
//--------------------------------------------------
CPointCollider::CPointCollider(CTransform* t)
	:CCollider(1,t)
{
}
//点×矩形
bool CPointCollider::GetHit(CBoxCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	CVec2 _v[4] = {
	{ b->hitBase.x,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.h },
	{ b->hitBase.x,b->hitBase.h }
	};
	KL::Rotate(b->Rotate(), _v);
	for (int i = 0; i < 4; ++i)
	{
		if ((((_v[(i + 1) % 4].x - _v[i].x)*
			(hitBase.y - _v[i].y)) -
			((hitBase.x - _v[i].x)*
			(_v[(i + 1) % 4].y - _v[i].y)))
			< 0)
		{
			return false;
		}
	}
	return true;
}
//点×円
bool CPointCollider::GetHit(CCircleCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	CVec2 _ver[1] = {
		{ b->hitBase.cEntry_x,b->hitBase.cEntry_y }
	};
	CVec2 _v[1] = {
		{ hitBase.x,hitBase.y },
	};
	//円の中に頂点が存在する場合TRUEを返す
	if (((_ver[0].x - _v[0].x) * (_ver[0].x - _v[0].x)) + ((_ver[0].y - _v[0].y) * (_ver[0].y - _v[0].y)) <= b->hitBase.r * b->hitBase.r)
	{
		return true;
	}
	return false;
}
//点×点
bool CPointCollider::GetHit(CPointCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	return hitBase == b->hitBase;
}
//点×線
bool CPointCollider::GetHit(CLineCollider* b)
{
	CreateCollision();
	b->CreateCollision();
	float line_1 = sqrt(
		(b->hitBase[1].x - b->hitBase[0].x)*(b->hitBase[1].x - b->hitBase[0].x) +
		(b->hitBase[1].y - b->hitBase[0].y)*(b->hitBase[1].y - b->hitBase[0].y)
	);
	float line_2 = sqrt(
		(hitBase.x - b->hitBase[0].x)*(hitBase.x - b->hitBase[0].x) +
		(hitBase.y - b->hitBase[0].y)*(hitBase.y - b->hitBase[0].y)
	);
	if (
		((b->hitBase[1].x - b->hitBase[0].x)*(hitBase.x - b->hitBase[0].x) +
		(b->hitBase[1].y - b->hitBase[0].y)*(hitBase.x - b->hitBase[0].y)) == line_1 * line_2 &&
		line_1 >= line_2
		)
	{
		return true;
	}
	return false;
}
//点×カプセル
bool CPointCollider::GetHit(CCapsuleCollider* b)
{
	return false;
}
//判定生成
void CPointCollider::CreateCollision()
{
	hitBase = transform->position;
}
//判定
bool CPointCollider::Hit(CCollider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionLine
//--------------------------------------------------
CLineCollider::CLineCollider(CTransform* t)
	:CCollider(2,t)
{

}
//線×矩形
bool CLineCollider::GetHit(CBoxCollider* b)
{
	return false;
}
//線×円
bool CLineCollider::GetHit(CCircleCollider* b)
{
	return false;
}
//線×線
bool CLineCollider::GetHit(CLineCollider* b)
{
	return false;
}
//線×点
bool CLineCollider::GetHit(CPointCollider* b)
{
	b->CreateCollision();
	CreateCollision();
	float line_1 = sqrt(
		(hitBase[1].x - hitBase[0].x)*(hitBase[1].x - hitBase[0].x) +
		(hitBase[1].y - hitBase[0].y)*(hitBase[1].y - hitBase[0].y)
	);
	float line_2 = sqrt(
		(b->hitBase.x - hitBase[0].x)*(b->hitBase.x - hitBase[0].x) +
		(b->hitBase.y - hitBase[0].y)*(b->hitBase.y - hitBase[0].y)
	);
	if (
		((hitBase[1].x - hitBase[0].x)*(b->hitBase.x - hitBase[0].x) +
		(hitBase[1].y - hitBase[0].y)*(b->hitBase.x - hitBase[0].y)) == line_1 * line_2 &&
		line_1 >= line_2
		)
	{
		return true;
	}
	return false;
}
//線×カプセル
bool CLineCollider::GetHit(CCapsuleCollider* b)
{
	return false;
}
//判定生成
void CLineCollider::CreateCollision()
{
	hitBase[0] = transform->position;
	hitBase[1] = transform->scale;
}
//判定
bool CLineCollider::Hit(CCollider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionCapsule
//--------------------------------------------------
CCapsuleCollider::CCapsuleCollider(CTransform* t)
	:CCollider(6,t)
{

}
//カプセル×カプセル
bool CCapsuleCollider::GetHit(CCapsuleCollider* b)
{
	return false;
}
//カプセル×矩形
bool CCapsuleCollider::GetHit(CBoxCollider* b)
{
	return false;
}
//カプセル×円
bool CCapsuleCollider::GetHit(CCircleCollider* b)
{
	return false;
}
//カプセル×点
bool CCapsuleCollider::GetHit(CPointCollider* b)
{
	return false;
}
//カプセル×線
bool CCapsuleCollider::GetHit(CLineCollider* b)
{
	return false;
}
//判定
bool CCapsuleCollider::Hit(CCollider* collision)
{
	return collision->Hit(this);
}