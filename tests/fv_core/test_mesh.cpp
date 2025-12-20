// tests/fv_core/test_mesh1d.cpp

#include <doctest/doctest.h>

#include <pp_ader/fv_core/concepts.hpp>
#include <pp_ader/fv_core/mesh.hpp>

using namespace PpADER::FvCore;

TEST_SUITE("fv_core::Mesh1d") {
  TEST_CASE("Mesh1d satisfies Mesh concept") {
    // Compile-time check (Rust-like trait satisfaction)
    static_assert(Mesh<Mesh1d>);
    CHECK(true);  // runtime anchor
  }

  TEST_CASE("Mesh1d::make sets sizes and ghost cells correctly") {
    auto m = Mesh1d::make(0.0,  // x_begin
                          1.0,  // x_end
                          4,    // physical points
                          2,    // ghost left
                          2     // ghost right
    );

    CHECK(MeshAPI::length(m) == 8);
    CHECK(MeshAPI::num_phys_points(m) == 4);
    CHECK(MeshAPI::ghost_left(m) == 2);
    CHECK(MeshAPI::ghost_right(m) == 2);
  }

  TEST_CASE("dx is computed from physical domain") {
    auto m = Mesh1d::make(0.0, 1.0, 4, 1, 1);

    // dx = (1 - 0) / 4
    CHECK(doctest::Approx(MeshAPI::dx(m)).epsilon(1e-12) == 0.25);
  }

  TEST_CASE("Cell centers are correctly placed (with ghost cells)") {
    auto m = Mesh1d::make(0.0, 1.0, 4, 2, 2);

    // Physical indices are [2..5]
    CHECK(doctest::Approx(MeshAPI::cell_center(m, 2)).epsilon(1e-12) == 0.125);
    CHECK(doctest::Approx(MeshAPI::cell_center(m, 3)).epsilon(1e-12) == 0.375);
    CHECK(doctest::Approx(MeshAPI::cell_center(m, 4)).epsilon(1e-12) == 0.625);
    CHECK(doctest::Approx(MeshAPI::cell_center(m, 5)).epsilon(1e-12) == 0.875);
  }

  TEST_CASE("Ghost cells lie outside the physical domain") {
    auto m = Mesh1d::make(0.0, 1.0, 4, 2, 2);

    // Left ghost cells should be < 0
    CHECK(MeshAPI::cell_center(m, 0) < 0.0);
    CHECK(MeshAPI::cell_center(m, 1) < 0.0);

    // Right ghost cells should be > 1
    CHECK(MeshAPI::cell_center(m, 6) > 1.0);
    CHECK(MeshAPI::cell_center(m, 7) > 1.0);
  }

}  // TEST_SUITE
