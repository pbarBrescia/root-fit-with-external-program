#include <iostream>
#include <iomanip>


/*
	A simple program that takes x, m and q as arguments and returns
	the corresponding y = mx + q

	NOTE: notice the precision of the output floating number. That could be
	an issue in the fit (is no precision is set, the fit does not converge)
*/
int main(int argc,char** argv){


	double x = std::atof(argv[1]) ;
	double m = std::atof(argv[2]) ;
	double q = std::atof(argv[3]) ;

	std::cout << std::fixed << std::setprecision(6) << m*x+q << std::endl;
	return 0;
}