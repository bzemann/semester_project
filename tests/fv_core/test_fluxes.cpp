#include <doctest/doctest.h>

#include <pp_ader/fv_core/law_concepts.hpp>
#include <pp_ader/fv_core/flux_concept.hpp>

// include your concrete laws/fluxes (adjust path to your file)
#include <pp_ader/fv_core/conv_law_flux.hpp>

#include <vector>
#include <span>

using namespace PpADER::FvCore;

TEST_SUITE("fv_core::Flux") {

TEST_CASE("RusanovLin satisfies Flux concept") {
    static_assert(Flux<RusanovLin>);
    CHECK(true);
}

TEST_CASE("RusanovBur satisfies Flux concept") {
    static_assert(Flux<RusanovBur>);
    CHECK(true);
}

TEST_CASE("Linear advection: Rusanov equals upwind flux") {
    // For linear advection f(u)=c u, Rusanov with alpha=|c| becomes upwind:
    // if c>0: Fhat = c*u_minus
    // if c<0: Fhat = c*u_plus

    RusanovLin nf;
    LinAdvScalar law_pos{.c = 2.0};
    LinAdvScalar law_neg{.c = -2.0};

    const double uL = 3.0;
    const double uR = -1.0;

    const double Fpos = FluxAPI::flux(nf, law_pos, uL, uR);
    CHECK(doctest::Approx(Fpos).epsilon(1e-12) == law_pos.c * uL);

    const double Fneg = FluxAPI::flux(nf, law_neg, uL, uR);
    CHECK(doctest::Approx(Fneg).epsilon(1e-12) == law_neg.c * uR);
}

TEST_CASE("Burgers: consistency property F(U,U)=f(U)") {
    // Any consistent numerical flux should satisfy: Fhat(U,U) = f(U)

    RusanovBur nf;
    BurgerScalar law;

    const double u = 1.25;

    const double Fhat = FluxAPI::flux(nf, law, u, u);
    const double f    = LawAPI::phys_flux(law, u);

    CHECK(doctest::Approx(Fhat).epsilon(1e-12) == f);
}

TEST_CASE("compute_interface_fluxes fills all interfaces") {
    // Simple regression test for your helper function.
    // We'll create 6 interfaces (Nphys=5 -> N+1=6), with arbitrary UL/UR.

    RusanovLin nf;
    LinAdvScalar law{.c = 1.0};

    std::vector<double> u_minus{ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 };
    std::vector<double> u_plus { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

    std::vector<double> Fhat(u_minus.size(), 0.0);

    compute_interface_fluxes(law, nf,
        std::span<const double>(u_minus),
        std::span<const double>(u_plus),
        std::span<double>(Fhat)
    );

    // Since c=1>0 and Rusanov reduces to upwind: Fhat[i] = c*u_minus[i] = u_minus[i]
    for (std::size_t i = 0; i < Fhat.size(); ++i) {
        CHECK(doctest::Approx(Fhat[i]).epsilon(1e-12) == u_minus[i]);
    }
}

} // TEST_SUITE
