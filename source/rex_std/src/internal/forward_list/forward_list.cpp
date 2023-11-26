#include "rex_std/forward_list.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      forward_list_node_base* forward_lst_node_base_get_previous(forward_list_node_base* node_base, const forward_list_node_base* node)
      {
        while(node_base && (node_base->next != node))
        {
          node_base = node_base->next;
        }
        return node_base;
      }

      const forward_list_node_base* forward_lst_node_base_get_previous(const forward_list_node_base* node_base, const forward_list_node_base* node)
      {
        while(node_base && (node_base->next != node))
        {
          node_base = node_base->next;
        }
        return node_base;
      }

      void forward_list_node_splice_after(forward_list_node_base* pNode, forward_list_node_base* pNodeBeforeFirst, forward_list_node_base* pNodeBeforeLast)
      {
        if ((pNode != pNodeBeforeFirst) && (pNode != pNodeBeforeLast))
        {
          forward_list_node_base* const pFirst = pNodeBeforeFirst->next;
          forward_list_node_base* const pPosition = pNode->next;

          pNodeBeforeFirst->next = pNodeBeforeLast->next;
          pNode->next = pFirst;
          pNodeBeforeLast->next = pPosition;
        }
      }

      void forward_list_node_splice_after(forward_list_node_base* pNode, forward_list_node_base* pNodeBase)
      {
        forward_list_node_base* const pNodeBeforeLast = forward_lst_node_base_get_previous(pNodeBase, NULL);

        if (pNodeBeforeLast != pNodeBase)
        {
          forward_list_node_base* const pPosition = pNode->next;
          pNode->next = pNodeBase->next;
          pNodeBase->next = NULL;
          pNodeBeforeLast->next = pPosition;
        }
      }

      forward_list_node_base* reverse_list(forward_list_node_base* node)
      {
        forward_list_node_base* head = node;
        forward_list_node_base* next = head->next;
        head->next = nullptr;
        while (next)
        {
          forward_list_node_base* tmp = next;
          next = head;
          head = node;
          node = tmp;
        }

        return head;
      }
    } // namespace internal
  }   // namespace v1
} // namespace rsl