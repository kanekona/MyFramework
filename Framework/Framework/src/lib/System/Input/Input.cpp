#include "Input.h"
#include "File\File.hpp"
#include "Event\Event.h"
//--------------------------------------------------
//@:Input::GamePadclass									
//--------------------------------------------------
void CInput::GamePad::SetConfig(std::unordered_map<CStrID, CInput::ConfigData>* ConfigData)
{
	//入力値をenumと配列で管理
#if DEBUG_ENABLE
	printf("SetConfig.Start[%s]\n",name);
#endif
	for (auto& it : *ConfigData)
	{
		gPadData[it.second.index] = it.second.key;
#if DEBUG_ENABLE
		printf("[%s] [%d]\n", it.first.ToString().c_str(), it.second.key);
#endif
	}
#if DEBUG_ENABLE
	printf("SetConfig.End[%s]\n",name);
#endif
}
bool CInput::GamePad::IsPresent() const
{
	//Joystickが存在するかどうか
	return glfwJoystickPresent(id) == GLFW_TRUE;
}
CInput::GamePad::GamePad(const int padID) :
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
	axis_button_on.resize(In::STICK_NUM);
	std::fill(std::begin(axis_button_on), std::end(axis_button_on), 0);
	axis_button_down.resize(In::STICK_NUM);
	std::fill(std::begin(axis_button_down), std::end(axis_button_down), 0);
	axis_button_up.resize(In::STICK_NUM);
	std::fill(std::begin(axis_button_up), std::end(axis_button_up), 0);
	axis_threshold = 1.f;
}
void CInput::GamePad::Reset()
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
std::vector<CInput::GamePad*> CInput::InitGamePad()
{
	//GamePadが存在する分だけ生成する
	std::vector<CInput::GamePad*> gamepad_;
	for (int it = GLFW_JOYSTICK_1; it <= GLFW_JOYSTICK_LAST; ++it)
	{
		if (glfwJoystickPresent(it) == GLFW_TRUE)
		{
			gamepad_.emplace_back(new GamePad(it));
		}
	}
	return gamepad_;
}
int CInput::GamePad::buttons() const
{
	return button_num;
}
int CInput::GamePad::GetStickNum() const
{
	return axis_num;
}
bool CInput::GamePad::on(const int index) const
{
	return button_on[index];
}
bool CInput::GamePad::down(const int index) const
{
	return button_down[index];
}
bool CInput::GamePad::up(const int index) const
{
	return button_up[index];
}
bool CInput::GamePad::EitherDown() const
{
	for (auto it = button_down.begin(); it != button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = axis_button_down.begin(); it != axis_button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::GamePad::EitherOn() const
{
	for (auto it = button_on.begin(); it != button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = axis_button_on.begin(); it != axis_button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::GamePad::EitherUp() const
{
	for (auto it = button_up.begin(); it != button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	for (auto it = axis_button_up.begin(); it != axis_button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
float CInput::GamePad::axis(const int index) const
{
	return axis_value[index];
}
bool CInput::GamePad::axis_on(const int index) const
{
	return axis_button_on[index];
}
bool CInput::GamePad::axis_down(const int index) const
{
	return axis_button_down[index];
}
bool CInput::GamePad::axis_up(const int index) const
{
	return axis_button_up[index];
}
bool CInput::GamePad::RegistAxisButton(const float axis_threshold_)
{
	axis_threshold = axis_threshold_;
	return true;
}
void CInput::GamePad::Update()
{
	//現在の入力状況と1回前の入力状況からtrueかfalseをいれる
	int nowButtonNum;
	//GamePadのButtonの状況を取得
	const auto* buttons_ = glfwGetJoystickButtons(id, &nowButtonNum);
	for (int i = 0; i < nowButtonNum; ++i)
	{
		button_down[i] = !button_on[i] && buttons_[i];
		button_up[i] = button_on[i] && !buttons_[i];
		button_on[i] = buttons_[i];
	}
	int axisNumber;
	//GamePadのJoyStickの状態を取得
	const auto* axes = glfwGetJoystickAxes(id, &axisNumber);
	for (int i = 0; i < axisNumber; ++i) {
		axis_value[i] = axes[i];
	}
	u_char buttons[In::STICK_NUM];
	std::fill(std::begin(buttons), std::end(buttons), 0);
	buttons[In::LSTICK_LEFT] = axis_value[In::AXIS_LEFT_X] <= -axis_threshold;
	buttons[In::LSTICK_RIGHT] = axis_value[In::AXIS_LEFT_X] >= axis_threshold;
	buttons[In::LSTICK_UP] = axis_value[In::AXIS_LEFT_Y] >= axis_threshold;
	buttons[In::LSTICK_DOWN] = axis_value[In::AXIS_LEFT_Y] <= -axis_threshold;

	buttons[In::RSTICK_LEFT] = axis_value[In::AXIS_RIGHT_X] <= -axis_threshold;
	buttons[In::RSTICK_RIGHT] = axis_value[In::AXIS_RIGHT_X] >= axis_threshold;
	buttons[In::RSTICK_UP] = axis_value[In::AXIS_RIGHT_Y] >= axis_threshold;
	buttons[In::RSTICK_DOWN] = axis_value[In::AXIS_RIGHT_Y] <= -axis_threshold;

	//押し込み入力の値のずれを修正
	axis_value[In::AXIS_R2] = (axis_value[In::AXIS_R2] + 1.0f) / 2.0f;
	axis_value[In::AXIS_L2] = (axis_value[In::AXIS_L2] + 1.0f) / 2.0f;
	buttons[In::BUTTON_R2] = axis_value[In::AXIS_R2] >= axis_threshold;
	buttons[In::BUTTON_L2] = axis_value[In::AXIS_L2] >= axis_threshold;

	for (int i = 0; i < In::STICK_NUM; ++i)
	{
		axis_button_down[i] = !axis_button_on[i] && buttons[i];
		axis_button_up[i] = axis_button_on[i] && !buttons[i];
		axis_button_on[i] = buttons[i];
	}
}
const char* CInput::GamePad::GetName() const
{
	return name;
}
#if DEBUG_ENABLE
void CInput::GamePad::DebugLog()
{
	printf("===GamePadInput.Start[%s]===\n", GetName());
	printf("==Button==\n");
	for (int i = 0; i < button_on.size(); ++i)
	{
		printf("[%d][%d]\n", i, button_on[i]);
	}
	printf("==StickButton==\n");
	for (int i = 0; i < axis_button_on.size(); ++i)
	{
		printf("[%d][%d]", i, axis_button_on[i]);
	}
	printf("==Axis==\n");
	for (int i = 0; i < axis_value.size(); ++i)
	{
		printf("[%d][%f]", i, axis_value[i]);
	}
	printf("===GamePadInput.End  [%s]===\n", GetName());
}
#endif
void ResetGamePad(std::vector<CInput::GamePad*>& gamepad_)
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
CInput::KeyBoard::KeyBoard()
{
	//仮想キーとの組み合わせ
	keyData[In::EKey::A] = GLFW_KEY_A;
	keyData[In::EKey::B] = GLFW_KEY_B;
	keyData[In::EKey::C] = GLFW_KEY_C;
	keyData[In::EKey::D] = GLFW_KEY_D;
	keyData[In::EKey::E] = GLFW_KEY_E;
	keyData[In::EKey::F] = GLFW_KEY_F;
	keyData[In::EKey::G] = GLFW_KEY_G;
	keyData[In::EKey::H] = GLFW_KEY_H;
	keyData[In::EKey::I] = GLFW_KEY_I;
	keyData[In::EKey::J] = GLFW_KEY_J;
	keyData[In::EKey::K] = GLFW_KEY_K;
	keyData[In::EKey::L] = GLFW_KEY_L;
	keyData[In::EKey::N] = GLFW_KEY_N;
	keyData[In::EKey::M] = GLFW_KEY_M;
	keyData[In::EKey::O] = GLFW_KEY_O;
	keyData[In::EKey::P] = GLFW_KEY_P;
	keyData[In::EKey::Q] = GLFW_KEY_Q;
	keyData[In::EKey::R] = GLFW_KEY_R;
	keyData[In::EKey::S] = GLFW_KEY_S;
	keyData[In::EKey::T] = GLFW_KEY_T;
	keyData[In::EKey::U] = GLFW_KEY_U;
	keyData[In::EKey::V] = GLFW_KEY_V;
	keyData[In::EKey::W] = GLFW_KEY_W;
	keyData[In::EKey::X] = GLFW_KEY_X;
	keyData[In::EKey::Y] = GLFW_KEY_Y;
	keyData[In::EKey::Z] = GLFW_KEY_Z;
	keyData[In::EKey::SPACE] = GLFW_KEY_SPACE;
	keyData[In::EKey::ENTER] = GLFW_KEY_ENTER;
	keyData[In::EKey::UP] = GLFW_KEY_UP;
	keyData[In::EKey::DOWN] = GLFW_KEY_DOWN;
	keyData[In::EKey::RIGHT] = GLFW_KEY_RIGHT;
	keyData[In::EKey::LEFT] = GLFW_KEY_LEFT;
	keyData[In::EKey::ESCAPE] = GLFW_KEY_ESCAPE;
	keyData[In::EKey::F01] = GLFW_KEY_F1;
	keyData[In::EKey::F02] = GLFW_KEY_F2;
	keyData[In::EKey::F03] = GLFW_KEY_F3;
	keyData[In::EKey::F04] = GLFW_KEY_F4;
	keyData[In::EKey::F05] = GLFW_KEY_F5;
	keyData[In::EKey::F06] = GLFW_KEY_F6;
	keyData[In::EKey::F07] = GLFW_KEY_F7;
	keyData[In::EKey::F08] = GLFW_KEY_F8;
	keyData[In::EKey::F09] = GLFW_KEY_F9;
	keyData[In::EKey::F10] = GLFW_KEY_F10;
	keyData[In::EKey::F11] = GLFW_KEY_F11;
	keyData[In::EKey::F12] = GLFW_KEY_F12;
	keyData[In::EKey::N0] = GLFW_KEY_0;
	keyData[In::EKey::N1] = GLFW_KEY_1;
	keyData[In::EKey::N2] = GLFW_KEY_2;
	keyData[In::EKey::N3] = GLFW_KEY_3;
	keyData[In::EKey::N4] = GLFW_KEY_4;
	keyData[In::EKey::N5] = GLFW_KEY_5;
	keyData[In::EKey::N6] = GLFW_KEY_6;
	keyData[In::EKey::N7] = GLFW_KEY_7;
	keyData[In::EKey::N8] = GLFW_KEY_8;
	keyData[In::EKey::N9] = GLFW_KEY_9;

	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	IsPresent = true;
}
CInput::KeyBoard* CInput::InitkeyBoard()
{
	//キーボードを１つ生成
	KeyBoard* keyBoard_ = new KeyBoard;
	keyBoard_->IsPresent = true;
	return keyBoard_;
}
void CInput::KeyBoard::SetWindow(GLFWwindow* w)
{
	nowWindow = w;
}
bool CInput::KeyBoard::down(const int index) const
{
	return button_down[index];
}
bool CInput::KeyBoard::on(const int index) const
{
	return button_on[index];
}
bool CInput::KeyBoard::up(const int index) const
{
	return button_up[index];
}
bool CInput::KeyBoard::EitherDown() const
{
	for (auto it = button_down.begin(); it != button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::KeyBoard::EitherOn() const
{
	for (auto it = button_on.begin(); it != button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::KeyBoard::EitherUp() const
{
	for (auto it = button_up.begin(); it != button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
void CInput::KeyBoard::Update()
{
	for (int i = 0; i < In::EKey::KEY_NUM; ++i)
	{
		//キーボードの入力状況を取得
		int state = glfwGetKey(nowWindow, keyData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = (u_char)state;
	}
}
void ResetKeyBoard(CInput::KeyBoard& keyboard)
{
	std::fill(std::begin(keyboard.button_on), std::end(keyboard.button_on), 0);
	std::fill(std::begin(keyboard.button_down), std::end(keyboard.button_down), 0);
	std::fill(std::begin(keyboard.button_up), std::end(keyboard.button_up), 0);
}
//--------------------------------------------------
//@:Mouseclass									
//--------------------------------------------------
CInput::Mouse::Mouse()
{
	mouseData[In::EMouse::MOUSE_LEFT] = GLFW_MOUSE_BUTTON_1;
	mouseData[In::EMouse::MOUSE_RIGHT] = GLFW_MOUSE_BUTTON_2;
	mouseData[In::EMouse::MOUSE_CENTER] = GLFW_MOUSE_BUTTON_3;
	mouseData[In::EMouse::MOUSE_BUTTON_4] = GLFW_MOUSE_BUTTON_4;
	mouseData[In::EMouse::MOUSE_BUTTON_5] = GLFW_MOUSE_BUTTON_5;
	mouseData[In::EMouse::MOUSE_BUTTON_6] = GLFW_MOUSE_BUTTON_6;
	mouseData[In::EMouse::MOUSE_BUTTON_7] = GLFW_MOUSE_BUTTON_7;
	mouseData[In::EMouse::MOUSE_BUTTON_8] = GLFW_MOUSE_BUTTON_8;
	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	IsPresent = true;
	collision = new CPointCollider(&transform);
}
CInput::Mouse::~Mouse()
{
	delete collision;
}
CInput::Mouse* CInput::InitMouse()
{
	Mouse* mouse_ = new CInput::Mouse;
	mouse_->IsPresent = true;
	return mouse_;
}
void CInput::Mouse::SetWindow(GLFWwindow* w)
{
	nowWindow = w;
	glfwSetScrollCallback(nowWindow, CInput::Mouse::SetScroll_Callback);
	glfwSetDropCallback(nowWindow, CInput::Mouse::SetDrop_Callback);
}
void CInput::Mouse::SetScroll_Callback(GLFWwindow* w, double x, double y)
{
	CInput::Mouse::scroll = { (float)x,(float)y };
}
void CInput::Mouse::SetDrop_Callback(GLFWwindow * w, int count, const char ** path)
{
	for (int i = 0; i < count; ++i)
	{
#if ENGINE_DEVELOP
		printf("DropCallback[%s]\n", path[i]);
		CEventTask et;
		et.Load(EEvent::INPUT_CONFIG, path[i]);
#endif
	}
}
bool CInput::Mouse::on(const int index) const
{
	return button_on[index];
}
bool CInput::Mouse::down(const int index) const
{
	return button_down[index];
}
bool CInput::Mouse::up(const int index) const
{
	return button_up[index];
}
bool CInput::Mouse::EitherDown() const
{
	for (auto it = button_down.begin(); it != button_down.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::Mouse::EitherOn() const
{
	for (auto it = button_on.begin(); it != button_on.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
bool CInput::Mouse::EitherUp() const
{
	for (auto it = button_up.begin(); it != button_up.end(); ++it)
	{
		if (*it)
		{
			return true;
		}
	}
	return false;
}
void CInput::Mouse::Update()
{
	for (int i = 0; i < 8; ++i)
	{
		//マウスの入力状況を取得
		int state = glfwGetMouseButton(nowWindow, mouseData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = (u_char)state;
	}
	scrollValue = CInput::Mouse::scroll;
	CInput::Mouse::scroll = { 0,0 };

	glfwGetCursorPos(nowWindow, &pos_x, &pos_y);
	transform.position = { (float)pos_x,(float)pos_y };
}
CVec2 CInput::Mouse::GetScroll() const
{
	return scrollValue;
}
CVec2 CInput::Mouse::GetPos() const
{
	return transform.position;
}
CPointCollider* CInput::Mouse::GetCollision() const
{
	return collision;
}
CColor CInput::Mouse::GetPixcel()
{
	glReadBuffer(GL_FRONT);
	int32 w, h;
	glfwGetWindowSize(nowWindow, &w, &h);
	uint8* data = new uint8[4];
	glReadPixels((int)transform.position.x, h - (int)transform.position.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
	CColor Return(data[0], data[1], data[2], data[3]);
	delete[] data;
	return Return;
}
void CInput::Mouse::ResetMouse()
{
	std::fill(std::begin(button_on), std::end(button_on), 0);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	std::fill(std::begin(button_up), std::end(button_up), 0);
}
//--------------------------------------------------
//@:Inputclass									
//--------------------------------------------------
CInput::~CInput()
{
	delete mouse;
	delete key;
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		delete *it;
	}
}
void CInput::Inputinit(GLFWwindow *w)
{
	//キーボードの初期化
	key = InitkeyBoard();
	key->SetWindow(w);
	//マウスの初期化
	mouse = InitMouse();
	mouse->SetWindow(w);
	//ゲームパッドの初期化
	pad = InitGamePad();
	//ゲームパッドが１つ以上存在している場合
	pad_Connection = false;
	for (int i = 0; i < pad.size(); ++i)
	{
		pad[i]->SetConfig(&PadConfigData);
		pad_Connection = true;
	}
	//ゲームパッドとの紐づけ
	{
		inputdata[In::EVirtual::B1].button = In::EButton::BUTTON_A;
		inputdata[In::EVirtual::B2].button = In::EButton::BUTTON_B;
		inputdata[In::EVirtual::B3].button = In::EButton::BUTTON_X;
		inputdata[In::EVirtual::B4].button = In::EButton::BUTTON_Y;

		inputdata[In::EVirtual::L1].button = In::EButton::BUTTON_L1;
		inputdata[In::EVirtual::R1].button = In::EButton::BUTTON_R1;

		inputdata[In::EVirtual::D1].button = In::EButton::BUTTON_BACK;
		inputdata[In::EVirtual::D2].button = In::EButton::BUTTON_START;

		inputdata[In::EVirtual::SL].button = In::EButton::BUTTON_L3;
		inputdata[In::EVirtual::SR].button = In::EButton::BUTTON_R3;

		inputdata[In::EVirtual::CU].button = In::EButton::BUTTON_U;
		inputdata[In::EVirtual::CR].button = In::EButton::BUTTON_R;
		inputdata[In::EVirtual::CD].button = In::EButton::BUTTON_D;
		inputdata[In::EVirtual::CL].button = In::EButton::BUTTON_L;
				 
		inputdata[In::EVirtual::LU].button = In::EStick::LSTICK_UP;
		inputdata[In::EVirtual::LD].button = In::EStick::LSTICK_DOWN;
		inputdata[In::EVirtual::LL].button = In::EStick::LSTICK_LEFT;
		inputdata[In::EVirtual::LR].button = In::EStick::LSTICK_RIGHT;

		inputdata[In::EVirtual::RU].button = In::EStick::RSTICK_UP;
		inputdata[In::EVirtual::RD].button = In::EStick::RSTICK_DOWN;
		inputdata[In::EVirtual::RL].button = In::EStick::RSTICK_LEFT;
		inputdata[In::EVirtual::RR].button = In::EStick::RSTICK_RIGHT;

		inputdata[In::EVirtual::L2].button = In::EStick::BUTTON_L2;
		inputdata[In::EVirtual::R2].button = In::EStick::BUTTON_R2;
	}
	//キーボードとの紐づけ
	{
		inputdata[In::EVirtual::B1].key = In::EKey::Z;
		inputdata[In::EVirtual::B2].key = In::EKey::X;
		inputdata[In::EVirtual::B3].key = In::EKey::C;
		inputdata[In::EVirtual::B4].key = In::EKey::V;

		inputdata[In::EVirtual::L1].key = In::EKey::Q;
		inputdata[In::EVirtual::R1].key = In::EKey::E;

		inputdata[In::EVirtual::D1].key = In::EKey::ENTER;
		inputdata[In::EVirtual::D2].key = In::EKey::SPACE;

		inputdata[In::EVirtual::SL].key = In::EKey::B;
		inputdata[In::EVirtual::SR].key = In::EKey::N;

		inputdata[In::EVirtual::CU].key = In::EKey::UP;
		inputdata[In::EVirtual::CR].key = In::EKey::RIGHT;
		inputdata[In::EVirtual::CD].key = In::EKey::DOWN;
		inputdata[In::EVirtual::CL].key = In::EKey::LEFT;

		inputdata[In::EVirtual::LU].key = In::EKey::W;
		inputdata[In::EVirtual::LD].key = In::EKey::S;
		inputdata[In::EVirtual::LL].key = In::EKey::A;
		inputdata[In::EVirtual::LR].key = In::EKey::D;

		inputdata[In::EVirtual::RU].key = In::EKey::I;
		inputdata[In::EVirtual::RD].key = In::EKey::K;
		inputdata[In::EVirtual::RL].key = In::EKey::J;
		inputdata[In::EVirtual::RR].key = In::EKey::L;

		inputdata[In::EVirtual::L2].key = In::EKey::O;
		inputdata[In::EVirtual::R2].key = In::EKey::U;
	}
}
void CInput::Update()
{
	for (int i = 0; i < pad.size(); ++i)
	{
		pad[i]->Update();
	}
	key->Update();
	mouse->Update();
}
bool CInput::down(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return key->down(inputdata[index].key);
	}
	if (index < 14)
	{
		return key->down(inputdata[index].key) || pad[padNum]->down(inputdata[index].button);
	}
	return key->down(inputdata[index].key) || pad[padNum]->axis_down(inputdata[index].button);
	//return key.down(inputdata[index].key) || index < 14 ? pad[padNum].down(inputdata[index].button) : pad[padNum].axis_down(inputdata[index].button);
}
bool CInput::on(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return key->on(inputdata[index].key);
	}
	if (index < 14)
	{
		return key->on(inputdata[index].key) || pad[padNum]->on(inputdata[index].button);
	}
	return key->on(inputdata[index].key) || pad[padNum]->axis_on(inputdata[index].button);
	//return key.on(inputdata[index].key) || index < 14 ? pad[padNum].on(inputdata[index].button) : pad[padNum].axis_on(inputdata[index].button);
}
bool CInput::up(const int index, const int padNum) const
{
	//選択された番号のゲームパッドが存在しない場合
	if (!glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		return key->up(inputdata[index].key);
	}
	if (index < 14)
	{
		return key->up(inputdata[index].key) || pad[padNum]->up(inputdata[index].button);
	}
	return key->up(inputdata[index].key) || pad[padNum]->axis_up(inputdata[index].button);
	//return key.up(inputdata[index].key) || index < 14 ? pad[padNum].up(inputdata[index].button) : pad[padNum].axis_up(inputdata[index].button);
}
bool CInput::EitherDown() const
{
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		if ((*it)->EitherDown())
		{
			return true;
		}
	}
	return key->EitherDown() || mouse->EitherDown();
}
bool CInput::EitherOn() const
{
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		if ((*it)->EitherOn())
		{
			return true;
		}
	}
	return key->EitherOn() || mouse->EitherOn();
}
bool CInput::EitherUp() const
{
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		if ((*it)->EitherUp())
		{
			return true;
		}
	}
	return key->EitherUp() || mouse->EitherUp();
}
void CInput::SetPadConfig(const CStrID& Key, const int padKey)
{
	PadConfigData[Key].key = padKey;
}
void CInput::RegisterPadConfig(const int padNum)
{
	pad[padNum]->SetConfig(&PadConfigData);
}
float CInput::axis(const int index, const int padNum) const
{
	float ang = 0.f;
	switch (index)
	{
	case In::EAxis::AXIS_LEFT_X:
		if (key->on(In::EKey::A))
		{
			ang -= 1.0f;
		}
		if (key->on(In::EKey::D))
		{
			ang += 1.0f;
		}
		break;
	case In::EAxis::AXIS_LEFT_Y:
		if (key->on(In::EKey::W))
		{
			ang += 1.0f;
		}
		if (key->on(In::EKey::S))
		{
			ang -= 1.0f;
		}
		break;
	case In::EAxis::AXIS_RIGHT_X:
		if (key->on(In::EKey::J))
		{
			ang -= 1.0f;
		}
		if (key->on(In::EKey::L))
		{
			ang += 1.0f;
		}
		break;
	case In::EAxis::AXIS_RIGHT_Y:
		if (key->on(In::EKey::I))
		{
			ang += 1.0f;
		}
		if (key->on(In::EKey::K))
		{
			ang -= 1.0f;
		}
		break;
	case In::EAxis::AXIS_L2:
		if (key->on(In::EKey::O))
		{
			ang += 1.0f;
		}
		break;
	case In::EAxis::AXIS_R2:
		if (key->on(In::EKey::U))
		{
			ang += 1.0f;
		}
	default:
		break;
	}
	if (glfwJoystickPresent(padNum) == GLFW_TRUE)
	{
		if (pad[padNum]->axis(index) != 0.f)
		{
			ang = pad[padNum]->axis(index);
		}
	}
	return ang;
}
void CInput::ResetInputData()
{
	ResetGamePad(pad);
	ResetKeyBoard(*key);
	mouse->ResetMouse();
}
void CInput::RegistAxis(const float regist)
{
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		(*it)->RegistAxisButton(regist);
	}
}
CVec2 CInput::Mouse::scroll;
CInput::CInput()
{
	std::vector<std::string> ConfigTag;
	CFile::LoadStrings(&ConfigTag, "./data/bin/InputTag.txt");
	for (int i = 0; i < ConfigTag.size(); ++i)
	{
		PadConfigData.insert(std::make_pair(CStrID(ConfigTag[i]), ConfigData(i, i)));
	}
}
CInput* CInput::Create(GLFWwindow* window)
{
	if (instance == nullptr)
	{
		instance = new CInput();
		instance->Inputinit(window);
	}
	return CInput::Get();
}
CInput* CInput::Get()
{
	return CInput::instance;
}
void CInput::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
#if DEBUG_ENABLE
void CInput::DebugLog()
{
	for (int i = 0; i < pad.size(); ++i)
	{
		pad[i]->DebugLog();
	}
}
#endif
CInput* CInput::instance = nullptr;