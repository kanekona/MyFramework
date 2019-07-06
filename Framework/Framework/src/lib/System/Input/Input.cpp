#include "Input.h"
#include "StrID\StrID.h"
#include "ENgine\EngineMacro.h"
#include "File\File.hpp"
//--------------------------------------------------
//@:Input::GamePadclass									
//--------------------------------------------------
void Input::GamePad::SetConfig(std::unordered_map<StrID, Input::ConfigData>* ConfigData)
{
	//入力値をenumと配列で管理
	//this->gPadData[Pad::BUTTON_A] = GLFW_JOYSTICK_1;
	//this->gPadData[Pad::BUTTON_B] = GLFW_JOYSTICK_2;
	//this->gPadData[Pad::BUTTON_X] = GLFW_JOYSTICK_3;
	//this->gPadData[Pad::BUTTON_Y] = GLFW_JOYSTICK_4;
	//this->gPadData[Pad::BUTTON_L1] = GLFW_JOYSTICK_5;
	//this->gPadData[Pad::BUTTON_R1] = GLFW_JOYSTICK_6;
	//this->gPadData[Pad::BUTTON_BACK] = GLFW_JOYSTICK_7;
	//this->gPadData[Pad::BUTTON_START] = GLFW_JOYSTICK_8;
	//this->gPadData[Pad::BUTTON_L3] = GLFW_JOYSTICK_9;
	//this->gPadData[Pad::BUTTON_R3] = GLFW_JOYSTICK_10;
	//this->gPadData[Pad::BUTTON_U] = GLFW_JOYSTICK_11;
	//this->gPadData[Pad::BUTTON_R] = GLFW_JOYSTICK_12;
	//this->gPadData[Pad::BUTTON_D] = GLFW_JOYSTICK_13;
	//this->gPadData[Pad::BUTTON_L] = GLFW_JOYSTICK_14;
	for (auto& it : *ConfigData)
	{
		gPadData[it.second.index] = it.second.key;
	}
}
bool Input::GamePad::IsPresent() const
{
	//Joystickが存在するかどうか
	return glfwJoystickPresent(this->id) == GLFW_TRUE;
}
Input::GamePad::GamePad(const int padID) :
	id(padID),
	name(glfwGetJoystickName(padID))
{
	//GamePadが存在するかどうか、ボタン数スティック数はいくつかの計測とその分の要素の確保
	glfwGetJoystickButtons(padID, &button_num);
	glfwGetJoystickAxes(padID, &axis_num);
#if DEBUG_ENABLE
	std::cout <<
		"GamePadID: " << id << 
		" button:" << button_num << 
		" axis:" << axis_num << 
		" name:" << name <<
	std::endl;
#endif
	button_on.resize(button_num);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(button_num);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(button_num);
	std::fill(std::begin(button_up), std::end(button_up), 0);
	axis_value.resize(axis_num);
	std::fill(std::begin(axis_value), std::end(axis_value), 0.0f);
	axis_button_on.resize(STICK_NUM);
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	axis_button_down.resize(STICK_NUM);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	axis_button_up.resize(STICK_NUM);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
	axis_threshold = 1.f;
}
void Input::GamePad::Reset()
{
	//確保した要素の初期化
	std::fill(std::begin(button_on), std::end(button_on), 0);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	std::fill(std::begin(button_up), std::end(button_up), 0);
	std::fill(std::begin(axis_value), std::end(axis_value), 0.0f);
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
}
std::vector<Input::GamePad*> Input::InitGamePad()
{
	//GamePadが存在する分だけ生成する
	std::vector<Input::GamePad*> gamepad_;
	for (int it = GLFW_JOYSTICK_1; it <= GLFW_JOYSTICK_LAST; ++it)
	{
		if (glfwJoystickPresent(it) == GLFW_TRUE)
		{
			gamepad_.emplace_back(new GamePad(it));
		}
	}
	return gamepad_;
}
int Input::GamePad::buttons() const
{
	return button_num;
}
int Input::GamePad::GetStickNum() const
{
	return axis_num;
}
bool Input::GamePad::on(const int index) const
{
	return button_on[index];
}
bool Input::GamePad::down(const int index) const
{
	return button_down[index];
}
bool Input::GamePad::up(const int index) const
{
	return button_up[index];
}
bool Input::GamePad::EitherDown() const
{
	for (auto it = this->button_down.begin(); it != this->button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = this->axis_button_down.begin(); it != this->axis_button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::GamePad::EitherOn() const
{
	for (auto it = this->button_on.begin(); it != this->button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = this->axis_button_on.begin(); it != this->axis_button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::GamePad::EitherUp() const
{
	for (auto it = this->button_up.begin(); it != this->button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = this->axis_button_up.begin(); it != this->axis_button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
float Input::GamePad::axis(const int index) const
{
	return axis_value[index];
}
bool Input::GamePad::axis_on(const int index) const
{
	return this->axis_button_on[index];
}
bool Input::GamePad::axis_down(const int index) const
{
	return this->axis_button_down[index];
}
bool Input::GamePad::axis_up(const int index) const
{
	return this->axis_button_up[index];
}
bool Input::GamePad::RegistAxisButton(const float axis_threshold_)
{
	axis_threshold = axis_threshold_;
	return true;
}
void Input::GamePad::Update()
{
	//現在の入力状況と1回前の入力状況からtrueかfalseをいれる
	int nowButtonNum;
	//GamePadのButtonの状況を取得
	const auto* buttons_ = glfwGetJoystickButtons(id, &nowButtonNum);
	if (nowButtonNum > 0)
	{
		for (int i = 0; i < nowButtonNum; ++i)
		{
			button_down[i] = !button_on[i] && buttons_[i];
			button_up[i] = button_on[i] && !buttons_[i];
			button_on[i] = buttons_[i];
		}
	}
	int axisNumber;
	//GamePadのJoyStickの状態を取得
	const auto* axes = glfwGetJoystickAxes(id, &axisNumber);
	if (axisNumber > 0) {
		for (int i = 0; i < axisNumber; ++i) {
			axis_value[i] = axes[i];
		}
		u_char buttons[STICK_NUM];
		std::fill(std::begin(buttons), std::end(buttons), 0);
		buttons[LSTICK_LEFT] = axis_value[AXIS_LEFT_X] <= -axis_threshold;
		buttons[LSTICK_RIGHT] = axis_value[AXIS_LEFT_X] >= axis_threshold;
		buttons[LSTICK_UP] = axis_value[AXIS_LEFT_Y] >= axis_threshold;
		buttons[LSTICK_DOWN] = axis_value[AXIS_LEFT_Y] <= -axis_threshold;

		buttons[RSTICK_LEFT] = axis_value[AXIS_RIGHT_X] <= -axis_threshold;
		buttons[RSTICK_RIGHT] = axis_value[AXIS_RIGHT_X] >= axis_threshold;
		buttons[RSTICK_UP] = axis_value[AXIS_RIGHT_Y] >= axis_threshold;
		buttons[RSTICK_DOWN] = axis_value[AXIS_RIGHT_Y] <= -axis_threshold;

		//押し込み入力の値のずれを修正
		axis_value[AXIS_R2] = (axis_value[AXIS_R2] + 1.0f) / 2.0f;
		axis_value[AXIS_L2] = (axis_value[AXIS_L2] + 1.0f) / 2.0f;
		buttons[BUTTON_R2] = axis_value[AXIS_R2] >= axis_threshold;
		buttons[BUTTON_L2] = axis_value[AXIS_L2] >= axis_threshold;

		for (int i = 0; i < STICK_NUM; ++i)
		{
			axis_button_down[i] = !axis_button_on[i] && buttons[i];
			axis_button_up[i] = axis_button_on[i] && !buttons[i];
			axis_button_on[i] = buttons[i];
		}
	}
}
const char* Input::GamePad::GetName() const
{
	return this->name;
}
void ResetGamePad(std::vector<Input::GamePad*>& gamepad_)
{
	//入力状況を初期化する
	for (auto& it : gamepad_)
	{
		if (it->IsPresent())
		{
			it->Reset();
		}
	}
}
//--------------------------------------------------
//@:Input::KeyBoardclass									
//--------------------------------------------------
Input::KeyBoard::KeyBoard()
{
	//仮想キーとの組み合わせ
	this->keyData[Key::A] = GLFW_KEY_A;
	this->keyData[Key::B] = GLFW_KEY_B;
	this->keyData[Key::C] = GLFW_KEY_C;
	this->keyData[Key::D] = GLFW_KEY_D;
	this->keyData[Key::E] = GLFW_KEY_E;
	this->keyData[Key::F] = GLFW_KEY_F;
	this->keyData[Key::G] = GLFW_KEY_G;
	this->keyData[Key::H] = GLFW_KEY_H;
	this->keyData[Key::I] = GLFW_KEY_I;
	this->keyData[Key::J] = GLFW_KEY_J;
	this->keyData[Key::K] = GLFW_KEY_K;
	this->keyData[Key::L] = GLFW_KEY_L;
	this->keyData[Key::N] = GLFW_KEY_N;
	this->keyData[Key::M] = GLFW_KEY_M;
	this->keyData[Key::O] = GLFW_KEY_O;
	this->keyData[Key::P] = GLFW_KEY_P;
	this->keyData[Key::Q] = GLFW_KEY_Q;
	this->keyData[Key::R] = GLFW_KEY_R;
	this->keyData[Key::S] = GLFW_KEY_S;
	this->keyData[Key::T] = GLFW_KEY_T;
	this->keyData[Key::U] = GLFW_KEY_U;
	this->keyData[Key::V] = GLFW_KEY_V;
	this->keyData[Key::W] = GLFW_KEY_W;
	this->keyData[Key::X] = GLFW_KEY_X;
	this->keyData[Key::Y] = GLFW_KEY_Y;
	this->keyData[Key::Z] = GLFW_KEY_Z;
	this->keyData[Key::SPACE] = GLFW_KEY_SPACE;
	this->keyData[Key::ENTER] = GLFW_KEY_ENTER;
	this->keyData[Key::UP] = GLFW_KEY_UP;
	this->keyData[Key::DOWN] = GLFW_KEY_DOWN;
	this->keyData[Key::RIGHT] = GLFW_KEY_RIGHT;
	this->keyData[Key::LEFT] = GLFW_KEY_LEFT;
	this->keyData[Key::ESCAPE] = GLFW_KEY_ESCAPE;

	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	this->IsPresent = true;
}
Input::KeyBoard* Input::InitkeyBoard()
{
	//キーボードを１つ生成
	KeyBoard* keyBoard_ = new KeyBoard;
	keyBoard_->IsPresent = true;
	return keyBoard_;
}
void Input::KeyBoard::SetWindow(GLFWwindow* w)
{
	this->nowWindow = w;
}
bool Input::KeyBoard::down(const int index) const
{
	return button_down[index];
}
bool Input::KeyBoard::on(const int index) const
{
	return button_on[index];
}
bool Input::KeyBoard::up(const int index) const
{
	return button_up[index];
}
bool Input::KeyBoard::EitherDown() const
{
	for (auto it = this->button_down.begin(); it != this->button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::KeyBoard::EitherOn() const
{
	for (auto it = this->button_on.begin(); it != this->button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::KeyBoard::EitherUp() const
{
	for (auto it = this->button_up.begin(); it != this->button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
void Input::KeyBoard::Update()
{
	for (int i = 0; i < Key::Num; ++i)
	{
		//キーボードの入力状況を取得
		int state = glfwGetKey(this->nowWindow, this->keyData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = (u_char)state;
	}
}
void ResetKeyBoard(Input::KeyBoard& keyboard)
{
	std::fill(std::begin(keyboard.button_on), std::end(keyboard.button_on), 0);
	std::fill(std::begin(keyboard.button_down), std::end(keyboard.button_down), 0);
	std::fill(std::begin(keyboard.button_up), std::end(keyboard.button_up), 0);
}
//--------------------------------------------------
//@:Mouseclass									
//--------------------------------------------------
Input::Mouse::Mouse()
{
	this->mouseData[Button::LEFT] = GLFW_MOUSE_BUTTON_1;
	this->mouseData[Button::RIGHT] = GLFW_MOUSE_BUTTON_2;
	this->mouseData[Button::CENTER] = GLFW_MOUSE_BUTTON_3;
	this->mouseData[Button::BUTTON_4] = GLFW_MOUSE_BUTTON_4;
	this->mouseData[Button::BUTTON_5] = GLFW_MOUSE_BUTTON_5;
	this->mouseData[Button::BUTTON_6] = GLFW_MOUSE_BUTTON_6;
	this->mouseData[Button::BUTTON_7] = GLFW_MOUSE_BUTTON_7;
	this->mouseData[Button::BUTTON_8] = GLFW_MOUSE_BUTTON_8;
	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	this->IsPresent = true;
	this->collision = new PointCollider(&transform);
}
Input::Mouse::~Mouse()
{
	delete this->collision;
}
Input::Mouse* Input::InitMouse()
{
	Mouse* mouse_ = new Input::Mouse;
	mouse_->IsPresent = true;
	return mouse_;
}
void Input::Mouse::SetWindow(GLFWwindow* w)
{
	this->nowWindow = w;
	glfwSetScrollCallback(this->nowWindow, Input::Mouse::SetScroll_Callback);
}
void Input::Mouse::SetScroll_Callback(GLFWwindow* w, double x, double y)
{
	Input::Mouse::scroll = { (float)x,(float)y };
}
bool Input::Mouse::on(const int index) const
{
	return button_on[index];
}
bool Input::Mouse::down(const int index) const
{
	return button_down[index];
}
bool Input::Mouse::up(const int index) const
{
	return button_up[index];
}
bool Input::Mouse::EitherDown() const
{
	for (auto it = this->button_down.begin(); it != this->button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::Mouse::EitherOn() const
{
	for (auto it = this->button_on.begin(); it != this->button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool Input::Mouse::EitherUp() const
{
	for (auto it = this->button_up.begin(); it != this->button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
void Input::Mouse::Update()
{
	for (int i = 0; i < 8; ++i)
	{
		//マウスの入力状況を取得
		int state = glfwGetMouseButton(this->nowWindow, this->mouseData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = (u_char)state;
	}
	this->scrollValue = Input::Mouse::scroll;
	Input::Mouse::scroll = { 0,0 };

	glfwGetCursorPos(this->nowWindow, &this->pos_x, &this->pos_y);
	this->transform.position = { (float)pos_x,(float)pos_y };
}
Vec2 Input::Mouse::GetScroll() const
{
	return this->scrollValue;
}
Vec2 Input::Mouse::GetPos() const
{
	return this->transform.position;
}
PointCollider* Input::Mouse::GetCollision() const
{
	return this->collision;
}
void Input::Mouse::ResetMouse()
{
	std::fill(std::begin(this->button_on), std::end(this->button_on), 0);
	std::fill(std::begin(this->button_down), std::end(this->button_down), 0);
	std::fill(std::begin(this->button_up), std::end(this->button_up), 0);
}
//--------------------------------------------------
//@:Inputclass									
//--------------------------------------------------
Input::~Input()
{
	delete this->mouse;
	delete this->key;
	for (auto it = this->pad.begin(); it != this->pad.end(); ++it)
	{
		delete *it;
	}
}
void Input::Inputinit(GLFWwindow *w)
{
	//キーボードの初期化
	this->key = this->InitkeyBoard();
	this->key->SetWindow(w);
	//マウスの初期化
	this->mouse = this->InitMouse();
	this->mouse->SetWindow(w);
	//ゲームパッドの初期化
	this->pad = this->InitGamePad();
	//ゲームパッドが１つ以上存在している場合
	this->pad_Connection = false;
	for (int i = 0; i < this->pad.size(); ++i)
	{
		this->pad[i]->SetConfig(&PadConfigData);
		this->pad_Connection = true;
	}
	//ゲームパッドとの紐づけ
	{
		this->inputdata[B1].button = Input::GamePad::Pad::BUTTON_A;
		this->inputdata[B2].button = Input::GamePad::Pad::BUTTON_B;
		this->inputdata[B3].button = Input::GamePad::Pad::BUTTON_X;
		this->inputdata[B4].button = Input::GamePad::Pad::BUTTON_Y;

		this->inputdata[L1].button = Input::GamePad::Pad::BUTTON_L1;
		this->inputdata[R1].button = Input::GamePad::Pad::BUTTON_R1;

		this->inputdata[D1].button = Input::GamePad::Pad::BUTTON_BACK;
		this->inputdata[D2].button = Input::GamePad::Pad::BUTTON_START;

		this->inputdata[SL].button = Input::GamePad::Pad::BUTTON_L3;
		this->inputdata[SR].button = Input::GamePad::Pad::BUTTON_R3;

		this->inputdata[CU].button = Input::GamePad::Pad::BUTTON_U;
		this->inputdata[CR].button = Input::GamePad::Pad::BUTTON_R;
		this->inputdata[CD].button = Input::GamePad::Pad::BUTTON_D;
		this->inputdata[CL].button = Input::GamePad::Pad::BUTTON_L;

		this->inputdata[LU].button = Input::GamePad::AXISBUTTON::LSTICK_UP;
		this->inputdata[LD].button = Input::GamePad::AXISBUTTON::LSTICK_DOWN;
		this->inputdata[LL].button = Input::GamePad::AXISBUTTON::LSTICK_LEFT;
		this->inputdata[LR].button = Input::GamePad::AXISBUTTON::LSTICK_RIGHT;

		this->inputdata[RU].button = Input::GamePad::AXISBUTTON::RSTICK_UP;
		this->inputdata[RD].button = Input::GamePad::AXISBUTTON::RSTICK_DOWN;
		this->inputdata[RL].button = Input::GamePad::AXISBUTTON::RSTICK_LEFT;
		this->inputdata[RR].button = Input::GamePad::AXISBUTTON::RSTICK_RIGHT;

		this->inputdata[L2].button = Input::GamePad::AXISBUTTON::BUTTON_L2;
		this->inputdata[R2].button = Input::GamePad::AXISBUTTON::BUTTON_R2;
	}
	//キーボードとの紐づけ
	{
		this->inputdata[B1].key = Input::KeyBoard::Key::Z;
		this->inputdata[B2].key = Input::KeyBoard::Key::X;
		this->inputdata[B3].key = Input::KeyBoard::Key::C;
		this->inputdata[B4].key = Input::KeyBoard::Key::V;

		this->inputdata[L1].key = Input::KeyBoard::Key::Q;
		this->inputdata[R1].key = Input::KeyBoard::Key::E;

		this->inputdata[D1].key = Input::KeyBoard::Key::ENTER;
		this->inputdata[D2].key = Input::KeyBoard::Key::SPACE;

		this->inputdata[SL].key = Input::KeyBoard::Key::B;
		this->inputdata[SR].key = Input::KeyBoard::Key::N;

		this->inputdata[CU].key = Input::KeyBoard::Key::UP;
		this->inputdata[CR].key = Input::KeyBoard::Key::RIGHT;
		this->inputdata[CD].key = Input::KeyBoard::Key::DOWN;
		this->inputdata[CL].key = Input::KeyBoard::Key::LEFT;

		this->inputdata[LU].key = Input::KeyBoard::Key::W;
		this->inputdata[LD].key = Input::KeyBoard::Key::S;
		this->inputdata[LL].key = Input::KeyBoard::Key::A;
		this->inputdata[LR].key = Input::KeyBoard::Key::D;

		this->inputdata[RU].key = Input::KeyBoard::Key::I;
		this->inputdata[RD].key = Input::KeyBoard::Key::K;
		this->inputdata[RL].key = Input::KeyBoard::Key::J;
		this->inputdata[RR].key = Input::KeyBoard::Key::L;

		this->inputdata[L2].key = Input::KeyBoard::Key::O;
		this->inputdata[R2].key = Input::KeyBoard::Key::U;
	}
}
void Input::Update()
{
	for (int i = 0; i < this->pad.size(); ++i)
	{
		this->pad[i]->Update();
	}
	this->key->Update();
	this->mouse->Update();
}
bool Input::down(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key->down(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key->down(this->inputdata[index].key) || this->pad[padNum]->down(this->inputdata[index].button);
	}
	return this->key->down(this->inputdata[index].key) || this->pad[padNum]->axis_down(this->inputdata[index].button);
	//return this->key.down(this->inputdata[index].key) || index < 14 ? this->pad[padNum].down(this->inputdata[index].button) : this->pad[padNum].axis_down(this->inputdata[index].button);
}
bool Input::on(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key->on(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key->on(this->inputdata[index].key) || this->pad[padNum]->on(this->inputdata[index].button);
	}
	return this->key->on(this->inputdata[index].key) || this->pad[padNum]->axis_on(this->inputdata[index].button);
	//return this->key.on(this->inputdata[index].key) || index < 14 ? this->pad[padNum].on(this->inputdata[index].button) : this->pad[padNum].axis_on(this->inputdata[index].button);
}
bool Input::up(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return this->key->up(this->inputdata[index].key);
	}
	if (index < 14)
	{
		return this->key->up(this->inputdata[index].key) || this->pad[padNum]->up(this->inputdata[index].button);
	}
	return this->key->up(this->inputdata[index].key) || this->pad[padNum]->axis_up(this->inputdata[index].button);
	//return this->key.up(this->inputdata[index].key) || index < 14 ? this->pad[padNum].up(this->inputdata[index].button) : this->pad[padNum].axis_up(this->inputdata[index].button);
}
bool Input::EitherDown() const
{
	for (auto it = this->pad.begin(); it != this->pad.end(); ++it)
	{
		if ((*it)->EitherDown())
		{
			return true;
		}
	}
	return this->key->EitherDown() || this->mouse->EitherDown();
}
bool Input::EitherOn() const
{
	for (auto it = this->pad.begin(); it != this->pad.end(); ++it)
	{
		if ((*it)->EitherOn())
		{
			return true;
		}
	}
	return this->key->EitherOn() || this->mouse->EitherOn();
}
bool Input::EitherUp() const
{
	for (auto it = this->pad.begin(); it != this->pad.end(); ++it)
	{
		if ((*it)->EitherUp())
		{
			return true;
		}
	}
	return this->key->EitherUp() || this->mouse->EitherUp();
}
void Input::SetPadConfig(const StrID& Key, const int padKey)
{
	PadConfigData[Key].key = padKey;
}
float Input::axis(const int index, const int padNum) const
{
	float ang = 0.f;
	switch (index)
	{
	case In::AXIS::AXIS_LEFT_X:
		if (this->key->on(KeyBoard::A))
		{
			ang -= 1.0f;
		}
		if (this->key->on(KeyBoard::D))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_LEFT_Y:
		if (this->key->on(KeyBoard::W))
		{
			ang += 1.0f;
		}
		if (this->key->on(KeyBoard::S))
		{
			ang -= 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_X:
		if (this->key->on(KeyBoard::J))
		{
			ang -= 1.0f;
		}
		if (this->key->on(KeyBoard::L))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_Y:
		if (this->key->on(KeyBoard::I))
		{
			ang += 1.0f;
		}
		if (this->key->on(KeyBoard::K))
		{
			ang -= 1.0f;
		}
		break;
	case In::AXIS::AXIS_L2:
		if (this->key->on(KeyBoard::O))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_R2:
		if (this->key->on(KeyBoard::U))
		{
			ang += 1.0f;
		}
	default:
		break;
	}
	if (glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		if (this->pad[padNum]->axis(index) != 0.f)
		{
			ang = this->pad[padNum]->axis(index);
		}
	}
	return ang;
}
void Input::ResetInputData()
{
	ResetGamePad(this->pad);
	ResetKeyBoard(*this->key);
	this->mouse->ResetMouse();
}
void Input::RegistAxis(const float regist)
{
	for (auto it = this->pad.begin(); it != this->pad.end(); ++it)
	{
		(*it)->RegistAxisButton(regist);
	}
}
Vec2 Input::Mouse::scroll;
Input::Input()
{
	std::vector<std::string> ConfigTag;
	File::LoadStrings(&ConfigTag, "./data/bin/InputTag.txt");
	for (int i = 0; i < ConfigTag.size(); ++i)
	{
		PadConfigData.insert(std::make_pair(StrID(ConfigTag[i]), ConfigData(i, i)));
	}
}
Input* Input::Create(GLFWwindow* window)
{
	if (instance == nullptr)
	{
		instance = new Input();
		instance->Inputinit(window);
	}
	return Input::Get();
}
Input* Input::Get()
{
	return Input::instance;
}
void Input::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
Input* Input::instance = nullptr;