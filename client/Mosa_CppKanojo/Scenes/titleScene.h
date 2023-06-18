#pragma once
# include <Siv3D.hpp>
# include "../readUserData.h"
#include "../Button.hpp"

// タイトルシーン
// 挙動 : 左クリックでゲームがスタート
// 　　　ESCキーで終了

class Title : public App::Scene
{
private:

	const Image titlebg_raw{ U"assets/Textures/BackGround/titleBg.png" };
	const Texture titleBg{ {titlebg_raw}};
	UserData userData;
	String userName;
	bool isSetUserName = false;
	TextEditState setNameBox;
	ogm::Button<RoundRect> decideButton{ RoundRect(700, 500, 100, 50 ,5), U"決定" };
public:

	// コンストラクタ
	Title(const InitData& init)
		: IScene{ init }{
		this->userName = this->userData.getUserData(U"username");	// ユーザネームを取得
		this->isSetUserName = false;
		// ボタンの色設定など
		this->decideButton.setFont(20, Typeface::Regular, FontStyle::Default);
		this->decideButton.setBackColors(ColorF{ 1.0, 0.714, 0.757, 1.0 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
		this->decideButton.setOutlineWidth(3, 0);
		this->decideButton.setOutlineColors(ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.078, 0.576 ,1 }, ColorF{ 1, 0.412, 0.706 , 1 });
	}

	void update() override
	{
		// ESCキーが押されたらゲームを終了
		if (KeyEscape.pressed()) {
			System::Exit();
		}
		if (this->isSetUserName == true) {	// 名前入力モード
			SimpleGUI::TextBox(this->setNameBox, Vec2{ 650, 400 }, 200, 10);	// 名前入力用のテキストボックスを表示
			if (decideButton.update() && setNameBox.text != U"") {	// 決定ボタンが押されたなら
				userData.setUserData(U"username", setNameBox.text);
				changeScene(U"Choice");
			}
		}
		// 左クリックもしくは任意のキー入力で
		if (MouseL.down() || Keyboard::GetAllInputs())
		{
			if (this->userName == U"") {	// ユーザネームが未設定であれば設定する
				this->isSetUserName = true;
			}
			else {
				 // 曲選択シーンに遷移
				changeScene(U"Choice");
			}
		}
	}

	void draw() const override
	{
		if (this->isSetUserName == true) {
			FontAsset(U"TitleFont")(U"ユーザ名を設定").drawAt(750, 100);
			this->decideButton.draw();
		}
		else {
			this->titleBg.draw();
		}
	}
};
