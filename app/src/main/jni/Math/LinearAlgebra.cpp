//
// Created by dongdokee on 2015-11-18.
//

#include "LinearAlgebra.h"

Matrix inv(Matrix& input, bool& succ)
{
    // create a working copy of the input
    Matrix A(input);

    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = boost::numeric::ublas::lu_factorize(A, pm);
    if (res != 0) {
        succ = false;
        return Matrix();
    }

    // create identity matrix of "inverse"
    Matrix inverse(A.size1(), A.size1());
    inverse.assign(IdentityMatrix (A.size1()));

    // backsubstitute to get the inverse
    boost::numeric::ublas::lu_substitute(A, pm, inverse);

    succ = true;
    return inverse;
}

// C = A * B
void prod(Matrix& A, Matrix& B, Matrix& C) {
    Matrix result(C);
    boost::numeric::ublas::axpy_prod(A, B, result, true);
    C = result;
}

void cross_prod(Vector& a, Vector& b, Vector& c) {
    Vector result(c);
    result(0) = a(1) * b(2) - a(2) * b(1);
    result(1) = a(2) * b(0) - a(0) * b(2);
    result(2) = a(0) * b(1) - a(1) * b(0);
    c = result;
}

void linalgebra_test()
{
    Matrix A(3, 3);
    A(0,0) = 0.8147;
    A(0,1) = 0.9134;
    A(0,2) = 0.2785;
    A(1,0) = 0.9058;
    A(1,1) = 0.6324;
    A(1,2) = 0.5469;
    A(2,0) = 0.1270;
    A(2,1) = 0.0975;
    A(2,2) = 0.9575;

    LOGD("inverse operation start");
    bool succ;
    Matrix inv_mat = inv(A, succ);
    //Matrix inv_mat(3, 3);
    prod(inv_mat, A, inv_mat);
    LOGD("inverse operation end");
    LOGD("%d", succ);
    LOGD("%lf %lf %lf", inv_mat(0, 0), inv_mat(0, 1), inv_mat(0, 2));
    LOGD("%lf %lf %lf", inv_mat(1, 0), inv_mat(1, 1), inv_mat(1, 2));
    LOGD("%lf %lf %lf", inv_mat(2, 0), inv_mat(2, 1), inv_mat(2, 2));

    // PASS TEST
}