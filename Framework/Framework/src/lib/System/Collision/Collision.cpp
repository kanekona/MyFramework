#include "Collision.h"
//--------------------------------------------------
//@:CollisionBase
//--------------------------------------------------
Collider::Collider(const unsigned short vertex,Transform* t)
	:VERTEX_NUM(vertex)
{
	this->transform = t;
	this->radius = { 1,1 };
}
//--------------------------------------------------
//@:CollisionBox
//--------------------------------------------------
BoxCollider::BoxCollider(Transform* t)
	:Collider(4,t)
{
}
//矩形×矩形
bool BoxCollider::GetHit(BoxCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	Vec2 _ver[4] = {
		{ b->hitBase.x,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.h },
	{ b->hitBase.x,b->hitBase.h }
	};
	Vec2 _v[4] = {
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
		Vec2 mainvec = _v[(i + 1) % 4] - _v[i % 4];
		for (int j = 0; j < 4; ++j)
		{
			//オブジェクトBの終点-始点の方向ベクトル
			Vec2 subvec = _ver[(j + 1) % 4] - _ver[j % 4];
			Vec2 v = _ver[j % 4] - _v[i % 4];
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
bool BoxCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ b->hitBase.center_x,b->hitBase.center_y }
	};
	Vec2 _v[4] = {
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
bool BoxCollider::GetHit(PointCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	Vec2 _v[4] = {
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
bool BoxCollider::GetHit(LineCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	return false;
}
//矩形×カプセル
bool BoxCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//判定生成
void BoxCollider::CreateCollision()
{
	Vec2 scaleSize = { transform->scale.x * radius.x,transform->scale.y * radius.y };
	this->hitBase = {
		transform->position.x - (scaleSize.x / 2.f),
		transform->position.y - (scaleSize.y / 2.f),
		transform->position.x + (scaleSize.x / 2.f),
		transform->position.y + (scaleSize.y / 2.f)
	};
	this->Rotate(transform->angle);
}
//回転適用
void BoxCollider::Rotate(const float _angle) {
	//回転の値を格納
	this->angle = _angle;
}
//回転取得
float BoxCollider::Rotate() const
{
	return this->angle;
}
//判定
bool BoxCollider::Hit(Collider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionCircle
//--------------------------------------------------
CircleCollider::CircleCollider(Transform* t)
	:Collider(1,t)
{
}
//円×矩形
bool CircleCollider::GetHit(BoxCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ hitBase.center_x,hitBase.center_y }
	};
	Vec2 _v[4] = {
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
bool CircleCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//円の範囲内に相手の円の範囲が存在する場合TRUEを返す
	if (((b->hitBase.center_x - this->hitBase.center_x)*
		(b->hitBase.center_x - this->hitBase.center_x)) +
		((b->hitBase.center_y - this->hitBase.center_y)*
		(b->hitBase.center_y - this->hitBase.center_y)) <=
			(b->hitBase.r + this->hitBase.r)*(b->hitBase.r + this->hitBase.r))
	{
		return true;
	}
	return false;
}
//円×点
bool CircleCollider::GetHit(PointCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ hitBase.center_x,hitBase.center_y }
	};
	Vec2 _v[1] = {
		{ b->hitBase.x,b->hitBase.y },
	};
	//円の中に頂点が存在する場合TRUEを返す
	if (((_ver[0].x - _v[0].x) * (_ver[0].x - _v[0].x)) + ((_ver[0].y - _v[0].y) * (_ver[0].y - _v[0].y)) <= this->hitBase.r * this->hitBase.r)
	{
		return true;
	}
	return false;
}
//円×線
bool CircleCollider::GetHit(LineCollider* b)
{
	return false;
}
//円×カプセル
bool CircleCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//判定生成
void CircleCollider::CreateCollision()
{
	this->hitBase = {
		transform->position.x,
		transform->position.y,
		(transform->scale.x * radius.x) / 2.f
	};
}
//判定
bool CircleCollider::Hit(Collider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionPointer
//--------------------------------------------------
PointCollider::PointCollider(Transform* t)
	:Collider(1,t)
{
}
//点×矩形
bool PointCollider::GetHit(BoxCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	Vec2 _v[4] = {
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
bool PointCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//頂点情報のセット
	Vec2 _ver[1] = {
		{ b->hitBase.center_x,b->hitBase.center_y }
	};
	Vec2 _v[1] = {
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
bool PointCollider::GetHit(PointCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	return this->hitBase == b->hitBase;
}
//点×線
bool PointCollider::GetHit(LineCollider* b)
{
	this->CreateCollision();
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
bool PointCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//判定生成
void PointCollider::CreateCollision()
{
	this->hitBase = transform->position;
}
//判定
bool PointCollider::Hit(Collider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionLine
//--------------------------------------------------
LineCollider::LineCollider(Transform* t)
	:Collider(2,t)
{

}
//線×矩形
bool LineCollider::GetHit(BoxCollider* b)
{
	return false;
}
//線×円
bool LineCollider::GetHit(CircleCollider* b)
{
	return false;
}
//線×線
bool LineCollider::GetHit(LineCollider* b)
{
	return false;
}
//線×点
bool LineCollider::GetHit(PointCollider* b)
{
	b->CreateCollision();
	this->CreateCollision();
	float line_1 = sqrt(
		(this->hitBase[1].x - this->hitBase[0].x)*(this->hitBase[1].x - this->hitBase[0].x) +
		(this->hitBase[1].y - this->hitBase[0].y)*(this->hitBase[1].y - this->hitBase[0].y)
	);
	float line_2 = sqrt(
		(b->hitBase.x - this->hitBase[0].x)*(b->hitBase.x - this->hitBase[0].x) +
		(b->hitBase.y - this->hitBase[0].y)*(b->hitBase.y - this->hitBase[0].y)
	);
	if (
		((this->hitBase[1].x - this->hitBase[0].x)*(b->hitBase.x - this->hitBase[0].x) +
		(this->hitBase[1].y - this->hitBase[0].y)*(b->hitBase.x - this->hitBase[0].y)) == line_1 * line_2 &&
		line_1 >= line_2
		)
	{
		return true;
	}
	return false;
}
//線×カプセル
bool LineCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//判定生成
void LineCollider::CreateCollision()
{
	this->hitBase[0] = transform->position;
	this->hitBase[1] = transform->scale;
}
//判定
bool LineCollider::Hit(Collider* collision)
{
	return collision->GetHit(this);
}
//--------------------------------------------------
//@:CollisionCapsule
//--------------------------------------------------
CapsuleCollider::CapsuleCollider(Transform* t)
	:Collider(6,t)
{

}
//カプセル×カプセル
bool CapsuleCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//カプセル×矩形
bool CapsuleCollider::GetHit(BoxCollider* b)
{
	return false;
}
//カプセル×円
bool CapsuleCollider::GetHit(CircleCollider* b)
{
	return false;
}
//カプセル×点
bool CapsuleCollider::GetHit(PointCollider* b)
{
	return false;
}
//カプセル×線
bool CapsuleCollider::GetHit(LineCollider* b)
{
	return false;
}
//判定
bool CapsuleCollider::Hit(Collider* collision)
{
	return collision->Hit(this);
}