//
// Created by Evan on 11/29/2019.
//

#ifndef ASSIGNMENT5_PAGETABLE_H
#define ASSIGNMENT5_PAGETABLE_H

#include <deque>

enum algorithmType {
    RANDOM, FIFO, LRU
};

class PageEntry {
public:
    // Physical frame number for a given page
    int frame_num;
    // valid bit represents whether a page is in the physical memory
    bool valid = false;
    // dirty bit represents whether a page is changed
    bool dirty = false;
    int page_number;
    PageEntry();
};


class PageTable {
public:
    bool is_entry_in_table(int frame_num);
    int index_of_entry(int frame_num);
    void replace_page(algorithmType alg);

    int size;
    std::deque<PageEntry> pages;
};


#endif //ASSIGNMENT5_PAGETABLE_H
