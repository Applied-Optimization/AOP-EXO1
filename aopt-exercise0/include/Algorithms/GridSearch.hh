#pragma once

#include <Functions/FunctionQuadratic2D.hh>
#include <Functions/FunctionQuadraticND.hh>
#include <Functions/FunctionNonConvex2D.hh>
#include <vector>

//== NAMESPACES ===================================================================

namespace AOPT {

    //== CLASS DEFINITION =========================================================
    class GridSearch {
    public:
        using Vec = FunctionBase::Vec;
        using Mat = FunctionBase::Mat;

        GridSearch(const int _n_cells = 10) : n_cells_(_n_cells){}
        ~GridSearch() {}

    public:

        /** Evaluation of a 2D function over the whole grid to find its minimum
         *
         * \param _func a pointer to any 2D function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define a square in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_2d(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            std::cout<<"Grid searching the minimum of a 2-D function..."<<std::endl;
            double f = 0., fmin = std::numeric_limits<double>::max();
            
            // Define the step size in each dimension (x and y)
	    double step_x = (_x_u[0] - _x_l[0]) / n_cells_;
	    double step_y = (_x_u[1] - _x_l[1]) / n_cells_;
            
            Vec x_min(2);
            
            //------------------------------------------------------//
            //Todo: implement the 2d version of the grid search
            // algorithm to find minimum value of _func between _x_l and _x_u
            //------------------------------------------------------//
                        // Implement the 2D version of the grid search algorithm
            for (int i = 0; i <= n_cells_; ++i) {
                for (int j = 0; j <= n_cells_; ++j) {
                    Vec x(2);
                    x[0] = _x_l[0] + i * step_x; // x-coordinate
                    x[1] = _x_l[1] + j * step_y; // y-coordinate
                    f = _func->eval_f(x);
                    if (f < fmin) {
                        fmin = f;
                        x_min = x; // Update the minimum point
                    }
                }
            }
            
            //------------------------------------------------------//
            _f_min = fmin;
            std::cout<<"Minimum value of the function is: "<<fmin<<" at x:\n"<<x_min<<std::endl;
            return 0;
        }



        /** Evaluation of an ND function over the whole grid to find its minimum
         *  using an iterative approach
         *
         * \param _func a pointer to any ND function inheriting from FunctionBase
         *              (see include/FunctionBase/FunctionBase.hh)
         * \param _x_l the coordinates of the lower corner of the grid
         * \param _x_u the coordinates of the upper corner of the grid.
         *             _x_l and _x_u together define an ND cuboid in which the grid lies
         * \return 0 if all went well, -1 if not.*/
        int grid_search_nd(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, double& _f_min) const {
            int n = _func->n_unknowns();
            if (_x_l.size() != n || _x_u.size() != n) {
                std::cout << "Error: input limits are not of correct dimension!" << std::endl;
                return -1;
            }
            std::cout << "Grid searching the minimum of a " << n << "-D function..." << std::endl;

            double f_min = std::numeric_limits<double>::max();
            Vec x_min(n);
            //------------------------------------------------------//
            //Todo: implement the nd version of the grid search
            // algorithm to find minimum value of a nd quadratic function
            // set f_min with the minimum, which is then stored in the referenced argument _f_min
            std::vector<int> indices(n, 0);
            std::vector<double> steps(n);
            for (int i = 0; i < n; ++i) {
                steps[i] = (_x_u[i] - _x_l[i]) / n_cells_; // Calculate step size for each dimension
            }
            // Create a loop to generate all combinations of grid points
            while (true) {
                // Calculate the current grid point
                Vec x(n);
                for (int i = 0; i < n; ++i) {
                    x[i] = _x_l[i] + indices[i] * steps[i];
                }

                // Evaluate the function at this point
                double f = _func->eval_f(x);

                // Check if we found a new minimum
                if (f < f_min) {
                    f_min = f;
                    x_min = x; // Update the minimum point
                }

                // Update indices to generate the next grid point
                int dim = n - 1;
                while (dim >= 0) {
                    if (++indices[dim] > n_cells_) { // Check if we exceeded the limit
                        indices[dim] = 0; // Reset current dimension
                        dim--; // Move to the next dimension
                    } else {
                        break; // Valid index found, exit the loop
                    }
                }

                if (dim < 0) { // All indices have been reset
                    break; // Exit the loop
                }
            }
            
            //------------------------------------------------------//
            _f_min = f_min;
            std::cout << "Minimum value of the function is: " << f_min << " at x:\n" << x_min << std::endl;

            return 0;
        }



    private:
        int n_cells_;
    };

    //=============================================================================
}





