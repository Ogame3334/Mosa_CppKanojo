#pragma once
#include <Siv3D.hpp>

namespace ogm {
	template<typename T>
	concept ClickableRange = requires (T & t) {
		t.mouseOver();
		t.draw();
		t.drawFrame();
	};
	template<ClickableRange CR>
	class Button {
	private:
		Font font{ 16, Typeface::CJK_Regular_JP };
		CR clickableRange;
		bool canClick = true;
		CursorStyle onCursorStyle = CursorStyle::Hand;
		String buttonTitle = U"Button";
		Color defaultBackColor = Palette::White;
		Color mouseOverBackColor = Palette::Lightgray;
		Color pressedBackColor = Palette::Gray;
		Color defaultOutlineColor = Palette::Black;
		Color mouseOverOutlineColor = Palette::Black;
		Color pressedOutlineColor = Palette::Black;
		Point outlineWidth{0, 1};
	public:
		Button() {
			this->clickableRange = CR();
		}
		Button(CR range, String title) {
			this->clickableRange = range;
			this->buttonTitle = title;
		}

		void setFont(int fontsize, Typeface typeface, FontStyle fontstyle = FontStyle::Default) {
			this->font = Font(fontsize, typeface, fontstyle);
		}
		void setClickableRange(CR range) { this->clickableRange = range; }
		void setCanClick(bool can) { this->canClick = can; }
		void setOnCursorStyle(CursorStyle style) { this->onCursorStyle = style; }
		void setButtonTitle(String title) { this->buttonTitle = title; }
		void setDefaultBackColor(Color color) { this->defaultBackColor = color; }
		void setMouseOverBackColor(Color color) { this->mouseOverBackColor = color; }
		void setPressedBackColor(Color color) { this->pressedBackColor = color; }
		void setBackColors(Color defaultColor, Color mouseOverColor, Color pressedColor) {
			this->defaultBackColor = defaultColor;
			this->mouseOverBackColor = mouseOverColor;
			this->pressedBackColor = pressedColor;
		}
		void setDefaultOutlineColor(Color color) { this->defaultOutlineColor = color; }
		void setMouseOverOutlineColor(Color color) { this->mouseOverOutlineColor = color; }
		void setPressedOutlineColor(Color color) { this->pressedOutlineColor = color; }
		void setOutlineColors(Color defaultColor, Color mouseOverColor, Color pressedColor) {
			this->defaultOutlineColor = defaultColor;
			this->mouseOverOutlineColor = mouseOverColor;
			this->pressedOutlineColor = pressedColor;
		}
		void setOutlineColorsToTransparent() {
			this->setOutlineColors(Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0));
		}
		void setOutlineWidth(int inner, int outer) { this->outlineWidth = Point(inner, outer); }

		bool update() {
			bool out = false;
			Color backColor = this->defaultBackColor;
			Color outlineColor = this->defaultOutlineColor;
			if (this->canClick and this->clickableRange.mouseOver()) {
				backColor = this->mouseOverBackColor;
				outlineColor = this->mouseOverOutlineColor;
				Cursor::RequestStyle(this->onCursorStyle);
				if (MouseL.pressed()) {
					backColor = this->pressedBackColor;
					outlineColor = this->pressedOutlineColor;
				}
				if (MouseL.up()) {
					out = true;
				}
			}

			this->clickableRange.draw(backColor);
			this->clickableRange.drawFrame(this->outlineWidth.x, this->outlineWidth.y, outlineColor);
			font(this->buttonTitle).drawAt(this->clickableRange.center(), Palette::Black);

			return out;
		}
	};

	template<>
	class Button<Polygon> {
	private:
		Font font{ 16, Typeface::CJK_Regular_JP };
		Polygon clickableRange;
		bool canClick = true;
		CursorStyle onCursorStyle = CursorStyle::Hand;
		String buttonTitle = U"Button";
		Color defaultBackColor = Palette::White;
		Color mouseOverBackColor = Palette::Lightgray;
		Color pressedBackColor = Palette::Gray;
		Color defaultOutlineColor = Palette::Black;
		Color mouseOverOutlineColor = Palette::Black;
		Color pressedOutlineColor = Palette::Black;
		Point outlineWidth{ 0, 1 };
	public:
		Button() {
			this->clickableRange = Polygon();
		}
		Button(Polygon range, String title) {
			this->clickableRange = range;
			this->buttonTitle = title;
		}

		void setFont(int fontsize, Typeface typeface, FontStyle fontstyle = FontStyle::Default) {
			this->font = Font(fontsize, typeface, fontstyle);
		}
		void setClickableRange(Polygon range) { this->clickableRange = range; }
		void setCanClick(bool can) { this->canClick = can; }
		void setOnCursorStyle(CursorStyle style) { this->onCursorStyle = style; }
		void setButtonTitle(String title) { this->buttonTitle = title; }
		void setDefaultBackColor(Color color) { this->defaultBackColor = color; }
		void setMouseOverBackColor(Color color) { this->mouseOverBackColor = color; }
		void setPressedBackColor(Color color) { this->pressedBackColor = color; }
		void setBackColors(Color defaultColor, Color mouseOverColor, Color pressedColor) {
			this->defaultBackColor = defaultColor;
			this->mouseOverBackColor = mouseOverColor;
			this->pressedBackColor = pressedColor;
		}
		void setDefaultOutlineColor(Color color) { this->defaultOutlineColor = color; }
		void setMouseOverOutlineColor(Color color) { this->mouseOverOutlineColor = color; }
		void setPressedOutlineColor(Color color) { this->pressedOutlineColor = color; }
		void setOutlineColors(Color defaultColor, Color mouseOverColor, Color pressedColor) {
			this->defaultOutlineColor = defaultColor;
			this->mouseOverOutlineColor = mouseOverColor;
			this->pressedOutlineColor = pressedColor;
		}
		void setOutlineWidth(int inner, int outer) { this->outlineWidth = Point(inner, outer); }

		bool update() {
			bool out = false;
			Color backColor = this->defaultBackColor;
			Color outlineColor = this->defaultOutlineColor;
			if (this->canClick and this->clickableRange.mouseOver()) {
				backColor = this->mouseOverBackColor;
				outlineColor = this->mouseOverOutlineColor;
				Cursor::RequestStyle(this->onCursorStyle);
				if (MouseL.pressed()) {
					backColor = this->pressedBackColor;
					outlineColor = this->pressedOutlineColor;
				}
				if (MouseL.up()) {
					out = true;
				}
			}

			this->clickableRange.draw(backColor);
			this->clickableRange.drawFrame(this->outlineWidth.x + this->outlineWidth.y, outlineColor);
			font(this->buttonTitle).drawAt(this->clickableRange.centroid(), Palette::Black);

			return out;
		}
	};
}
