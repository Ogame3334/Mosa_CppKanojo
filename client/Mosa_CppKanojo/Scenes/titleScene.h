#pragma once
# include <Siv3D.hpp>

using App = SceneManager<String>;

// タイトルシーン
// 挙動 : 左クリックでゲームがスタート
// 　　　ESCキーで終了

class Title : public App::Scene
{
public:

	// コンストラクタ
	Title(const InitData& init)
		: IScene{ init }{}

	void update() override
	{
		// 左クリックで
		if (MouseL.down())
		{
			// 曲選択シーンに遷移
			changeScene(U"Choice");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"My Game").drawAt(750, 100);
		FontAsset(U"TitleFont")(U">PRESS ANY BUTTON<").drawAt(750, 600);

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
	}
};
