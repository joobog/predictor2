/*
 * =====================================================================================
 *
 *       Filename:  functions.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/08/2015 12:31:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */



#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>
#include <iostream>
#include <shogun/labels/MulticlassLabels.h>
#include <shogun/features/DenseFeatures.h>

void print_message(FILE* target, const char* str);
void print_warning(FILE* target, const char* str);
void print_error(FILE* target, const char* str);

std::vector<double> convert(const shogun::SGVector<float64_t>& sg_vector);
shogun::SGVector<float64_t> convert(const std::vector<double>& vector);
std::vector<std::vector<double>> convert(const shogun::SGMatrix<float64_t>& matrix);

//template <typename STDType>
//shogun::SGMatrix<float64_t> convert(const std::vector<std::vector<STDType>>& matrix);
shogun::SGMatrix<float64_t> convert(const std::vector<std::vector<double>>& matrix);

void normalize(shogun::SGMatrix<float64_t>& matrix);

std::ostream& operator<< (std::ostream& os, const shogun::SGMatrix<float64_t>& matrix);
std::ostream& operator<< (std::ostream& os, const shogun::SGVector<float64_t>& vector);

#endif // FUNCTIONS_HPP
