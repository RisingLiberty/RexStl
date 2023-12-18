#include "rex_std/forward_list.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      forward_list_node_base* forward_list_node_base_get_previous(forward_list_node_base* nodeBase, const forward_list_node_base* node)
      {
        while(nodeBase && (nodeBase->next != node)) // NOLINT(readability-implicit-bool-conversion)
        {
          nodeBase = nodeBase->next;
        }
        return nodeBase;
      }

      const forward_list_node_base* forward_list_node_base_get_previous(const forward_list_node_base* nodeBase, const forward_list_node_base* node)
      {
        while(nodeBase && (nodeBase->next != node)) // NOLINT(readability-implicit-bool-conversion)
        {
          nodeBase = nodeBase->next;
        }
        return nodeBase;
      }

      void forward_list_node_splice_after(forward_list_node_base* pNode, forward_list_node_base* pNodeBeforeFirst, forward_list_node_base* pNodeBeforeLast)
      {
        if((pNode != pNodeBeforeFirst) && (pNode != pNodeBeforeLast))
        {
          forward_list_node_base* const first    = pNodeBeforeFirst->next;
          forward_list_node_base* const position = pNode->next;

          pNodeBeforeFirst->next = pNodeBeforeLast->next;
          pNode->next            = first;
          pNodeBeforeLast->next  = position;
        }
      }

      void forward_list_node_splice_single_after(forward_list_node_base* pNode, forward_list_node_base* otherHead, forward_list_node_base* toMove)
      {
        if(pNode != toMove && pNode != toMove->next)
        {
          forward_list_node_base* const node_before_to_move = forward_list_node_base_get_previous(otherHead, toMove);
          node_before_to_move->next                         = toMove->next; // unlink from original list

          // insert into our list
          toMove->next = pNode->next;
          pNode->next  = toMove;
        }
      }

      forward_list_node_base* reverse_list(forward_list_node_base* node)
      {
        forward_list_node_base* first_node = node;
        node                               = node->next;
        first_node->next                   = nullptr;
        while(node) // NOLINT(readability-implicit-bool-conversion)
        {
          forward_list_node_base* tmp = node->next;
          node->next                  = first_node;
          first_node                  = node;
          node                        = tmp;
        }

        return first_node;
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl