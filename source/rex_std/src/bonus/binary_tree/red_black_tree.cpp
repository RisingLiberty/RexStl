#include "rex_std/bonus/binary_tree/red_black_tree.h"
#include "rex_std/assert.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {

      RedBlackTreeNodeBase* red_black_tree_min_child(const RedBlackTreeNodeBase* nodeBase)
      {
        while (nodeBase->left_node)
        {
          nodeBase = nodeBase->left_node;
        }
        return const_cast<RedBlackTreeNodeBase*>(nodeBase);
      }
      RedBlackTreeNodeBase* red_black_tree_max_child(const RedBlackTreeNodeBase* nodeBase)
      {
        while (nodeBase->right_node)
        {
          nodeBase = nodeBase->right_node;
        }
        return const_cast<RedBlackTreeNodeBase*>(nodeBase);
      }

      void red_black_tree_insert(RedBlackTreeNodeBase* node, RedBlackTreeNodeBase* nodeParent, RedBlackTreeNodeBase* nodeAnchor, internal::RedBlackTreeSide insertionSide)
      {
        RedBlackTreeNodeBase*& node_root_ref = nodeAnchor->parent_node;

        node->parent_node = nodeParent;
        node->right_node = nullptr;
        node->left_node = nullptr;
        node->color = internal::RedBlackTreeColor::Red;

        if (insertionSide == internal::RedBlackTreeSide::Left)
        {
          nodeParent->left_node = node;

          if (nodeParent == nodeAnchor)
          {
            nodeAnchor->parent_node = node;
            nodeAnchor->right_node = node;
          }
          else if (nodeParent == nodeAnchor->left_node)
          {
            nodeAnchor->left_node = node;
          }
        }
        else
        {
          nodeParent->right_node = node;

          if (nodeParent == nodeAnchor->right_node)
          {
            nodeAnchor->right_node = node;
          }
        }

        while ((node != node_root_ref) && (node->parent_node->color == internal::RedBlackTreeColor::Red))
        {
          RSL_ASSERT_X(node->parent_node != nullptr, "inserting a node without a parent");
          RedBlackTreeNodeBase* node_parent_parent = node->parent_node->parent_node;

          if (node->parent_node == node_parent_parent->left_node)
          {
            RedBlackTreeNodeBase* temp_node = node_parent_parent->right_node;

            if (temp_node && (temp_node->color == internal::RedBlackTreeColor::Red))
            {
              node->parent_node->color = internal::RedBlackTreeColor::Black;
              temp_node->color = internal::RedBlackTreeColor::Black;
              node_parent_parent->color = internal::RedBlackTreeColor::Red;
              node = node_parent_parent;
            }
            else
            {
              if (node->parent_node && node == node->parent_node->right_node)
              {
                node = node->parent_node;
                node_root_ref = red_black_tree_rotate_left(node, node_root_ref);
              }

              RSL_ASSERT_X(node->parent_node != nullptr, "inserting a node without a parent");
              node->parent_node->color = RedBlackTreeColor::Black;
              node_parent_parent->color = RedBlackTreeColor::Red;
              node_root_ref = red_black_tree_rotate_right(node_parent_parent, node_root_ref);
            }
          }
          else
          {
            RedBlackTreeNodeBase* temp_node = node_parent_parent->left_node;

            if (temp_node && (temp_node->color == internal::RedBlackTreeColor::Red))
            {
              node->parent_node->color = internal::RedBlackTreeColor::Black;
              temp_node->color = internal::RedBlackTreeColor::Black;
              node_parent_parent->color = internal::RedBlackTreeColor::Red;
              node = node_parent_parent;
            }
            else
            {
              RSL_ASSERT_X(node != nullptr && node->parent_node != nullptr, "invalid node");

              if (node == node->parent_node->left_node)
              {
                node = node->parent_node;
                node_root_ref = red_black_tree_rotate_right(node, node_root_ref);
              }

              node->parent_node->color = internal::RedBlackTreeColor::Black;
              node_parent_parent->color = internal::RedBlackTreeColor::Red;
              node_root_ref = red_black_tree_rotate_left(node_parent_parent, node_root_ref);
            }
          }

        }

        RSL_ASSERT_X(node_root_ref != nullptr, "invalid node root");
				node_root_ref->color = internal::RedBlackTreeColor::Black;
      }

      // returns the next item in a sorted red-black tree
      RedBlackTreeNodeBase* red_black_tree_increment(const RedBlackTreeNodeBase* node)
      {
        if (node->right_node)
        {
          node = node->right_node;

          while (node->left_node)
          {
            node = node->left_node;
          }
        }
        else
        {
          RedBlackTreeNodeBase* temp_node = node->parent_node;

          while (node == temp_node->right_node)
          {
            node = temp_node;
            temp_node = temp_node->parent_node;
          }

          if (node->right_node != temp_node)
          {
            node = temp_node;
          }
        }

        return const_cast<RedBlackTreeNodeBase*>(node);
      }

      // returns the previous item in a sorted red-black tree
      RedBlackTreeNodeBase* red_black_tree_decrement(const RedBlackTreeNodeBase* node)
      {
        if ((node->parent_node->parent_node == node) && (node->color == internal::RedBlackTreeColor::Red))
        {
          return node->right_node;
        }
        else if (node->left_node)
        {
          RedBlackTreeNodeBase* temp_node = node->left_node;

          while (temp_node->right_node)
          {
            temp_node = temp_node->right_node;
          }

          return temp_node;
        }

        RedBlackTreeNodeBase* temp_node = node->parent_node;

        while (node == temp_node->left_node)
        {
          node = temp_node;
          temp_node = temp_node->parent_node;
        }

        return const_cast<RedBlackTreeNodeBase*>(temp_node);
      }

      count_t red_black_tree_black_count(const RedBlackTreeNodeBase* top_node, const RedBlackTreeNodeBase* bottom_node)
      {
        count_t count = 0;

        for (; bottom_node; bottom_node = bottom_node->parent_node)
        {
          if (bottom_node->color == internal::RedBlackTreeColor::Black)
          {
            ++count;
          }

          if (bottom_node == top_node)
          {
            break;
          }
        }

        return count;
      }

      RedBlackTreeNodeBase* red_black_tree_rotate_left(RedBlackTreeNodeBase* node, RedBlackTreeNodeBase* root_node)
      {
        RedBlackTreeNodeBase* temp_node = node->right_node;

        node->right_node = temp_node->left_node;

        if (temp_node->left_node)
        {
          temp_node->left_node->parent_node = node;
        }
        temp_node->parent_node = node->parent_node;

        if (node == root_node)
        {
          root_node = temp_node;
        }
        else if (node == node->parent_node->left_node)
        {
          node->parent_node->left_node = temp_node;
        }
        else
        {
          node->parent_node->right_node = temp_node;
        }

        temp_node->left_node = node;
        node->parent_node = temp_node;

        return root_node;
      }

      RedBlackTreeNodeBase* red_black_tree_rotate_right(RedBlackTreeNodeBase* node, RedBlackTreeNodeBase* root_node)
      {
        RedBlackTreeNodeBase* temp_node = node->left_node;

        node->left_node = temp_node->right_node;

        if (temp_node->right_node)
        {
          temp_node->right_node->parent_node = node;
        }
        temp_node->parent_node = node->parent_node;

        if (node == root_node)
        {
          root_node = temp_node;
        }
        else if (node == node->parent_node->right_node)
        {
          node->parent_node->right_node = temp_node;
        }
        else
        {
          node->parent_node->left_node = temp_node;
        }

        temp_node->right_node = node;
        node->parent_node = temp_node;

        return root_node;
      }

      void red_black_tree_erase(RedBlackTreeNodeBase* node, RedBlackTreeNodeBase* nodeAnchor)
      {
        RedBlackTreeNodeBase*& node_root_ref = nodeAnchor->parent_node;
        RedBlackTreeNodeBase*& node_leftmost_ref = nodeAnchor->left_node;
        RedBlackTreeNodeBase*& node_rightmost_ref = nodeAnchor->right_node;
        RedBlackTreeNodeBase* node_successor = node;
        RedBlackTreeNodeBase* child_node = nullptr;
        RedBlackTreeNodeBase* child_node_parent = nullptr;

        if (node_successor->left_node == nullptr)
        {
          child_node = node_successor->right_node;
        }
        else if (node_successor->right_node == nullptr)
        {
          child_node = node_successor->left_node;
        }
        else
        {
          node_successor = node_successor->right_node;

          while (node_successor->left_node)
          {
            node_successor = node_successor->left_node;
          }

          child_node = node_successor->right_node;
        }

        // here we remove node from the tree and fix up the node pointers appropriately around it
        if (node_successor == node)
        {
          child_node_parent = node_successor->parent_node;

          if (child_node)
          {
            child_node->parent_node = node_successor->parent_node;
          }

          if (node == node_root_ref)
          {
            node_root_ref = child_node;
          }
          else
          {
            if (node == node->parent_node->left_node)
            {
              node->parent_node->left_node = child_node;
            }
            else
            {
              node->parent_node->right_node = child_node;
            }
          }

          if (node == node_leftmost_ref)
          {
            if (node->right_node && child_node)
            {
              RSL_ASSERT_X(child_node != nullptr, "there should always be a child node");
              node_leftmost_ref = red_black_tree_min_child(child_node);
            }
            else
            {
              node_leftmost_ref = node->parent_node;
            }
          }

          if (node == node_rightmost_ref)
          {
            if (node->left_node && child_node)
            {
              RSL_ASSERT_X(child_node != nullptr, "there should always be a child node");
              node_rightmost_ref = red_black_tree_max_child(child_node);
            }
            else
            {
              node_rightmost_ref = node->parent_node;
            }
          }
        }
        else
        {
          node->left_node->parent_node = node_successor;
          node_successor->left_node = node->left_node;

          if (node_successor == node->right_node)
          {
            child_node_parent = node_successor;
          }
          else
          {
            child_node_parent = node_successor->parent_node;

            if (child_node)
            {
              child_node->parent_node = child_node_parent;
            }

            child_node_parent->left_node = child_node;

            node_successor->right_node = node->right_node;
            node->right_node->parent_node = node_successor;
          }

          if (node == node_root_ref)
          {
            node_root_ref = node_successor;
          }
          else if (node == node->parent_node->left_node)
          {
            node->parent_node->left_node = node_successor;
          }
          else
          {
            node->parent_node->right_node = node_successor;
          }

          // now node is disconnected from the tree
          node_successor->parent_node = node->parent_node;
          ::rsl::swap(node_successor->color, node->color);
        }

        // here we do tree balancing as per the conventional red-black tree algorithm
        if (node->color == internal::RedBlackTreeColor::Black)
        {
          while ((child_node != node_root_ref) && ((child_node == nullptr) || (child_node->color == internal::RedBlackTreeColor::Black)))
          {
            if (child_node == child_node_parent->left_node)
            {
              RedBlackTreeNodeBase* temp_node = child_node_parent->right_node;

              if (temp_node->color == internal::RedBlackTreeColor::Red)
              {
                temp_node->color = internal::RedBlackTreeColor::Black;
                child_node_parent->color = internal::RedBlackTreeColor::Red;
                node_root_ref = red_black_tree_rotate_left(child_node_parent, node_root_ref);
                temp_node = child_node_parent->right_node;
              }

              if (((temp_node->left_node == nullptr) || (temp_node->left_node->color == internal::RedBlackTreeColor::Black)) && ((temp_node->right_node == nullptr) || (temp_node->right_node->color == internal::RedBlackTreeColor::Black)))
              {
                temp_node->color = internal::RedBlackTreeColor::Red;
                child_node = child_node_parent;
                child_node_parent = child_node_parent->parent_node;
              }
              else
              {
                if ((temp_node->right_node == nullptr) || (temp_node->right_node->color == internal::RedBlackTreeColor::Black))
                {
                  temp_node->left_node->color = internal::RedBlackTreeColor::Black;
                  temp_node->color = internal::RedBlackTreeColor::Red;
                  node_root_ref = red_black_tree_rotate_right(temp_node, node_root_ref);
                  temp_node = child_node_parent->right_node;
                }

                temp_node->color = child_node_parent->color;
                child_node_parent->color = internal::RedBlackTreeColor::Black;

                if (temp_node->right_node)
                {
                  temp_node->right_node->color = internal::RedBlackTreeColor::Black;
                }

                node_root_ref = red_black_tree_rotate_left(child_node_parent, node_root_ref);
                break;
              }
            }
            else
            {
              RedBlackTreeNodeBase* temp_node = child_node_parent->left_node;

              if (temp_node->color == internal::RedBlackTreeColor::Red)
              {
                temp_node->color = internal::RedBlackTreeColor::Black;
                child_node_parent->color = internal::RedBlackTreeColor::Red;

                node_root_ref = red_black_tree_rotate_right(child_node_parent, node_root_ref);
                temp_node = child_node_parent->left_node;
              }

              if (((temp_node->right_node == nullptr) || (temp_node->right_node->color == internal::RedBlackTreeColor::Black)) && ((temp_node->left_node == nullptr) || (temp_node->left_node->color == internal::RedBlackTreeColor::Black)))
              {
                temp_node->color = internal::RedBlackTreeColor::Red;
                child_node = child_node_parent;
                child_node_parent = child_node_parent->parent_node;
              }
              else
              {
                if ((temp_node->left_node == nullptr) || (temp_node->left_node->color == internal::RedBlackTreeColor::Black))
                {
                  temp_node->right_node->color = internal::RedBlackTreeColor::Black;
                  temp_node->color = internal::RedBlackTreeColor::Red;

                  node_root_ref = red_black_tree_rotate_left(temp_node, node_root_ref);
                  temp_node = child_node_parent->left_node;
                }

                temp_node->color = child_node_parent->color;
                child_node_parent->color = internal::RedBlackTreeColor::Black;

                if (temp_node->left_node)
                {
                  temp_node->left_node->color = internal::RedBlackTreeColor::Black;
                }

                node_root_ref = red_black_tree_rotate_right(child_node_parent, node_root_ref);
                break;
              }
            }
          }

          if (child_node)
          {
            child_node->color = internal::RedBlackTreeColor::Black;
          }
        }
      }

    }
  }
}