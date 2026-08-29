#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdint.h>

int32_t bt_left(int32_t id)
{
    return 2 * id + 1;
}

int32_t bt_right(int32_t id)
{
    return 2 * id + 2;
}

int32_t bt_parent(int32_t id)
{
    return (id - 1) / 2;
}

#endif /* BINARYTREE_H */
