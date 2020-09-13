/*
 * Author: Harshit Vadodaria
 * Date: 9/9/2020.
*/

#ifndef CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP
#define CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP

#define DEQUE_GROWTH_FACTOR     1.5
#define DEQUE_INITIAL_CAPACITY  10

#include <stdlib.h>

#define Deque_DEFINE(t)
    struct Deque_##t;

    std::size_t  Deque_##t##_size(Deque_##t *);
    void Deque_##t##_push_front(Deque_##t *, t);
    void Deque_##t##_push_back(Deque_##t *, t);
    t    Deque_##t##_pop_front(Deque_##t *);
    t    Deque_##t##_pop_back(Deque_##t *);
    int  Deque_##t##_begin(Deque_##t *);
    int  Deque_##t##_end(Deque_##t *);
    bool Deque_##t##_is_full(Deque_##t *);
    bool Deque_##t##_is_empty(Deque_##t *);
    void Deque_##t##_resize(Deque_##t *);

    struct Deque_##t {
        /* Data Members: */
        t *data;
        int _size = 0, _capacity = 10, _front = 9, _back = 0;
        const char type_name[] = #t;

        /* Functions: */
        std::size_t  (*size)(Deque_##t *) = &Deque_##t##_size;
        t    at(Deque_##t, int);
        void (*push_front)(Deque_##t *, t) = &Deque_##t##_push_front;
        void (*push_back)(Deque_##t *, t) = &Deque_##t##_push_back;
        t    (*pop_front)(Deque_##t *) = &Deque_##t##_pop_front;
        t    (*pop_back)(Deque_##t *) = &Deque_##t##_pop_back;
        int  (*begin)(Deque_##t *) = &Deque_##t##_begin;
        int  (*end)(Deque_##t *) = &Deque_##t##_end;
        bool (*empty)(Deque_##t *) = &Deque_##t##_is_empty;
        bool (*full)(Deque_##t *) = &Deque_##t##_is_full;
        void (*_resize)(Deque_##t *) = &Deque_##t##_resize;

        bool (*comparator)(const t, const t);
    };
    Deque_##t##_ctor( Deque_##t *q, bool (*comparator)(const t o1, const t o2) ) {
        q->data = malloc(sizeof(t) * DEQUE_INITIAL_CAPACITY );
        q->comparator = comparator;
    }
    std::size_t Deque_##t##_size(Deque_##t *q) {
        return q->_size;
    }
    t at(Deque_##t q, int idx) {
        return q->data[idx];
    }
    bool Deque_##t##_is_empty(Deque_##t *q) {
        return q->size() == 0;
    }
    bool Deque_##t##_is_full(Deque_##t *q) {
        return q->_capacity == q->_size;
    }
    void &Deque_##t##_push_back(Deque_##t *q, t data) {
        if (q->full())
            q->resize();
        q->data[q->_back++] = data;
        q->_size++;
        if (q->_back >= q->_capacity)
            q->_back = 0;
    }
    void &Deque_##t##_push_front(Deque_##t *q, t data) {
        if (q->full())
            q->resize();
        if (q->_front == 0)
            q->_front = q->_capacity - 1;
        q->data[--q->_front] = data;
        q->_size++;
    }
    t &Deque_##t##_pop_back(Deque_##t *q) {
        if ( q->_back == 0 )
            q->_back = q->_capacity;
        q->_size--;
        return q->data[--q->_back];
    }
    t &Deque_##t##_pop_back(Deque_##t *q) {
        if ( q->_front >= q->_capacity )
            q->_front = 0;
        q->_size--;
        return q->data[q->_front++];
    }
    void Deque_##t##_resize(Deque_##t *q) {
        q->data = realloc(q->data, (q->capacity *= DEQUE_GROWTH_FACTOR));
        for (int i = 0)
    }




#endif //CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP
