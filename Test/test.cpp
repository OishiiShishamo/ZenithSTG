#include "gtest/gtest.h"
#include <chrono>
#include <random>
#include "color.h"

using namespace zenithstg;

//-----------------------------------------
// 正常動作テスト
//-----------------------------------------
TEST(ColorTest, BasicGetterSetter) {
    Color c(255, 128, 0, 64);

    EXPECT_NEAR(c.GetR(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetG(), 128.0f, 1e-3);
    EXPECT_NEAR(c.GetB(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetA(), 64.0f, 1e-3);

    c.Set(0, 255, 0);
    EXPECT_NEAR(c.GetR(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetG(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetB(), 0.0f, 1e-3);
}

TEST(ColorTest, OperatorAddSub) {
    Color c1(255, 0, 0);
    Color c2(0, 255, 0);
    Color c3 = c1 + c2;

    EXPECT_NEAR(c3.GetR(), 255.0f, 1e-3);
    EXPECT_NEAR(c3.GetG(), 255.0f, 1e-3);
    EXPECT_NEAR(c3.GetB(), 0.0f, 1e-3);

    c3 -= Color(128, 128, 0);
    EXPECT_NEAR(c3.GetR(), 127.0f, 1e-3);
    EXPECT_NEAR(c3.GetG(), 127.0f, 1e-3);
    EXPECT_NEAR(c3.GetB(), 0.0f, 1e-3);
}

TEST(ColorTest, SaturationClamp) {
    Color c(9999, -100, 500);
    EXPECT_NEAR(c.GetR(), 255.0f, 1e-3);
    EXPECT_NEAR(c.GetG(), 0.0f, 1e-3);
    EXPECT_NEAR(c.GetB(), 255.0f, 1e-3);
}

TEST(ColorTest, MultiplyScalar) {
    Color c(100, 50, 25);
    c *= 2.0f;
    EXPECT_NEAR(c.GetR(), 200.0f, 1e-3);
    EXPECT_NEAR(c.GetG(), 100.0f, 1e-3);
    EXPECT_NEAR(c.GetB(), 50.0f, 1e-3);
}

//-----------------------------------------
// パフォーマンス測定（安定版）
//-----------------------------------------
TEST(ColorPerfTest, SSEvsScalar) {
    constexpr int N = 100'000'000;  // 大きめループでタイマー精度を確保
    std::vector<Color> colors;
    colors.reserve(N);
    std::mt19937 rng(123);
    std::uniform_real_distribution<float> dist(0, 255);

    for (int i = 0; i < N; ++i)
        colors.emplace_back(dist(rng), dist(rng), dist(rng));

    // SSE 版
    Color acc(0, 0, 0);
    auto start_sse = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i)
        acc += colors[i] * 0.5f;
    auto end_sse = std::chrono::high_resolution_clock::now();
    double sse_ms = std::chrono::duration<double, std::milli>(end_sse - start_sse).count();

    // スカラ版
    auto start_scalar = std::chrono::high_resolution_clock::now();
    float r = 0, g = 0, b = 0, a = 0;
    for (int i = 0; i < N; ++i) {
        r += colors[i].GetNR() * 0.5f;
        g += colors[i].GetNG() * 0.5f;
        b += colors[i].GetNB() * 0.5f;
        a += colors[i].GetNA() * 0.5f;
    }
    auto end_scalar = std::chrono::high_resolution_clock::now();
    double scalar_ms = std::chrono::duration<double, std::milli>(end_scalar - start_scalar).count();

    // ループ削除防止：acc の結果を使用
    volatile float prevent_opt = acc.GetR() + acc.GetG() + acc.GetB() + acc.GetA() + r + g + b + a;
    (void)prevent_opt;

    std::cout << "[PERF] SSE   : " << sse_ms << " ms\n";
    std::cout << "[PERF] Scalar: " << scalar_ms << " ms\n";

    EXPECT_GT(sse_ms, 0.0);
    EXPECT_GT(scalar_ms, 0.0);
    EXPECT_LE(sse_ms, scalar_ms * 1.3);
}