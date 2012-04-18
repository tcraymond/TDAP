/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "matrix.h"
#include <vector>

#include "mtl/matrix.h"
#include "mtl/mtl.h"
#include "mtl/utils.h"  
#include "mtl/linalg_vec.h"
 
 typedef matrix<double> Matrix;
 
 typedef linalg_vector<double> Vector;
 
 typedef mtl::matrix<double, mtl::symmetric<mtl::upper>, mtl::array< mtl::compressed<> >, mtl::row_major >::type SparseMatrix;
 
 typedef mtl::dense1D<double> BigVector;
 
#endif
