#include "Camera.h"
#include "Shader\shader.h"
//--------------------------------------------------
//@:Camera2Dclass									
//--------------------------------------------------
Camera2D::Camera2D()
	: collision(&transform)
{
}
Camera2D::Camera2D(const Box2D& pos)
	: collision(&transform)
{
	//各値をセットする
	cameraPos = pos;
	position = { 0,0 };
	scale = { pos.w,pos.h };
}
Camera2D::~Camera2D()
{

}
void Camera2D::Initialize(const Box2D& pos)
{
	//各値をセットする
	cameraPos = pos;
	position = { 0,0 };
	scale = { pos.w,pos.h };
}
void Camera2D::Update()
{
	//行列をプロジェクションモードに変更
	glMatrixMode(GL_PROJECTION);
	//行列の初期化
	glLoadIdentity();
	//元データが書き換わらないよう値の代入
	Box2D _camera(cameraPos);
	//初期設定値からの変更値
	_camera.x += position.x;
	_camera.y += position.y;
	_camera.w = scale.x;
	_camera.h = scale.y;
	_camera.OffsetSize();
	//描画縦横サイズの指定
	transform.position = { position.x + scale.x / 2,position.y + scale.y / 2 };
	transform.scale = scale * 1.5f;
	glOrtho(_camera.x, _camera.w, _camera.h, _camera.y, -1.0f, 1.0f);
	SetProjectionMatrix(_camera.x, _camera.w, _camera.h, _camera.y, -1.0, 1.0f);
}
void Camera2D::MovePos(const Vec2& est)
{
	//位置を加算する
	position += est;
}
void Camera2D::SetPos(const Vec2& est)
{
	//位置を上書きする
	position = est;
}
void Camera2D::SetSize(const Vec2& size_)
{
	//サイズを上書きする
	scale = size_;
}
void Camera2D::MoveSize(const Vec2& size_)
{
	//サイズを加算する
	scale += size_;
}
void Camera2D::SetPos_x(const float& x_)
{
	position.x = x_;
}
void Camera2D::SetPos_y(const float& y_)
{
	position.y = y_;
}
void Camera2D::SetSize_w(const float& w_)
{
	scale.x = w_;
}
void Camera2D::SetSize_h(const float& h_)
{
	scale.y = h_;
}
const Vec2& Camera2D::GetPos() const
{
	//位置を返す
	return position;
}
const Vec2& Camera2D::GetSize() const
{
	//サイズを返す
	return scale;
}
void Camera2D::SetProjectionMatrix(float cl, float cr, float cb, float ct, float cn, float cf)
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
GLfloat* Camera2D::GetProjectionMatrix()
{
	return projectionMatrix;
}
CircleCollider* Camera2D::GetCollision()
{
	return &collision;
}