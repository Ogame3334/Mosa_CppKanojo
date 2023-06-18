#pragma once
# include <Siv3D.hpp>

// ユーザデータ用クラスを実装
class UserData {
private:

	JSON userData;	// ユーザデータを格納用変数

public:

	UserData() {	// コンストラクタ
		this->userData = JSON::Load(U"../UserData/userdata.json");	// ユーザデータの読み込み
		if (not this->userData) // もし読み込みに失敗したら
		{
			throw Error{ U"Failed to load `config.json`" };
		}
	}

	int32 getUserOptionData(String lavel) {	// 指定されたラベルのユーザデータを返す関数
		return this->userData[U"options"][lavel].get<int32>();
	}
	void setUserOptionData(String lavel, int32 value) {	// 指定されたラベルのユーザデータを保存する関数
		userData[U"options"][lavel] = value;
		userData.save(U"../UserData/userdata.json");	// ユーザデータの保存
	}
	String getUserData(String lavel) {
		return this->userData[U"gamedata"][lavel].getString();
	}
	void setUserData(String lavel, String value) {
		userData[U"gamedata"][lavel] = value;
		userData.save(U"../UserData/userdata.json");
	}
};
