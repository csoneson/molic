// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "molic_types.h"
#include <Rcpp.h>

using namespace Rcpp;

// dfs
VS dfs(Rcpp::List adj, std::string root);
RcppExport SEXP _molic_dfs(SEXP adjSEXP, SEXP rootSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type adj(adjSEXP);
    Rcpp::traits::input_parameter< std::string >::type root(rootSEXP);
    rcpp_result_gen = Rcpp::wrap(dfs(adj, root));
    return rcpp_result_gen;
END_RCPP
}
// count_unique
RIV count_unique(VS x);
RcppExport SEXP _molic_count_unique(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(count_unique(x));
    return rcpp_result_gen;
END_RCPP
}
// matpr
VS matpr(Rcpp::CharacterMatrix A);
RcppExport SEXP _molic_matpr(SEXP ASEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::CharacterMatrix >::type A(ASEXP);
    rcpp_result_gen = Rcpp::wrap(matpr(A));
    return rcpp_result_gen;
END_RCPP
}
// n_a
RIV n_a(RCM& A);
RcppExport SEXP _molic_n_a(SEXP ASEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RCM& >::type A(ASEXP);
    rcpp_result_gen = Rcpp::wrap(n_a(A));
    return rcpp_result_gen;
END_RCPP
}
// na_ya
int na_ya(RIV& na, std::string ya);
RcppExport SEXP _molic_na_ya(SEXP naSEXP, SEXP yaSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RIV& >::type na(naSEXP);
    Rcpp::traits::input_parameter< std::string >::type ya(yaSEXP);
    rcpp_result_gen = Rcpp::wrap(na_ya(na, ya));
    return rcpp_result_gen;
END_RCPP
}
// n_b
RIV n_b(RIV& na, RIV& b);
RcppExport SEXP _molic_n_b(SEXP naSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RIV& >::type na(naSEXP);
    Rcpp::traits::input_parameter< RIV& >::type b(bSEXP);
    rcpp_result_gen = Rcpp::wrap(n_b(na, b));
    return rcpp_result_gen;
END_RCPP
}
// subtract_one
VD subtract_one(VD x);
RcppExport SEXP _molic_subtract_one(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VD >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(subtract_one(x));
    return rcpp_result_gen;
END_RCPP
}
// Gx_
VD Gx_(VD x);
RcppExport SEXP _molic_Gx_(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VD >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(Gx_(x));
    return rcpp_result_gen;
END_RCPP
}
// Hx_
VD Hx_(VD x);
RcppExport SEXP _molic_Hx_(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VD >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(Hx_(x));
    return rcpp_result_gen;
END_RCPP
}
// subM
RCM subM(RCM& A, RCV& x);
RcppExport SEXP _molic_subM(SEXP ASEXP, SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RCM& >::type A(ASEXP);
    Rcpp::traits::input_parameter< RCV& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(subM(A, x));
    return rcpp_result_gen;
END_RCPP
}
// a_marginals
RL a_marginals(RCM A, RL& am);
RcppExport SEXP _molic_a_marginals(SEXP ASEXP, SEXP amSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RCM >::type A(ASEXP);
    Rcpp::traits::input_parameter< RL& >::type am(amSEXP);
    rcpp_result_gen = Rcpp::wrap(a_marginals(A, am));
    return rcpp_result_gen;
END_RCPP
}
// TY
double TY(RCV y, RL& C_marginals, RL& S_marginals);
RcppExport SEXP _molic_TY(SEXP ySEXP, SEXP C_marginalsSEXP, SEXP S_marginalsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< RCV >::type y(ySEXP);
    Rcpp::traits::input_parameter< RL& >::type C_marginals(C_marginalsSEXP);
    Rcpp::traits::input_parameter< RL& >::type S_marginals(S_marginalsSEXP);
    rcpp_result_gen = Rcpp::wrap(TY(y, C_marginals, S_marginals));
    return rcpp_result_gen;
END_RCPP
}
// mcs
Rcpp::List mcs(Rcpp::List& adj);
RcppExport SEXP _molic_mcs(SEXP adjSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type adj(adjSEXP);
    rcpp_result_gen = Rcpp::wrap(mcs(adj));
    return rcpp_result_gen;
END_RCPP
}
// perfect_cliques
VVS perfect_cliques(VVS& x);
RcppExport SEXP _molic_perfect_cliques(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VVS& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(perfect_cliques(x));
    return rcpp_result_gen;
END_RCPP
}
// perfect_separators
Rcpp::List perfect_separators(VVS& x);
RcppExport SEXP _molic_perfect_separators(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VVS& >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(perfect_separators(x));
    return rcpp_result_gen;
END_RCPP
}
// rip
Rcpp::List rip(Rcpp::List& adj);
RcppExport SEXP _molic_rip(SEXP adjSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type adj(adjSEXP);
    rcpp_result_gen = Rcpp::wrap(rip(adj));
    return rcpp_result_gen;
END_RCPP
}
// mcs2
Rcpp::List mcs2(Rcpp::List& adj);
RcppExport SEXP _molic_mcs2(SEXP adjSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type adj(adjSEXP);
    rcpp_result_gen = Rcpp::wrap(mcs2(adj));
    return rcpp_result_gen;
END_RCPP
}
// rip2
Rcpp::List rip2(Rcpp::List& adj);
RcppExport SEXP _molic_rip2(SEXP adjSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type adj(adjSEXP);
    rcpp_result_gen = Rcpp::wrap(rip2(adj));
    return rcpp_result_gen;
END_RCPP
}
// set_intersect
VS set_intersect(VS& v1, VS& v2);
RcppExport SEXP _molic_set_intersect(SEXP v1SEXP, SEXP v2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS& >::type v1(v1SEXP);
    Rcpp::traits::input_parameter< VS& >::type v2(v2SEXP);
    rcpp_result_gen = Rcpp::wrap(set_intersect(v1, v2));
    return rcpp_result_gen;
END_RCPP
}
// set_union
VS set_union(VS& v1, VS& v2);
RcppExport SEXP _molic_set_union(SEXP v1SEXP, SEXP v2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS& >::type v1(v1SEXP);
    Rcpp::traits::input_parameter< VS& >::type v2(v2SEXP);
    rcpp_result_gen = Rcpp::wrap(set_union(v1, v2));
    return rcpp_result_gen;
END_RCPP
}
// set_diff
VS set_diff(VS& v1, VS& v2);
RcppExport SEXP _molic_set_diff(SEXP v1SEXP, SEXP v2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS& >::type v1(v1SEXP);
    Rcpp::traits::input_parameter< VS& >::type v2(v2SEXP);
    rcpp_result_gen = Rcpp::wrap(set_diff(v1, v2));
    return rcpp_result_gen;
END_RCPP
}
// set_eq
bool set_eq(VS& v1, VS& v2);
RcppExport SEXP _molic_set_eq(SEXP v1SEXP, SEXP v2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS& >::type v1(v1SEXP);
    Rcpp::traits::input_parameter< VS& >::type v2(v2SEXP);
    rcpp_result_gen = Rcpp::wrap(set_eq(v1, v2));
    return rcpp_result_gen;
END_RCPP
}
// set_in
bool set_in(std::string& a, VS& b);
RcppExport SEXP _molic_set_in(SEXP aSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string& >::type a(aSEXP);
    Rcpp::traits::input_parameter< VS& >::type b(bSEXP);
    rcpp_result_gen = Rcpp::wrap(set_in(a, b));
    return rcpp_result_gen;
END_RCPP
}
// set_issubeq
bool set_issubeq(VS& a, VS& b);
RcppExport SEXP _molic_set_issubeq(SEXP aSEXP, SEXP bSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< VS& >::type a(aSEXP);
    Rcpp::traits::input_parameter< VS& >::type b(bSEXP);
    rcpp_result_gen = Rcpp::wrap(set_issubeq(a, b));
    return rcpp_result_gen;
END_RCPP
}
// set_any
bool set_any(std::vector<bool>& v);
RcppExport SEXP _molic_set_any(SEXP vSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<bool>& >::type v(vSEXP);
    rcpp_result_gen = Rcpp::wrap(set_any(v));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_molic_dfs", (DL_FUNC) &_molic_dfs, 2},
    {"_molic_count_unique", (DL_FUNC) &_molic_count_unique, 1},
    {"_molic_matpr", (DL_FUNC) &_molic_matpr, 1},
    {"_molic_n_a", (DL_FUNC) &_molic_n_a, 1},
    {"_molic_na_ya", (DL_FUNC) &_molic_na_ya, 2},
    {"_molic_n_b", (DL_FUNC) &_molic_n_b, 2},
    {"_molic_subtract_one", (DL_FUNC) &_molic_subtract_one, 1},
    {"_molic_Gx_", (DL_FUNC) &_molic_Gx_, 1},
    {"_molic_Hx_", (DL_FUNC) &_molic_Hx_, 1},
    {"_molic_subM", (DL_FUNC) &_molic_subM, 2},
    {"_molic_a_marginals", (DL_FUNC) &_molic_a_marginals, 2},
    {"_molic_TY", (DL_FUNC) &_molic_TY, 3},
    {"_molic_mcs", (DL_FUNC) &_molic_mcs, 1},
    {"_molic_perfect_cliques", (DL_FUNC) &_molic_perfect_cliques, 1},
    {"_molic_perfect_separators", (DL_FUNC) &_molic_perfect_separators, 1},
    {"_molic_rip", (DL_FUNC) &_molic_rip, 1},
    {"_molic_mcs2", (DL_FUNC) &_molic_mcs2, 1},
    {"_molic_rip2", (DL_FUNC) &_molic_rip2, 1},
    {"_molic_set_intersect", (DL_FUNC) &_molic_set_intersect, 2},
    {"_molic_set_union", (DL_FUNC) &_molic_set_union, 2},
    {"_molic_set_diff", (DL_FUNC) &_molic_set_diff, 2},
    {"_molic_set_eq", (DL_FUNC) &_molic_set_eq, 2},
    {"_molic_set_in", (DL_FUNC) &_molic_set_in, 2},
    {"_molic_set_issubeq", (DL_FUNC) &_molic_set_issubeq, 2},
    {"_molic_set_any", (DL_FUNC) &_molic_set_any, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_molic(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
