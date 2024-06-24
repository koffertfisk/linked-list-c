#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "iterator.h"

/**
 * @file linked_list.c
 * @brief Implementation of the linked list for holding generic elements.
 * 
 * This file contains the implementation of the linked list functions defined in
 * linked_list.h. The detailed descriptions of the functions are provided in the
 * header file.
 * 
 * @date 2021-04-15
 * @version 1.0
 * 
 * @author Marcus Enderskog
 **/

/// Link pointer to an element stored in a linked list.
typedef struct link link_t;

/// Link pointer to an element stored in a linked list.
struct link
{
  elem_t value;   // Element value.
  link_t *next;   // Next element.
};

/// Linked list structure for holding generic elements.
struct list
{
  link_t *first;    // Pointer to first element in a linked list.
  link_t *last;     // Pointer to last element in a linked list.
  size_t size;      // Number of elements stored in a linked list.
  eq_function fun;  // Function pointer for element equality comparison.
};

/// Iterator for a linked list.
struct iter
{
  link_t *current;  // Pointer to the current link.
  list_t* list;     // The linked list itself.
};

/**
 * @brief Create a new link.
 * @param value Element value to set.
 * @param next The next link.
 * @return A pointer to the newly created link, or NULL if memory allocation failed.
 **/
static link_t *link_new(const elem_t value, link_t *next);

/**
 * @brief Check and adjust a provided linked list index.
 * @param index The provided index to check and adjust.
 * @param upper_bound Maximum number.
 * @return An adjusted index number or -1 if the operation failed.
 **/
static int list_inner_adjust_index(const int index, const size_t upper_bound);

/**
 * @brief Check and adjust a provided linked list index.
 * @param index The provided index to check and adjust.
 * @param upper_bound Maximum number.
 * @return An adjusted index number or -1 if the operation failed.
 **/
static int list_inner_adjust_index(const int index, const size_t upper_bound)
{
  int index_adjusted = index;
  if (index < 0)
    {
      index_adjusted = index + upper_bound;
    }
  if (index_adjusted < 0)
    {
      return -1;
    }
  else if ((size_t)index_adjusted > upper_bound)
    {
      return -1;
    }

  return index_adjusted;
}

/**
 * @brief Create a new link.
 * @param value Element value to set.
 * @param next The next link.
 * @return A pointer to the newly created link, or NULL if memory allocation failed.
 **/
static link_t *link_new(const elem_t value, link_t *next)
{
  link_t *new = calloc(1, sizeof(link_t));
  if (new == NULL)
  {
    puts("Failed to allocate memory for another link.");
    return NULL;
  }
  new->value = value;
  new->next = next;

  return new;
}

list_iterator_t *list_iterator(list_t *list)
{
  list_iterator_t *result = calloc(1, sizeof(list_iterator_t));
  result->current = list->first;
  result->list = list;

  return result;
}

void iterator_insert(list_iterator_t *iter, const elem_t element)
{
  link_t *link_to_insert = link_new(element, iter->current->next);
  if (link_to_insert == NULL)
  {
    puts("Insertion failed due to memory corruption!");
    return;
  }
  iter->current->next = link_to_insert;
}

bool iterator_has_next(list_iterator_t *iter)
{
  return iter->current->next != NULL;
}

elem_t iterator_next(list_iterator_t *iter)
{
  iter->current = iter->current->next;
  return iter->current->value;
}

elem_t iterator_remove(list_iterator_t *iter)
{
  link_t *link_to_remove = iter->current->next;
  const elem_t value_removed = link_to_remove->value;
  iter->current->next = link_to_remove->next;
  free(link_to_remove);

  return value_removed;
}

void iterator_reset(list_iterator_t *iter)
{
  iter->current = iter->list->first;
}

elem_t iterator_current(list_iterator_t *iter)
{
  if (!iterator_has_next(iter))
    {
      elem_t result = {.i = -1};
      return result;
    }
  return iter->current->next->value;
}

void iterator_destroy(list_iterator_t *iter)
{
  free(iter);
}

list_t *linked_list_create(eq_function fun)
{
  list_t *list = calloc(1, sizeof(list_t));
  list->first = list->last = calloc(1, sizeof(link_t));
  list->size = 0;
  list->fun = fun;
  
  return list;
}

void linked_list_destroy(list_t *list)
{
  linked_list_clear(list);
  free(list->first);
  free(list);
}

void linked_list_append(list_t *list, const elem_t value)
{
  link_t *link_to_append = link_new(value, NULL);
  if (link_to_append == NULL)
  {
    puts("Append failed due to memory corruption!");
    return;
  }
  list->last->next = link_to_append;
  list->last = link_to_append;
  list->size += 1;
}

void linked_list_prepend(list_t *list, const elem_t value)
{
  link_t *link_to_prepend = link_new(value, list->first->next);
  if (link_to_prepend == NULL)
  {
    puts("Prepend failed due to memory corruption!");
    return;
  }
  if (list->first == list->last)
    {
      list->last = link_to_prepend;
    }
  
  list->first->next = link_to_prepend;
  list->size += 1;
}

void linked_list_insert(list_t *list, const int index, const elem_t value)
{
  const size_t size = linked_list_size(list);
  const int adjusted_index = list_inner_adjust_index(index, size);
  const size_t valid_index = (size_t)adjusted_index;
  if (adjusted_index == -1)
    {
      printf("%d is not a valid index!\n", index);
      return;
    }
  else if (valid_index == 0)
  {
    linked_list_prepend(list, value);
    return;
  }
  else if (valid_index == size)
  {
    linked_list_append(list, value);
    return;
  }
  else
  {
    list_iterator_t *iter = list_iterator(list);
    
    for (size_t i = 0; i < valid_index; ++i)
      {
        iterator_next(iter);
      }
    
    iterator_insert(iter, value);
    list->size += 1;
    iterator_destroy(iter);
  }
}

elem_t linked_list_remove(list_t *list, const int index)
{
  const int size = linked_list_size(list);
  const int upper_limit = size - 1;
  const int adjusted_index = list_inner_adjust_index(index, upper_limit);
  const size_t valid_index = (size_t)adjusted_index;
  if (adjusted_index == -1)
  {
    elem_t result = {.i = -1};
    return result;
  }
    
  list_iterator_t *iter = list_iterator(list);

  for (size_t i = 0; i < valid_index; ++i)
    {
      iterator_next(iter);
    }

  const elem_t value_removed = iterator_remove(iter);
  list->size -= 1;
  iterator_destroy(iter);

  return value_removed;
}

elem_t linked_list_get(list_t *list, const int index)
{
  const int size = linked_list_size(list);
  const int upper_limit = size - 1;
  const int adjusted_index = list_inner_adjust_index(index, upper_limit);
  const size_t valid_index = (size_t)adjusted_index;
  
  if (adjusted_index == -1)
  {
    elem_t result = {.i = -1};
    return result;
  }
  list_iterator_t *iter = list_iterator(list);
  
  for (size_t i = 0; i < valid_index; ++i)
    {
      iterator_next(iter);
    }

  elem_t value = iterator_current(iter);
  iterator_destroy(iter);

  return value;
  
}

bool linked_list_contains(list_t *list, const elem_t element)
{
  bool result = false;
  list_iterator_t *iter = list_iterator(list);
  
  while (iterator_has_next(iter))
    {
      elem_t current_value = iterator_next(iter);
      if (list->fun(current_value, element))
        {
          result = true;
          break;
        }
    }
  iterator_destroy(iter);
  return result;
}

size_t linked_list_size(list_t *list)
{
  return list->size;
}

size_t linked_list_calculate_size(list_t *list)
{
  size_t size = 0;
  list_iterator_t *iter = list_iterator(list);

  while (iterator_has_next(iter))
    {
      iterator_next(iter);
      ++size;
    }
  
  iterator_destroy(iter);
  return size;
}

bool linked_list_is_empty(list_t *list)
{
  const size_t size = linked_list_size(list);
  if (size == 0)
    {
      return true;
    }
  return false;
}

void linked_list_clear(list_t *list)
{
  if (!linked_list_is_empty(list))
    {
      list_iterator_t *iter = list_iterator(list);
      while (iterator_has_next(iter))
        {
          iterator_remove(iter);
          iterator_reset(iter);
          list->size -= 1;
        }
      iterator_destroy(iter);
    }
}

bool linked_list_all(list_t *list, predicate prop, const void *extra)
{
  bool result = true;
  list_iterator_t *iter = list_iterator(list);
  while (iterator_has_next(iter))
    {
      result = result && prop(iterator_current(iter), extra);
      iterator_next(iter);
    }

  iterator_destroy(iter);
  return result;
}

bool linked_list_any(list_t *list, predicate prop, const void *extra)
{
  bool result = false;
  list_iterator_t *iter = list_iterator(list);
  while (iterator_has_next(iter) && !result)
    {
      result = !result && prop(iterator_current(iter), extra);
      iterator_next(iter);
    }

  iterator_destroy(iter);
  return result;
}

void linked_list_apply_to_all(list_t *list, apply_function fun, const void *extra)
{
  for (link_t *cursor = list->first; cursor; cursor = cursor->next)
    {
      fun(&cursor->value, extra);
    }
}
