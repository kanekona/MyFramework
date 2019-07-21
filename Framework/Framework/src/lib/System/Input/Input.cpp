#include "Input.h"
#include "StrID\StrID.h"
#include "File\File.hpp"
#include "Event\Event.h"
//--------------------------------------------------
//@:Input::GamePadclass									
//--------------------------------------------------
void Input::GamePad::SetConfig(std::unordered_map<StrID, Input::ConfigData>* ConfigData)
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
bool Input::GamePad::IsPresent() const
{
	//Joystickが存在するかどうか
	return glfwJoystickPresent(id) == GLFW_TRUE;
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
bool Input::GamePad::EitherOn() const
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
bool Input::GamePad::EitherUp() const
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
float Input::GamePad::axis(const int index) const
{
	return axis_value[index];
}
bool Input::GamePad::axis_on(const int index) const
{
	return axis_button_on[index];
}
bool Input::GamePad::axis_down(const int index) const
{
	return axis_button_down[index];
}
bool Input::GamePad::axis_up(const int index) const
{
	return axis_button_up[index];
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
const char* Input::GamePad::GetName() const
{
	return name;
}
#if DEBUG_ENABLE
void Input::GamePad::DebugLog()
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
	keyData[Key::A] = GLFW_KEY_A;
	keyData[Key::B] = GLFW_KEY_B;
	keyData[Key::C] = GLFW_KEY_C;
	keyData[Key::D] = GLFW_KEY_D;
	keyData[Key::E] = GLFW_KEY_E;
	keyData[Key::F] = GLFW_KEY_F;
	keyData[Key::G] = GLFW_KEY_G;
	keyData[Key::H] = GLFW_KEY_H;
	keyData[Key::I] = GLFW_KEY_I;
	keyData[Key::J] = GLFW_KEY_J;
	keyData[Key::K] = GLFW_KEY_K;
	keyData[Key::L] = GLFW_KEY_L;
	keyData[Key::N] = GLFW_KEY_N;
	keyData[Key::M] = GLFW_KEY_M;
	keyData[Key::O] = GLFW_KEY_O;
	keyData[Key::P] = GLFW_KEY_P;
	keyData[Key::Q] = GLFW_KEY_Q;
	keyData[Key::R] = GLFW_KEY_R;
	keyData[Key::S] = GLFW_KEY_S;
	keyData[Key::T] = GLFW_KEY_T;
	keyData[Key::U] = GLFW_KEY_U;
	keyData[Key::V] = GLFW_KEY_V;
	keyData[Key::W] = GLFW_KEY_W;
	keyData[Key::X] = GLFW_KEY_X;
	keyData[Key::Y] = GLFW_KEY_Y;
	keyData[Key::Z] = GLFW_KEY_Z;
	keyData[Key::SPACE] = GLFW_KEY_SPACE;
	keyData[Key::ENTER] = GLFW_KEY_ENTER;
	keyData[Key::UP] = GLFW_KEY_UP;
	keyData[Key::DOWN] = GLFW_KEY_DOWN;
	keyData[Key::RIGHT] = GLFW_KEY_RIGHT;
	keyData[Key::LEFT] = GLFW_KEY_LEFT;
	keyData[Key::ESCAPE] = GLFW_KEY_ESCAPE;

	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	IsPresent = true;
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
	nowWindow = w;
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
	for (auto it = button_down.begin(); it != button_down.end(); ++it)
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
	for (auto it = button_on.begin(); it != button_on.end(); ++it)
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
	for (auto it = button_up.begin(); it != button_up.end(); ++it)
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
		int state = glfwGetKey(nowWindow, keyData[i]);
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
	mouseData[Button::LEFT] = GLFW_MOUSE_BUTTON_1;
	mouseData[Button::RIGHT] = GLFW_MOUSE_BUTTON_2;
	mouseData[Button::CENTER] = GLFW_MOUSE_BUTTON_3;
	mouseData[Button::BUTTON_4] = GLFW_MOUSE_BUTTON_4;
	mouseData[Button::BUTTON_5] = GLFW_MOUSE_BUTTON_5;
	mouseData[Button::BUTTON_6] = GLFW_MOUSE_BUTTON_6;
	mouseData[Button::BUTTON_7] = GLFW_MOUSE_BUTTON_7;
	mouseData[Button::BUTTON_8] = GLFW_MOUSE_BUTTON_8;
	button_on.resize(256);
	std::fill(std::begin(button_on), std::end(button_on), 0);
	button_down.resize(256);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	button_up.resize(256);
	std::fill(std::begin(button_up), std::end(button_up), 0);

	IsPresent = true;
	collision = new PointCollider(&transform);
}
Input::Mouse::~Mouse()
{
	delete collision;
}
Input::Mouse* Input::InitMouse()
{
	Mouse* mouse_ = new Input::Mouse;
	mouse_->IsPresent = true;
	return mouse_;
}
void Input::Mouse::SetWindow(GLFWwindow* w)
{
	nowWindow = w;
	glfwSetScrollCallback(nowWindow, Input::Mouse::SetScroll_Callback);
	glfwSetDropCallback(nowWindow, Input::Mouse::SetDrop_Callback);
}
void Input::Mouse::SetScroll_Callback(GLFWwindow* w, double x, double y)
{
	Input::Mouse::scroll = { (float)x,(float)y };
}
void Input::Mouse::SetDrop_Callback(GLFWwindow * w, int count, const char ** path)
{
	for (int i = 0; i < count; ++i)
	{
#if ENGINE_DEVELOP
		printf("DropCallback[%s]\n", path[i]);
		EventTask et;
		et.Load(Event::INPUT_CONFIG, path[i]);
#endif
	}
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
	for (auto it = button_down.begin(); it != button_down.end(); ++it)
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
	for (auto it = button_on.begin(); it != button_on.end(); ++it)
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
	for (auto it = button_up.begin(); it != button_up.end(); ++it)
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
		int state = glfwGetMouseButton(nowWindow, mouseData[i]);
		button_down[i] = !button_on[i] && state;
		button_up[i] = button_on[i] && !state;
		button_on[i] = (u_char)state;
	}
	scrollValue = Input::Mouse::scroll;
	Input::Mouse::scroll = { 0,0 };

	glfwGetCursorPos(nowWindow, &pos_x, &pos_y);
	transform.position = { (float)pos_x,(float)pos_y };
}
Vec2 Input::Mouse::GetScroll() const
{
	return scrollValue;
}
Vec2 Input::Mouse::GetPos() const
{
	return transform.position;
}
PointCollider* Input::Mouse::GetCollision() const
{
	return collision;
}
void Input::Mouse::ResetMouse()
{
	std::fill(std::begin(button_on), std::end(button_on), 0);
	std::fill(std::begin(button_down), std::end(button_down), 0);
	std::fill(std::begin(button_up), std::end(button_up), 0);
}
//--------------------------------------------------
//@:Inputclass									
//--------------------------------------------------
Input::~Input()
{
	delete mouse;
	delete key;
	for (auto it = pad.begin(); it != pad.end(); ++it)
	{
		delete *it;
	}
}
void Input::Inputinit(GLFWwindow *w)
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
		inputdata[B1].button = Input::GamePad::Pad::BUTTON_A;
		inputdata[B2].button = Input::GamePad::Pad::BUTTON_B;
		inputdata[B3].button = Input::GamePad::Pad::BUTTON_X;
		inputdata[B4].button = Input::GamePad::Pad::BUTTON_Y;

		inputdata[L1].button = Input::GamePad::Pad::BUTTON_L1;
		inputdata[R1].button = Input::GamePad::Pad::BUTTON_R1;

		inputdata[D1].button = Input::GamePad::Pad::BUTTON_BACK;
		inputdata[D2].button = Input::GamePad::Pad::BUTTON_START;

		inputdata[SL].button = Input::GamePad::Pad::BUTTON_L3;
		inputdata[SR].button = Input::GamePad::Pad::BUTTON_R3;

		inputdata[CU].button = Input::GamePad::Pad::BUTTON_U;
		inputdata[CR].button = Input::GamePad::Pad::BUTTON_R;
		inputdata[CD].button = Input::GamePad::Pad::BUTTON_D;
		inputdata[CL].button = Input::GamePad::Pad::BUTTON_L;

		inputdata[LU].button = Input::GamePad::AXISBUTTON::LSTICK_UP;
		inputdata[LD].button = Input::GamePad::AXISBUTTON::LSTICK_DOWN;
		inputdata[LL].button = Input::GamePad::AXISBUTTON::LSTICK_LEFT;
		inputdata[LR].button = Input::GamePad::AXISBUTTON::LSTICK_RIGHT;

		inputdata[RU].button = Input::GamePad::AXISBUTTON::RSTICK_UP;
		inputdata[RD].button = Input::GamePad::AXISBUTTON::RSTICK_DOWN;
		inputdata[RL].button = Input::GamePad::AXISBUTTON::RSTICK_LEFT;
		inputdata[RR].button = Input::GamePad::AXISBUTTON::RSTICK_RIGHT;

		inputdata[L2].button = Input::GamePad::AXISBUTTON::BUTTON_L2;
		inputdata[R2].button = Input::GamePad::AXISBUTTON::BUTTON_R2;
	}
	//キーボードとの紐づけ
	{
		inputdata[B1].key = Input::KeyBoard::Key::Z;
		inputdata[B2].key = Input::KeyBoard::Key::X;
		inputdata[B3].key = Input::KeyBoard::Key::C;
		inputdata[B4].key = Input::KeyBoard::Key::V;

		inputdata[L1].key = Input::KeyBoard::Key::Q;
		inputdata[R1].key = Input::KeyBoard::Key::E;

		inputdata[D1].key = Input::KeyBoard::Key::ENTER;
		inputdata[D2].key = Input::KeyBoard::Key::SPACE;

		inputdata[SL].key = Input::KeyBoard::Key::B;
		inputdata[SR].key = Input::KeyBoard::Key::N;

		inputdata[CU].key = Input::KeyBoard::Key::UP;
		inputdata[CR].key = Input::KeyBoard::Key::RIGHT;
		inputdata[CD].key = Input::KeyBoard::Key::DOWN;
		inputdata[CL].key = Input::KeyBoard::Key::LEFT;

		inputdata[LU].key = Input::KeyBoard::Key::W;
		inputdata[LD].key = Input::KeyBoard::Key::S;
		inputdata[LL].key = Input::KeyBoard::Key::A;
		inputdata[LR].key = Input::KeyBoard::Key::D;

		inputdata[RU].key = Input::KeyBoard::Key::I;
		inputdata[RD].key = Input::KeyBoard::Key::K;
		inputdata[RL].key = Input::KeyBoard::Key::J;
		inputdata[RR].key = Input::KeyBoard::Key::L;

		inputdata[L2].key = Input::KeyBoard::Key::O;
		inputdata[R2].key = Input::KeyBoard::Key::U;
	}
}
void Input::Update()
{
	for (int i = 0; i < pad.size(); ++i)
	{
		pad[i]->Update();
	}
	key->Update();
	mouse->Update();
}
bool Input::down(const int index, const int padNum) const
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
bool Input::on(const int index, const int padNum) const
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
bool Input::up(const int index, const int padNum) const
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
bool Input::EitherDown() const
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
bool Input::EitherOn() const
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
bool Input::EitherUp() const
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
void Input::SetPadConfig(const StrID& Key, const int padKey)
{
	PadConfigData[Key].key = padKey;
}
void Input::RegisterPadConfig(const int padNum)
{
	pad[padNum]->SetConfig(&PadConfigData);
}
float Input::axis(const int index, const int padNum) const
{
	float ang = 0.f;
	switch (index)
	{
	case In::AXIS::AXIS_LEFT_X:
		if (key->on(KeyBoard::A))
		{
			ang -= 1.0f;
		}
		if (key->on(KeyBoard::D))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_LEFT_Y:
		if (key->on(KeyBoard::W))
		{
			ang += 1.0f;
		}
		if (key->on(KeyBoard::S))
		{
			ang -= 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_X:
		if (key->on(KeyBoard::J))
		{
			ang -= 1.0f;
		}
		if (key->on(KeyBoard::L))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_RIGHT_Y:
		if (key->on(KeyBoard::I))
		{
			ang += 1.0f;
		}
		if (key->on(KeyBoard::K))
		{
			ang -= 1.0f;
		}
		break;
	case In::AXIS::AXIS_L2:
		if (key->on(KeyBoard::O))
		{
			ang += 1.0f;
		}
		break;
	case In::AXIS::AXIS_R2:
		if (key->on(KeyBoard::U))
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
void Input::ResetInputData()
{
	ResetGamePad(pad);
	ResetKeyBoard(*key);
	mouse->ResetMouse();
}
void Input::RegistAxis(const float regist)
{
	for (auto it = pad.begin(); it != pad.end(); ++it)
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
#if DEBUG_ENABLE
void Input::DebugLog()
{
	for (int i = 0; i < pad.size(); ++i)
	{
		pad[i]->DebugLog();
	}
}
#endif
Input* Input::instance = nullptr;