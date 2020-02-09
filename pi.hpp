#pragma once

#include <gmp.h>
#include <gmpxx.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define PRECISION 4

/**
 * @brief: Implementation of Bailey–Borwein–Plouffe formula (BBP formula)
 * @param unsigned int: n'th decimal of pi to compute
 * @param unsigned int: start
 * @param unsigned int: step
 * @param mpf_class*: pointer on mpf_class object
 */
void bbp(unsigned int, unsigned int, unsigned int, mpf_class&);

/**
 * @brief: Function to write results in file(s).
 * @param int: precision
 * @param mpf_class: mpf_class object
 */
void writeOutputFile(unsigned int, mpf_class&);