#include "Camera.h"
#include "Shader\shader.h"
//--------------------------------------------------
//@:Camera2Dclass									
//--------------------------------------------------
CCamera2D::CCamera2D()
	: collision(&transform)
{
}
CCamera2D::CCamera2D(const CBox2D& pos)
	: collision(&transform)
{
	//�e�l���Z�b�g����
	cameraPos = pos;
	position = { 0,0 };
	scale = { pos.w,pos.h };
}
CCamera2D::~CCamera2D()
{

}
void CCamera2D::Initialize(const CBox2D& pos)
{
	//�e�l���Z�b�g����
	cameraPos = pos;
	position = { 0,0 };
	scale = { pos.w,pos.h };
}
void CCamera2D::Update()
{
	//�s����v���W�F�N�V�������[�h�ɕύX
	glMatrixMode(GL_PROJECTION);
	//�s��̏�����
	glLoadIdentity();
	//���f�[�^�����������Ȃ��悤�l�̑��
	CBox2D _camera(cameraPos);
	//�����ݒ�l����̕ύX�l
	_camera.x += position.x;
	_camera.y += position.y;
	_camera.w = scale.x;
	_camera.h = scale.y;
	_camera.OffsetSize();
	//�`��c���T�C�Y�̎w��
	transform.position = { position.x + scale.x / 2,position.y + scale.y / 2 };
	transform.scale = scale * 1.5f;
	glOrtho(_camera.x, _camera.w, _camera.h, _camera.y, -1.0f, 1.0f);
	SetProjectionMatrix(_camera.x, _camera.w, _camera.h, _camera.y, -1.0, 1.0f);
}
void CCamera2D::MovePos(const CVec2& est)
{
	//�ʒu�����Z����
	position += est;
}
void CCamera2D::SetPos(const CVec2& est)
{
	//�ʒu���㏑������
	position = est;
}
void CCamera2D::SetSize(const CVec2& size_)
{
	//�T�C�Y���㏑������
	scale = size_;
}
void CCamera2D::MoveSize(const CVec2& size_)
{
	//�T�C�Y�����Z����
	scale += size_;
}
void CCamera2D::SetPos_x(const float& x_)
{
	position.x = x_;
}
void CCamera2D::SetPos_y(const float& y_)
{
	position.y = y_;
}
void CCamera2D::SetSize_w(const float& w_)
{
	scale.x = w_;
}
void CCamera2D::SetSize_h(const float& h_)
{
	scale.y = h_;
}
const CVec2& CCamera2D::GetPos() const
{
	//�ʒu��Ԃ�
	return position;
}
const CVec2& CCamera2D::GetSize() const
{
	//�T�C�Y��Ԃ�
	return scale;
}
void CCamera2D::SetProjectionMatrix(float cl, float cr, float cb, float ct, float cn, float cf)
{
	projectionMatrix[0] = 2.f / (cr - cl);
	projectionMatrix[1] = 0.f;
	projectionMatrix[2] = 0.f;
	projectionMatrix[3] = (cr + cl) / (cr - cl) * -1;
	projectionMatrix[4] = 0.f;
	projectionMatrix[5] = 2.f / (ct - cb);
	projectionMatrix[6] = 0.f;
	projectionMatrix[7] = (ct + cb) / (ct - cb) * -1;
	projectionMatrix[8] = 0.f;
	projectionMatrix[9] = 0.f;
	projectionMatrix[10] = 2.f / (cf - cn);
	projectionMatrix[11] = (cf + cn) / (cf - cn) * -1;
	projectionMatrix[12] = 0.f;
	projectionMatrix[13] = 0.f;
	projectionMatrix[14] = 0.f;
	projectionMatrix[15] = 1.0f;
}
const GLfloat* CCamera2D::GetProjectionMatrix() const
{
	return projectionMatrix;
}
const CCircleCollider* CCamera2D::GetCollision() const
{
	return &collision;
}

void CCamera2D::ReverseProjectionMatrix(GLfloat* out)
{
	//���f�[�^�����������Ȃ��悤�l�̑��
	CBox2D _camera(cameraPos);
	//�����ݒ�l����̕ύX�l
	_camera.x += position.x;
	_camera.y += position.y;
	_camera.w = scale.x;
	_camera.h = scale.y;
	_camera.OffsetSize();
	out[0] = 2.f / (_camera.w - _camera.x);
	out[1] = 0.f;
	out[2] = 0.f;
	out[3] = (_camera.w + _camera.x) / (_camera.w - _camera.x) * -1;
	out[4] = 0.f;
	out[5] = 2.f / (_camera.h - _camera.y);
	out[6] = 0.f;
	out[7] = (_camera.h + _camera.y) / (_camera.h - _camera.y) * -1;
	out[8] = 0.f;
	out[9] = 0.f;
	out[10] = 2.f / (1.f - (-1.f));
	out[11] = (1.f + (-1.f)) / (1.f - (-1.f)) * -1;
	out[12] = 0.f;
	out[13] = 0.f;
	out[14] = 0.f;
	out[15] = 1.0f;
}
