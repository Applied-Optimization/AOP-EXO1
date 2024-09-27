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
            
            const double x_start = _x_l(0);
            const double y_start = _x_l(1);

            const double x_end = _x_u(0);
            const double y_end = _x_u(1);

            const int x_n_cells = this->n_cells_;
            const int y_n_cells = this->n_cells_;

            
            Vec x_min(2);
            x_min << std::numeric_limits<double>::min(), std::numeric_limits<double>::min();

            const double x_step = (x_end - x_start) / x_n_cells;
            const double y_step = (y_end - y_start) / y_n_cells;
            
            for (double i = x_start; i <= x_end; i += x_step) {
                for(double j = y_start; j <= y_end; j += y_step) {
                    Vec point(2);
                    point << i, j;
                    const double f_x_y = _func->eval_f(point);
                    if(f_x_y <= fmin) {
                        fmin = f_x_y;
                        x_min = point;
                    }
                }
            }
            
            _f_min = fmin;
            Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "(", ")");
            std::cout<<"Minimum value of the function is: "<<fmin<<" at x:"<<x_min.format(fmt)<<std::endl;
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

            Vec current = Eigen::VectorXd::Zero(_x_l.size());
            this->iterate_over_dimension_(_func, _x_l, _x_u, current, 0, f_min, x_min);
            _f_min = f_min;
            Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "(", ")");
            std::cout << "Minimum value of the function is: " << f_min << " at x:" << x_min.format(fmt) << std::endl;

            return 0;
        }

    private:
        int n_cells_;

        void iterate_over_dimension_(FunctionBase* _func, const Vec& _x_l, const Vec& _x_u, Vec& _current, int dim, double &_f_min, Vec &_x_min) const {
            if(dim == _current.size()) {
                const double f_x = _func->eval_f(_current);
                if(f_x <= _f_min) {
                    _f_min = f_x;
                    _x_min << _current;
                }
                return;
            }
            
            double step = (_x_u(dim) - _x_l(dim)) / (this->n_cells_);

            for(int i = 0; i <= this->n_cells_; ++i) {
                _current(dim) = _x_l(dim) + i * step;
                iterate_over_dimension_(_func, _x_l, _x_u, _current, dim + 1, _f_min, _x_min);
            }
        }
    };

    //=============================================================================
}