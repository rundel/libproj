// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// proj_version
Rcpp::IntegerVector proj_version();
RcppExport SEXP _libproj_proj_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(proj_version());
    return rcpp_result_gen;
END_RCPP
}
// test_api
Rcpp::NumericMatrix test_api(Rcpp::NumericMatrix lat_long);
RcppExport SEXP _libproj_test_api(SEXP lat_longSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type lat_long(lat_longSEXP);
    rcpp_result_gen = Rcpp::wrap(test_api(lat_long));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_libproj_proj_version", (DL_FUNC) &_libproj_proj_version, 0},
    {"_libproj_test_api", (DL_FUNC) &_libproj_test_api, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_libproj(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
