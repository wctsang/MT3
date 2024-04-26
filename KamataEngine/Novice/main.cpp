#include <Novice.h>
<<<<<<< Updated upstream

const char kWindowTitle[] = "学籍番号";
=======
#include <assert.h>
#include <cmath>

// 構造体宣言

struct Matrix4x4 {
	float m[4][4];
};

struct Vector3 {
	float x, y, z;
};

// 関数宣言

// 加算

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) { 
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 減算

Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) { 
	Matrix4x4 result; 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 積

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& matrix) {
	Matrix4x4 result{};
	float determinant = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] + matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
	                                      matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] - matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) -
	                    matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] + matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
	                                      matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] - matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) +
	                    matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] + matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
	                                      matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] - matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) -
	                    matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] + matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
	                                      matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] - matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]);

	if (determinant != 0) {
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] + matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
		                  matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] - matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) /
		                 determinant;

		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][1] * matrix.m[3][2] * matrix.m[0][3] + matrix.m[3][1] * matrix.m[0][2] * matrix.m[2][3] -
		                   matrix.m[3][1] * matrix.m[2][2] * matrix.m[0][3] - matrix.m[2][1] * matrix.m[0][2] * matrix.m[3][3] - matrix.m[0][1] * matrix.m[3][2] * matrix.m[2][3]) /
		                 determinant;

		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] + matrix.m[1][1] * matrix.m[3][2] * matrix.m[0][3] + matrix.m[3][1] * matrix.m[0][2] * matrix.m[1][3] -
		                  matrix.m[3][1] * matrix.m[1][2] * matrix.m[0][3] - matrix.m[1][1] * matrix.m[0][2] * matrix.m[3][3] - matrix.m[0][1] * matrix.m[3][2] * matrix.m[1][3]) /
		                 determinant;

		result.m[0][3] = -(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] + matrix.m[1][1] * matrix.m[2][2] * matrix.m[0][3] + matrix.m[2][1] * matrix.m[0][2] * matrix.m[1][3] -
		                   matrix.m[2][1] * matrix.m[1][2] * matrix.m[0][3] - matrix.m[1][1] * matrix.m[0][2] * matrix.m[2][3] - matrix.m[0][1] * matrix.m[2][2] * matrix.m[1][3]) /
		                 determinant;

		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] + matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
		                   matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] - matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] - matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) /
		                 determinant;

		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][2] * matrix.m[0][3] + matrix.m[3][0] * matrix.m[0][2] * matrix.m[2][3] -
		                  matrix.m[3][0] * matrix.m[2][2] * matrix.m[0][3] - matrix.m[2][0] * matrix.m[0][2] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[3][2] * matrix.m[2][3]) /
		                 determinant;

		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] + matrix.m[1][0] * matrix.m[3][2] * matrix.m[0][3] + matrix.m[3][0] * matrix.m[0][2] * matrix.m[1][3] -
		                   matrix.m[3][0] * matrix.m[1][2] * matrix.m[0][3] - matrix.m[1][0] * matrix.m[0][2] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[3][2] * matrix.m[1][3]) /
		                 determinant;

		result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] + matrix.m[1][0] * matrix.m[2][2] * matrix.m[0][3] + matrix.m[2][0] * matrix.m[0][2] * matrix.m[1][3] -
		                  matrix.m[2][0] * matrix.m[1][2] * matrix.m[0][3] - matrix.m[1][0] * matrix.m[0][2] * matrix.m[2][3] - matrix.m[0][0] * matrix.m[2][2] * matrix.m[1][3]) /
		                 determinant;

		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] + matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
		                  matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] - matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] - matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) /
		                 determinant;

		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][3] + matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][3] -
		                   matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][3] - matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][3]) /
		                 determinant;

		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] + matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][3] + matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][3] -
		                  matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][3] - matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][3] - matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][3]) /
		                 determinant;

		result.m[2][3] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] + matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][3] + matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][3] -
		                   matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][3] - matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][3] - matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][3]) /
		                 determinant;

		result.m[3][0] = -(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] + matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
		                   matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] - matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] - matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]) /
		                 determinant;

		result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] + matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][2] + matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][2] -
		                  matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][2] - matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][2] - matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][2]) /
		                 determinant;

		result.m[3][2] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] + matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][2] + matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][2] -
		                   matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][2] - matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][2] - matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][2]) /
		                 determinant;

		result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][2] + matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][2] -
		                  matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][2] - matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][2]) /
		                 determinant;
	}

	return result;
};


// 転置行列

Matrix4x4 Transpose(Matrix4x4 matrix) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[j][i] = matrix.m[i][j];
		}
	}
	return result;
}

//単位行列

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			} else {
				result.m[i][j] = 0.0f;
			}
		}
	}
	return result;
}

//平行移動行列

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) { 
	Matrix4x4 result = { 0 };
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}


//拡大縮小行列

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {0};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	return result;
}

//回転行列

Matrix4x4 MakeRotateXMatrix(float radian) { 
	Matrix4x4 result = { 0 }; 
	result.m[0][0] = 1;
	result.m[3][3] = 1;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -1 * std::sin(radian);
	result.m[2][2] = std::cos(radian);

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) { 
	Matrix4x4 result = { 0 }; 
	result.m[1][1] = 1;
	result.m[3][3] = 1;
	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -1 * std::sin(radian);
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{ 0 };
	result.m[2][2] = 1;
	result.m[3][3] = 1;
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -1 * std::sin(radian);
	result.m[1][1] = std::cos(radian);

	return result;
}

//座標変換

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) { 
	Vector3 result; 
	
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// 数値表示

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* name) {
	Novice::ScreenPrintf(x, y + kRowHeight, "%s", name);
	for (int row = 1; row <= 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f", matrix.m[row - 1][column]);
		}
	}
};

void VectorScreenPrintf(int x, int y, const Vector3& vector3, const char* name) {
	Novice::ScreenPrintf(x, y, "%6.02f  %6.02f  %6.02f  %s", vector3.x, vector3.y, vector3.z, name);
}

const char kWindowTitle[] = "GC2C_05_ソウ_イチョウ_MT3";
>>>>>>> Stashed changes

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

<<<<<<< Updated upstream
=======
	Vector3 rotate = {0.4f, 1.43f, -0.8f};
	

>>>>>>> Stashed changes
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

<<<<<<< Updated upstream
=======
		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

>>>>>>> Stashed changes
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

<<<<<<< Updated upstream
=======
		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");


>>>>>>> Stashed changes
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
