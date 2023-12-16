const D = [ [ -1, 0 ], [ 1, 0 ], [ 0, -1 ], [ 0, 1 ] ];
const A = [ 0, 1, 2, 3 ];
const E = [ 1, 2, 4, 8 ];
const L = {
    ".": { 0: 1, 1: 2, 2: 4, 3: 8 },
    "/": { 0: 8, 1: 4, 2: 2, 3: 1 },
    "\\": { 0: 4, 1: 8, 2: 1, 3: 2 },
    "-": { 0: 12, 1: 12, 2: 4, 3: 8 },
    "|": { 0: 1, 1: 2, 2: 3, 3: 3 },
};

const step = (m, l, c, [ y, x ]) => {
    // console.log()
    if (y < 0 || x < 0 || y >= m.length || x >= m[0].length) return;
    if (E[c] & l[y][x]) return;
    l[y][x] |= E[c];
    A.filter(a => E[a] & L[m[y][x]][c])
        .forEach(a => step(m, l, a, [ y + D[a][0], x + D[a][1] ]));
};

const part1 = file => {
    const mirrors = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n");

    const light = Array(mirrors.length)
        .fill(0)
        .map(() => Array(mirrors[0].length).fill(0));

    step(mirrors, light, 3, [ 0, 0 ]);

    return light
        .map(row => row.map(e => +!!e))
        .flat()
        .reduce((p, c) => p + c);
};

console.log(part1("input"));
