#include "basic/input.h"

#include <atomic>
#include <raylib.h>
#include "common/vec2.h"

namespace urd
{
	namespace input
	{
		constexpr int _MouseKeyMap[] = {
			MOUSE_LEFT_BUTTON, MOUSE_RIGHT_BUTTON, MOUSE_MIDDLE_BUTTON};
		constexpr int _KeyCodeMap[] = {
			KEY_APOSTROPHE,
			KEY_COMMA,
			KEY_MINUS,
			KEY_PERIOD,
			KEY_SLASH,
			KEY_ZERO,
			KEY_ONE,
			KEY_TWO,
			KEY_THREE,
			KEY_FOUR,
			KEY_FIVE,
			KEY_SIX,
			KEY_SEVEN,
			KEY_EIGHT,
			KEY_NINE,
			KEY_SEMICOLON,
			KEY_EQUAL,
			KEY_A,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,
			KEY_LEFT_BRACKET,
			KEY_BACKSLASH,
			KEY_RIGHT_BRACKET,
			KEY_GRAVE,
			// Function keys
			KEY_SPACE,
			KEY_ESCAPE,
			KEY_ENTER,
			KEY_TAB,
			KEY_BACKSPACE,
			KEY_INSERT,
			KEY_DELETE,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_DOWN,
			KEY_UP,
			KEY_PAGE_UP,
			KEY_PAGE_DOWN,
			KEY_HOME,
			KEY_END,
			KEY_CAPS_LOCK,
			KEY_SCROLL_LOCK,
			KEY_NUM_LOCK,
			KEY_PRINT_SCREEN,
			KEY_PAUSE,
			KEY_F1,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			KEY_LEFT_SHIFT,
			KEY_LEFT_CONTROL,
			KEY_LEFT_ALT,
			KEY_LEFT_SUPER,
			KEY_RIGHT_SHIFT,
			KEY_RIGHT_CONTROL,
			KEY_RIGHT_ALT,
			KEY_RIGHT_SUPER,
			KEY_KB_MENU,
			// Keypad keys
			KEY_KP_0,
			KEY_KP_1,
			KEY_KP_2,
			KEY_KP_3,
			KEY_KP_4,
			KEY_KP_5,
			KEY_KP_6,
			KEY_KP_7,
			KEY_KP_8,
			KEY_KP_9,
			KEY_KP_DECIMAL,
			KEY_KP_DIVIDE,
			KEY_KP_MULTIPLY,
			KEY_KP_SUBTRACT,
			KEY_KP_ADD,
			KEY_KP_ENTER,
			KEY_KP_EQUAL,
			// Android key buttons
			KEY_BACK,
			KEY_MENU,
			KEY_VOLUME_UP,
			KEY_VOLUME_DOWN,
		};

		bool getMouseKeyDown(MouseKey key)
		{
			return IsMouseButtonPressed(_MouseKeyMap[(int)key]);
		}
		bool getMouseKeyUp(MouseKey key)
		{
			return IsMouseButtonReleased(_MouseKeyMap[(int)key]);
		}
		bool getMouseKey(MouseKey key)
		{
			return IsMouseButtonDown(_MouseKeyMap[(int)key]);
		}

		bool getKeyDown(KeyCode key) { return IsKeyPressed(_KeyCodeMap[(int)key]); }
		bool getKeyUp(KeyCode key) { return IsKeyReleased(_KeyCodeMap[(int)key]); }
		bool getKey(KeyCode key) { return IsKeyDown(_KeyCodeMap[(int)key]); }

		bool getKeyDown(std::initializer_list<KeyCode> keys, bool all)
		{
			for (auto key : keys)
			{
				if (getKeyDown(key) ^ all) return !all;
			}
			return all;
		}
		bool getKeyUp(std::initializer_list<KeyCode> keys, bool all)
		{
			for (auto key : keys)
			{
				if (getKeyUp(key) ^ all) return !all;
			}
			return all;
		}
		bool getKey(std::initializer_list<KeyCode> keys, bool all)
		{
			for (auto key : keys)
			{
				if (getKey(key) ^ all) return !all;
			}
			return all;
		}

		vec2 getMousePosition() { return vec2{(float)GetMouseX(), (float)GetMouseY()}; }

		int getHorizontalAxis()
		{
			int xInp = 0;
			if (getKey(KeyCode::D) || getKey(KeyCode::Right)) xInp = 1;
			else if (getKey(KeyCode::A) || getKey(KeyCode::Left))
				xInp = -1;
			return xInp;
		}
		int getVerticalAxis()
		{
			int yInp = 0;
			if (getKey(KeyCode::W) || getKey(KeyCode::Up)) yInp = 1;
			else if (getKey(KeyCode::S) || getKey(KeyCode::Down))
				yInp = -1;
			return yInp;
		}
	} // namespace input
} // namespace urd
