# String-ADT

This project employs 6 different functions that work with the String abstract data type

UTString* utstrdup where src is a UTstring. Creates a UTString on the heap that holds a copy of source, setting the length, capacity, 
and check appropriately. Returns a pointer to the UTString. 

uint32_t utstrlen where src is a UTString. Finds and returns the length of the string. 

UTString* utstrcat appends characters to s from suffix until out of capacity or done copying. Does not copy 
more than can be stored. Returns s after appending. 

UTString* utstrcpy replace characters in dst with characters from src until out of capacity or done 
copying. Does not copy more than can be stored. Returns dst after copying.

void utstrfree is used to free a UTString. Similar to the C stdlib function free. 
Deallocates both the string buffer and the UTString itself.

UTString* utstrrealloc used to reallocate space for a UTString. Similar to the C stdlib function realloc. If new_capacity is larger than the current 
capacity, it creates a buffer with new_capacity capacity, copies all the old contents, and deallocates 
the old buffer. Otherwise, it does nothing, either way the function returns s.
