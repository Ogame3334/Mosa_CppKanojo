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
		Color nowBackColor = Palette::White;
		Color defaultBackColor = Palette::White;
		Color mouseOverBackColor = Palette::Lightgray;
		Color pressedBackColor = Palette::Gray;
		Color nowOutlineColor = Palette::Black;
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
			this->nowBackColor = this->defaultBackColor;
			this->nowOutlineColor = this->defaultOutlineColor;
			if (this->canClick and this->clickableRange.mouseOver()) {
				this->nowBackColor = this->mouseOverBackColor;
				this->nowOutlineColor = this->mouseOverOutlineColor;
				Cursor::RequestStyle(this->onCursorStyle);
				if (MouseL.pressed()) {
					this->nowBackColor = this->pressedBackColor;
					this->nowOutlineColor = this->pressedOutlineColor;
				}
				if (MouseL.up()) {
					out = true;
				}
			}

			return out;
		}

		void draw() const {
			this->clickableRange.draw(this->nowBackColor);
			this->clickableRange.drawFrame(this->outlineWidth.x, this->outlineWidth.y, this->nowOutlineColor);
			font(this->buttonTitle).drawAt(this->clickableRange.center(), Palette::Black);
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
		Color nowBackColor = Palette::White;
		Color defaultBackColor = Palette::White;
		Color mouseOverBackColor = Palette::Lightgray;
		Color pressedBackColor = Palette::Gray;
		Color nowOutlineColor = Palette::Black;
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
		void setOutlineColorsToTransparent() {
			this->setOutlineColors(Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0));
		}
		void setOutlineWidth(int inner, int outer) { this->outlineWidth = Point(inner, outer); }

		bool update() {
			bool out = false;
			this->nowBackColor = this->defaultBackColor;
			this->nowOutlineColor = this->defaultOutlineColor;
			if (this->canClick and this->clickableRange.mouseOver()) {
				this->nowBackColor = this->mouseOverBackColor;
				this->nowOutlineColor = this->mouseOverOutlineColor;
				Cursor::RequestStyle(this->onCursorStyle);
				if (MouseL.pressed()) {
					this->nowBackColor = this->pressedBackColor;
					this->nowOutlineColor = this->pressedOutlineColor;
				}
				if (MouseL.up()) {
					out = true;
				}
			}

			return out;
		}

		void draw() const {
			this->clickableRange.draw(this->nowBackColor);
			this->clickableRange.drawFrame(this->outlineWidth.x + this->outlineWidth.y, this->nowOutlineColor);
			font(this->buttonTitle).drawAt(this->clickableRange.centroid(), Palette::Black);
		}
	};

	template<>
	class Button<Triangle> {
	private:
		Font font{ 16, Typeface::CJK_Regular_JP };
		Triangle clickableRange;
		bool canClick = true;
		CursorStyle onCursorStyle = CursorStyle::Hand;
		String buttonTitle = U"Button";
		Color nowBackColor = Palette::White;
		Color defaultBackColor = Palette::White;
		Color mouseOverBackColor = Palette::Lightgray;
		Color pressedBackColor = Palette::Gray;
		Color nowOutlineColor = Palette::Black;
		Color defaultOutlineColor = Palette::Black;
		Color mouseOverOutlineColor = Palette::Black;
		Color pressedOutlineColor = Palette::Black;
		Point outlineWidth{ 0, 1 };
	public:
		Button() {
			this->clickableRange = Triangle();
		}
		Button(Triangle range, String title) {
			this->clickableRange = range;
			this->buttonTitle = title;
		}

		void setFont(int fontsize, Typeface typeface, FontStyle fontstyle = FontStyle::Default) {
			this->font = Font(fontsize, typeface, fontstyle);
		}
		void setClickableRange(Triangle range) { this->clickableRange = range; }
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
			this->nowBackColor = this->defaultBackColor;
			this->nowOutlineColor = this->defaultOutlineColor;
			if (this->canClick and this->clickableRange.mouseOver()) {
				this->nowBackColor = this->mouseOverBackColor;
				this->nowOutlineColor = this->mouseOverOutlineColor;
				Cursor::RequestStyle(this->onCursorStyle);
				if (MouseL.pressed()) {
					this->nowBackColor = this->pressedBackColor;
					this->nowOutlineColor = this->pressedOutlineColor;
				}
				if (MouseL.up()) {
					out = true;
				}
			}

			return out;
		}

		void draw() const {
			this->clickableRange.draw(this->nowBackColor);
			this->clickableRange.drawFrame(this->outlineWidth.x + this->outlineWidth.y, this->nowOutlineColor);
			font(this->buttonTitle).drawAt(this->clickableRange.centroid(), Palette::Black);
		}
	};
}
