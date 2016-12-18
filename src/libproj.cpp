#include <Rcpp.h>
#include <proj_api.h>

// [[Rcpp::export]]
Rcpp::IntegerVector proj_version() 
{
  int v = PJ_VERSION; 

  return Rcpp::IntegerVector::create(
    v / 100,
    (v / 10) % 10,
    v % 10
  );
}


// [[Rcpp::export]]
Rcpp::NumericMatrix test_api(Rcpp::NumericMatrix lat_long)
{
  if (lat_long.ncol() != 2)
    Rcpp::stop("Invalid data format");

  projPJ pj_merc = pj_init_plus("+proj=merc +ellps=clrk66 +lat_ts=33");
  projPJ pj_latlong = pj_init_plus("+proj=latlong +ellps=clrk66");
  double x, y;

  if (!pj_merc || !pj_latlong)
    Rcpp::stop("Initialization failed");

  Rcpp::NumericMatrix res(lat_long);
  for(int i=0; i<lat_long.nrow(); ++i)
  {
    double x = lat_long(i,0) * DEG_TO_RAD;
    double y = lat_long(i,1) * DEG_TO_RAD;
    pj_transform(pj_latlong, pj_merc, 1, 1, &x, &y, NULL);

    res(i,0) = x;
    res(i,1) = y;
  }
  
  return res;
}