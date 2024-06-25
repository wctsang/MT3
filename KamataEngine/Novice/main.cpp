#include <Novice.h>
#include "Functions.h"
#include <imgui.h>

struct Plane {
	Vector3 normal; // 法線
	float distance; // 距離
};

bool IsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	if (t < 0.0f || t > 1.0f) {
		return false;
	} else {
		return true;
	}
}

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendicular[4];
	perpendicular[0] = Normalize(Perpendicular(plane.normal));
	perpendicular[1] = {-perpendicular[0].x, -perpendicular[0].y, -perpendicular[0].z};
	perpendicular[2] = Cross(plane.normal, perpendicular[0]);
	perpendicular[3] = {-perpendicular[2].x, -perpendicular[2].y, -perpendicular[2].z};

	Vector3 points[4];
	for (uint32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendicular[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);
}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void VectorScreenPrintf(int x, int y, const Vector3& vector3, const char* name) { 
	Novice::ScreenPrintf(x, y, "%6.02f  %6.02f  %6.02f  %s", vector3.x, vector3.y, vector3.z, name);
}

const char kWindowTitle[] = "GC2C_05_ソウ_イチョウ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Vector3 rotate{0, 0, 0};
	Vector3 translate{0, 0, 0};
	Vector3 cameraTranslate{0, 1.9f, -6.49f};
	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};

	Segment segment{
	    {-0.5f, 0,    -0.5f},
        {1.0f,  1.0f, 2.0f }
    };
	Plane plane{
	    {0.0f, 1.0f, 0.0f},
        1.0f
    };

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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

		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewPortMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

		Vector3 start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewPortMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewPortMatrix);

		ImGui::Begin("Window");
		ImGui::DragFloat3("segment Position", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment radius", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("Plane Normal", &plane.normal.x, 0.01f);
		ImGui::DragFloat("Plane Distance", &plane.distance, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		if (IsCollision(segment, plane)) {
			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), RED);
		} else {
			Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);
		}
		DrawPlane(plane, worldViewProjectionMatrix, viewPortMatrix, WHITE);

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
