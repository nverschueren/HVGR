// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

// we only include RcppArmadillo.h which pulls Rcpp.h in for us
#include "RcppArmadillo.h"

// via the depends attribute we tell Rcpp to create hooks for
// RcppArmadillo so that the build process will know what to do
//
// [[Rcpp::depends(RcppArmadillo)]]

// simple example of creating two matrices and
// returning the result of an operatioon on them
//
// via the exports attribute we tell Rcpp to make this function
// available from R
//
// [[Rcpp::export]]
arma::mat rcpparma_hello_world() {
    arma::mat m1 = arma::eye<arma::mat>(3, 3);
    arma::mat m2 = arma::eye<arma::mat>(3, 3);
	                     
    return m1 + 3 * (m1 + m2);
}


// another simple example: outer product of a vector, 
// returning a matrix
//
// [[Rcpp::export]]
arma::mat hvgedges(const arma::vec & xt) {
  int N=xt.n_rows;
  arma::mat edges(2*N,2);
  edges.ones();edges=-edges;
  int ed=0;
  bool look, lookleft,lookright;
  int der,izq;
  for(int i=0;i<N;i++)
  {
  lookleft=true;
  izq=1;
  lookright=true;
  der=1;
  look=bool(lookleft+lookright);
  while(look)
  {
  //look right
  if((i+der<N) && (xt(i)<=xt(i+der)) && lookright)
  {
  edges(ed,0)=i; edges(ed,1)=i+der;
  ed++;
  lookright=false;
  }
  der++;
  if(i+der>N){lookright=false;}
  //look left
  if((i-izq>=0) && (xt(i)<=xt(i-izq)) && lookleft)
  {
  edges(ed,0)=i; edges(ed,1)=i-izq;
  ed++;
  lookleft=false;
  }
  izq++;
  if(i-izq<0){lookleft=false;}
  look=bool(lookleft+lookright);
  }//endofwhile
  }//endofor
  return edges.rows(0,ed-1)+1;  
}

// and the inner product returns a scalar
//
// [[Rcpp::export]]
double rcpparma_innerproduct(const arma::colvec & x) {
    double v = arma::as_scalar(x.t() * x);
    return v;
}


// and we can use Rcpp::List to return both at the same time
//
// [[Rcpp::export]]
Rcpp::List rcpparma_bothproducts(const arma::colvec & x) {
    arma::mat op = x * x.t();
    double    ip = arma::as_scalar(x.t() * x);
    return Rcpp::List::create(Rcpp::Named("outer")=op,
                              Rcpp::Named("inner")=ip);
}
