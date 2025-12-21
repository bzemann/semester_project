#include <doctest/doctest.h>

#include <Eigen/Core>

#include <pp_ader/fv_core/field_concept.hpp>
#include <pp_ader/fv_core/fields.hpp>

#include <pp_ader/fv_core/bc_concept.hpp>
#include <pp_ader/fv_core/boundary_condition.hpp>

#include <pp_ader/fv_core/mesh1d.hpp> // adjust include if your mesh header is named differently
#include <pp_ader/fv_core/mesh_concept.hpp>

#include <vector>

using namespace PpADER::FvCore;

TEST_SUITE("fv_core::FieldLike + BC") {

  TEST_CASE("std::vector<double> satisfies FieldLike") {
    static_assert(FieldLike<std::vector<double>>);
    CHECK(true);
  }

  TEST_CASE("std::vector<Eigen::VectorXd> satisfies FieldLike") {
    static_assert(FieldLike<std::vector<Eigen::VectorXd>>);
    CHECK(true);
  }

  TEST_CASE(
      "PeriodicBC satisfies BoundaryCondition for Mesh1d + vector<double>") {
    static_assert(Mesh<Mesh1d>);
    static_assert(BoundaryCondition<PeriodicBC, Mesh1d, std::vector<double>>);
    CHECK(true);
  }

  TEST_CASE("PeriodicBC fills ghost cells correctly for scalar field") {
    // N=5 physical, K=1 left ghost, L=1 right ghost => total = 7
    auto mesh = Mesh1d::make(0.0, 1.0, 5, 1, 1);

    std::vector<double> u(MeshAPI::length(mesh), 0.0);

    // Physical indices are [K .. K+N-1] = [1..5]
    u[1] = 10.0;
    u[2] = 11.0;
    u[3] = 12.0;
    u[4] = 13.0;
    u[5] = 14.0;

    PeriodicBC bc;
    BcAPI::apply(bc, mesh, u);

    // Expected periodic ghosts:
    // left ghost u[0] = last physical u[5] = 14
    // right ghost u[6] = first physical u[1] = 10
    CHECK(u[0] == doctest::Approx(14.0));
    CHECK(u[6] == doctest::Approx(10.0));
  }

  TEST_CASE("PeriodicBC works for vector-valued states (Eigen::VectorXd)") {
    auto mesh = Mesh1d::make(0.0, 1.0, 3, 1, 1); // total = 5

    std::vector<Eigen::VectorXd> U(MeshAPI::length(mesh));
    for (auto &v : U)
      v = Eigen::VectorXd::Zero(2);

    // physical indices [1..3]
    U[1] << 1.0, 2.0;
    U[2] << 3.0, 4.0;
    U[3] << 5.0, 6.0;

    PeriodicBC bc;
    BcAPI::apply(bc, mesh, U);

    // left ghost [0] should copy last physical [3]
    CHECK(U[0].isApprox(U[3], 1e-12));

    // right ghost [4] should copy first physical [1]
    CHECK(U[4].isApprox(U[1], 1e-12));
  }

} // TEST_SUITE
