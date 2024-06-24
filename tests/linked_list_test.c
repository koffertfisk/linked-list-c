#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "linked_list.h"
#include "iterator.h"
#include "common.h"

static bool compare_int_elements(elem_t a, elem_t b)
{
  return a.i == b.i;
}

static bool compare_str_elements(elem_t a, elem_t b)
{
  return strcmp((char*)a.p, (char*)b.p) == 0;
}

static bool dummy_func_ptr(elem_t a, elem_t b)
{
  return true;
}

static bool int_less(const elem_t element, const void *extra)
{
  return element.i < *(int*)extra;
}

void test_create_destroy()
{
  list_t *list = linked_list_create(dummy_func_ptr);
   CU_ASSERT_PTR_NOT_NULL(list);
   CU_ASSERT(linked_list_size(list) == 0);
   linked_list_destroy(list);
}

void test_iterator_create_destroy()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  list_iterator_t *iter = list_iterator(list);
  CU_ASSERT_PTR_NOT_NULL(iter);
  iterator_destroy(iter);
  linked_list_destroy(list);
}

void test_insert_size()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  CU_ASSERT(linked_list_size(list) == 3);
  linked_list_destroy(list);
}

void test_calculate_size()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_prepend(list, int_elem(3));
  linked_list_prepend(list, int_elem(2));
  linked_list_prepend(list, int_elem(1));
  CU_ASSERT(linked_list_calculate_size(list) == 3);
  linked_list_destroy(list);
}

void test_clear()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  linked_list_clear(list);
  CU_ASSERT(linked_list_size(list) == 0);
  linked_list_destroy(list);
}

void test_get()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, ptr_elem("two"));
  linked_list_insert(list, 2, int_elem(3));
  elem_t first_result = linked_list_get(list, 1);
  CU_ASSERT(strcmp((char*) first_result.p, "two") == 0);
  elem_t second_result = linked_list_get(list, 3);
  CU_ASSERT(second_result.i == -1);
  linked_list_insert(list, 1, ptr_elem("new"));
  elem_t third_result = linked_list_get(list, 1);
  CU_ASSERT(strcmp((char*) third_result.p, "new") == 0);
  linked_list_destroy(list);
}

void test_insert_invalid_index()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 1, int_elem(2));
  CU_ASSERT(linked_list_size(list) == 0);
  linked_list_insert(list, -3, int_elem(2));
  CU_ASSERT(linked_list_size(list) == 0);
  linked_list_destroy(list);
}

void test_prepend()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  linked_list_prepend(list, int_elem(4));
  elem_t result = linked_list_get(list, 0);
  CU_ASSERT(result.i == 4);
  linked_list_destroy(list);
}

void test_append()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  linked_list_append(list, int_elem(4));
  elem_t result = linked_list_get(list, 3);
  CU_ASSERT(result.i == 4);
  linked_list_destroy(list);
}

void test_remove()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  elem_t first_result = linked_list_remove(list, 3);
  CU_ASSERT(first_result.i == -1);
  elem_t second_result = linked_list_remove(list, 1);
  CU_ASSERT(second_result.i == 2);
  elem_t third_result = linked_list_remove(list, 2);
  CU_ASSERT(third_result.i == -1);
  linked_list_destroy(list);
}

void test_remove_invalid_index()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  elem_t result = linked_list_remove(list, 4);
  CU_ASSERT(result.i == -1);
  linked_list_destroy(list);
}

void test_contains()
{
  list_t *list = linked_list_create(compare_int_elements);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  CU_ASSERT(linked_list_contains(list, int_elem(2)));
  CU_ASSERT_FALSE(linked_list_contains(list, int_elem(4)));  
  linked_list_destroy(list);

  list = linked_list_create(compare_str_elements);
  linked_list_insert(list, 0, ptr_elem("one"));
  linked_list_insert(list, 1, ptr_elem("two"));
  linked_list_insert(list, 2, ptr_elem("three"));
  CU_ASSERT(linked_list_contains(list, ptr_elem("two")));
  CU_ASSERT_FALSE(linked_list_contains(list, ptr_elem("four")));  
  linked_list_destroy(list);
}

void test_is_empty()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  CU_ASSERT(linked_list_is_empty(list));
  linked_list_insert(list, 0, int_elem(1));
  CU_ASSERT_FALSE(linked_list_is_empty(list));
  linked_list_destroy(list);
}

void test_all()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  int value_less_than = 4;
  CU_ASSERT(linked_list_all(list, int_less, &value_less_than));
  value_less_than = 2;
  CU_ASSERT_FALSE(linked_list_all(list, int_less, &value_less_than));
  linked_list_destroy(list);
}

void test_any()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  int value_less_than = 2;
  CU_ASSERT(linked_list_any(list, int_less, &value_less_than));
  value_less_than = 0;
  CU_ASSERT_FALSE(linked_list_any(list, int_less, &value_less_than));
  linked_list_destroy(list);
}

void set_value(elem_t *value, const void *extra)
{ 
  *value = *(elem_t*)extra;
}

static bool int_equiv(const elem_t value, const void *extra)
{
  return value.i == *(int*)extra;
}

static bool str_equiv(const elem_t value, const void *extra)
{
  return strcmp((char*)value.p, (char*)(*(elem_t*)extra).p) == 0;
}

void test_apply_to_all()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, int_elem(1));
  linked_list_insert(list, 1, int_elem(2));
  linked_list_insert(list, 2, int_elem(3));
  apply_function apply_func = &set_value;
  elem_t value_to_apply = int_elem(4);
  linked_list_apply_to_all(list, apply_func, &value_to_apply);
  predicate pred_func = int_equiv;
  CU_ASSERT(linked_list_all(list, pred_func, &value_to_apply));
  linked_list_destroy(list);

  list = linked_list_create(dummy_func_ptr);
  linked_list_insert(list, 0, ptr_elem("one"));
  linked_list_insert(list, 1, ptr_elem("two"));
  linked_list_insert(list, 2, ptr_elem("three"));
  apply_func = set_value;
  linked_list_apply_to_all(list, apply_func, &ptr_elem("four"));
  pred_func = str_equiv;
  CU_ASSERT(linked_list_all(list, pred_func, &ptr_elem("four")));
  linked_list_destroy(list);
}

void test_iterator_current()
{
  list_t *list = linked_list_create(dummy_func_ptr);
  list_iterator_t *iter = list_iterator(list);
  elem_t result = iterator_current(iter);
  CU_ASSERT(result.i == -1);
  iterator_destroy(iter);
  linked_list_destroy(list);
}

int main()
{
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  CU_pSuite creation = CU_add_suite("Creation", NULL, NULL);
  CU_pSuite size = CU_add_suite("Size", NULL, NULL);
  CU_pSuite insertion = CU_add_suite("Insertion", NULL, NULL);
  CU_pSuite retrieval = CU_add_suite("Retrieval", NULL, NULL);
  CU_pSuite removal = CU_add_suite("Removal", NULL, NULL);
  CU_pSuite function_application = CU_add_suite("Function Application", NULL, NULL);
  
  CU_add_test(creation, "List Creation", test_create_destroy);
  CU_add_test(creation, "Iterator Creation", test_iterator_create_destroy);
  CU_add_test(creation, "Clear", test_clear);

  CU_add_test(size, "Size", test_insert_size);
  CU_add_test(size, "Calculate Size", test_calculate_size);
  CU_add_test(size, "Is Empty", test_is_empty);

  CU_add_test(insertion, "Insert At Invalid Index", test_insert_invalid_index);
  CU_add_test(insertion, "Prepend", test_prepend);
  CU_add_test(insertion, "Append", test_append);

  CU_add_test(retrieval, "Get", test_get);
  CU_add_test(retrieval, "Iterator Current", test_iterator_current);
  CU_add_test(retrieval, "Contains", test_contains);

  CU_add_test(removal, "Remove", test_remove);
  CU_add_test(removal, "Remove At Invalid Index", test_remove_invalid_index);

  CU_add_test(function_application, "All", test_all);
  CU_add_test(function_application, "Any", test_any);
  CU_add_test(function_application, "Apply To All", test_apply_to_all);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  
  return CU_get_error();
}
