/*
main.cpp
Programmers Name: Evan Smith, Andrew Tse
Date Written: 11/29/19
Course: CS 433 Assignment 5
Summary: This program simulates page replacement algorithms
Assumptions:

How To Run Program:
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include "pagetable.h"

using namespace std;

#define NEC_ARG_COUNT 4
#define LINE_SIZE 256


// Check if an integer is power of 2
bool isPowerOfTwo(int x) {
    /* First x in the below expression is for the case when x is 0 */
    return x && (!(x & (x - 1)));
}

int main(int argc, char **argv) {

    int page_size, phys_mem_size, page_number, frame_number, page_fault;

    printf("============================================================================ \n");
    printf("CS 433: Assignment 5 \n");
    printf("Authors: Evan Smith & Andrew Tse \n");
    printf("Date: 11/29/19 \n");
    printf("Course: CS 433 (Operating Systems) \n");
    printf("Description: Analysis of Page Replacement Algorithms\n");
    printf("============================================================================ \n");
    cout << endl;

    if (argc != NEC_ARG_COUNT) {
        cout << "two command-line arguments:\n";
        cout << "- the page size (in bytes): between 256 and 8192, inclusive \n";

        //this is for testing
        cout << "\n\n";
        cout << "Enter page size: ";
        cin >> page_size;
        cout << "Phys memory: ";
        cin >> phys_mem_size;
    } else {
        /*
         * The page size must be a number of power of 2 between 256 (2^8) and 8192 (2^13) bytes inclusively
         * The physical memory size is also a power of 2 between 4 MB (2^22) and 64 MB (2^26).
        */
        page_size = atoi(argv[1]);
        phys_mem_size = atoi(argv[2]) << 20;
    }


    //some error handling for page size and phys memory size.
    if (!isPowerOfTwo(page_size)) {
        cout << "You have entered an invalid parameter for page size (bytes)" << endl;
        cout << "  (must be an power of 2 between 256 and 8192, inclusive)." << endl;
        return 1;
    }
    if (!isPowerOfTwo(phys_mem_size)) {
        cout << "You have entered an invalid parameter for physical memory size (MB)" << endl;
        cout << "  (must be an even integer between 4 and 64, inclusive)." << endl;
        return 1;
    }

    // calculate number of pages and frames;
    int logic_mem_bits = 27;        // 27-bit logical memory (128 MB logical memory assumed by the assignment)
    int phys_mem_bits = log2(phys_mem_size);       // Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
    int page_offset_bits = log2(page_size);                // Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page

    // Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
    int num_pages = 1 << (logic_mem_bits - page_offset_bits);
    // Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
    int num_frames = 1 << (phys_mem_bits - page_offset_bits);

    cout << "Page size = " << page_size << " bytes" << endl;
    cout << "Physical Memory size = " << phys_mem_size << " bytes" << endl;
    cout << "Number of pages = " << num_pages << endl;
    cout << "Number of physical frames = " << num_frames << endl;


    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
    cout << "\n================================Test 1==========================================\n";
    // TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address

    ifstream small_ref_file;
    small_ref_file.open("C:\\Users\\User\\CLionProjects\\Assignment5\\small_refs.txt");
    char line[LINE_SIZE];
    int logical_address_int, last_digit, current_entry_index, line_count, fault_count, temp_fault;
    bool temp_dirty;
    PageTable page_table;

    if (!small_ref_file.is_open()) {
        cout << "Unable to open file" << endl;
        exit(1);
    }

    while (small_ref_file.eof() == 0) {
        
        small_ref_file >> line;

        logical_address_int = stoi(line);
        last_digit = logical_address_int % 10;
        page_number = logical_address_int / page_size;

        PageEntry entry;

        //set dirty bit
        if (last_digit % 2 == 0) {
            temp_dirty = false;
        } else {
            temp_dirty = true;
        }

        //see if value exists in current page table
        if (page_table.is_entry_in_table(entry.frame_num)) {
            current_entry_index = page_table.index_of_entry(entry);
            page_table.pages[current_entry_index].dirty = temp_dirty;
            temp_fault = 0;

        } else {
            //generate page fault and place in page...
            entry.frame_num = line_count;
            entry.dirty = temp_dirty;
            entry.valid = true;
            temp_fault = 1;

            fault_count++;
        }

        line_count++;

        // output
        cout << "Logical address: " << logical_address_int << "\tPage Number: " << page_number << "\tframe number = " << line_count;
        cout << "\tis page fault? " << temp_fault << endl;
    }

    small_ref_file.close();

    //NOTE THERE SHOULD BE NO PAGE REPLACEMENTS


    // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    cout << "\n================================Test 2==========================================\n";
    //TODO: just print total number of references here:
    auto begin = std::chrono::system_clock::now();
//    ifstream logicalAddressesFile;
//    logicalAddressesFile.open("large_refs.txt");


    cout << "****************Simulate FIFO replacement****************************" << endl;
    // TODO: Add your code to calculate number of page faults using FIFO replacement algorithm
    // TODO: print the statistics and run-time


    cout << "****************Simulate Random replacement****************************" << endl;
    // TODO: Add your code to calculate number of page faults using Random replacement algorithm
    // TODO: print the statistics and run-time


    cout << "****************Simulate LRU replacement****************************" << endl;
    // TODO: Add your code to calculate number of page faults using LRU replacement algorithm
    // TODO: print the statistics and run-time



    small_ref_file.close();


}