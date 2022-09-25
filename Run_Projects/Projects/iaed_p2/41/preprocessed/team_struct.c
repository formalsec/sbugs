/*File generated by PreProcessor.py*/


#include "team_struct.h"


void init_tree(team_node *node)
{
  *node = 0;
}

void free_teams(team_node node)
{
  if (node != 0)
  {
    free_teams(node->left);
    free_teams(node->right);
    free_team(node->team);
    free(node);
  }
  else
  {
    
  }

}

int height(team_node node)
{
  if (node == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return node->height;
}

int max(int a, int b)
{
  return (a > b) ? (a) : (b);
}

team_node node_create(team team)
{
  team_node node = (team_node) malloc(sizeof(struct t_node));
  node->team = team;
  node->left = 0;
  node->right = 0;
  node->height = 1;
  return node;
}

team_node rotate_right(team_node node)
{
  team_node auxiliar_node = node->left;
  team_node temporary = auxiliar_node->right;
  auxiliar_node->right = node;
  node->left = temporary;
  node->height = max(height(node->left), height(node->right)) + 1;
  auxiliar_node->height = max(height(auxiliar_node->left), height(auxiliar_node->right)) + 1;
  return auxiliar_node;
}

team_node rotate_left(team_node node)
{
  team_node auxiliar_node = node->right;
  team_node temporary = auxiliar_node->left;
  auxiliar_node->left = node;
  node->right = temporary;
  node->height = max(height(node->left), height(node->right)) + 1;
  auxiliar_node->height = max(height(auxiliar_node->left), height(auxiliar_node->right)) + 1;
  return auxiliar_node;
}

int getBalanceFactor(team_node node)
{
  if (node == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return height(node->left) - height(node->right);
}

team_node team_insert(team_node node, team team)
{
  int balance;
  if (node == 0)
  {
    return node_create(team);
  }
  else
  {
    
  }

  if (strcmp(team->name, node->team->name) < 0)
  {
    node->left = team_insert(node->left, team);
  }
  else
  {
    if (strcmp(team->name, node->team->name) > 0)
    {
      node->right = team_insert(node->right, team);
    }
    else
    {
      return node;
    }

  }

  node->height = 1 + max(height(node->left), height(node->right));
  balance = getBalanceFactor(node);
  if ((balance > 1) && (strcmp(team->name, node->left->team->name) < 0))
  {
    return rotate_right(node);
  }
  else
  {
    
  }

  if ((balance < (-1)) && (strcmp(team->name, node->right->team->name) > 0))
  {
    return rotate_left(node);
  }
  else
  {
    
  }

  if ((balance > 1) && (strcmp(team->name, node->left->team->name) > 0))
  {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  }
  else
  {
    
  }

  if ((balance < (-1)) && (strcmp(team->name, node->right->team->name) < 0))
  {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }
  else
  {
    
  }

  return node;
}

void insert_team(team_node *node, team team)
{
  *node = team_insert(*node, team);
}

void print_inorder(team_node node, int m, int NL)
{
  if (node != 0)
  {
    print_inorder(node->left, m, NL);
    if (node->team->score == m)
    {
      print_team(node->team, NL);
    }
    else
    {
      
    }

    print_inorder(node->right, m, NL);
  }
  else
  {
    
  }

}

void in_order(team_node *node, int m, int NL)
{
  print_inorder(*node, m, NL);
}

team_node search(team_node node, char *name)
{
  if (node == 0)
  {
    return 0;
  }
  else
  {
    
  }

  if (strcmp(name, node->team->name) == 0)
  {
    return node;
  }
  else
  {
    
  }

  if (strcmp(name, node->team->name) < 0)
  {
    return search(node->left, name);
  }
  else
  {
    return search(node->right, name);
  }

}

team_node search_team(team_node *node, char *name)
{
  return search(*node, name);
}

int victories(team_node node)
{
  int r;
  int r_left;
  int r_right;
  if (node == 0)
  {
    return -1;
  }
  else
  {
    
  }

  r = node->team->score;
  r_left = victories(node->left);
  r_right = victories(node->right);
  if (r_left > r)
  {
    r = r_left;
  }
  else
  {
    
  }

  if (r_right > r)
  {
    r = r_right;
  }
  else
  {
    
  }

  return r;
}

