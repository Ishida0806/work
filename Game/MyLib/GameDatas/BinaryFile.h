/// <summary>
/// バイナリファイルを扱うクラス
/// </summary>
#pragma once

class BinaryFile
{
public:
	// アクセサ
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }

private:

	// データ
	std::unique_ptr<char[]> m_data;

	// サイズ
	unsigned int m_size;

public:

	// ファイル名を指定してロード
	static BinaryFile LoadFile(const wchar_t* fileName);

	/// <summary>
	/// デファクトコンストラクタ
	/// </summary>
	BinaryFile();


	/// <summary>
	/// ムーブコンストラクタ
	/// </summary>
	/// <param name="in"></param>
	BinaryFile(BinaryFile&& in);
};
