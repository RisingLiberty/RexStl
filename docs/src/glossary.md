# Dictionary

## abbreviations
| abbreviation | full word |
|--------------|-----------|
| calc | calculate |
| impl | implementation |
| init | initialise |

## Important differences between words
In the coding worlds data types and byte size are closely related, but they're not the same.
a byte is not the same as a char, a word is not the same as a short.
bytes, words, dwords are different __sizes__, chars, shorts, int, are different __types__.

therefore be careful which word you use and where you use it.

| size | type |
| ---- | ---- |
| byte | char |
| word | short |
| dword | int |

## common used words and their meaning

__Acquire__ <br/>
type: prefix <br/>
Getting access to something you otherwise don't have access to. Useful to get access to members that are otherwise private. <br/>
eg. acquire_node(Iterator) - declared a friend of the class so it can acquire the private member "m_node".


