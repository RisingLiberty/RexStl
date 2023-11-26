#include "rex_std/forward_list.h"

namespace rsl
{
  inline namespace v1
  {
    namespace internal
    {
      forward_list_node_base* forward_lst_node_base_get_previous(forward_list_node_base* node_base, const forward_list_node_base* node)
      {
        while (node_base && (node_base->next != node))
        {
          node_base = node_base->next;
        }
        return node_base;
      }

      const forward_list_node_base* forward_lst_node_base_get_previous(const forward_list_node_base* node_base, const forward_list_node_base* node)
      {
        while (node_base && (node_base->next != node))
        {
          node_base = node_base->next;
        }
        return node_base;
      }
    }
  }
}