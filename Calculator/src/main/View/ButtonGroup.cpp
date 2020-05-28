#ifndef TEST

#include "ButtonGroup.h"
#include "../Any/View.h"
#include <SDL.h>
#include "Button.h"
#include "../Struct/Rect.h"
#include "../Struct/Point.h"
#include "../Struct/Size.h"
#include "../Struct/Color.h"
#include "../Any/Enums.h"
#include "../Functions/control_flow.h"
#include "../Any/ButtonGrid.h"
#include "../Struct/Pair.h"
#include "../Struct/Message.h"

namespace ii887522::Calculator
{
	ButtonGroup::ButtonGroup(SDL_Renderer*const renderer, const ButtonGrid& buttonGrid) : View{ renderer }, buttons{
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(0), buttonGrid.getButtonY(0) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_LEFT }, SDLK_LEFT },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(1), buttonGrid.getButtonY(1) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_SQR } },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(2), buttonGrid.getButtonY(2) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_SQRT } },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(3), buttonGrid.getButtonY(3) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_RIGHT }, SDLK_RIGHT },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(4), buttonGrid.getButtonY(4) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_CE } },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(5), buttonGrid.getButtonY(5) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_C }, SDLK_c },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(6), buttonGrid.getButtonY(6) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_BACKSPACE }, SDLK_BACKSPACE },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(7), buttonGrid.getButtonY(7) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_DIVIDE }, SDLK_KP_DIVIDE },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(8), buttonGrid.getButtonY(8) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_7 }, SDLK_KP_7 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(9), buttonGrid.getButtonY(9) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_8 }, SDLK_KP_8 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(10), buttonGrid.getButtonY(10) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_9 }, SDLK_KP_9 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(11), buttonGrid.getButtonY(11) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_MULTIPLY }, SDLK_KP_MULTIPLY },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(12), buttonGrid.getButtonY(12) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_4 }, SDLK_KP_4 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(13), buttonGrid.getButtonY(13) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_5 }, SDLK_KP_5 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(14), buttonGrid.getButtonY(14) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_6 }, SDLK_KP_6 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(15), buttonGrid.getButtonY(15) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_MINUS }, SDLK_KP_MINUS },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(16), buttonGrid.getButtonY(16) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_1 }, SDLK_KP_1 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(17), buttonGrid.getButtonY(17) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_2 }, SDLK_KP_2 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(18), buttonGrid.getButtonY(18) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_3 }, SDLK_KP_3 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(19), buttonGrid.getButtonY(19) }, buttonGrid.buttonSize },
			Color{ 224u, 224u, 224u }, Message{ Message::Head::INPUT_PLUS }, SDLK_KP_PLUS },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(20), buttonGrid.getButtonY(20) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_SIGN } },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(21), buttonGrid.getButtonY(21) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_0 }, SDLK_KP_0 },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(22), buttonGrid.getButtonY(22) }, buttonGrid.buttonSize },
			Color{ 255u, 255u, 255u }, Message{ Message::Head::INPUT_DOT }, SDLK_KP_PERIOD },
		Button{ renderer, Rect{ Point{ buttonGrid.getButtonX(23), buttonGrid.getButtonY(23) }, buttonGrid.buttonSize },
			Color{ 86u, 173u, 255u }, Message{ Message::Head::INPUT_EQUAL }, SDLK_KP_ENTER }
	}, isAnimating{ false }, buttonAnimationsCount{ 0u } { }

	Action ButtonGroup::reactMouseMotion(const SDL_MouseMotionEvent& motionEvent)
	{
		auto result{ Action::NONE };
		loop(sizeof buttons / sizeof Button, [=, &result](const auto i) {
			const auto action{ buttons[i].reactMouseMotion(motionEvent) };
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			result = action;
			isAnimating = true;
		});
		return result;
	}

	Action ButtonGroup::reactLeftMouseButtonDown(const SDL_MouseButtonEvent& buttonEvent)
	{
		auto result{ Action::NONE };
		loop(sizeof buttons / sizeof Button, [=, &result](const auto i) {
			const auto action{ buttons[i].reactLeftMouseButtonDown(buttonEvent) };
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			result = action;
			isAnimating = true;
		});
		return result;
	}

	Pair<Action, Message> ButtonGroup::reactLeftMouseButtonUp(const SDL_MouseButtonEvent& buttonEvent)
	{
		auto resultAction{ Action::NONE };
		auto resultMessage{ Message{ } };
		loop(sizeof buttons / sizeof Button, [=, &resultAction, &resultMessage](const auto i) {
			const auto [action, message]{ buttons[i].reactLeftMouseButtonUp(buttonEvent) };
			if (message.head != Message::Head::EMPTY) resultMessage = message;
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			resultAction = action;
			isAnimating = true;
		});
		return Pair{ resultAction, resultMessage };
	}

	Action ButtonGroup::reactMouseLeaveWindow(const SDL_WindowEvent& windowEvent)
	{
		auto result{ Action::NONE };
		loop(sizeof buttons / sizeof Button, [=, &result](const auto i) {
			const auto action{ buttons[i].reactMouseLeaveWindow(windowEvent) };
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			result = action;
			isAnimating = true;
		});
		return result;
	}

	Pair<Action, Message> ButtonGroup::reactKeyDown(const SDL_KeyboardEvent& keyEvent)
	{
		auto resultAction{ Action::NONE };
		auto resultMessage{ Message{ } };
		loop(sizeof buttons / sizeof Button, [=, &resultAction, &resultMessage](const auto i) {
			const auto [action, message]{ buttons[i].reactKeyDown(keyEvent) };
			if (message.head != Message::Head::EMPTY) resultMessage = message;
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			resultAction = action;
			isAnimating = true;
		});
		return Pair{ resultAction, resultMessage };
	}

	Action ButtonGroup::reactKeyUp(const SDL_KeyboardEvent& keyEvent)
	{
		auto result{ Action::NONE };
		loop(sizeof buttons / sizeof Button, [=, &result](const auto i) {
			const auto action{ buttons[i].reactKeyUp(keyEvent) };
			if (action != Action::START_ANIMATION) return;
			++buttonAnimationsCount;
			if (isAnimating) return;
			result = action;
			isAnimating = true;
		});
		return result;
	}

	Action ButtonGroup::step(const unsigned int dt)
	{
		auto result{ Action::NONE };
		loop(sizeof buttons / sizeof Button, [=, &result](const auto i) {
			const auto action{ buttons[i].step(dt) };
			if (action != Action::STOP_ANIMATION) return;
			--buttonAnimationsCount;
			if (buttonAnimationsCount != 0u) return;
			result = action;
			isAnimating = false;
		});
		return result;
	}

	void ButtonGroup::render()
	{
		loop(sizeof buttons / sizeof Button, [=](const auto i) {
			buttons[i].render();
		});
	}
}

#endif