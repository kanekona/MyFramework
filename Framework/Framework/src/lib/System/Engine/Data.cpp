#include "Data.h"

#include <cmath>

CCircle::CCircle()
	:cEntry_x(0.f), cEntry_y(0.f), r(0.f)
{}
CCircle::CCircle(const float _x, const float _y, const float _r)
	:r(_r), cEntry_x(_x), cEntry_y(_y)
{}
CCircle::CCircle(const int _x, const int _y, const int _r)
	:r((float)_r), cEntry_x((float)_x), cEntry_y((float)_y)
{}
CCircle::CCircle(const CCircle&_c)
	:r(_c.r), cEntry_x(_c.cEntry_x), cEntry_y(_c.cEntry_y)
{}
CVec3::CVec3()
	:x(0.f), y(0.f), z(0.f)
{}
CVec3::CVec3(const float ex, const float ey, const float ez)
	:x(ex), y(ey), z(ez)
{}
CVec3::CVec3(const int ex, const int ey, const int ez)
	:x((float)ex), y((float)ey), z((float)ez)
{}
CVec2::CVec2()
	:x(0.f), y(0.f)
{}
CVec2::CVec2(const float ex, const float ey)
	:x(ex), y(ey)
{}
CVec2::CVec2(const int ex, const int ey)
	:x((float)ex), y((float)ey)
{}
CVec2::CVec2(const CVec2Int& vec)
	:x((float)vec.x),y((float)vec.y)
{}
void CVec2::Set(const int vx, const int vy)
{
	x = (float)vx;
	y = (float)vy;
}
void CVec2::Set(const float vx, const float vy)
{
	x = vx;
	y = vy;
}
void CVec2::Normalize() {
	float len = GetLength();
	if (len == 0) { return; }
	x /= len;
	y /= len;
}
float CVec2::GetLength() {
	return powf(x*x + y * y, 0.5f);
}
CVec2 CVec2::operator+(const CVec2& v) { return CVec2(x + v.x, y + v.y); }
CVec2 CVec2::operator+(const CVec2Int& v) { return CVec2(x + (float)v.x, y + (float)v.y); }
CVec2 CVec2::operator-(const CVec2& v) { return CVec2(x - v.x, y - v.y); }
CVec2 CVec2::operator-(const CVec2Int& v) { return CVec2(x - (float)v.x, y - (float)v.y); }
CVec2 CVec2::operator*(const float n) { return CVec2(x*n, y*n); }
CVec2 CVec2::operator/(const float n) { return CVec2(x / n, y / n); }
CVec2 CVec2::operator*(const CVec2& v) { return(CVec2(x*v.x, y*v.y)); }
CVec2 CVec2::operator*(const CVec2Int& v) { return CVec2(x * (float)v.x, y * (float)v.y); }
void CVec2::operator+=(const CVec2& v) { x += v.x; y += v.y; }
void CVec2::operator+=(const CVec2Int& v) { x += (float)v.x; y += (float)v.y; }
void CVec2::operator*=(const float n) { x *= n; y *= n; }
void CVec2::operator*=(const CVec2& v) { x *= v.x; y *= v.y; };
void CVec2::operator*=(const CVec2Int& v) { x *= (float)v.x; y *= (float)v.y; }
void CVec2::operator/=(const float n) { x /= n; y /= n; }
void CVec2::operator-=(const CVec2& v) { x -= v.x; y -= v.y; }
void CVec2::operator-=(const CVec2Int& v) { x -= (float)v.x; y -= (float)v.y; }
bool CVec2::operator==(const CVec2& v) { return x == v.x && y == v.y; }
bool CVec2::operator==(const CVec2Int& v) { return x == (float)v.x && y == (float)v.y; }
bool CVec2::operator!=(const CVec2& v) { return x != v.x || y != v.y; }
bool CVec2::operator!=(const CVec2Int& v) { return x != (float)v.x || y != (float)v.y; }

CVec2Int::CVec2Int()
	:x(0),y(0)
{}
CVec2Int::CVec2Int(const int vx,const int vy)
	:x(vx),y(vy)
{}
CVec2Int::CVec2Int(const float vx, const float vy)
	: x((int)vx), y((int)vy)
{}
CVec2Int::CVec2Int(const CVec2& vec)
	:x((int)vec.x),y((int)vec.y)
{}
void CVec2Int::Set(const int vx, const int vy)
{
	x = vx;
	y = vy;
}
void CVec2Int::Set(const float vx, const float vy)
{
	x = (int)vx;
	y = (int)vy;
}
void CVec2Int::Normalize()
{
	float len = GetLength();
	if (len == 0) { return; }
	x /= (int)len;
	y /= (int)len;
}
float CVec2Int::GetLength()
{
	return powf((float)(x*x + y * y), 0.5f);
}
CVec2Int CVec2Int::operator+(const CVec2& v) { return CVec2Int(x + (int)v.x, y + (int)v.y); }
CVec2Int CVec2Int::operator+(const CVec2Int& v) { return CVec2Int(x + v.x, y + v.y); }
CVec2Int CVec2Int::operator-(const CVec2& v) { return CVec2Int(x - (int)v.x, y - (int)v.y); }
CVec2Int CVec2Int::operator-(const CVec2Int& v) { return CVec2Int(x - v.x, y - v.y); }
CVec2Int CVec2Int::operator*(const int v) { return CVec2Int(x * v, y * v); }
CVec2Int CVec2Int::operator*(const CVec2& v) { return CVec2Int(x * (int)v.x, y * (int)v.y); }
CVec2Int CVec2Int::operator*(const CVec2Int& v) { return CVec2Int(x * v.x, y * v.y); }
CVec2Int CVec2Int::operator/(const int v) { return CVec2Int(x / v, y / v); }
void CVec2Int::operator+=(const CVec2& v) { x += (int)v.x; y += (int)v.y; }
void CVec2Int::operator+=(const CVec2Int& v) { x += v.x; y += v.y; }
void CVec2Int::operator-=(const CVec2& v) { x -= (int)v.x; y -= (int)v.y; }
void CVec2Int::operator-=(const CVec2Int& v) { x -= v.x; y -= v.y; }
void CVec2Int::operator*=(const int v) { x *= v; y *= v; }
void CVec2Int::operator*=(const CVec2& v) { x *= (int)v.x; y *= (int)v.y; }
void CVec2Int::operator*=(const CVec2Int& v) { x *= v.x; y *= v.y; }
void CVec2Int::operator/=(const int v) { x /= v; y /= v; }
bool CVec2Int::operator==(const CVec2& v) { return x == (int)v.x && y == (int)v.y; }
bool CVec2Int::operator==(const CVec2Int& v) { return x == v.x && y == v.y; }
bool CVec2Int::operator!=(const CVec2& v) { return x != (int)v.x || y != (int)v.y; }
bool CVec2Int::operator!=(const CVec2Int& v) { return x != v.x || y != v.y; }


CMat4::CMat4(const float ex, const float ey, const float ez, const float ew)
{
	mat4[0] = ex;
	mat4[1] = ey;
	mat4[2] = ez;
	mat4[3] = ew;
}
CMat4::CMat4(const int ex, const int ey, const int ez, const int ew)
{
	mat4[0] = (float)ex;
	mat4[1] = (float)ey;
	mat4[2] = (float)ez;
	mat4[3] = (float)ew;
}

CMat4x4::CMat4x4(const float ex, const float ey, const float ez, const float ew,
	const float sx, const float sy, const float sz, const float sw,
	const float dx, const float dy, const float dz, const float dw,
	const float rx, const float ry, const float rz, const float rw) {
	mat4[0] = ex;
	mat4[1] = ey;
	mat4[2] = ez;
	mat4[3] = ew;
	mat4[4] = sx;
	mat4[5] = sy;
	mat4[6] = sz;
	mat4[7] = sw;
	mat4[8] = dx;
	mat4[9] = dy;
	mat4[10] = dz;
	mat4[11] = dw;
	mat4[12] = rx;
	mat4[13] = ry;
	mat4[14] = rz;
	mat4[15] = rw;
}
CMat4x4::CMat4x4(const int ex, const int ey, const int ez, const int ew,
	const int sx, const int sy, const int sz, const int sw,
	const int dx, const int dy, const int dz, const int dw,
	const int rx, const int ry, const int rz, const int rw) {
	mat4[0] = (float)ex;
	mat4[1] = (float)ey;
	mat4[2] = (float)ez;
	mat4[3] = (float)ew;
	mat4[4] = (float)sx;
	mat4[5] = (float)sy;
	mat4[6] = (float)sz;
	mat4[7] = (float)sw;
	mat4[8] = (float)dx;
	mat4[9] = (float)dy;
	mat4[10] = (float)dz;
	mat4[11] = (float)dw;
	mat4[12] = (float)rx;
	mat4[13] = (float)ry;
	mat4[14] = (float)rz;
	mat4[15] = (float)rw;
}

CBox3D::CBox3D()
	:x(0.f), y(0.f), z(0.f), w(0.f), h(0.f), d(0.f)
{}
CBox3D::CBox3D(const float ex, const float ey, const float ez, const float ew, const float eh, const float ed)
	:x(ex), y(ey), z(ez), w(ew), h(eh), d(ed)
{}
CBox3D::CBox3D(const CBox3D &_e)
	:x(_e.x), y(_e.y), z(_e.z), w(_e.w), h(_e.h), d(_e.d)
{}
int CBox3D::IsOdd(const int n, const int a, const int b) {
	if (n % 2 == 0) {
		return a;
	}
	return b;
}
int CBox3D::InOdd(const int n, const int a, const int b) {
	if ((n / 2) % 2 == 0) {
		return a;
	}
	return b;
}
int CBox3D::IfOdd(const int n, const int a, const int b) {
	if ((n / 4) % 2 == 0) {
		return a;
	}
	return b;
}

CBox2D::CBox2D()
	:x(0), y(0), w(0), h(0)
{}
CBox2D::CBox2D(const float x_, const float y_, const float w_, const float h_)
	:x(x_), y(y_), w(w_), h(h_)
{}
CBox2D::CBox2D(const int x_, const int y_, const int w_, const int h_)
	:x((float)x_), y((float)y_), w((float)w_), h((float)h_)
{}
CBox2D::CBox2D(const CBox2D& b_)
	:x(b_.x), y(b_.y), w(b_.w), h(b_.h)
{}
CBox2D::CBox2D(const CVec2& p, const CVec2& s)
	:x(p.x), y(p.y), w(s.x), h(s.y)
{}
void CBox2D::Offset(const float x_, const float y_)
{
	x += x_;
	y += y_;
}
void CBox2D::Offset(const int x_, const int y_)
{
	x += (float)x_;
	y += (float)y_;
}
void CBox2D::OffsetSize()
{
	w = w + x;
	h = h + y;
}
void CBox2D::Offset()
{
	x -= w / 2;
	y -= h / 2;
}
void CBox2D::OffsetCEntrySize()
{
	Offset();
	OffsetSize();
}
//Box2D Box2D::operator+(const Box2D& b) { return Box2D(x += b.x, y += b.y, w += b.w, h += b.h); }
//Box2D Box2D::operator+(const Box2D& b) { x += b.x, y += b.y, w += b.w, h += b.h; return *this; }
CBox2D CBox2D::operator+(const CBox2D& b) { return CBox2D(x + b.x, y + b.y, w + b.w, h + b.h); }
//Box2D Box2D::operator-(const Box2D& b) { return Box2D(x -= b.x, y -= b.y, w -= b.w, h -= b.h); }
CBox2D CBox2D::operator-(const CBox2D& b) { return CBox2D(x - b.x, y - b.y, w - b.w, h - b.h); }
//Box2D Box2D::operator*(const Box2D& b) { return Box2D(x *= b.x, y *= b.y, w *= b.w, h *= b.h); }
CBox2D CBox2D::operator*(const CBox2D& b) { return CBox2D(x - b.x, y - b.y, w - b.w, h - b.h); }
void CBox2D::operator+=(const CBox2D& b){ { x += b.x; y += b.y; w += b.w; h += b.h; } }
void CBox2D::operator-=(const CBox2D& b){ { x -= b.x; y -= b.y; w -= b.w; h -= b.h; } }
void CBox2D::operator*=(const CBox2D& b){ { x *= b.x; y *= b.y; w *= b.w; h *= b.h; } }
CColor::CColor()
	:red(1.f), green(1.f), blue(1.f), alpha(1.f)
{}
CColor::CColor(const float r, const float g, const float b, const float a)
	:red(r), green(g), blue(b), alpha(a)
{}
CColor::CColor(const int r, const int g, const int b, const int a)
	:red((float)r), green((float)g), blue((float)b), alpha((float)a)
{}
unsigned int CColor::Getcolor() const
{
	unsigned char r = (unsigned char)(red * 255.0f);
	unsigned char g = (unsigned char)(green * 255.0f);
	unsigned char b = (unsigned char)(blue * 255.0f);
	unsigned char a = (unsigned char)(alpha * 255.0f);

	return (r) | (g << 8) | (b << 16) | (a << 24);
}
void CColor::operator+=(const CColor& b) { red += b.red; green += b.green; blue += b.blue; alpha += b.alpha; }
void CColor::operator*=(const CColor& b) { red *= b.red; green *= b.green; blue *= b.blue; alpha *= b.alpha; }
void CColor::operator-=(const CColor& b) { red -= b.red; green -= b.green; blue -= b.blue; alpha -= b.alpha; }
//Color Color::operator+(const Color& b) { return Color(red += b.red, green += b.green, blue += b.blue, alpha += b.alpha); }
//Color Color::operator-(const Color& b){ return Color(red -= b.red, green -= b.green, blue -= b.blue, alpha -= b.alpha); }
//Color Color::operator*(const Color& b){ return Color(red *= b.red, green *= b.green, blue *= b.blue, alpha *= b.alpha); }
CColor CColor::operator+(const CColor& b) { red += b.red, green += b.green, blue += b.blue, alpha += b.alpha; return *this; }
CColor CColor::operator-(const CColor& b) { red -= b.red, green -= b.green, blue -= b.blue, alpha -= b.alpha; return *this; }
CColor CColor::operator*(const CColor& b) { red *= b.red, green *= b.green, blue *= b.blue, alpha *= b.alpha; return *this; }

CTransform::CTransform()
{
	angle = 0.0f;
}
CTransform::CTransform(const CVec2& pos, const CVec2& s)
{
	position = pos;
	scale = s;
	angle = 0.0f;
}
CTransform::CTransform(const CVec2& pos, const CVec2& s,const float a)
{
	position = pos;
	scale = s;
	angle = a;
}
void CTransform::operator+=(const CTransform& t) { position += t.position; scale += t.scale; angle += t.angle; }
CTransform CTransform::operator+(const CTransform& t) { return CTransform(position + t.position, scale + t.scale, angle + t.angle); }

float KL::ToRadian(const  float  degree_)
{
	return  degree_ * PI / 180.0f;
}
void KL::Cross(float* src1, float* src2, float* dst) {
	dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
	dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
	dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
float KL::inner(const CVec2& _v1,const CVec2& _v2) {
	return ((_v1.x * _v2.x) + (_v1.y*_v2.y));
}
float KL::inner(const float _x1, const float _y1, const float _x2, const float _y2) {
	return ((_x1 * _x2) + (_y1*_y2));
}
float KL::inner(const int _x1, const int _y1, const int _x2, const int _y2) {
	return (float)((_x1 * _x2) + (_y1*_y2));
}
float KL::cross(const CVec2& _v1, const CVec2& _v2) {
	return ((_v1.x * _v2.y) - (_v1.y*_v2.x));
}
float KL::cross(const float _x1, const float _y1, const float _x2, const float _y2) {
	return ((_x1 * _y2) - (_y1*_x2));
}
float KL::cross(const int _x1, const int _y1, const int _x2, const int _y2) {
	return (float)((_x1 * _y2) - (_y1*_x2));
}
float KL::doubleinner(const CVec2& _v) {
	return inner(_v, _v);
}
float KL::doubleinner(const float _x, const float _y) {
	return inner(_x, _y, _x, _y);
}
float KL::doubleinner(const int _x, const int _y) {
	return inner(_x, _y, _x, _y);
}
float KL::get_distance(const float x, const float y, const float x1, const float y1, const float x2, const float y2) {
	float dx, dy, a, b, t, tx, ty;
	float distance;
	dx = (x2 - x1);
	dy = (y2 - y1);
	a = dx * dx + dy * dy;
	b = dx * (x1 - x) + dy * (y1 - y);
	t = -b / a;
	if (t < 0) t = 0;
	if (t > 1) t = 1;
	tx = x1 + dx * t;
	ty = y1 + dy * t;
	distance = sqrt((x - tx)*(x - tx) + (y - ty)*(y - ty));
	return distance;
}
bool KL::innerJudge(const CVec2* line, const CVec2* point) 
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
		{
			if (((
				((line + ((j + 1) % 4))->x - (line + j)->x)*
				((point + i)->y - (line + j)->y)) - 
				(((point + i)->x - (line + j)->x) * 
				((line + ((j + 1) % 4))->y - (line + j)->y))) 
				< 0)
			{
				return false;
			}
		}
	}
	return true;
}
//bool OG::crossJudge(const Vec2* line1, const Vec2* line2)
//{
//	for (int i = 0; i < 4; ++i)
//	{
//		//オブジェクトAの終点-始点の方向ベクトル
//		Vec2 mainvec = line1[(i + 1) % 4] - line1[i % 4];
//		Vec2 mainvec(((line1 + ((i + 1) % 4)) - (line1 + (i % 4))));
//		for (int j = 0; j < 4; ++j)
//		{
//			//オブジェクトBの終点-始点の方向ベクトル
//			Vec2 subvec = line2[(j + 1) % 4] - line2[j % 4];
//			Vec2 v = line2[j % 4] - line1[i % 4];
//			//外積計算
//			float crs = OG::cross(mainvec, subvec);
//			if (crs == 0.0f)
//			{
//				//平行状態
//				continue;
//			}
//			float crs_v1 = OG::cross(v, mainvec);
//			float crs_v2 = OG::cross(v, subvec);
//			float t1 = crs_v2 / crs;
//			float t2 = crs_v1 / crs;
//			if (t1 > 0.f && t1 < 1.f && t2 > 0.f && t2 < 1.f)
//			{
//				//交差してる
//				return true;
//			}
//		}
//	}
//	return false;
//}

CColor CColor::one = CColor(1.f, 1.f, 1.f, 1.f);