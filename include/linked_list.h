#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "iterator.h"
#include "common.h"

/**
 * @file linked_list.h
 * @brief Linked list for holding generic elements.
 * 
 * This header file defines the interface for a linked list that can store
 * generic elements. It provides functions for creating, manipulating, and
 * destroying linked lists, as well as iterating over their elements.
 * 
 * @date 2021-04-15
 * @version 1.0
 * 
 * @note Ensure that the elements stored in the list are compatible with the
 *       elem_t union defined in common.h.
 * 
 * @see common.h
 * @see iterator.h
 * 
 * @authored Marcus Enderskog
 */

/// @brief Linked list structure for holding generic elements.
typedef struct list list_t;

/** 
 * @brief Function pointer type for testing a condition on a value.
 * 
 * This function pointer type defines a predicate function that takes an element
 * and an additional argument and returns true if the condition is satisfied, 
 * and false otherwise.
 * 
 * @param value Value to operate on.
 * @param extra Data to check against.
 * @return True if the condition holds, false otherwise.
 **/
typedef bool(*predicate)(const elem_t value, const void *extra);

/** 
 * @brief Function pointer type for updating a value.
 * 
 * This function pointer type defines an apply function that updates an element
 * with new data provided as an additional argument.
 * 
 * @param value Value to update.
 * @param extra New data to update value with.
 **/
typedef void(*apply_function)(elem_t *value, const void *extra);

/**
 * @brief Function pointer type for comparing two elements for equality.
 * 
 * This function pointer type defines an equality function that compares two
 * elements and returns true if they are equal, and false otherwise.
 * 
 * @param a First element.
 * @param b Second element.
 * @return True if the two elements are equal, false otherwise.
 **/
typedef bool(*eq_function)(const elem_t a, const elem_t b);

/**
 * @brief Creates a new empty list.
 * 
 * This function creates a new empty linked list and returns a pointer to it.
 * 
 * @param fun Function pointer for element equality comparison to store in the list.
 * @return A pointer to an empty linked list.
 **/
list_t *linked_list_create(eq_function fun);

/**
 * @brief Creates an iterator for a given list.
 * 
 * This function creates and returns an iterator positioned at the start of the linked list.
 * 
 * @param list List to be iterated over.
 * @return An iterator positioned at the start of the list.
 **/
list_iterator_t *list_iterator(list_t *list);

/**
 * @brief Destroys the linked list and frees its memory.
 * 
 * This function tears down the linked list and frees all its memory, but not the memory of the elements.
 * 
 * @param list The list to be destroyed.
 **/
void linked_list_destroy(list_t *list);

/** 
 * @brief Inserts an element at the end of the linked list in O(1) time.
 * 
 * This function appends an element to the end of the linked list.
 * 
 * @param list The linked list to be appended to.
 * @param value The value to be appended.
 **/
void linked_list_append(list_t *list, const elem_t value);

/**
 * @brief Inserts an element at the front of the linked list in O(1) time.
 * 
 * This function prepends an element to the front of the linked list.
 * 
 * @param list The linked list to be prepended to.
 * @param value The value to be prepended.
 **/
void linked_list_prepend(list_t *list, const elem_t value);

/**
 * @brief Inserts an element into the linked list at a specific position in O(n) time.
 * 
 * This function inserts an element at the specified index in the linked list.
 * The valid values of index are [0, n] for a list of n elements,
 * where 0 means before the first element and n means after the last element.
 * 
 * @param list The linked list to be extended.
 * @param index The position in the list.
 * @param value The value to be inserted.
 **/
void linked_list_insert(list_t *list, const int index, const elem_t value);

/**
 * @brief Removes an element from the linked list at a specific position in O(n) time.
 * 
 * This function removes an element at the specified index in the linked list.
 * The valid values of index are [0, n-1] for a list of n elements,
 * where 0 means the first element and n-1 means the last element.
 * 
 * @param list The linked list to be modified.
 * @param index The position in the list.
 * @return The removed value, or an element with an undefined value if the index is incorrect.
 **/
elem_t linked_list_remove(list_t *list, const int index);

/**
 * @brief Retrieves an element from the linked list at a specific position in O(n) time.
 * 
 * This function retrieves an element at the specified index in the linked list.
 * The valid values of index are [0, n-1] for a list of n elements,
 * where 0 means the first element and n-1 means the last element.
 * 
 * @param list The linked list to be accessed.
 * @param index The position in the list.
 * @return The value at the given position, or an element with an undefined value if the index is incorrect.
 **/
elem_t linked_list_get(list_t *list, const int index);

/**
 * @brief Checks if an element is in the list.
 * 
 * This function checks if a specified element is present in the linked list.
 * 
 * @param list The linked list.
 * @param element The element sought.
 * @return True if the element is in the list, false otherwise.
 **/
bool linked_list_contains(list_t *list, const elem_t element);

/** 
 * @brief Gets the number of elements in the linked list in O(1) time.
 * 
 * This function returns the number of elements in the linked list.
 * 
 * @param list The linked list.
 * @return The number of elements in the list.
 **/
size_t linked_list_size(list_t *list);

/** 
 * @brief Calculates the number of elements in the linked list by iterating through it.
 * 
 * This function iterates through the linked list to count the number of elements.
 * 
 * @param list The linked list.
 * @return The number of elements in the list.
 **/
size_t linked_list_calculate_size(list_t *list);

/**
 * @brief Checks if the linked list is empty.
 * 
 * This function checks if the linked list has no elements.
 * 
 * @param list The linked list.
 * @return True if the list is empty, false otherwise.
 **/
bool linked_list_is_empty(list_t *list);

/**
 * @brief Removes all elements from the linked list.
 * 
 * This function clears the linked list, removing all its elements.
 * 
 * @param list The linked list.
 **/
void linked_list_clear(list_t *list);

/**
 * @brief Checks if a supplied property holds for all elements in the list.
 * 
 * This function tests if a given predicate holds for all elements in the linked list.
 * The function returns as soon as the result can be determined.
 * 
 * @param list The linked list.
 * @param prop The property to be tested (function pointer).
 * @param extra An additional argument (may be NULL) that will be passed to all internal calls of prop.
 * @return True if the property holds for all elements in the list, false otherwise.
 **/
bool linked_list_all(list_t *list, predicate prop, const void *extra);

/**
 * @brief Checks if a supplied property holds for any element in the list.
 * 
 * This function tests if a given predicate holds for any element in the linked list.
 * The function returns as soon as the result can be determined.
 * 
 * @param list The linked list.
 * @param prop The property to be tested.
 * @param extra An additional argument (may be NULL) that will be passed to all internal calls of prop.
 * @return True if the property holds for any element in the list, false otherwise.
 **/
bool linked_list_any(list_t *list, predicate prop, const void *extra);

/** 
 * @brief Applies a supplied function to all elements in the list.
 * 
 * This function applies a given function to all elements in the linked list.
 * 
 * @param list The linked list.
 * @param fun The function to be applied.
 * @param extra An additional argument (may be NULL) that will be passed to all internal calls of fun.
 **/
void linked_list_apply_to_all(list_t *list, apply_function fun, const void *extra);