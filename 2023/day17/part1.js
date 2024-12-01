class BinaryTree {
    #heap = [];

    root() {
        return 0;
    }

    last() {
        return this.size() - 1;
    }

    size() {
        return this.#heap.length;
    }

    get(index) {
        return this.#heap[index];
    }

    swap(index1, index2) {
        [ this.#heap[index1], this.#heap[index2] ] =
            [ this.#heap[index2], this.#heap[index1] ];
    }

    parent(index) {
        return ((index + 1) >>> 1) - 1;
    }

    left(index) {
        return (index << 1) + 1;
    }

    right(index) {
        return (index + 1) << 1;
    }
    
    push(value) {
        return this.#heap.push(value);
    }

    pop() {
        return this.#heap.pop();
    }
}

class PriorityQueue {
    #cmp;
    #tree;

    constructor(cmp) {
        this.#cmp = cmp;
        this.#tree = new BinaryTree();
    }

    size() {
        return this.#tree.size();
    }

    peek() {
        return this.#tree.get(this.#tree.root());
    }

    push(value) {
        this.#tree.push(value);
        this.#up();
        return this.#tree.size();
    }
    
    pop() {
        const value = this.peek();
        const last = this.#tree.last();
        this.#tree.swap(this.#tree.root(), last);
        this.#tree.pop();
        this.#down();
        return value;
    }

    #greater(index1, index2) {
        return this.#cmp(this.#tree.get(index1), this.#tree.get(index2));
    }

    #up() {
        let node = this.#tree.last();
        while (node > this.#tree.root() && this.#greater(node, this.#tree.parent(node))) {
            this.#tree.swap(node, this.#tree.parent(node));
            node = this.#tree.parent(node);
        }
    }

    #down() {
        let node = this.#tree.root();
        while (
            (this.#tree.left(node) < this.size() && this.#greater(this.#tree.left(node), node)) ||
            (this.#tree.right(node) < this.size() && this.#greater(this.#tree.right(node), node))
        ) {
            const max = (this.#tree.right(node) < this.size() && this.#greater(this.#tree.right(node), this.#tree.left(node)))
                ? this.#tree.right(node)
                : this.#tree.left(node);
            this.#tree.swap(node, max);
            node = max;
        }
    }
}

const mat = (y, x, f) => Array(y)
    .fill(0)
    .map(() => Array(x).fill(0).map(f));

const tile = () => mat(4, 3, () => Infinity);

// up down left right

const A = [ 0, 1, 2, 3 ];
const R = [ 1, 0, 3, 2 ];
const D = [ [ -1, 0 ], [ 1, 0 ], [ 0, -1 ], [ 0, 1 ] ];

const dijkstra = i => {
    const queue = new PriorityQueue(({ l: l1 }, { l: l2 }) => l1 < l2);
    const map = mat(i.length, i[0].length, tile);

    const add = ({ y, x, d, n, l }) => {
        if (map[y][x][d][n] <= l) return;
        for (let i = n; i < 3; i++) map[y][x][d][i] = l;
        queue.push({ y, x, d, n, l });
    };

    add({ y: 1, x: 0, d: 1, n: 0, l: i[1][0] });
    add({ y: 0, x: 1, d: 3, n: 0, l: i[0][1] });

    while (queue.size() > 0) {
        const top = queue.pop();
        if (map[top.y][top.x][top.d][top.n] < top.l) continue;
        if (top.y === i.length - 1 && top.x === i[0].length - 1) break;
        A
            .filter(e => top.d !== R[e])
            .filter(e => !(e === top.d && top.n === 2))
            .map(d => [ d, D[d] ])
            .map(([ d, delta ]) => [ d, [ top.y + delta[0], top.x + delta[1] ] ])
            .filter(([ d, [ y, x ] ]) => !(y < 0 || i.length <= y || x < 0 || i[0].length <= x))
            .forEach(([ d, [ y, x ]]) => add({
                y, x, d,
                n: d === top.d ? top.n + 1 : 0,
                l: top.l + i[y][x],
            }));
    }

    return map;
}

const part1 = file => {
    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split("").map(char => +char));

    const map = dijkstra(input);
    return Math.min(...map.at(-1).at(-1).flat());
};

console.log(part1("input"));
