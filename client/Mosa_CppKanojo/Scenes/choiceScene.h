#pragma once
# include <Siv3D.hpp>

using App = SceneManager<String>;

// 曲選択シーン
// 挙動 : 左右キーで曲を選択、Enterか左クリックで決定
// 　　　ESCキーでタイトル画面に戻る
class Choice : public App::Scene {
public:

	// コンストラクタ
	Choice(const InitData& init)
		: IScene{ init } {}

    void update() override
	{
		// 左クリックかenterで
		if (MouseL.down() || KeyEnter.pressed())
		{
			// 実際のゲームシーンに遷移
			changeScene(U"Game");
		}
		// ESCキーでタイトル画面に戻る
		if (KeyEscape.pressed()) {
			// タイトル画面に遷移
			changeScene(U"title");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"Select a Music").drawAt(750, 100);
		FontAsset(U"TitleFont")(U">PRESS ANY BUTTON<").drawAt(750, 600);

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
	}
};
