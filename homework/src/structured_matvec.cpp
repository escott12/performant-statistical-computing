#include <Rcpp.h>
using Rcpp::NumericVector;
using Rcpp::NumericMatrix;

// [[Rcpp::export]]
NumericVector ar_precision_matvec(
    const NumericVector& v, double auto_corr
  ) {
	int n = v.size(); // Specify length of return vector
	NumericVector result(n); // Allocate return vector
	double auto_corr_sq = pow(auto_corr, 2.); // '^' operator would not work
	
	// Calculate return vector
	result += v;
	
	for (int i = 1; i < n-2; ++i) {
	  result[i] += (1 + auto_corr_sq) * result[i];
	}

  // Add contributions from the off-diagonals
  // for (int i = 0; i < n-2; ++i) {
  //   result[i] += result[i] - auto_corr * v[i+1];
  //   result[i+1] += result[i+1] - auto_corr * v[i];
  // }
  
  // result += result / (1 - auto_corr_sq);
	
	return result;
}

// [[Rcpp::export]]
NumericVector sym_banded_matvec(
    const NumericVector& v, const NumericMatrix& banded_mat) {
  int n_col = banded_mat.ncol();
  int n_row = banded_mat.nrow();
  if (n_row != v.size()) {
    Rcpp::stop("Incompatible dimensions");
  }
  NumericVector result(n_row);
  // Multiplication by the diagonal
  for (int i = 0; i < n_row; ++i) {
    result[i] = banded_mat(i, 0) * v[i]; // Use (,) to access matrix elements
  }
  // Multiplication by the off-diagonals
  for (int diag_offset = 1; diag_offset < n_col; ++diag_offset) {
    for (int i = 0; i < n_row - diag_offset; ++i) {
      // Fill in
    }
  }
  return result;
}
