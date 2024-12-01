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

const _mincut = ({ nodes, edges }) => {
    edges = [ ...edges ];

    const djs = new DisjointSet();
    for (const node of nodes) {
        djs.set(node);
    }

    while (djs.count() > 2) {
        const rand = Math.floor(Math.random() * edges.length);
        const [ a, b ] = edges[rand];
        djs.union(a, b);
        edges[rand] = edges.at(-1);
        edges.length--;
    }

    const count = edges
        .filter(([ a, b ]) => djs.find(a) !== djs.find(b))
        .length
    
    return [ count, djs ];
}

const mincut = graph => {
    while (true) {
        const [ count, djs ] = _mincut(graph);
        if (count !== 3) continue;
        return Array.from(graph
            .nodes
            .map(node => djs.find(node))
            .reduce((p, c) => p.set(c, (p.get(c) ?? 0) + 1), new Map())
            .values()).reduce((p, c) => p * c)
    }
};

const part1 = file => {
    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(/:?\s/g));
    
    const lookup = Object.fromEntries(input
        .flat()
        .filter((e, i, a) => a.indexOf(e) === i)
        .map((e, i) => [ e, i ]));

    const nodes = Object.values(lookup);
    const edges = input
        .map(row => row.map(e => lookup[e]))
        .map(([ src, ...dest ]) => dest.map(e => [ src, e ]))
        .flat();

    return mincut({ nodes, edges });
};

console.log(part1("input"));
