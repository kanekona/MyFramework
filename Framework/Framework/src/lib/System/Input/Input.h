
#pragma once

#include "Collision\Collision.h"
#include "Engine\Data.h"
#include "NonCopyable\NonCopyable.hpp"
#include "StrID\StrID.h"
#include "Engine\EngineMacro.h"
#include <unordered_map>

/**
*namespace In
*@brief	簡易引数用
*/
namespace In
{
	/**
	*enum Button
	*@brief	仮装コントローラの入力設定
	*/
	enum Button
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
	*@brief	コントローラのスティックと押し込み
	*/
	enum AXIS
	{
		//! 左スティックX値
		AXIS_LEFT_X,		
		//! 左スティックY値
		AXIS_LEFT_Y,	
		//! 右スティックX値
		AXIS_RIGHT_X,	
		//! 右スティックY値
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
	*@brief	スティックをボタンButton入力にも対応
	*/
	enum StickButton
	{
		//! 左スティック左入力
		LSTICK_LEFT,
		//! 左スティック右入力
		LSTICK_RIGHT,
		//! 左スティック上入力
		LSTICK_UP,
		//! 左スティック下入力
		LSTICK_DOWN,
		//! 右スティック左入力
		RSTICK_LEFT,
		//! 右スティっク右入力
		RSTICK_RIGHT,
		//! 右スティック上入力	
		RSTICK_UP,
		//! 右スティック下入力
		RSTICK_DOWN,
		//! R2
		BUTTON_R2,
		//! L2
		BUTTON_L2,
		//! スティック数
		STICK_NUM,
	};
	/**
	*enum IN
	*@brief	仮想入力
	*/
	enum
	{
		B1,
		B2,
		B3,
		B4,
		CD,
		CU,
		CR,
		CL,
		L1,
		R1,
		D1,
		D2,
		SR,
		SL,
		LD,
		LU,
		LR,
		LL,
		RD,
		RU,
		RR,
		RL,
		L2,
		R2,
	};
	/**
	*enum Key
	*@brief	キーボード入力
	*/
	enum Key
	{
		A, S, D, W, Q, E, Z, X, C, R, F, V, T,
		G, B, Y, H, N, U, J, M, I, K, O, L, P,
		SPACE, ENTER, ESCAPE,
		UP, DOWN, LEFT, RIGHT,
	};
}
/**
*namespace Mouse
*@brief	マウス用簡易引数
*/
namespace Mouse
{
	/**
	*enum Button
	*@brief	Mouseのボタン
	*/
	enum Button
	{
		//! 左
		LEFT,
		//! 右
		RIGTH,
		//! 中心
		CENTER,
		BUTTON_4,
		BUTTON_5,
		BUTTON_6,
		BUTTON_7,
		BUTTON_8,
	};
}
/**
*@brief	ゲームパッド、キーボード、マウスの入力を扱うclass
*
*既存GameEngineを使用している場合は自動で生成される
*/
class Input : private NonCopyable
{
public:
	/**
	*@brief	ゲームパッドとキーボードを区別する
	*/
	struct InputData
	{
		//! ゲームパッドのボタン
		int button;
		//! キーボードのキー
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
	*enum in
	*@brief	入力用仮想入力
	*/
	enum in {
		B1,
		B2,
		B3,
		B4,
		CD,
		CU,
		CR,
		CL,
		L1,
		R1,
		D1,
		D2,
		SR,
		SL,
		LD,
		LU,
		LR,
		LL,
		RD,
		RU,
		RR,
		RL,
		L2,
		R2,
	};
	/**
	*@brief	ゲームパッド入力
	*/
	class GamePad
	{
	public:
		/**
		*enum Pad
		*@brief	仮装コントローラの入力設定
		*/
		enum Pad
		{
			//! 0
			BUTTON_A,
			//! 1
			BUTTON_B,
			//! 2
			BUTTON_X,
			//! 3
			BUTTON_Y,		
			//! 4
			BUTTON_L1,		
			//! 5
			BUTTON_R1,		
			//! 6
			BUTTON_BACK,	
			//! 7
			BUTTON_START,	
			//! 8
			BUTTON_L3,		
			//! 9
			BUTTON_R3,		
			//! 10
			BUTTON_U,		
			//! 11
			BUTTON_R,	
			//! 12
			BUTTON_D,	
			//! 13
			BUTTON_L,
		};
		/**
		*enum AXIS
		*@brief	仮装コントローラの入力設定
		*/
		enum AXIS {
			//! 左スティックX値
			AXIS_LEFT_X,
			//! 左スティックY値
			AXIS_LEFT_Y,
			//! 右スティックX値
			AXIS_RIGHT_X,
			//! 右スティックY値
			AXIS_RIGHT_Y,
			//!	R2
			AXIS_R2,
			//! L2
			AXIS_L2,
			//! ButtonNumber
			AXIS_BUTTON_NUM,
		};
		/**
		*enum AXISBUTTON
		*@brief	仮装コントローラの入力設定
		*/
		enum AXISBUTTON
		{
			//! 左スティック左入力
			LSTICK_LEFT,
			//! 左スティック右入力
			LSTICK_RIGHT,
			//! 左スティック上入力
			LSTICK_UP,
			//! 左スティック下入力
			LSTICK_DOWN,
			//! 右スティック左入力
			RSTICK_LEFT,
			//! 右スティっク右入力
			RSTICK_RIGHT,
			//! 右スティック上入力	
			RSTICK_UP,
			//! 右スティック下入力
			RSTICK_DOWN,
			//! R2
			BUTTON_R2,
			//! L2
			BUTTON_L2,
			//! スティック数
			STICK_NUM,
		};
		/**
		*@brief	constructor
		*@param[in]	int id ゲームパッド番号
		*/
		explicit GamePad(const int id);
		/**
		*@brief	押している判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	押した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	離した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	全てのdown入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	全てのon入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	全てのup入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		/**
		*@brief	指定値のスティックの傾きを返す
		*@param[in]	int index スティック指定
		*@return float 傾き度(0~1)
		*/
		float axis(const int index) const;
		/**
		*@brief	指定スティックの押し状態を返す
		*@param[in]	int index スティック指定
		*@return bool 指定側に倒れていればtrue
		*/
		bool axis_on(const int index) const;
		/**
		*@brief	指定スティックの押し状態を返す
		*@param[in]	int index スティック指定
		*@return bool 指定側に倒された瞬間であればtrue
		*/
		bool axis_down(const int index) const;
		/**
		*@brief	指定スティックの押し状態を返す
		*@param[in]	int index スティック指定
		*@return bool 指定側から上がった瞬間であればtrue
		*/
		bool axis_up(const int index) const;
		/**
		*@brief	ゲームパッドの有無を返す
		*@return bool 存在すればtrue
		*/
		bool IsPresent() const;
		/**
		*@brief	入力状況の更新
		*/
		void Update();
		/**
		*@brief	各値の初期化
		*/
		void SetConfig(std::unordered_map<StrID,Input::ConfigData>* ConfigData);
		/**
		*@brief	入力状態のリセット
		*/
		void Reset();
		/**
		*@brief	スティックの範囲外処理
		*@param[in]	float axis_threshold_ 区切る値
		*@return 成功true
		*/
		bool RegistAxisButton(
			const float axis_threshold_);
		/**
		*@brief	ゲームパッド名を返す
		*@return char* ゲームパッド名
		*/
		const char* GetName() const;
#if DEBUG_ENABLE
		void DebugLog();
#endif
	private:
		//! ゲームパッド複数個に対応させるために１つ１つにidを振り分ける
		int id;
		//! ゲームパッドのボタン数
		int button_num;
		//! ゲームパッドのスティック数
		int axis_num;
		//! 入力データを格納する変数
		int gPadData[14];
		//! スティック情報を格納する変数
		std::vector<float> axis_value;
		//! スティックの頂点値
		float axis_threshold;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//! buttonのupを格納する変数
		std::vector<u_char> button_up;
		//! axisのonを格納する変数
		std::vector<u_char> axis_button_on;
		//! axisのdownを格納する変数
		std::vector<u_char> axis_button_down;
		//! axisのupを格納する変数
		std::vector<u_char> axis_button_up;
		//! コントローラ名
		const char* name;
		/**
		*@brief	ボタン数を返す
		*@return int ボタン数
		*/
		int buttons() const;
		/**
		*@brief	スティック数を返す
		*@return スティック数
		*/
		int GetStickNum() const;
	};
	/**
	*@brief	キーボード入力
	*/
	class KeyBoard
	{
	public:
		/**
		*enum Key
		*@brief	キーボードの仮装キー設定
		*/
		enum Key
		{	
			A, S, D, W, Q, E, Z, X, C, R, F, V, T,
			G, B, Y, H, N, U, J, M, I, K, O, L, P,
			SPACE, ENTER, ESCAPE,
			UP, DOWN, LEFT, RIGHT, Num
		};
		/**
		*@brief	constructor
		*/
		explicit KeyBoard();
		/**
		*@brief	離した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	押した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	押している判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@return bool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	全てのdown入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	全てのon入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	全てのup入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		/**
		*@brief	入力状況の更新
		*/
		void Update();
		/**
		*@brief	反映させるWindowを登録する
		*@param[in] GLFWWindow* w Windowのポインタ
		*/
		void SetWindow(GLFWwindow* w);
		//! キーボードの有無
		bool IsPresent;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//!buttonのupを格納する変数
		std::vector<u_char> button_up;
	private:
		//! 入力データを格納する変数
		int keyData[256];
		//! Window情報を格納する
		GLFWwindow* nowWindow;
	};
	/**
	*@brief	マウス入力
	*/
	class Mouse
	{
	public:
		/**
		*enum Mouse_
		*@brief	マウスの入力設定
		*/
		enum Button
		{
			//! 右
			LEFT,
			//! 左
			RIGHT,
			//! 中心
			CENTER,
			BUTTON_4,
			BUTTON_5,
			BUTTON_6,
			BUTTON_7,
			BUTTON_8,
		};
		/**
		*@brief	constructor
		*/
		explicit Mouse();
		/**
		*@brief	destructor
		*/
		virtual ~Mouse();
		/**
		*@brief	入力状況の更新
		*/
		void Update();
		/**
		*@brief	反映させるWindowを登録する
		*@param[in]	GLFWWindow* w Windowのポインタ
		*/
		void SetWindow(GLFWwindow *w);
		/**
		*@brief	Windowからのマウスの位置を返す
		*@return Vec2 マウスの位置
		*/
		Vec2 GetPos() const;
		/**
		*@brief	押している判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@returnbool 押していればtrue
		*/
		bool on(const int index) const;
		/**
		*@brief	押した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@returnbool 押した瞬間であればtrue
		*/
		bool down(const int index) const;
		/**
		*@brief	離した瞬間の判定を返す
		*@param[in] int index 判定を行いたい入力番号
		*@returnbool 離した瞬間であればtrue
		*/
		bool up(const int index) const;
		/**
		*@brief	全てのdown入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherDown() const;
		/**
		*@brief	てのon入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherOn() const;
		/**
		*@brief	全てのup入力のうち１つでも判定があるか調べる
		*@return 1つ以上入力されているとtrue
		*/
		bool EitherUp() const;
		/**
		*@brief	マウスのホイール値を返す
		*@return Vec2 ホイールの値
		*/
		Vec2 GetScroll() const;
		/**
		*@brief	マウスの入力状況をリセットする
		*/
		void ResetMouse();
		/**
		*@brief	マウスの判定を取得する
		*@return CollisionPointer* マウスのCollision
		*/
		PointCollider* GetCollision() const;
		//! マウスの有無
		bool IsPresent;
	private:
		//! MauseButtonデータ
		int mouseData[8];
		//! マウスの座標を保存する変数
		//Vec2 position;
		Transform transform;
		//! Windowの情報を格納する
		GLFWwindow* nowWindow;
		//! ホイール値
		Vec2 scrollValue;
		//! マウスの判定
		PointCollider* collision;
		//! buttonのonを格納する変数
		std::vector<u_char> button_on;
		//! buttonのdownを格納する変数
		std::vector<u_char> button_down;
		//! buttonのupを格納する変数
		std::vector<u_char> button_up;
		//! Mouse位置取得時に使用するdouble型
		double pos_x, pos_y;
		//! ホイール獲得のコールバックで得た値をいれておく
		static Vec2 scroll;
		/**
		*@brief	マウスのホイール状態を獲得する
		*@param[in]	GLFWWindow* w window情報
		*@param[in]	double x x座標のホイール値
		*@param[in] double y y座標のホイール値
		*/
		static void SetScroll_Callback(GLFWwindow* w, double x, double y);
		/**
		*
		*/
		static void SetDrop_Callback(GLFWwindow* w, int count, const char** path);
	};
	//! ゲームパッド配列
	std::vector<GamePad*> pad;
	//! キーボード
	KeyBoard* key;
	//! マウス
	Mouse* mouse;
	//! ゲームパッドの存在有無
	bool pad_Connection;
	//関数
	/**
	*@brief	入力初期化
	*@param[in]	GLFWWindow* w 指定するWindowのポインタ
	*/
	void Inputinit(GLFWwindow *w);
	/**
	*@brief	押している判定を返す
	*@param[in] int index 判定を行いたい入力番号
	*@param[in]	int padNum 判定を行うゲームパッドの番号
	*@return bool 押していればtrue
	*/
	bool on(const int index, const int padNum = 0) const;
	/**
	*@brief	押した瞬間の判定を返す
	*@param[in] int index 判定を行いたい入力番号
	*@param[in]	int padNum 判定を行うゲームパッドの番号
	*@return bool 押した瞬間であればtrue
	*/
	bool down(const int index, const int padNum = 0) const;
	/**
	*@brief	離した瞬間の判定を返す
	*@param[in] int index 判定を行いたい入力番号
	*@param[in]	int padNum 判定を行うゲームパッドの番号
	*@return bool 離した瞬間であればtrue
	*/
	bool up(const int index, const int padNum = 0) const;
	/**
	*@brief	指定値のスティックの傾きを返す
	*@param[in]	int index スティック指定
	*@param[in]	int padNum 判定を行うゲームパッドの番号
	*@return float 傾き度(0~1)
	*/
	float axis(const int index, const int padNum = 0) const;
	/**
	*@brief	全てのゲームパッドのスティックの傾き範囲を制限する
	*@param[in]	float regist 指定値
	*/
	void RegistAxis(const float regist);
	/**
	*@brief	入力状況の更新
	*/
	void Update();
	/**
	*@brief	全てのdown入力のうち１つでも判定があるか調べる
	*@return bool 1つ以上入力されているとtrue
	*/
	bool EitherDown() const;
	/**
	*@brief	全てのon入力のうち１つでも判定があるか調べる
	*@return bool 1つ以上入力されているとtrue
	*/
	bool EitherOn() const;
	/**
	*@brief	全てのup入力のうち１つでも判定があるか調べる
	*@return bool 1つ以上入力されているとtrue
	*/
	bool EitherUp() const;
	/**
	*
	*/
	void SetPadConfig(const StrID& key,const int padKey);
	/**
	 * 
	 */
	void RegisterPadConfig(const int padNum = 0);
	/**
	 * @brief constructor
	 */
	explicit Input();
	/**
	*@brief	destructor
	*/
	virtual ~Input();
	/**
	*@brief	Create Singleton
	*@param[in] GLFWWindow* window Current Window
	*@return Input* instance
	*/
	static Input* Create(GLFWwindow* window);
	/**
	*@brief	Get Singleton
	*@return Input* instance
	*/
	static Input* Get();
	/**
	*@brief	Destroy Singleton
	*/
	static void Destroy();
#if DEBUG_ENABLE
	void DebugLog();
#endif
private:
	/**
	*@brief	入力状態をリセット
	*/
	void ResetInputData();
	//! 入力データ
	int inputData[256];
	//! Singleton
	static Input* instance;
	/**
	*@brief	ゲームパッド初期化
	*@return vetor<GamePad*> 生成したゲームパッド達
	*/
	std::vector<Input::GamePad*> InitGamePad();
	/**
	*@brief	キーボード初期化
	*return KeyBoard* 生成したキーボード
	*/
	KeyBoard* InitkeyBoard();
	/**
	*@brief	マウス初期化
	*@return Mouse* 生成したマウス
	*/
	Mouse* InitMouse();
	//! in分のデータ
	InputData inputdata[24];
	//! コンフィグデータ
	std::unordered_map<StrID, ConfigData> PadConfigData;
};
//Input* Input::instance = nullptr;