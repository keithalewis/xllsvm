// xlltemplate.cpp
#include <cmath>
#include "xllsvm.h"

using namespace xll;

//enum { C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR };	/* svm_type */
XLL_ENUM_DOC(C_SVC, SVM_C_SVC, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(NU_SVC, SVM_NU_SVC, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(ONE_CLASS, SVM_ONE_CLASS, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(EPSILON_SVR, SVM_EPSILON_SVR, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(NU_SVR, SVM_NU_SVR, CATEGORY, L"description", L"documentation");

//enum { LINEAR, POLY, RBF, SIGMOID, PRECOMPUTED }; /* kernel_type */
XLL_ENUM_DOC(LINEAR, KERNEL_LINEAR, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(POLY, KERNEL_POLY, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(RBF, KERNEL_RBF, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(SIGMOID, KERNEL_SIGMOID, CATEGORY, L"description", L"documentation");
XLL_ENUM_DOC(PRECOMPUTED, KERNEL_PRECOMPUTED, CATEGORY, L"description", L"documentation");

AddIn xai_svm_problem(
    Function(XLL_HANDLE, L"?xll_svm_problem", L"SVM.PROBLEM")
    .Arg(XLL_FP, L"y", L"is the classification vector.")
    .Arg(XLL_LPOPER, L"data", L"range")
    .Category(CATEGORY)
    .FunctionHelp(L"Arrays of training data.")
);
HANDLEX WINAPI xll_svm_problem(_FP12* py, LPOPER12 pdata)
{
#pragma XLLEXPORT
    handlex h;

    try {
        ensure(pdata->xltype == xltypeMulti);
        RW rw = pdata->val.array.rows;
        COL col = pdata->val.array.columns;
        ensure(size(*py) == rw);

        handle<svm::problem> h_(new svm::problem(size(*py), begin(*py)));

        for (int i = 0; i < rw; ++i) {
            for (int j = 0; j < col; ++j) {
                h_->push_back(i, j);
            }
        }

        h = h_.get();
    }
    catch (const std::exception& ex) {
        XLL_ERROR(ex.what());
    }

    return h;
}

// Information Excel needs to register add-in.
AddIn xai_function(
    Function(XLL_DOUBLE, L"?xll_function", L"XLL.FUNCTION")
    .Arg(XLL_DOUBLE, L"x", L"is the first double argument.")
    .Category(CATEGORY)
    .FunctionHelp(L"Help on XLL.FUNCTION goes here.")
);
double WINAPI xll_function(double x)
{
#pragma XLLEXPORT
    return exp(x);
}