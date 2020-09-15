/*
 * Author: Harshit Vadodaria
 * Date: 9/9/2020.
*/

#ifndef CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP
#define CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP

#define DEQUE_GROWTH_FACTOR     1.5
#define DEQUE_INITIAL_CAPACITY  10

#include <stdlib.h>
#include <string.h>

#define Deque_DEFINE(t)                                                                             \
    struct Deque_##t;                                                                               \
    struct Deque_##t##_Iterator;                                                                    \
                                                                                                    \
    std::size_t  Deque_##t##_size(Deque_##t *);                                                     \
    t&   Deque_##t##_at(Deque_##t *, int);                                                          \
    t&   Deque_##t##_front(Deque_##t *);                                                            \
    t&   Deque_##t##_back(Deque_##t *);                                                             \
    void Deque_##t##_push_front(Deque_##t *, t);                                                    \
    void Deque_##t##_push_back(Deque_##t *, t);                                                     \
    t    Deque_##t##_pop_front(Deque_##t *);                                                        \
    t    Deque_##t##_pop_back(Deque_##t *);                                                         \
    bool Deque_##t##_is_full(Deque_##t *);                                                          \
    bool Deque_##t##_is_empty(Deque_##t *);                                                         \
    void Deque_##t##__resize(Deque_##t *);                                                          \
    bool Deque_##t##_equal(Deque_##t, Deque_##t);                                                   \
    Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *);                                            \
    Deque_##t##_Iterator  Deque_##t##_end(Deque_##t *);                                             \
    void Deque_##t##_clear(Deque_##t *q);                                                           \
    void Deque_##t##_dtor(Deque_##t *q);                                                            \
                                                                                                    \
    void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *);                                          \
    void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *);                                          \
    t&   Deque_##t##_Iterator_deref(Deque_##t##_Iterator *);                                        \
    bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator, Deque_##t##_Iterator);                    \
                                                                                                    \
    struct Deque_##t##_Iterator {                                                                   \
        int _index;                                                                                 \
        Deque_##t *deq;                                                                             \
        bool _begin;                                                                                \
        void (*inc)(Deque_##t##_Iterator *) = &Deque_##t##_Iterator_inc;                            \
        void (*dec)(Deque_##t##_Iterator *) = &Deque_##t##_Iterator_dec;                            \
        t&   (*deref)(Deque_##t##_Iterator *) = &Deque_##t##_Iterator_deref;                        \
    };                                                                                              \
    struct Deque_##t {                                                                              \
        /* Data Members: */                                                                         \
        t *data;                                                                                    \
        int _size = 0, _capacity = DEQUE_INITIAL_CAPACITY, _front = 0, _back = 0;                   \
        const char type_name[strlen(#t) + 1] = #t;                                                  \
                                                                                                    \
        /* Functions: */                                                                            \
        std::size_t  (*size)(Deque_##t *) = &Deque_##t##_size;                                      \
        t&   (*at)(Deque_##t *, int) = &Deque_##t##_at;                                             \
        t&   (* front)(Deque_##t *) = &Deque_##t##_front;                                           \
        t&   (* back)(Deque_##t *) = &Deque_##t##_back;                                             \
        void (*push_front)(Deque_##t *, t) = &Deque_##t##_push_front;                               \
        void (*push_back)(Deque_##t *, t) = &Deque_##t##_push_back;                                 \
        t    (*pop_front)(Deque_##t *) = &Deque_##t##_pop_front;                                    \
        t    (*pop_back)(Deque_##t *) = &Deque_##t##_pop_back;                                      \
        bool (*empty)(Deque_##t *) = &Deque_##t##_is_empty;                                         \
        bool (*full)(Deque_##t *) = &Deque_##t##_is_full;                                           \
        void (*_resize)(Deque_##t *) = &Deque_##t##__resize;                                        \
                                                                                                    \
        Deque_##t##_Iterator (*begin)(Deque_##t *) = &Deque_##t##_begin;                            \
        Deque_##t##_Iterator (*end)(Deque_##t *) = &Deque_##t##_end;                                \
        bool (*is_smaller)(const t&, const t&);                                                     \
                                                                                                    \
        void (*clear)(Deque_##t *) = &Deque_##t##_clear;                                            \
        void (*dtor)(Deque_##t *) = &Deque_##t##_dtor;                                              \
                                                                                                    \
    };                                                                                              \
    Deque_##t* Deque_##t##_ctor( Deque_##t *q, bool (*comparator)(const t&, const t&) ) {           \
        q->data = (t *) malloc(sizeof(t) * DEQUE_INITIAL_CAPACITY );                                \
        q->is_smaller = comparator;                                                                 \
        return q;                                                                                   \
    }                                                                                               \
    std::size_t Deque_##t##_size(Deque_##t *q) {                                                    \
        return q->_size;                                                                            \
    }                                                                                               \
    t& at(Deque_##t *q, int idx) {                                                                  \
        return q->data[idx];                                                                        \
    }                                                                                               \
    bool Deque_##t##_is_empty(Deque_##t *q) {                                                       \
        return q->size(q) == 0;                                                                     \
    }                                                                                               \
    bool Deque_##t##_is_full(Deque_##t *q) {                                                        \
        return q->_capacity == q->_size;                                                            \
    }                                                                                               \
    void Deque_##t##_push_back(Deque_##t *q, t data) {                                              \
        if (q->full(q))                                                                             \
            q->_resize(q);                                                                          \
        q->data[q->_back++] = data;                                                                 \
        q->_size++;                                                                                 \
        if (q->_back >= q->_capacity)                                                               \
            q->_back = 0;                                                                           \
    }                                                                                               \
    void Deque_##t##_push_front(Deque_##t *q, t data) {                                             \
        if (q->full(q))                                                                             \
            q->_resize(q);                                                                          \
        --q->_front;                                                                                \
        if (q->_front <= 0)                                                                         \
            q->_front = q->_capacity - 1;                                                           \
        q->data[q->_front] = data;                                                                  \
        q->_size++;                                                                                 \
    }                                                                                               \
    t Deque_##t##_pop_back(Deque_##t *q) {                                                          \
        if ( q->_back == 0 )                                                                        \
            q->_back = q->_capacity;                                                                \
        q->_size--;                                                                                 \
        return q->data[--q->_back];                                                                 \
    }                                                                                               \
    t Deque_##t##_pop_front(Deque_##t *q) {                                                         \
        if ( q->_front >= q->_capacity )                                                            \
            q->_front = 0;                                                                          \
        q->_size--;                                                                                 \
        return q->data[q->_front++];                                                                \
    }                                                                                               \
    void Deque_##t##__resize(Deque_##t *q) {                                                        \
        int initial_cap = q->_capacity;                                                             \
        q->data = (t *) realloc(q->data, sizeof(t) * (q->_capacity *= DEQUE_GROWTH_FACTOR));        \
        if ((q->_front < q->_back) || !q->_size) return;                                            \
        int diff = q->_capacity - initial_cap;                                                      \
        for (int i = initial_cap-1; i >= q->_front; i--)                                            \
            q->data[i + diff] = q->data[i];                                                         \
        q->_front += diff;                                                                          \
    }                                                                                               \
    t& Deque_##t##_front(Deque_##t *q) {                                                            \
        return q->data[q->_front];                                                                  \
    }                                                                                               \
    t& Deque_##t##_back(Deque_##t *q) {                                                             \
        int backP = q->_back - 1;                                                                   \
        if (backP < 0)                                                                              \
            backP = q->_capacity - 1;                                                               \
        return q->data[backP];                                                                      \
    }                                                                                               \
                                                                                                    \
    void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it) {                                       \
        if (++(it->_index) >= it->deq->_capacity)                                                   \
            it->_index = 0;                                                                         \
        it->_begin = false;                                                                         \
    }                                                                                               \
    void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it) {                                       \
        if (--(it->_index) < 0)                                                                     \
            it->_index = it->deq->_capacity-1;                                                      \
        if (it->_index == it->deq->_front)                                                          \
            it->_begin = true;                                                                      \
    }                                                                                               \
    t& Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it) {                                       \
        return it->deq->data[it->_index];                                                           \
    }                                                                                               \
    bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2) {           \
        return it1._index == it2._index && it1._begin == it2._begin;                                \
    }                                                                                               \
    Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *q) {                                          \
        return {                                                                                    \
            ._index = q->_front,                                                                    \
            .deq = q,                                                                               \
            ._begin = true,                                                                         \
        };                                                                                          \
    }                                                                                               \
    Deque_##t##_Iterator Deque_##t##_end(Deque_##t *q) {                                            \
        return {                                                                                    \
            ._index = q->_back,                                                                     \
            .deq = q,                                                                               \
            ._begin = false,                                                                        \
        };                                                                                          \
    }                                                                                               \
    bool Deque_##t##_equal(Deque_##t q1, Deque_##t q2) {                                            \
        if (                                                                                        \
                q1.is_smaller != q2.is_smaller  ||                                                  \
                q1.size(&q1) != q2.size(&q2)    ||                                                  \
                q1._capacity != q2._capacity                                                        \
            )                                                                                       \
            return false;                                                                           \
        Deque_##t##_Iterator it1 = q1.begin(&q1), it2 = q2.begin(&q2);                              \
        Deque_##t##_Iterator end1 = q1.end(&q1), end2 = q2.end(&q2);                                \
        for (;                                                                                      \
                !Deque_##t##_Iterator_equal(it1, end1) && !Deque_##t##_Iterator_equal(it2, end2);   \
                it1.inc(&it1), it2.inc(&it2)                                                        \
            )                                                                                       \
            if (                                                                                    \
                    it1.deq->is_smaller(it1.deref(&it1), it2.deref(&it2)) ||                        \
                    it2.deq->is_smaller(it2.deref(&it2), it1.deref(&it1))                           \
                )                                                                                   \
                return false;                                                                       \
        return true;                                                                                \
    }                                                                                               \
    void Deque_##t##_dtor(Deque_##t *q) {                                                           \
        free(q->data);                                                                              \
    }                                                                                               \
    void Deque_##t##_clear(Deque_##t *q) {                                                          \
        q->_front = q->_back = q->_size = 0;                                                        \
    }

#endif //CS540_ASSIGNMENT1_HVADODA1_DEQUE_HPP
