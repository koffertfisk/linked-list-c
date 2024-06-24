#pragma once

#include <stdbool.h>
#include "common.h"

/**
 * @file iterator.h
 * @brief Iterator to be used with linked lists.
 * 
 * This header file defines the interface for an iterator that can be used
 * to traverse and manipulate elements in a linked list. It provides functions
 * for checking the presence of next elements, iterating, removing elements,
 * inserting elements, resetting the iterator, accessing the current element,
 * and destroying the iterator.
 * 
 * @date 2021-04-15
 * @version 1.0
 * 
 * @note Ensure that the linked list implementation is compatible with this iterator.
 *       Refer to the documentation of the linked list for further details.
 * 
 * @author
 * Marcus Enderskog
 **/

/// @brief Iterator for a linked list.
typedef struct iter list_iterator_t;

/**
 * @brief Checks if there are more elements to iterate over.
 * 
 * This function checks if the iterator has more elements to traverse
 * in the linked list.
 * 
 * @param iter The iterator.
 * @return True if another element exists, false otherwise.
 **/
bool iterator_has_next(list_iterator_t *iter);

/**
 * @brief Steps the iterator forward one step.
 * 
 * This function advances the iterator to the next element in the linked list
 * and returns the current element.
 * 
 * @param iter The iterator.
 * @return The next element.
 **/
elem_t iterator_next(list_iterator_t *iter);

/**
 * @brief Removes the current element from the underlying list.
 * 
 * This function removes the element currently pointed to by the iterator
 * from the linked list and returns it.
 * 
 * @param iter The iterator.
 * @return The removed element.
 **/
elem_t iterator_remove(list_iterator_t *iter);

/**
 * @brief Inserts a new element into the underlying list.
 * 
 * This function inserts a new element into the linked list such that the
 * new element becomes the next element of the current position of the iterator.
 * 
 * @param iter The iterator.
 * @param element The element to be inserted.
 **/
void iterator_insert(list_iterator_t *iter, const elem_t element);

/**
 * @brief Repositions the iterator at the start of the underlying list.
 * 
 * This function resets the iterator to point to the first element in the linked list.
 * 
 * @param iter The iterator.
 **/
void iterator_reset(list_iterator_t *iter);
 
/**
 * @brief Returns the current element from the underlying list.
 * 
 * This function returns the element currently pointed to by the iterator.
 * If the list is empty, it returns an element with an undefined value.
 * 
 * @param iter The iterator.
 * @return The current element or an element with an undefined value if the list is empty.
 **/
elem_t iterator_current(list_iterator_t *iter);

/**
 * @brief Destroys the iterator and frees its resources.
 * 
 * This function deallocates any resources associated with the iterator.
 * 
 * @param iter The iterator.
 **/
void iterator_destroy(list_iterator_t *iter);
