#include "List.hpp"

    List::List() {
        meeleeHead = NULL;
        rangedHead = NULL;
    }

    // getters
    List::meeleeList* List::getMeeleeHead() { return meeleeHead; }
    List::rangedList* List::getRangedHead() { return rangedHead; }

    // list functions

    // aggiunta di nemici meelee
    void List::addMeelee(Meelee meelee) {
        meeleeList* newMeelee = new meeleeList(meelee);
        newMeelee->next = meeleeHead;
        meeleeHead = newMeelee;
    }

    // aggiunta di nemici ranged
    void List::addRanged(Ranged ranged) {
        rangedList* newRanged = new rangedList(ranged);
        newRanged->next = rangedHead;
        rangedHead = newRanged;
    }

    // rimozione di nemici meelee
    void List::removeMeelee(int x, int y) {
        meeleeList* current = meeleeHead;
        meeleeList* previous = NULL;
        while (current != NULL) {
            if (current->meelee.getPositionX() == x
                && current->meelee.getPositionY() == y) {
                if (previous == NULL) {
                    meeleeHead = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // rimozione di nemici ranged
    void List::removeRanged(int x, int y) {
        rangedList* current = rangedHead;
        rangedList* previous = NULL;
        while (current != NULL) {
            if (current->ranged.getPositionX() == x
                && current->ranged.getPositionY() == y) {
                if (previous == NULL) {
                    rangedHead = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }