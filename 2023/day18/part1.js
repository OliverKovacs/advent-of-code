const D = { U: 0, D: 1, L: 2, R: 3 };
const L = [ [ -1, 0 ], [ 1, 0 ], [ 0, -1 ], [ 0, 1 ] ];

class DisjointSet {
    #heap = [];
    #count = 0;

    count() {
        return this.#count;
    }

    set(index) {
        if (!this.#heap[index] || this.find(index) !== index) this.#count++;
        this.#heap[index] ??= {};
        this.#heap[index].parent = index;
        this.#heap[index].rank = 0;
    }

    find(index) {
        if (this.#heap[index].parent === index) return index;
        this.#heap[index].parent = this.find(this.#heap[index].parent);
        return this.#heap[index].parent;
    }

    union(index1, index2) {
        index1 = this.find(index1);
        index2 = this.find(index2);

        if (index1 === index2) return;
        if (this.#heap[index1].rank < this.#heap[index2].rank) {
            [ index1, index2 ] = [ index2, index1 ];
        }

        this.#heap[index2].parent = index1;
        this.#count--;

        if (this.#heap[index1].rank !== this.#heap[index2].rank) return;
        this.#heap[index1].rank++;
    }
}

const part1 = file => {
    const plan = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(" "))
        .map(([ d, s, c ]) => [ L[D[d]], +s, c.slice(2, -1) ])

    const bounds = plan
        .reduce((p, [ [ y, x ], s ]) => [ ...p, [ s * y + p.at(-1)[0], s * x + p.at(-1)[1] ] ], [ [ 0, 0 ] ])
        .reduce((p, c) => [ [ ...p[0], c[0] ], [ ...p[1], c[1] ] ], [ [], [] ])
        .map(e => [ Math.min(...e), Math.max(...e) ])

    const map = Array(bounds[0][1] - bounds[0][0] + 1)
        .fill(0)
        .map(() => Array(bounds[1][1] - bounds[1][0] + 1).fill(0));

    const [ by, bx ] = [ -1 * bounds[0][0], -1 * bounds[1][0] ];
    let [ y, x ] = [ by, bx ];
    map[y][x] = 1;
    for (const [ [ dy, dx ], s ] of plan) {
        for (let i = 0; i < s; i++) {
            y += dy;
            x += dx;
            map[y][x] = 1;
        }
    }

    const c2i = (y, x) => y * (map[0].length + 1) + x;
    
    const djs = new DisjointSet();
    for (let i = 0; i <= c2i(map.length + 2, map[0].length + 1); i++) {
        djs.set(i);
    }
    
    for (let y = 0; y < map.length + 2; y++) {
        for (let x = 0; x < map[0].length + 2; x++) {
            if ((map[y - 1]?.[x - 1] ?? 0) === 1) {
                djs.union(c2i(y, x), c2i(by + 1, bx + 1));
                continue;
            }
            if (x !== 0 && (map[y - 1]?.[x - 2] ?? 0) !== 1) djs.union(c2i(y, x), c2i(y, x - 1));
            if (y !== 0 && (map[y - 2]?.[x - 1] ?? 0) !== 1) djs.union(c2i(y, x), c2i(y - 1, x));
        }
    }

    let out = Array(map.length + 2)
        .fill(0)
        .map((_, y) => Array(map[0].length + 2)
            .fill(0)
            .map((_, x) => djs.find(c2i(y, x))));

    const indices = out
        .flat()
        .filter((e, i, a) => a.indexOf(e) === i);
    
    out = out.map(row => row.map(e => indices.indexOf(e)));

    const outer = out[0][0];

    return out
        .flat()
        .reduce((p, c) => p + ((c !== outer) ? 1 : 0))
};

console.log(part1("input"))
