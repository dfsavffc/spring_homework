
#include <gtest/gtest.h>

#include "bs_tree.hpp"

TEST(bs_tree, Simple) {
  BSTree<int> tree;
  tree.Insert(10);
  tree.Insert(5);
  tree.Insert(15);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(12);
  tree.Insert(17);

  ASSERT_EQ(tree.Contains(10), true);
  ASSERT_EQ(tree.Contains(5), true);
  ASSERT_EQ(tree.Contains(15), true);
  ASSERT_EQ(tree.Contains(3), true);
  ASSERT_EQ(tree.Contains(7), true);
  ASSERT_EQ(tree.Contains(12), true);
  ASSERT_EQ(tree.Contains(17), true);
  ASSERT_EQ(tree.Contains(8), false);
  ASSERT_EQ(tree.Contains(20), false);

  tree.Remove(3);
  ASSERT_EQ(tree.Contains(3), false);

  tree.Remove(15);
  ASSERT_EQ(tree.Contains(15), false);

  tree.Insert(20);
  tree.Insert(8);
  ASSERT_EQ(tree.Contains(20), true);
  ASSERT_EQ(tree.Contains(8), true);

  tree.Remove(5);
  ASSERT_EQ(tree.Contains(5), false);

  tree.Insert(1);
  tree.Insert(25);
  ASSERT_EQ(tree.Contains(1), true);
  ASSERT_EQ(tree.Contains(25), true);
}

TEST(bs_tree, DuplicateData) {
  BSTree<int> Tree;

  ASSERT_EQ(Tree.Contains(10), false);

  Tree.Insert(5);
  Tree.Remove(5);
  ASSERT_EQ(Tree.Contains(5), false);

  Tree.Insert(1);
  Tree.Insert(2);
  Tree.Insert(3);
  Tree.Remove(1);
  Tree.Remove(2);
  Tree.Remove(3);
  ASSERT_EQ(Tree.Contains(1), false);
  ASSERT_EQ(Tree.Contains(2), false);
  ASSERT_EQ(Tree.Contains(3), false);
}