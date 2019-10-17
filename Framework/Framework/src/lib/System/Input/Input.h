
#pragma once

#include "Collision\Collision.h"
#include "Engine\Data.h"
#include "NonCopyable\NonCopyable.hpp"
#include "StrID\StrID.h"
#include "Engine\EngineMacro.h"
#include "Engine\EngineTypedef.h"
#include <unordered_map>

/**
*�S�̓I�C���\��
*�e���͂�Delegate�@�\��ǉ�����
*/

/**
*namespace In
*@brief	�ȈՈ����p
*/
namespace In
{
	/**
	*enum Button
	*@brief	�����R���g���[���̓��͐ݒ�
	*/
	enum EButton : uint8
	{
		//!	1
		BUTTON_A,		
		//! 2
		BUTTON_B,
		//! 3
		BUTTON_X,
		//! 4
		BUTTON_Y,
		//! 5
		BUTTON_L1,
		//! 6
		BUTTON_R1,		
		//! 7
		BUTTON_BACK,
		//! 8
		BUTTON_START,
		//! 9
		BUTTON_L3,
		//! 10
		BUTTON_R3,
		//! 11
		BUTTON_U,
		//! 12
		BUTTON_R,
		//! 13
		BUTTON_D,
		//! 14
		BUTTON_L,
	};
	/**
	*enum AXIS
	*@brief	�R���g���[���̃X�e�B�b�N�Ɖ�������
	*/
	enum EAxis : uint8
	{
		//! ���X�e�B�b�NX�l
		AXIS_LEFT_X,		
		//! ���X�e�B�b�NY�l
		AXIS_LEFT_Y,	
		//! �E�X�e�B�b�NX�l
		AXIS_RIGHT_X,	
		//! �E�X�e�B�b�NY�l
		AXIS_RIGHT_Y,
		//!	R2
		AXIS_R2,
		//! L2
		AXIS_L2,
		//! AXISNumber
		AXIS_BUTTON_NUM,
	};
	/**
	*enum StickButton
	*@brief	�X�e�B�b�N���{�^��Button���͂ɂ��Ή�
	*/
	enum EStick : uint8
	{
		//! ���X�e�B�b�N������
		LSTICK_LEFT,
		//! ���X�e�B�b�N�E����
		LSTICK_RIGHT,
		//! ���X�e�B�b�N�����
		LSTICK_UP,
		//! ���X�e�B�b�N������
		LSTICK_DOWN,
		//! �E�X�e�B�b�N������
		RSTICK_LEFT,
		//! �E�X�e�B���N�E����
		RSTICK_RIGHT,
		//! �E�X�e�B�b�N�����	
		RSTICK_UP,
		//! �E�X�e�B�b�N������
		RSTICK_DOWN,
		//! R2
		BUTTON_R2,
		//! L2
		BUTTON_L2,
		//! �X�e�B�b�N��
		STICK_NUM,
	};
	/**
	*enum IN
	*@brief	���z����
	*/
	enum EVirtual : uint8
	{
		B1,	B2,	B3,	B4,
		CD,	CU,	CR,	CL,
		L1,	R1,
		D1,	D2,
		SR,	SL,	
		LD,	LU,	LR,	LL,
		RD,	RU,	RR,	RL,
		L2,	R2,
	};
	/**
	*enum Key
	*@brief	�L�[�{�[�h����
	*/
	enum EKey : uint8
	{
		A, S, D, W, Q, E, Z, X, C, R, F, V, T,
		G, B, Y, H, N, U, J, M, I, K, O, L, P,
		SPACE, ENTER, ESCAPE,
		UP, DOWN, LEFT, RIGHT,
		F01,F02,F03,F04,F05,F06,F07,F08,F09,F10,F11,F12,
		N0,N1,N2,N3,N4,N5,N6,N7,N8,N9,
		KEY_NUM
	};
	/**
	*enum Button
	*@brief	Mouse�̃{�^��
	*/
	enum EMouse : uint8
	{
		//! ��
		MOUSE_LEFT,
		//! �E
		MOUSE_RIGHT,
		//! ���S
		MOUSE_CENTER,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,
	};
}
/**
*@brief	�Q�[���p�b�h�A�L�[�{�[�h�A�}�E�X�̓��͂�����class
*
*����GameEngine���g�p���Ă���ꍇ�͎����Ő��������
*/
class CInput : private CNonCopyable
{
public:
	/**
	*@brief	�Q�[���p�b�h�ƃL�[�{�[�h����ʂ���
	*/
	struct InputData
	{
		//! �Q�[���p�b�h�̃{�^��
		int button;
		//! �L�[�{�[�h�̃L�[
		int key;
	};
	/**
	 * @brief
	 */
	struct ConfigData
	{
		int index;
		int key;
		ConfigData()
		{

		}
		ConfigData(int i, int k)
		{
			index = i;
			key = k;
		}
	};
	/**
	*@brief	�Q�[���p�b�h����
	*/
	class GamePad
	{
	public:
		/**
		*@brief	constructor
		*@param[in]	int id �Q�[���p�b�h�ԍ�
		*/
		explicit GamePad(const int id);
		/**
		*@brief	�����Ă��锻���Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �����Ă����true
		*/
		bool on(const int index) const;
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �������u�Ԃł����true
		*/
		bool down(const int index) const;
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �������u�Ԃł����true
		*/
		bool up(const int index) const;
		/**
		*@brief	�S�Ă�down���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherDown() const;
		/**
		*@brief	�S�Ă�on���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherOn() const;
		/**
		*@brief	�S�Ă�up���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherUp() const;
		/**
		*@brief	�w��l�̃X�e�B�b�N�̌X����Ԃ�
		*@param[in]	int index �X�e�B�b�N�w��
		*@return float �X���x(0~1)
		*/
		float axis(const int index) const;
		/**
		*@brief	�w��X�e�B�b�N�̉�����Ԃ�Ԃ�
		*@param[in]	int index �X�e�B�b�N�w��
		*@return bool �w�葤�ɓ|��Ă����true
		*/
		bool axis_on(const int index) const;
		/**
		*@brief	�w��X�e�B�b�N�̉�����Ԃ�Ԃ�
		*@param[in]	int index �X�e�B�b�N�w��
		*@return bool �w�葤�ɓ|���ꂽ�u�Ԃł����true
		*/
		bool axis_down(const int index) const;
		/**
		*@brief	�w��X�e�B�b�N�̉�����Ԃ�Ԃ�
		*@param[in]	int index �X�e�B�b�N�w��
		*@return bool �w�葤����オ�����u�Ԃł����true
		*/
		bool axis_up(const int index) const;
		/**
		*@brief	�Q�[���p�b�h�̗L����Ԃ�
		*@return bool ���݂����true
		*/
		bool IsPresent() const;
		/**
		*@brief	���͏󋵂̍X�V
		*/
		void Update();
		/**
		*@brief	�e�l�̏�����
		*/
		void SetConfig(std::unordered_map<CStrID,CInput::ConfigData>* ConfigData);
		/**
		*@brief	���͏�Ԃ̃��Z�b�g
		*/
		void Reset();
		/**
		*@brief	�X�e�B�b�N�͈̔͊O����
		*@param[in]	float axis_threshold_ ��؂�l
		*@return ����true
		*/
		bool RegistAxisButton(
			const float axis_threshold_);
		/**
		*@brief	�Q�[���p�b�h����Ԃ�
		*@return char* �Q�[���p�b�h��
		*/
		const char* GetName() const;
#if DEBUG_ENABLE
		void DebugLog();
#endif
	private:
		//! �Q�[���p�b�h�����ɑΉ������邽�߂ɂP�P��id��U�蕪����
		int id;
		//! �Q�[���p�b�h�̃{�^����
		int button_num;
		//! �Q�[���p�b�h�̃X�e�B�b�N��
		int axis_num;
		//! ���̓f�[�^���i�[����ϐ�
		int gPadData[14];
		//! �X�e�B�b�N�����i�[����ϐ�
		std::vector<float> axis_value;
		//! �X�e�B�b�N�̒��_�l
		float axis_threshold;
		//! button��on���i�[����ϐ�
		std::vector<u_char> button_on;
		//! button��down���i�[����ϐ�
		std::vector<u_char> button_down;
		//! button��up���i�[����ϐ�
		std::vector<u_char> button_up;
		//! axis��on���i�[����ϐ�
		std::vector<u_char> axis_button_on;
		//! axis��down���i�[����ϐ�
		std::vector<u_char> axis_button_down;
		//! axis��up���i�[����ϐ�
		std::vector<u_char> axis_button_up;
		//! �R���g���[����
		const char* name;
		/**
		*@brief	�{�^������Ԃ�
		*@return int �{�^����
		*/
		int buttons() const;
		/**
		*@brief	�X�e�B�b�N����Ԃ�
		*@return �X�e�B�b�N��
		*/
		int GetStickNum() const;
	};
	/**
	*@brief	�L�[�{�[�h����
	*/
	class KeyBoard
	{
	public:
		/**
		*@brief	constructor
		*/
		explicit KeyBoard();
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �������u�Ԃł����true
		*/
		bool up(const int index) const;
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �������u�Ԃł����true
		*/
		bool down(const int index) const;
		/**
		*@brief	�����Ă��锻���Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@return bool �����Ă����true
		*/
		bool on(const int index) const;
		/**
		*@brief	�S�Ă�down���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherDown() const;
		/**
		*@brief	�S�Ă�on���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherOn() const;
		/**
		*@brief	�S�Ă�up���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherUp() const;
		/**
		*@brief	���͏󋵂̍X�V
		*/
		void Update();
		/**
		*@brief	���f������Window��o�^����
		*@param[in] GLFWWindow* w Window�̃|�C���^
		*/
		void SetWindow(GLFWwindow* w);
		//! �L�[�{�[�h�̗L��
		bool IsPresent;
		//! button��on���i�[����ϐ�
		std::vector<u_char> button_on;
		//! button��down���i�[����ϐ�
		std::vector<u_char> button_down;
		//!button��up���i�[����ϐ�
		std::vector<u_char> button_up;
	private:
		//! ���̓f�[�^���i�[����ϐ�
		int keyData[256];
		//! Window�����i�[����
		GLFWwindow* nowWindow;
	};
	/**
	*@brief	�}�E�X����
	*/
	class Mouse
	{
	public:
		/**
		*@brief	constructor
		*/
		explicit Mouse();
		/**
		*@brief	destructor
		*/
		virtual ~Mouse();
		/**
		*@brief	���͏󋵂̍X�V
		*/
		void Update();
		/**
		*@brief	���f������Window��o�^����
		*@param[in]	GLFWWindow* w Window�̃|�C���^
		*/
		void SetWindow(GLFWwindow *w);
		/**
		*@brief	Window����̃}�E�X�̈ʒu��Ԃ�
		*@return Vec2 �}�E�X�̈ʒu
		*/
		CVec2 GetPos() const;
		/**
		*@brief	�����Ă��锻���Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@returnbool �����Ă����true
		*/
		bool on(const int index) const;
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@returnbool �������u�Ԃł����true
		*/
		bool down(const int index) const;
		/**
		*@brief	�������u�Ԃ̔����Ԃ�
		*@param[in] int index ������s���������͔ԍ�
		*@returnbool �������u�Ԃł����true
		*/
		bool up(const int index) const;
		/**
		*@brief	�S�Ă�down���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherDown() const;
		/**
		*@brief	�Ă�on���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherOn() const;
		/**
		*@brief	�S�Ă�up���͂̂����P�ł����肪���邩���ׂ�
		*@return 1�ȏ���͂���Ă����true
		*/
		bool EitherUp() const;
		/**
		*@brief	�}�E�X�̃z�C�[���l��Ԃ�
		*@return Vec2 �z�C�[���̒l
		*/
		CVec2 GetScroll() const;
		/**
		*@brief	�}�E�X�̓��͏󋵂����Z�b�g����
		*/
		void ResetMouse();
		/**
		*@brief	�}�E�X�̔�����擾����
		*@return CollisionPointer* �}�E�X��Collision
		*/
		CPointCollider* GetCollision() const;
		/**
		*@brief �}�E�X�ʒu�̃J���[�擾
		*@return Color Pixcel Color
		*/
		CColor GetPixcel();
		//! �}�E�X�̗L��
		bool IsPresent;
	private:
		//! MauseButton�f�[�^
		int mouseData[8];
		//! �}�E�X�̍��W��ۑ�����ϐ�
		//Vec2 position;
		CTransform transform;
		//! Window�̏����i�[����
		GLFWwindow* nowWindow;
		//! �z�C�[���l
		CVec2 scrollValue;
		//! �}�E�X�̔���
		CPointCollider* collision;
		//! button��on���i�[����ϐ�
		std::vector<u_char> button_on;
		//! button��down���i�[����ϐ�
		std::vector<u_char> button_down;
		//! button��up���i�[����ϐ�
		std::vector<u_char> button_up;
		//! Mouse�ʒu�擾���Ɏg�p����double�^
		double pos_x, pos_y;
		//! �z�C�[���l���̃R�[���o�b�N�œ����l������Ă���
		static CVec2 scroll;
		/**
		*@brief	�}�E�X�̃z�C�[����Ԃ��l������
		*@param[in]	GLFWWindow* w window���
		*@param[in]	double x x���W�̃z�C�[���l
		*@param[in] double y y���W�̃z�C�[���l
		*/
		static void SetScroll_Callback(GLFWwindow* w, double x, double y);
		/**
		*
		*/
		static void SetDrop_Callback(GLFWwindow* w, int count, const char** path);
	};
	//! �Q�[���p�b�h�z��
	std::vector<GamePad*> pad;
	//! �L�[�{�[�h
	KeyBoard* key;
	//! �}�E�X
	Mouse* mouse;
	//! �Q�[���p�b�h�̑��ݗL��
	bool pad_Connection;
	//�֐�
	/**
	*@brief	���͏�����
	*@param[in]	GLFWWindow* w �w�肷��Window�̃|�C���^
	*/
	void Inputinit(GLFWwindow *w);
	/**
	*@brief	�����Ă��锻���Ԃ�
	*@param[in] int index ������s���������͔ԍ�
	*@param[in]	int padNum ������s���Q�[���p�b�h�̔ԍ�
	*@return bool �����Ă����true
	*/
	bool on(const int index, const int padNum = 0) const;
	/**
	*@brief	�������u�Ԃ̔����Ԃ�
	*@param[in] int index ������s���������͔ԍ�
	*@param[in]	int padNum ������s���Q�[���p�b�h�̔ԍ�
	*@return bool �������u�Ԃł����true
	*/
	bool down(const int index, const int padNum = 0) const;
	/**
	*@brief	�������u�Ԃ̔����Ԃ�
	*@param[in] int index ������s���������͔ԍ�
	*@param[in]	int padNum ������s���Q�[���p�b�h�̔ԍ�
	*@return bool �������u�Ԃł����true
	*/
	bool up(const int index, const int padNum = 0) const;
	/**
	*@brief	�w��l�̃X�e�B�b�N�̌X����Ԃ�
	*@param[in]	int index �X�e�B�b�N�w��
	*@param[in]	int padNum ������s���Q�[���p�b�h�̔ԍ�
	*@return float �X���x(0~1)
	*/
	float axis(const int index, const int padNum = 0) const;
	/**
	*@brief	�S�ẴQ�[���p�b�h�̃X�e�B�b�N�̌X���͈͂𐧌�����
	*@param[in]	float regist �w��l
	*/
	void RegistAxis(const float regist);
	/**
	*@brief	���͏󋵂̍X�V
	*/
	void Update();
	/**
	*@brief	�S�Ă�down���͂̂����P�ł����肪���邩���ׂ�
	*@return bool 1�ȏ���͂���Ă����true
	*/
	bool EitherDown() const;
	/**
	*@brief	�S�Ă�on���͂̂����P�ł����肪���邩���ׂ�
	*@return bool 1�ȏ���͂���Ă����true
	*/
	bool EitherOn() const;
	/**
	*@brief	�S�Ă�up���͂̂����P�ł����肪���邩���ׂ�
	*@return bool 1�ȏ���͂���Ă����true
	*/
	bool EitherUp() const;
	/**
	*
	*/
	void SetPadConfig(const CStrID& key,const int padKey);
	/**
	 * 
	 */
	void RegisterPadConfig(const int padNum = 0);
	/**
	 * @brief constructor
	 */
	explicit CInput();
	/**
	*@brief	destructor
	*/
	virtual ~CInput();
	/**
	*@brief	Create Singleton
	*@param[in] GLFWWindow* window Current Window
	*@return Input* instance
	*/
	static CInput* Create(GLFWwindow* window);
	/**
	*@brief	Get Singleton
	*@return Input* instance
	*/
	static CInput* Get();
	/**
	*@brief	Destroy Singleton
	*/
	static void Destroy();
#if DEBUG_ENABLE
	void DebugLog();
#endif
private:
	/**
	*@brief	���͏�Ԃ����Z�b�g
	*/
	void ResetInputData();
	//! ���̓f�[�^
	int inputData[256];
	//! Singleton
	static CInput* instance;
	/**
	*@brief	�Q�[���p�b�h������
	*@return vetor<GamePad*> ���������Q�[���p�b�h�B
	*/
	std::vector<CInput::GamePad*> InitGamePad();
	/**
	*@brief	�L�[�{�[�h������
	*return KeyBoard* ���������L�[�{�[�h
	*/
	KeyBoard* InitkeyBoard();
	/**
	*@brief	�}�E�X������
	*@return Mouse* ���������}�E�X
	*/
	Mouse* InitMouse();
	//! in���̃f�[�^
	InputData inputdata[24];
	//! �R���t�B�O�f�[�^
	std::unordered_map<CStrID, ConfigData> PadConfigData;
};
//Input* Input::instance = nullptr;