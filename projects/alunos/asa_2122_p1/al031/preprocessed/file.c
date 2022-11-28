#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <string.h>
#include <malloc.h>
#include <math.h>


struct solution
{
  long long a;
  long long b;
};
struct solution combine_solutions(struct solution lhs, struct solution rhs)
{
  if (lhs.a == rhs.a)
  {
    return (struct solution){lhs.a, lhs.b + rhs.b};
  }
  else
  {
    if (lhs.a > rhs.a)
    {
      return lhs;
    }
    else
    {
      return rhs;
    }

  }

}

struct fenwick_tree
{
  size_t size;
  struct solution *data;
};
void fenwick_tree_init(struct fenwick_tree *tree, size_t size)
{
  tree->size = 1 + (1 << ((size_t) ceil(log(((double) size) - 1.0) / log(2.0))));
  tree->data = (struct solution *) malloc((sizeof(struct solution)) * ((tree->size * 2) - 1));
  memset(tree->data, 0, (sizeof(struct solution)) * ((tree->size * 2) - 1));
}

void fenwick_tree_free(struct fenwick_tree *tree)
{
  free(tree->data);
}

void fenwick_tree_update(struct fenwick_tree *tree, size_t index, struct solution solution)
{
  if (index == 0)
  {
    tree->data[0] = combine_solutions(tree->data[0], solution);
  }
  else
  {
    for (; index < tree->size; index += index & (-index))
      tree->data[index] = combine_solutions(tree->data[index], solution);

  }

}

struct solution fenwick_tree_query(struct fenwick_tree *tree, size_t r)
{
  struct solution ans = tree->data[0];
  for (; r != 0; r -= r & (-r))
    ans = combine_solutions(ans, tree->data[r]);

  return ans;
}

void sort_indices(long long *array, size_t *in_i, size_t *out_i, size_t size)
{
  size_t i = 0;
  size_t j = 0;
  size_t size_i = size / 2;
  size_t size_j = size - (size / 2);
  if (size == 1)
  {
    out_i[0] = in_i[0];
    return;
  }
  else
  {
    
  }

  sort_indices(array, in_i, out_i, size_i);
  sort_indices(array, in_i + size_i, out_i + size_i, size_j);
  memcpy(in_i, out_i, (sizeof(size_t)) * size);
  while ((i + j) < size)
  {
    if ((j >= size_j) || ((i < size_i) && (array[in_i[i]] < array[in_i[size_i + j]])))
    {
      out_i[i + j] = in_i[i];
      i += 1;
    }
    else
    {
      out_i[i + j] = in_i[size_i + j];
      j += 1;
    }

  }

}

long long normalize(long long *array, size_t *n, size_t *m)
{
  size_t i;
  size_t j;
  size_t sz = (m) ? ((*n) + (*m)) : (*n);
  size_t prev_n;
  long long *tmp;
  size_t *indices = (size_t *) malloc(((sizeof(size_t)) * sz) * 2);
  long long max_value = 0;
  long long found;
  long long prev;
  for (i = 0; i < sz; i++)
    indices[sz + i] = i;

  sort_indices(array, indices + sz, indices, sz);
  for (i = 0; (i < (sz - 1)) && m; i++)
  {
    if (array[indices[i]] != array[indices[i + 1]])
    {
      indices[i] = -1;
      if (i == (sz - 2))
      {
        indices[i + 1] = -1;
      }
      else
      {
        
      }

    }
    else
    {
      found = 0;
      for (j = i + 1; (j < sz) && (array[indices[j]] == array[indices[i]]); j++)
        if (((indices[i] < (*n)) && (indices[j] >= (*n))) || ((indices[i] >= (*n)) && (indices[j] < (*n))))
      {
        found = 1;
      }
      else
      {
        
      }


      if (!found)
      {
        for (; i < j; i++)
          indices[i] = -1;

      }
      else
      {
        i = j;
      }

      i -= 1;
    }

  }

  if (m)
  {
    tmp = (long long *) malloc((sizeof(long long)) * sz);
    memset(tmp, 0, (sizeof(long long)) * sz);
  }
  else
  {
    
  }

  for (i = 0, found = 0; i < sz; i++)
  {
    if (indices[i] == (-1))
    {
      continue;
    }
    else
    {
      
    }

    if ((!found) || (array[indices[i]] != prev))
    {
      max_value += 1;
    }
    else
    {
      
    }

    found = 1;
    prev = array[indices[i]];
    if (m)
    {
      tmp[indices[i]] = max_value;
    }
    else
    {
      array[indices[i]] = max_value;
    }

  }

  if (m)
  {
    prev_n = *n;
    for (i = 0, j = 0; i < sz; i++)
    {
      if (tmp[i] == 0)
      {
        (i < prev_n) ? ((*n)--) : ((*m)--);
      }
      else
      {
        array[j++] = tmp[i];
      }

    }

    free(tmp);
  }
  else
  {
    
  }

  free(indices);
  return max_value;
}

struct solution first_problem(long long *array, size_t n)
{
  struct solution query;
  struct fenwick_tree tree;
  size_t max_value = normalize(array, &n, 0);
  size_t i;
  fenwick_tree_init(&tree, max_value + 1);
  fenwick_tree_update(&tree, 0, (struct solution){0, 1});
  for (i = 0; i < n; i++)
  {
    query = fenwick_tree_query(&tree, array[i] - 1);
    fenwick_tree_update(&tree, array[i], (struct solution){query.a + 1, query.b});
  }

  query = fenwick_tree_query(&tree, max_value);
  fenwick_tree_free(&tree);
  return query;
}

long long second_problem(long long *array, size_t n, size_t m)
{
  size_t max_value = normalize(array, &n, &m);
  size_t i;
  size_t j;
  size_t ki;
  size_t kn;
  size_t next_k;
  size_t *ks;
  struct solution query;
  struct fenwick_tree *trees;
  if ((n == 0) || (m == 0))
  {
    return 0;
  }
  else
  {
    
  }

  ks = (size_t *) malloc((sizeof(size_t)) * m);
  trees = (struct fenwick_tree *) malloc((sizeof(struct fenwick_tree)) * m);
  for (i = 0; i < m; i++)
  {
    fenwick_tree_init(&trees[i], max_value + 1);
    fenwick_tree_update(&trees[i], 0, (struct solution){0, 1});
  }

  for (i = 0; i < n; i++)
  {
    for (j = 0, kn = 0; j < m; j++)
      if (array[i] == array[n + j])
    {
      ks[kn++] = j;
    }
    else
    {
      
    }


    for (ki = 0; ki < kn; ki++)
    {
      next_k = (ki < (kn - 1)) ? (ks[ki + 1]) : (m);
      query = fenwick_tree_query(&trees[ks[ki]], array[i] - 1);
      for (j = ks[ki]; j < next_k; j++)
        fenwick_tree_update(&trees[j], array[i], (struct solution){query.a + 1, query.b});

    }

  }

  query = fenwick_tree_query(&trees[m - 1], max_value);
  for (i = 0; i < m; i++)
    fenwick_tree_free(&trees[i]);

  free(trees);
  free(ks);
  return query.a;
}

struct vector
{
  long long *array;
  size_t size;
  size_t capacity;
};
void vector_init(struct vector *vector, size_t capacity)
{
  vector->array = (long long *) malloc((sizeof(long long)) * capacity);
  vector->size = 0;
  vector->capacity = capacity;
}

void vector_free(struct vector *vector)
{
  free(vector->array);
}

void vector_push(struct vector *vector, long long value)
{
  if (vector->size == vector->capacity)
  {
    vector->capacity *= 2;
    vector->array = (long long *) realloc(vector->array, (sizeof(long long)) * vector->capacity);
  }
  else
  {
    
  }

  vector->array[vector->size++] = value;
}

size_t read_vector(struct vector *vector)
{
  size_t count = 1;
  char c;
  vector_push(vector, 0);
  for (;;)
  {
    c = getchar();
    if ((c == '\n') || (c == EOF))
    {
      break;
    }
    else
    {
      
    }

    if (c == ' ')
    {
      vector_push(vector, 0);
      count += 1;
    }
    else
    {
      vector->array[vector->size - 1] = ((vector->array[vector->size - 1] * 10) + c) - '0';
    }

  }

  return count;
}

int main(int argc, char **argv)
{
  struct vector vector;
  struct solution solution;
  size_t p;
  size_t n;
  size_t m;
  if (!1)
  {
    return 1;
  }
  else
  {
    p = new_sym_var(sizeof(size_t) * 8);
    
  }

  vector_init(&vector, 16);
  if (p == 1)
  {
    n = read_vector(&vector);
    solution = first_problem(vector.array, n);
    printf("%lld %lld\n", solution.a, solution.b);
  }
  else
  {
    if (p == 2)
    {
      n = read_vector(&vector);
      m = read_vector(&vector);
      printf("%lld\n", second_problem(vector.array, n, m));
    }
    else
    {
      
    }

  }

  vector_free(&vector);
  return 0;
}
