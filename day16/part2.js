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

const simulate = (m, c, p) => {
    const l = Array(m.length)
        .fill(0)
        .map(() => Array(m[0].length).fill(0));

    step(m, l, c, p);

    return l
        .map(row => row.map(e => +!!e))
        .flat()
        .reduce((p, c) => p + c);
}

const part2 = file => {
    const m = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n");

    let r = [];
    for (let y = 0; y < m.length; y++) {
        r.push(simulate(m, 3, [ y, 0 ]));
        r.push(simulate(m, 2, [ y, m[0].length - 1 ]));
    }
    for (let x = 0; x < m[0].length; x++) {
        r.push(simulate(m, 1, [ 0, x ]));
        r.push(simulate(m, 0, [ m.length - 1, x ]));
    }

    return Math.max(...r);
};

console.log(part2("input"));
