#include "pagetable.h"

/*
 create a stack to keep track of free frames
 can push pop onto stack as frames become occupied or are freed up
 the framenumber that is pushed to the stack can be used as the key to enter into a map
 
 could have two maps, one with {framenum, pagenum} and  {pagenum, pte}
 
 when you need to search for a page, you can just search in the map {pagenum, pte}
 if you need to replace it, then you can push the framenum to the free frame stack, then in the two maps zero them out?

*/

bool PageTable::is_entry_in_table(int val){
    for (PageEntry entry : pages) {
        if (entry.page_number == val) {
            return true;
        }
    }
    return false;
}

int PageTable::index_of_entry(int val){
    for (int i = 0; i < pages.size(); ++i) {
        if(pages[i].frame_num == val) {
            return i;
        }
    }
    return -1;
}


/*
 * One function that would handle page replacement, takes in an enum to specify what alrogithm to use for page replacement.
 */
void PageTable::replace_page(algorithmType alg){}


PageEntry::PageEntry(){
    frame_num = 0;
    valid = false;
    dirty = false;
}