//
// Created by dongdokee on 2015-11-18.
//

#ifndef LOCPROJECT_LINEARALGEBRA_H
#define LOCPROJECT_LINEARALGEBRA_H

#include "boost/numeric/ublas/matrix.hpp" // boost::numeric::ublas::matrix
#include "boost/numeric/ublas/matrix_proxy.hpp" // subrange?
#include "boost/numeric/ublas/lu.hpp"
#include "boost/numeric/ublas/io.hpp"
#include "../util/log.h"

typedef double ELEMENT_T;
typedef boost::numeric::ublas::matrix<ELEMENT_T> Matrix;
typedef boost::numeric::ublas::zero_matrix<ELEMENT_T> ZeroMatrix;
typedef boost::numeric::ublas::identity_matrix<ELEMENT_T> IdentityMatrix;
typedef boost::numeric::ublas::vector<ELEMENT_T> Vector;
typedef boost::numeric::ublas::unit_vector<ELEMENT_T> UnitVector;
typedef boost::numeric::ublas::zero_vector<ELEMENT_T> ZeroVector;

typedef boost::numeric::ublas::permutation_matrix<std::size_t> pmatrix;

Matrix inv(Matrix& input, bool& succ);
// C = A * B
void prod(Matrix& A, Matrix& B, Matrix& C);
void cross_prod(Vector& a, Vector& b, Vector& c);
void linalgebra_test();



#endif //LOCPROJECT_LINEARALGEBRA_H
