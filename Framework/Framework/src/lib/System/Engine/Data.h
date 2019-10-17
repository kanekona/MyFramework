
#pragma once
#define PI 3.1415926f
class CCircle;
class CVec3;
class CVec2;
class CVec2Int;
class CMat4;
class CMat4x4;
class CBox3D;
class CBox2D;
class CColor;
class CTransform;

/**
*@brief	円データ型
*/
class CCircle
{
public:
	float cEntry_x, cEntry_y, r;
	CCircle();
	CCircle(const float, const float, const float);
	CCircle(const int, const int, const int);
	CCircle(const CCircle&);
};
/**
*@brief	3次元Vector
*/
class CVec3 {
public:
	float x, y, z;
	CVec3();
	CVec3(const float, const float, const float);
	CVec3(const int, const int, const int);
};
/**
*@brief	2次元Vector
*/
class CVec2
{
public:
	float x, y;
	CVec2();
	CVec2(const float, const float);
	CVec2(const int, const int);
	CVec2(const CVec2Int&);
	void Set(const int, const int);
	void Set(const float, const float);
	void Normalize();
	float GetLength();

	CVec2 operator+(const CVec2&);
	CVec2 operator+(const CVec2Int&);
	CVec2 operator-(const CVec2&);
	CVec2 operator-(const CVec2Int&);
	CVec2 operator*(const float);
	CVec2 operator*(const CVec2&);
	CVec2 operator*(const CVec2Int&);
	CVec2 operator/(const float);
	void operator+=(const CVec2&);
	void operator+=(const CVec2Int&);
	void operator*=(const float);
	void operator*=(const CVec2&);
	void operator*=(const CVec2Int&);
	void operator/=(const float);
	void operator-=(const CVec2&);
	void operator-=(const CVec2Int&);
	bool operator==(const CVec2&);
	bool operator==(const CVec2Int&);
	bool operator!=(const CVec2&);
	bool operator!=(const CVec2Int&);
};
class CVec2Int
{
public:
	int x, y;
	CVec2Int();
	CVec2Int(const int, const int);
	CVec2Int(const float, const float);
	CVec2Int(const CVec2&);
	void Set(const int, const int);
	void Set(const float, const float);
	void Normalize();
	float GetLength();

	CVec2Int operator+(const CVec2&);
	CVec2Int operator+(const CVec2Int&);
	CVec2Int operator-(const CVec2&);
	CVec2Int operator-(const CVec2Int&);
	CVec2Int operator*(const int);
	CVec2Int operator*(const CVec2&);
	CVec2Int operator*(const CVec2Int&);
	CVec2Int operator/(const int);
	void operator+=(const CVec2&);
	void operator+=(const CVec2Int&);
	void operator*=(const int);
	void operator*=(const CVec2&);
	void operator*=(const CVec2Int&);
	void operator/=(const int);
	void operator-=(const CVec2&);
	void operator-=(const CVec2Int&);
	bool operator==(const CVec2&);
	bool operator==(const CVec2Int&);
	bool operator!=(const CVec2&);
	bool operator!=(const CVec2Int&);
};
/**
*@brief	2*2行列
*/
class CMat4 {
public:
	float mat4[4];
	CMat4(const float, const float, const float, const float);
	CMat4(const int, const int, const int, const int);
};
/**
*@brief	4*4行列
*/
class CMat4x4 {
public:
	float mat4[16];
	CMat4x4(const float ex, const float ey, const float ez, const float ew,
		const float sx, const float sy, const float sz, const float sw,
		const float dx, const float dy, const float dz, const float dw,
		const float rx, const float ry, const float rz, const float rw);
	CMat4x4(const int ex, const int ey, const int ez, const int ew,
		const int sx, const int sy, const int sz, const int sw,
		const int dx, const int dy, const int dz, const int dw,
		const int rx, const int ry, const int rz, const int rw);
};
/**
*@brief	3DBoxデータ型
*/
class CBox3D {
public:
	float x, y, z, w, h, d;
	CBox3D();
	CBox3D(const float ex, const float ey, const float ez, const float ew, const float eh, const float ed);
	CBox3D(const CBox3D &_e);
private:
	int IsOdd(const int n, const int a, const int b);
	int InOdd(const int n, const int a, const int b);
	int IfOdd(const int n, const int a, const int b);
};
/**
*@brief 2Dデータ型
*/
class CBox2D {
public:
	float x, y, w, h;
	CBox2D();
	CBox2D(const float x_, const float y_, const float w_, const float h_);
	CBox2D(const int x_, const int y_, const int w_, const int h_);
	CBox2D(const CBox2D& b_);
	CBox2D(const CVec2& p, const CVec2& s);
	void Offset(const float x_, const float y_);
	void Offset(const int x_, const int y_);
	void Offset();
	void OffsetSize();
	void OffsetCEntrySize();
	CBox2D operator+(const CBox2D& b);
	CBox2D operator-(const CBox2D& b);
	CBox2D operator*(const CBox2D& b);
	void operator+=(const CBox2D& b);
	void operator-=(const CBox2D& b);
	void operator*=(const CBox2D& b);
};
/**
*@brief	色データ
*/
class CColor
{
public:
	float red, green, blue, alpha;
	CColor();
	CColor(const float r, const float g, const float b, const float a);
	CColor(const int r, const int g, const int b, const int a);
	unsigned int Getcolor() const;
	void operator+=(const CColor& b);
	void operator*=(const CColor& b);
	void operator-=(const CColor& b);
	CColor operator+(const CColor&);
	CColor operator-(const CColor&);
	CColor operator*(const CColor&);
	static CColor one;
};
/**
*@brief	Transform
*/
class CTransform
{
public:
	CTransform();
	CTransform(const CVec2& pos, const CVec2& scale);
	CTransform(const CVec2& pos, const CVec2& scale, const float angle);
	CVec2 position;
	CVec2 scale;
	float angle;
	void operator+=(const CTransform& t);
	CTransform operator+(const CTransform& t);
};

/**
*namespace KL
*@brief	数学計算
*/
namespace KL
{
	float ToRadian(const  float  degree_);
	void Cross(float*, float*, float*);
	float inner(const CVec2&, const CVec2&);
	float inner(const float, const float, const float, const float);
	float inner(const int, const int, const int, const int);
	float cross(const CVec2&, const CVec2&);
	float cross(const float, const float, const float, const float);
	float cross(const int, const int, const int, const int);
	float doubleinner(const CVec2&);
	float doubleinner(const float, const float);
	float doubleinner(const int, const int);
	float get_distance(const float, const float, const float, const float, const float, const float);
	bool innerJudge(const CVec2* line, const CVec2* point);
	//bool crossJudge(const Vec2* line1, const Vec2* line2);
#ifdef ENGINE_DEVELOP
	template <class T> bool Destroy(T* t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
			return true;
		}
		return false;
	}
	template <class T> bool Destroy(const T* t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
			return true;
		}
		return false;
	}
#endif
}