# Allocator Traits

Allocator and Allocator traits has changed quite a bit over the years and it's hard to following which standard to follow now. That's why Rex Standard Library went to google to look up a proper definition of "Traits" and came up with this:
"a distinguishing quality or characteristic, typically one belonging to a person."

Going to one of its synonyms, more precisely Property, we get the following definition: "an attribute, quality, or characteristic of something."

With this in mind, allocator traits are defined as structures holding member types uses by systems using allocators. You can think of them as a structure combining all member types, however, logic is tied to an allocator. 

the C++20 Standard removed the member functions "address", "max_size", "construct" and "destroy" from the allocator class, however, due to the decision made above, we will keep these functions in allocator classes. However, address member function is superseded by addressof global function, which is why this function is not implemented in rtl allocators.