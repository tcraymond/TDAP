/***************************************************************************
 *   Copyright (C) 2005 by T. C. Raymond                                   *
 *   tc.raymond@ieee.org                                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                  *
 *                                                                         *
 ***************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

using namespace std;

template <typename Object>
class matrix
{
   
  public:
    matrix(){};
  
	matrix( const int rows, const int cols ) {//: array( rows ) {
       //setNumCols( cols );
       /*for(int i=0;i<numrows();i++){
         for(int j=0;j<numcols();j++){
            array[i][j]=0;
         }
      }*/
		num_rows = rows;
		num_cols = cols;
		array = new Object*[rows];
		for (int i = 0; i<rows; i++){
			array[i] = new Object[cols];
			for (int j = 0; j<cols; j++){
				array[i][j] = 0;
			}
		}
    };

    int numrows( ) const {
       //return array.size( );
		return num_rows;
    };
    
    int numcols( ) const { 
       //return numrows( ) > 0 ? array[ 0 ].size( ) : 0;
		return num_cols;
    };
/*
    void setNumRows( int rows ) {
       array.resize( rows );
    }; 
       
    void setNumCols( int cols ) {
       for( int i = 0; i < numrows( ); i++ ){
          array[ i ].resize( cols );
       }
    };
    
    void setDimensions( int rows, int cols ){
       setNumRows( rows );
       setNumCols( cols );
    };

    const vector<Object> & operator[]( int row ) const {
       return array[ row ];
    };*/
    
    //vector<Object> & operator[]( int row ){
	Object* & operator[]( int row ){
       return array[ row ];
    }

    matrix<Object> operator + (matrix<Object>);
    matrix<Object> operator - (matrix<Object>);

    matrix<Object> operator * (matrix<Object>);
    vector<Object> operator * (vector<Object>);
    
    matrix<Object> operator * (Object);

    matrix<Object> T();

	Object det();

	matrix<Object> inv();
    
    template<typename _T> friend ostream& operator<<(ostream&, const matrix<_T>&);

   private:
      //vector< vector<Object> > array;
		Object** array;
		int num_rows;
		int num_cols;
};

template <class Object>
matrix<Object> matrix<Object>::operator * (matrix<Object> rhs){
   matrix<Object> product(this->numrows(),rhs.numcols());

   int i,j,k;

   for(i=0;i<this->numrows();i++){
      for(j=0;j<rhs.numcols();j++){
         for(k=0;k<this->numcols();k++){
            product[i][j] = product[i][j]+array[i][k] * rhs[k][j];
         }
      }
   }

   return product;
};

template <class Object>
vector<Object> matrix<Object>::operator * (vector<Object> rhs){
   vector<Object> product(this->numrows());
   int i,j;
   
   for(i=0;i<this->numrows();i++){
      for(j=0;j<this->numcols();j++){
         product[i] = product[i] + array[i][j] * rhs[j];
      }
   }

   return product;
};

template <class Object>
matrix<Object> matrix<Object>::operator + (matrix<Object> rhs){
   matrix<Object> sum(this->numrows(), this->numcols());
   int i,j;

   sum = *this;

   for(i=0;i<this->numrows();i++){
      for(j=0;j<this->numcols();j++){
         sum[i][j] = sum[i][j] + rhs[i][j];
      }
   }
   return sum;
};

template <class Object>
matrix<Object> matrix<Object>::operator - (matrix<Object> rhs){
   matrix<Object> diff(this->numrows(), this->numcols());
   int i,j;

   diff = *this;

   for(i=0;i<this->numrows();i++){
      for(j=0;j<this->numcols();j++){
         diff[i][j] = diff[i][j] - rhs[i][j];
      }
   }
   return diff;
};

template <class Object>
matrix<Object> matrix<Object>::operator * (Object rhs){
   matrix<Object> product(this->numrows(), this->numcols());
   int i,j;

   product = *this;

   for(i=0;i<this->numrows();i++){
      for(j=0;j<this->numcols();j++){
         product[i][j] = product[i][j] * rhs;
      }
   }
   return product;
};

template <class Object>
matrix<Object> matrix<Object>::T(){
   matrix<Object> transp(this->numcols(), this->numrows());
   int i,j;

   for(i=0;i<this->numcols();i++){
      for(j=0;j<this->numrows();j++){
         transp[i][j] = array[j][i];
      }
   }
   return transp;
};

template <class Object>
Object matrix<Object>::det(){
   Object determinant;
   determinant = array[0][0] * array[1][1] - array[0][1] * array[1][0];
   
   return determinant;
};

template <class Object>
matrix<Object> matrix<Object>::inv(){
   matrix<Object> inverse(this->numcols(), this->numrows());
   Object determinant = det();
   
   // j_inv = dSdX
   // [drdx, drdy]
   // [dsdx, dsdy]
   // -equals-
   // 1/j * [dyds, -dxds]
   //       [-dydr, dxdr]
   
   inverse[0][0]=array[1][1]/determinant;
   inverse[0][1]=-1*array[0][1]/determinant;
   inverse[1][0]=-1*array[1][0]/determinant;
   inverse[1][1]=array[0][0]/determinant;
   
   return inverse;
};

template <class Object>
ostream& operator<<(ostream& Ostr, matrix<Object>& rhs){
   for(int i=0; i<rhs.numrows() ;i++){
      for(int j=0; j<rhs.numcols(); j++){
         Ostr << rhs[i][j] << "   ";
      }
      Ostr << endl;
   }
   return Ostr;
};

template <typename Object>
class linalg_vector
{
  public:
  
  linalg_vector(){};
  
   linalg_vector( int rows ) : vec( rows ) {
   };
   
   int size(){
      return vec.size();
   };
    
   linalg_vector<Object> operator+(const linalg_vector<Object> rhs);
 
   linalg_vector<Object> operator*(const double rhs);
   
   const Object & operator[]( int row ) const {
       return vec[ row ];
    };
    
    Object & operator[]( int row ){
       return vec[ row ];
    }
   
  private:
    vector<Object> vec;
};

template <class Object>
linalg_vector<Object> linalg_vector<Object>::operator+(const linalg_vector<Object> rhs){
   linalg_vector<Object> sum(this->size());
   sum = *this;
   
   for(int i=0; i<this->size(); i++){
      sum[i] = sum[i] + rhs[i];
   }
   return sum;
};

template <class Object> 
linalg_vector<Object> linalg_vector<Object>::operator*(const double rhs){
   linalg_vector<Object> prod(this->size());
   prod = *this;
   
   for(int i=0; i<this->size(); i++){
      prod[i] = prod[i] * rhs;
   }
   return prod;
};

#endif
