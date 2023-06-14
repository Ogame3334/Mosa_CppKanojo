# include <Siv3D.hpp>
#include"ResultScene.h"
#include"GameData.h"

using App = SceneManager<String, GameData>;

// タイトルシーン
class Title : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	Title(const InitData& init)
		: IScene{ init }
	{

	}

	// 更新関数（オプション）
	void update() override
	{
		if (MouseL.down())
		{
			// ゲームシーンに遷移
			changeScene(U"Result");
		}
		if (MouseR.down()) {
			getData().score += 10;
		}
	}

	// 描画関数（オプション）
	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);
		FontAsset(U"TitleFont")(U"Score {}"_fmt(getData().score)).drawAt(400, 200);

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
	}
};

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

	// シーンマネージャーを作成
	App manager;

	// タイトルシーン（名前は "Title"）を登録
	manager.add<Title>(U"Title");
	manager.add<ResultScene>(U"Result");

	while (System::Update())
	{
		// 現在のシーンを実行
		// シーンに実装した .update() と .draw() が実行される
		if (not manager.update())
		{
			break;
		}
	}
}
