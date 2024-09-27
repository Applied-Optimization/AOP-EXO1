#pragma once

#include <iostream>
#include <FunctionBase/FunctionBase.hh>

//== NAMESPACES ===============================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    /* This implements a generic non-convex function.
     * Its sole purpose is to test the ConvexitTest class */
    class FunctionNonConvex2D final : public FunctionBase {
    public:
        // f(x,y) = (y-x^2)^2+cos^2(4*y)*(1-x)^2+x^2+y^2

        // constructor
        FunctionNonConvex2D() {}

        // number of unknowns
        inline virtual int n_unknowns() { return 2; }

        /** funcion evaluation
         * \param _x the value at which to evaluate the function.
         *           It should be a 2D vector*/
        inline virtual double eval_f(const Vec &_x) {
            //------------------------------------------------------//
            //Todo: implement the function f(x,y) = (y-x^2)^2+cos^2(4*y)*(1-x)^2+x^2+y^2
            
            //------------------------------------------------------//
            //------------------------------------------------------//
            // Implement the function f(x,y)
            // Ensure input vector size is 2
            if (_x.size() != 2) {
                std::cerr << "Warning: Input vector size does not match 2D input!" << std::endl;
                return 0.0; // Handle error as preferred
            }

            double x = _x[0];
            double y = _x[1];

            // Implementing the function f(x, y)
            double term1 = pow(y - pow(x, 2), 2);
            double term2 = pow(cos(4 * y), 2) * pow(1 - x, 2);
            double term3 = pow(x, 2);
            double term4 = pow(y, 2);

            return term1 + term2 + term3 + term4;
            //------------------------------------------------------//
        }

        // gradient evaluation. Not necessary for this function
        inline virtual void eval_gradient(const Vec &_x, Vec &_g) {}

        // hessian matrix evaluation. Not necessary for this function
        inline virtual void eval_hessian(const Vec &_x, Mat &_H) {}
    };

//=============================================================================
}


