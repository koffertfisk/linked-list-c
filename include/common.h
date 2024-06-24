#pragma once

#include <stdbool.h>

/**
 * @file common.h
 * @brief Utility for handling and storing generic elements.
 * 
 * This header file defines a union for generic elements (`elem_t`) that can
 * represent various data types such as signed/unsigned integers, booleans,
 * floating point numbers, and generic pointers. It also provides macros to
 * facilitate the creation of these union elements.
 * 
 * @date 2021-04-15
 * @author Marcus Enderskog
 **/

/**
 * @brief Macro to create a signed integer element.
 * 
 * This macro takes a signed integer and returns an `elem_t` union
 * initialized with the given integer value.
 * 
 * @param x The signed integer value.
 * @return An `elem_t` union with the signed integer value.
 **/
#define int_elem(x) (elem_t) { .i=(x) }

/**
 * @brief Macro to create a pointer element.
 * 
 * This macro takes a pointer and returns an `elem_t` union initialized
 * with the given pointer value.
 * 
 * @param x The pointer value.
 * @return An `elem_t` union with the pointer value.
 **/
#define ptr_elem(x) (elem_t) { .p=(x) }

/**
 * @brief Macro to create a floating point element.
 * 
 * This macro takes a floating point number and returns an `elem_t` union
 * initialized with the given float value.
 * 
 * @param x The floating point value.
 * @return An `elem_t` union with the float value.
 **/
#define float_elem(x) (elem_t) { .f=(x) }

/**
 * @brief Macro to create a boolean element.
 * 
 * This macro takes a boolean value and returns an `elem_t` union
 * initialized with the given boolean value.
 * 
 * @param x The boolean value.
 * @return An `elem_t` union with the boolean value.
 **/
#define bool_elem(x) (elem_t) { .b=(x) }

/**
 * @brief Macro to create an unsigned integer element.
 * 
 * This macro takes an unsigned integer and returns an `elem_t` union
 * initialized with the given unsigned integer value.
 * 
 * @param x The unsigned integer value.
 * @return An `elem_t` union with the unsigned integer value.
 **/
#define unsigned_int_elem(x) (elem_t) { .u=(x) }

/**
 * @typedef elem_t
 * @brief Typedef for the generic element union.
 * 
 * This typedef provides a shorthand notation for referring to the union `elem`.
 **/
typedef union elem elem_t;

/**
 * @brief Generic element union.
 * 
 * This union can hold a value of various types, including signed/unsigned integers,
 * boolean, floating point number, or a generic pointer. It is useful for creating
 * data structures that need to store elements of different types in a uniform way.
 **/
union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
};
