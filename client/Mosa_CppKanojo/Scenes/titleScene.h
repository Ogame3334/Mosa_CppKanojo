#pragma once
# include <Siv3D.hpp>

// タイトルシーン
// 挙動 : 左クリックでゲームがスタート
// 　　　ESCキーで終了

class Title : public App::Scene
{
private:

	const Image titlebg_raw{ U"../Textures/BackGround/titleBg.png" };
	const Texture titleBg{ {titlebg_raw.scaled(0.8)}};
public:

	// コンストラクタ
	Title(const InitData& init)
		: IScene{ init }{}

	void update() override
	{
		// ESCキーが押されたらゲームを終了
		if (KeyEscape.pressed()) {
			System::Exit();
		}
		// 左クリックもしくは任意のキー入力で
		if (MouseL.down() || Keyboard::GetAllInputs())
		{
			// 曲選択シーンに遷移
			changeScene(U"Choice");
		}
	}

	void draw() const override
	{
		this->titleBg.draw();
	}
};
