const D = [ [ -1, 0 ], [ 1, 0 ], [ 0, -1 ], [ 0, 1 ] ];
const A = [ 0, 1, 2, 3 ];
const N = [ 1, 2, 4, 8 ];
const I = [ 2, 1, 8, 4 ];
const L = {
    "|": 1 | 2,
    "-": 4 | 8,
    "L": 1 | 8,
    "J": 1 | 4,
    "7": 2 | 4,
    "F": 2 | 8,
    ".": 0,
    "S": 1 | 2 | 4 | 8,
};

const add = (a, b) => a.map((e, i) => e + b[i]);
const get = (m, [ y, x ]) => (x >= 0
    && y >= 0 
    && x < m[0].length
    && y < m.length) ? m[y][x] : [];
const search = (m, v) => m
    .map((e, i) => [ i, e.indexOf(v) ])
    .filter(([ _, i ]) => i !== -1)[0];

const part1 = file => {
    const g = new Map();
    const m = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1)
        .map(l => l.split("").map(e => L[e]));

    m.forEach((r, y) => r.forEach((v, x) => g.set(`${y},${x}`, A
        .filter(e => N[e] & v)
        .filter(e => I[e] & (get(m, add([ y, x ], D[e])) ?? 0))
        .map(e => add([ y, x ], D[e])))));

    const s = search(m, 15);
    const d = Array
        .from({ length: m.length }, () => Array(m[0].length).fill(-1));
    const r = (p, i) => p.length 
        ? r(p
            .flatMap(e => g.get(e.join(",")))
            .filter(([ y, x ]) => d[y][x] === -1)
            .map(([ y, x ]) => { d[y][x] = i; return [ y, x ]; }), i + 1)
        : [];
    
    d[s[0]][s[1]] = 0;
    r([ s ], 1);
    return Math.max(...d.flatMap(e => e));
};

console.log(part1("input"));

