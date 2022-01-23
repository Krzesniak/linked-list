//
// Created by peter on 23.01.2022.
//

#include "SortingLinkedList.h"

void SortingLinkedList::swap(CarNode *a, CarNode *b) {
    auto temp = a->getCar();
    a->setCar(b->getCar());
    b->setCar(temp);
}

void SortingLinkedList::bubbleSort(CarNode *start) {
    int swapped, i;
    CarNode *ptr1;
    CarNode *lptr = nullptr;

    /* Checking for empty list */
    if (start == nullptr)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->getNext() != lptr)
        {
            if (ptr1->getCar()->getPrice() > ptr1->getNext()->getCar()->getPrice())
            {
                swap(ptr1, ptr1->getNext());
                swapped = 1;
            }
            ptr1 = ptr1->getNext();
        }
        lptr = ptr1;
    }
    while (swapped);

}
