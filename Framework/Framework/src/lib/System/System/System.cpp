#include "System.h"
#include <cctype>
#include <algorithm>
namespace KL {
	void MulitMatrixf(GLfloat*src1, GLfloat*src2, GLfloat*dst) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				dst[y * 4 + x] = src2[y * 4] * src1[x] + src2[y * 4 + 1] * src1[x + 4] + src2[y * 4 + 2] * src1[x + 8] + src2[y * 4 + 3] * src1[x + 12];
			}
		}
	}
	void Normalize(GLfloat *v) {
		float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		if (m > 0.0f) { m = 1.0f / m; }
		else { m = 0.0f; }
		v[0] *= m;
		v[1] *= m;
		v[2] *= m;
	}
	void LineBoxDraw(const CBox2D* _b, const CColor& color, const float linewidth)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b)->w, (_b)->y);

		glVertex2f((_b)->w, (_b)->y);
		glVertex2f((_b)->w, (_b)->h);

		glVertex2f((_b)->w, (_b)->h);
		glVertex2f((_b)->x, (_b)->h);

		glVertex2f((_b)->x, (_b)->h);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineBoxDraw(const CBox2D* _b, const float linewidth, const CColor& color)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b)->w, (_b)->y);

		glVertex2f((_b)->w, (_b)->y);
		glVertex2f((_b)->w, (_b)->h);

		glVertex2f((_b)->w, (_b)->h);
		glVertex2f((_b)->x, (_b)->h);

		glVertex2f((_b)->x, (_b)->h);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineBoxDraw(const CVec2* _b, const CColor& color, const float linewidth)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);

		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glVertex2f((_b + 2)->x, (_b + 2)->y);

		glVertex2f((_b + 2)->x, (_b + 2)->y);
		glVertex2f((_b + 3)->x, (_b + 3)->y);

		glVertex2f((_b + 3)->x, (_b + 3)->y);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineBoxDraw(const CVec2* _b, const float linewidth, const CColor& color)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);

		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glVertex2f((_b + 2)->x, (_b + 2)->y);

		glVertex2f((_b + 2)->x, (_b + 2)->y);
		glVertex2f((_b + 3)->x, (_b + 3)->y);

		glVertex2f((_b + 3)->x, (_b + 3)->y);
		glVertex2f((_b)->x, (_b)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineDraw(const CVec2* _b, const CColor& color, const float linewidth)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineDraw(const CVec2* _b, const float linewidth, const CColor& color)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_LINES);
		glLineWidth(linewidth);
		glVertex2f((_b)->x, (_b)->y);
		glVertex2f((_b + 1)->x, (_b + 1)->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void LineOvalDraw(const CVec2* pos, const CVec2* scale, const float linewidth, const CColor& color)
	{
		KL::LineOvalDraw(pos->x, pos->y, scale->x, scale->y, linewidth, color);
	}
	void LineOvalDraw(const int x, const int y, const float ovalx, const float ovaly, const float linewidth, const CColor& color)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0)
		{
			float th2 = th1 + 10.0;
			float th1_rad = th1 / 180.0 * PI;
			float th2_rad = th2 / 180.0 * PI;

			float x1 = cos(th1_rad)*(ovalx);
			float y1 = sin(th1_rad)*(ovaly);
			float x2 = cos(th2_rad)*(ovalx);
			float y2 = sin(th2_rad)*(ovaly);

			glBegin(GL_LINES);
			glLineWidth(linewidth);
			glVertex2f(x1 + x, y1 + y);
			glVertex2f(x2 + x, y2 + y);
			glEnd();
		}
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void PointDraw(const CVec2* pos, const CColor& color, const float linewidth)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_POINTS);
		glPointSize(linewidth);
		glVertex2f(pos->x, pos->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void PointDraw(const CVec2* pos, const float linewidth, const CColor& color)
	{
		glColor4f(color.red, color.green, color.blue, color.alpha);
		glBegin(GL_POINTS);
		glPointSize(linewidth);
		glVertex2f(pos->x, pos->y);
		glEnd();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void Rotate(const float _ang, CVec2* _b)
	{
		//ラジアンの値に変更
		float tora = KL::ToRadian(_ang);
		//原点を指定
		CVec2 center(((_b + 2)->x + (_b)->x) / 2, ((_b + 2)->y + (_b)->y) / 2);
		//回転軸の原点の値を導く
		GLfloat v[]
		{
			_b->x - center.x,_b->y - center.y,
			(_b + 1)->x - center.x,(_b + 1)->y - center.y,
			(_b + 2)->x - center.x,(_b + 2)->y - center.y,
			(_b + 3)->x - center.x,(_b + 3)->y - center.y,
		};
		//回転行列の生成
		GLfloat ma[4] = {
			cosf(tora),-sinf(tora),
			sinf(tora),cosf(tora),
		};
		//回転行列の計算
		(_b)->x = (*(v) * *(ma)) + (*(v + 1)* *(ma + 1));
		(_b)->y = (*(v) * *(ma + 2)) + (*(v + 1)* *(ma + 3));

		(_b + 1)->x = (*(v + 2)* *(ma)) + (*(v + 3)* *(ma + 1));
		(_b + 1)->y = (*(v + 2)* *(ma + 2)) + (*(v + 3)* *(ma + 3));

		(_b + 2)->x = (*(v + 4)* *(ma)) + (*(v + 5)* *(ma + 1));
		(_b + 2)->y = (*(v + 4)* *(ma + 2)) + (*(v + 5)* *(ma + 3));

		(_b + 3)->x = (*(v + 6)* *(ma)) + (*(v + 7)* *(ma + 1));
		(_b + 3)->y = (*(v + 6)* *(ma + 2)) + (*(v + 7)* *(ma + 3));

		//回転軸の原点の移動した分を元に戻す
		(_b)->x = (_b)->x + center.x;
		(_b)->y = (_b)->y + center.y;

		(_b + 1)->x = (_b + 1)->x + center.x;
		(_b + 1)->y = (_b + 1)->y + center.y;

		(_b + 2)->x = (_b + 2)->x + center.x;
		(_b + 2)->y = (_b + 2)->y + center.y;

		(_b + 3)->x = (_b + 3)->x + center.x;
		(_b + 3)->y = (_b + 3)->y + center.y;
	}
}
void KL::BackColor(const CColor& color)
{
	glClearColor((GLclampf)color.red, (GLclampf)color.green, (GLclampf)color.blue, (GLclampf)color.alpha);
}
void KL::BackColor(const float& red, const float& green, const float& blue, const float& alpha)
{
	glClearColor((GLclampf)red, (GLclampf)green, (GLclampf)blue, (GLclampf)alpha);
}
int KL::mbclen(const char* c)
{
	if ((*c & 0xc0) == 0x80)
	{
		return 2;
	}
	else if ((*c & 0x80) == 0)
	{
		return 1;
	}
	return 0;
}
void KL::cout(const CBox2D& b)
{
	std::cout << "x " << b.x << ":y " << b.y << ":w " << b.w << ":h " << b.h;
}
void KL::cout(const CVec2& v)
{
	std::cout << "x " << v.x << ":y " << v.y;
}
void KL::cout(const CColor& c)
{
	std::cout << "red " << c.red << ":green " << c.green << ":blue " << c.blue << ":alpha " << c.alpha;
}
void KL::cout(const CVec3& v)
{
	std::cout << "x " << v.x << ":y " << v.y << ":z " << v.z;
}
bool KL::Data_Cipher(const std::string& in_path, const std::string& out_path)
{
	char c;
	std::ifstream ifs(in_path, std::ios::in | std::ios::binary);
	if (!ifs) {
		return false;
	}

	std::ofstream ofs(out_path, std::ios::in | std::ios::binary);

	int i = 0;

	while (ifs.get(c)) {
		if (c != '\n')
		{
			c = (char)(c ^ randomCipher[i]);//データcの内容を暗号化
		}
		ofs << c;
		++i;
		if (i >= 40) {
			i = 0;
		}
	}
	ifs.close();
	ofs.close();
	return true;
}
std::string KL::Data_Composite(std::ifstream& ifs)
{
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);
	int j = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != '\n')
		{
			str[i] = (char)(str[i] ^ randomCipher[j]);
		}
		++j;
		if (j >= 40) {
			j = 0;
		}
	}
	return str;
}
void KL::OutDebugData(const std::string& out_path, const std::string& text)
{
	std::string path = "./data/debug/" + out_path;
	std::ofstream ofs(path, std::ios::app | std::ios::binary);
	if (!ofs)
	{
		std::cout << "ファイルが存在しない/生成に失敗しました\n";
		return;
	}
	ofs << text;
}
void KL::DataClear(const std::string& path)
{
	std::ofstream ofs(path, std::ios::trunc);
	if (!ofs)
	{
		std::cout << "ファイルは存在しません\n";
		return;
	}
	ofs.close();
}
bool KL::CheckText(std::string* first, std::string* second)
{
	for (unsigned int i = 0; i < first->size(); ++i)
	{
		if (first->at(i) == second->at(0))
		{
			std::string data = first->substr(i, first->size() - 1);
			if (data == *second)
			{
				return true;
			}
		}
	}
	return false;
}
void KL::FileCreate(const std::string& path, std::vector<std::string>& data)
{
	std::ofstream ofs(path);
	for (int i = 0; i < data.size(); ++i)
	{
		ofs << data[i] << "\n";
	}
	ofs.close();
}
bool KL::StringisNumber(const std::string& str)
{
	return std::all_of(str.cbegin(), str.cend(), std::isdigit);
}
bool KL::StringFromNumber(const std::string & str, float * out)
{
	if (!StringisNumber(str))
	{
		return false;
	}
	*out = std::stof(str);
	return true;
}
bool KL::StringFromNumber(const std::string & str, int * out)
{
	if (!StringisNumber(str))
	{
		return false;
	}
	*out = std::stoi(str);
	return true;
}
bool KL::StringFromStrID(const std::string& str, CStrID* out)
{
	CStrID id(str);
	*out = id;
	return true;
}
unsigned int KL::Count(const std::string& str, const char c)
{
	return static_cast<unsigned int>(std::count(str.cbegin(), str.cend(), c));
}
std::string* KL::SplitString(const std::string& text, const char c, int* out)
{
	*out = KL::Count(text, c) + 1;
	std::string* str = new std::string[*out];
	//stringはgetlineに非対応なので対応しているstrigstreamに文字列を一度渡してやる必要がある
	std::stringstream ss(text);
	//分割した文字列を格納するstring変数
	std::string line;
	int count = 0;
	//getlineで第三引数(char)ごとに分割する
	while (std::getline(ss, line, c))
	{
		str[count] = line;
		++count;
	}
	return str;
}

void KL::SplitString(std::vector<std::string>* out, const std::string& text, const char c)
{
	std::stringstream ss(text);
	std::string line;
	out->clear();
	while (std::getline(ss, line, c))
	{
		out->emplace_back(line);
	}
}

void KL::Trim(std::string* str, const char c)
{
	size_t size = 0;
	while ((size = str->find_first_of(c)) != std::string::npos)
	{
		str->erase(size, 1);
	}
}

void KL::Trim(std::string* str, const std::string& trim)
{
	size_t size = 0;
	while ((size = str->find(trim)) != std::string::npos)
	{
		str->erase(size, trim.size());
	}
}

bool KL::Split(const std::string& text,const std::string& find, std::string* outLeft, std::string* outRigth)
{
	std::string::size_type size = text.find_first_of(find);
	if (size == std::string::npos)
	{
		return false;
	}
	*outLeft = text.substr(0, size);
	*outRigth = text.substr(size + 1);
	return true;
}

bool KL::Split(const std::string & text, const char find, std::string * outLeft, std::string * outRigth)
{
	std::string::size_type size = text.find_first_of(find);
	if (size == std::string::npos)
	{
		return false;
	}
	*outLeft = text.substr(0, size);
	*outRigth = text.substr(size + 1);
	return true;
}
