// xllsvm.h - Support vector machine add-in.
#include <vector>
#include "libsvm/svm.h"
#include "xll12/xll/xll.h"

// Function Wizard category
#ifndef CATEGORY
#define CATEGORY L"SVM"
#endif

namespace svm {

    class problem : public svm_problem {
        std::vector<double> y_;
        std::vector<svm_node> x_;
        std::vector<svm_node*> px_;
    public:
        problem()
        { }
        problem(size_t l, const double* y)
            : y_(y, y + l)
        {
            l = y_.size();
            y = y_.data();
        }
        // Sparse vectors with index = -1 indicating end
        // Push index -1 twice to terminate
        problem& push_back(int index, double value)
        {
            static std::vector<svm_node> xs;

            if (index == -1 && xs.size() == 0 && x_.size() != 0) {
                // pushed (-1, ?) twice in a row
                ensure(l == static_cast<int>(x_.size()));
                // fix up the goofy data structure
                px_.push_back(&x_[0]);
                for (size_t i = 0; i + 1 < x_.size(); ++i) {
                    if (x_[i].index == -1) {
                        px_.push_back(&x_[i + 1]);
                    }
                }
                x = &px_[0];
                xs.resize(0);
            }
            else {
                xs.push_back(svm_node{ index, value });
                if (index == -1) {
                    x_.emplace_back(xs);
                    xs.resize(0);
                }
            }

            return *this;
        }
    };

    struct parameter : public svm_parameter {
        //parameter()
        //    : svm_parameter{ C_SVC, RBF, 3, 0, 0, 100, 1e-3, 1, 0, nullptr, nullptr, 0.5, 0.1, 1, 0 }
        //{ }
        parameter(
            int svm_type = C_SVC,
            int kernel_type = RBF,
            int degree = 3,	/* for poly */
            double gamma = 0,	/* for poly/rbf/sigmoid */
            double coef0 = 0,	/* for poly/sigmoid */

                            /* these are for training only */
            double cache_size = 100, /* in MB */
            double eps = 1e-3,	/* stopping criteria */
            double C = 1,	/* for C_SVC, EPSILON_SVR and NU_SVR */
            int nr_weight = 0,		/* for C_SVC */
            int *weight_label = nullptr,	/* for C_SVC */
            double* weight = nullptr,		/* for C_SVC */
            double nu = 0.5,	/* for NU_SVC, ONE_CLASS, and NU_SVR */
            double p = 0.1,	/* for EPSILON_SVR */
            int shrinking = 1,	/* use the shrinking heuristics */
            int probability = 0 /* do probability estimates */
        )
            : svm_parameter{svm_type, kernel_type, degree, gamma, coef0, cache_size, eps, C, nr_weight, weight_label, weight, nu, p, shrinking, probability}
        { }
        parameter(const parameter&) = delete;
        parameter& operator=(const parameter&) = delete;
        ~parameter()
        {
            svm_destroy_param(this);
        }
    };
    class model : public svm_model {
    public:
        model()
        { }
    };

} // namespace svm