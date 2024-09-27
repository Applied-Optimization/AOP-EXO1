#pragma once

#include <iostream>
#include <FunctionBase/FunctionBase.hh>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================

/* Implements a quadratic 2D function of the form f(x,y) = 0.5(x^2 + gamma *y^2)
 * gamma is given as a constructor parameter (see right below) */
    class FunctionQuadratic2D final : public FunctionBase {
    public:
        // f(x,y) = 0.5(x^2 + gamma *y^2)

        // constructor
        FunctionQuadratic2D(const double _gamma = 1)
                : FunctionBase(), gamma_(_gamma) {}

        // number of unknowns
        inline virtual int n_unknowns() { return 2; }

        /** funcion evaluation
         * \param _x the value at which to evaluate the function.
         *           It should be a 2D vector*/
        inline virtual double eval_f(const Vec &_x) {
            //------------------------------------------------------//
            //Todo: implement the function f(x,y) = 0.5(x^2 + gamma *y^2)

            //------------------------------------------------------//
            //------------------------------------------------------//
            // Check if the input vector _x has the correct size (2)
            if (_x.size() != 2) {
                throw std::invalid_argument("Input vector must be of size 2");
            }
            
            // Extract x1 and x2 from the input vector
            double x1 = _x[0];
            double x2 = _x[1];
            
            // Compute the value of the function: f(x) = 0.5 * (x1^2 + gamma * x2^2)
            double result = 0.5 * (x1 * x1 + gamma_ * x2 * x2);
            return result;
        }

        /** evaluates the quadratic function's gradient
         * \param _x the point on which to evaluate the function
         * \param _g gradient output */
        inline virtual void eval_gradient(const Vec &_x, Vec &_g) {
            // Assuming _g is already sized appropriately
            if (_x.size() != 2) {
                throw std::invalid_argument("Input vector must be of size 2");
            }
            _g[0] = _x[0]; // Gradient with respect to x1
            _g[1] = gamma_ * _x[1]; // Gradient with respect to x2
        }

        /** evaluates the quadratic function's Hessian
         * \param _x the point on which to evaluate the Hessian.
         *           Actually useless since the Hessian is constant but the method
         *           should still use the same interface as FunctionBase
         * \param _H Hessian output */
        inline virtual void eval_hessian(const Vec &_x, Mat &_H) {
            // Assuming _H is already sized appropriately (2x2)
            _H(0, 0) = 1;       // Second derivative w.r.t x1
            _H(0, 1) = 0;       // Mixed derivative
            _H(1, 0) = 0;       // Mixed derivative
            _H(1, 1) = gamma_;  // Second derivative w.r.t x2
        }

        double get_gamma() const { return gamma_; }

    private:
        double gamma_;
    };

//=============================================================================
}
