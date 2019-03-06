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
//��`�~��`
bool BoxCollider::GetHit(BoxCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//���_���̃Z�b�g
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
	//��]�̓K�p
	KL::Rotate(angle, _v);
	KL::Rotate(b->angle, _ver);
	//�ǂ��炩�͈͓̔��ɑ���̒��_�����݂���ꍇTRUE��Ԃ�
	for (int i = 0; i < 4; ++i) {
		if ((((_v[1].x - _v[0].x)*(_ver[i].y - _v[0].y)) - ((_ver[i].x - _v[0].x)*(_v[1].y - _v[0].y))) >= 0 &&
			(((_v[2].x - _v[1].x)*(_ver[i].y - _v[1].y)) - ((_ver[i].x - _v[1].x)*(_v[2].y - _v[1].y))) >= 0 &&
			(((_v[3].x - _v[2].x)*(_ver[i].y - _v[2].y)) - ((_ver[i].x - _v[2].x)*(_v[3].y - _v[2].y))) >= 0 &&
			(((_v[0].x - _v[3].x)*(_ver[i].y - _v[3].y)) - ((_ver[i].x - _v[3].x)*(_v[0].y - _v[3].y))) >= 0)
		{
			return true;
		}
	}
	//����I�u�W�F�N�g�ڐ��ł��������������s��
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
		//�I�u�W�F�N�gA�̏I�_-�n�_�̕����x�N�g��
		Vec2 mainvec = _v[(i + 1) % 4] - _v[i % 4];
		for (int j = 0; j < 4; ++j)
		{
			//�I�u�W�F�N�gB�̏I�_-�n�_�̕����x�N�g��
			Vec2 subvec = _ver[(j + 1) % 4] - _ver[j % 4];
			Vec2 v = _ver[j % 4] - _v[i % 4];
			//�O�όv�Z
			float crs = KL::cross(mainvec, subvec);
			if (crs == 0.0f)
			{
				//���s���
				continue;
			}
			float crs_v1 = KL::cross(v, mainvec);
			float crs_v2 = KL::cross(v, subvec);
			float t1 = crs_v2 / crs;
			float t2 = crs_v1 / crs;
			if (t1 > 0.f && t1 < 1.f && t2 > 0.f && t2 < 1.f)
			{
				//�������Ă�
				return true;
			}
		}
	}
	return false;
}
//��`�~�~
bool BoxCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//���_���̃Z�b�g
	Vec2 _ver[1] = {
		{ b->hitBase.center_x,b->hitBase.center_y }
	};
	Vec2 _v[4] = {
		{ hitBase.x,hitBase.y },
	{ hitBase.w - 1,hitBase.y },
	{ hitBase.w - 1,hitBase.h },
	{ hitBase.x,hitBase.h }
	};
	//Box�^�̉�]�̓K�p
	KL::Rotate(angle, _v);
	//�~�̒��ɒ��_�����݂���ꍇTRUE��Ԃ�
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) >= b->hitBase.r*b->hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) >= b->hitBase.r*b->hitBase.r)
	{
		return true;
	}
	
	//�~�̒��ɐ��������݂���ꍇTRUE��Ԃ�
	for (int i = 0; i<4; i++) {
		if (KL::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<b->hitBase.r)
			return true;
	}
	return false;
}
//��`�~�_
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
//��`�~��
bool BoxCollider::GetHit(LineCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	return false;
}
//��`�~�J�v�Z��
bool BoxCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//���萶��
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
//��]�K�p
void BoxCollider::Rotate(const float _angle) {
	//��]�̒l���i�[
	this->angle = _angle;
}
//��]�擾
float BoxCollider::Rotate() const
{
	return this->angle;
}
//����
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
//�~�~��`
bool CircleCollider::GetHit(BoxCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//���_���̃Z�b�g
	Vec2 _ver[1] = {
		{ hitBase.center_x,hitBase.center_y }
	};
	Vec2 _v[4] = {
		{ b->hitBase.x,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.y },
	{ b->hitBase.w - 1,b->hitBase.h },
	{ b->hitBase.x,b->hitBase.h }
	};
	//Box�^�̉�]�̓K�p
	KL::Rotate(b->Rotate(), _v);
	//�~�̒��ɒ��_�����݂���ꍇTRUE��Ԃ�
	if ((((_v[1].x - _v[0].x)*(_ver[0].y - _v[0].y)) - ((_ver[0].x - _v[0].x)*(_v[1].y - _v[0].y))) >= hitBase.r*hitBase.r &&
		(((_v[2].x - _v[1].x)*(_ver[0].y - _v[1].y)) - ((_ver[0].x - _v[1].x)*(_v[2].y - _v[1].y))) >= hitBase.r*hitBase.r &&
		(((_v[3].x - _v[2].x)*(_ver[0].y - _v[2].y)) - ((_ver[0].x - _v[2].x)*(_v[3].y - _v[2].y))) >= hitBase.r*hitBase.r &&
		(((_v[0].x - _v[3].x)*(_ver[0].y - _v[3].y)) - ((_ver[0].x - _v[3].x)*(_v[0].y - _v[3].y))) >= hitBase.r*hitBase.r)
	{
		return true;
	}
	//�~�̒��ɐ��������݂���ꍇTRUE��Ԃ�
	for (int i = 0; i<4; i++) {
		if (KL::get_distance(_ver[0].x, _ver[0].y, _v[i].x, _v[i].y, _v[(i + 1) % 4].x, _v[(i + 1) % 4].y)<hitBase.r)
			return true;
	}
	return false;
}
//�~�~�~
bool CircleCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//�~�͈͓̔��ɑ���̉~�͈̔͂����݂���ꍇTRUE��Ԃ�
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
//�~�~�_
bool CircleCollider::GetHit(PointCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//���_���̃Z�b�g
	Vec2 _ver[1] = {
		{ hitBase.center_x,hitBase.center_y }
	};
	Vec2 _v[1] = {
		{ b->hitBase.x,b->hitBase.y },
	};
	//�~�̒��ɒ��_�����݂���ꍇTRUE��Ԃ�
	if (((_ver[0].x - _v[0].x) * (_ver[0].x - _v[0].x)) + ((_ver[0].y - _v[0].y) * (_ver[0].y - _v[0].y)) <= this->hitBase.r * this->hitBase.r)
	{
		return true;
	}
	return false;
}
//�~�~��
bool CircleCollider::GetHit(LineCollider* b)
{
	return false;
}
//�~�~�J�v�Z��
bool CircleCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//���萶��
void CircleCollider::CreateCollision()
{
	this->hitBase = {
		transform->position.x,
		transform->position.y,
		(transform->scale.x * radius.x) / 2.f
	};
}
//����
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
//�_�~��`
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
//�_�~�~
bool PointCollider::GetHit(CircleCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	//���_���̃Z�b�g
	Vec2 _ver[1] = {
		{ b->hitBase.center_x,b->hitBase.center_y }
	};
	Vec2 _v[1] = {
		{ hitBase.x,hitBase.y },
	};
	//�~�̒��ɒ��_�����݂���ꍇTRUE��Ԃ�
	if (((_ver[0].x - _v[0].x) * (_ver[0].x - _v[0].x)) + ((_ver[0].y - _v[0].y) * (_ver[0].y - _v[0].y)) <= b->hitBase.r * b->hitBase.r)
	{
		return true;
	}
	return false;
}
//�_�~�_
bool PointCollider::GetHit(PointCollider* b)
{
	this->CreateCollision();
	b->CreateCollision();
	return this->hitBase == b->hitBase;
}
//�_�~��
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
//�_�~�J�v�Z��
bool PointCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//���萶��
void PointCollider::CreateCollision()
{
	this->hitBase = transform->position;
}
//����
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
//���~��`
bool LineCollider::GetHit(BoxCollider* b)
{
	return false;
}
//���~�~
bool LineCollider::GetHit(CircleCollider* b)
{
	return false;
}
//���~��
bool LineCollider::GetHit(LineCollider* b)
{
	return false;
}
//���~�_
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
//���~�J�v�Z��
bool LineCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//���萶��
void LineCollider::CreateCollision()
{
	this->hitBase[0] = transform->position;
	this->hitBase[1] = transform->scale;
}
//����
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
//�J�v�Z���~�J�v�Z��
bool CapsuleCollider::GetHit(CapsuleCollider* b)
{
	return false;
}
//�J�v�Z���~��`
bool CapsuleCollider::GetHit(BoxCollider* b)
{
	return false;
}
//�J�v�Z���~�~
bool CapsuleCollider::GetHit(CircleCollider* b)
{
	return false;
}
//�J�v�Z���~�_
bool CapsuleCollider::GetHit(PointCollider* b)
{
	return false;
}
//�J�v�Z���~��
bool CapsuleCollider::GetHit(LineCollider* b)
{
	return false;
}
//����
bool CapsuleCollider::Hit(Collider* collision)
{
	return collision->Hit(this);
}