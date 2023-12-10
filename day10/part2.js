// this is horrible
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
const id = (m, [ y, x ]) => { return (m[y][x].join(",") === [ y, x ].join(","))
    ? [ y, x ]
    : id(m, m[y][x]); }
const merge = (m, a, b) => {
    const i1 = [ ...id(m, a) ];
    const i2 = [ ...id(m, b) ];
    m[i1[0]][i1[1]] = i2;
};

const part2 = file => {
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
    let d_old = Array
        .from({ length: m.length }, () => Array(m[0].length).fill(-1));
    const r = (p, i) => p.length 
        ? r(p
            .flatMap(e => g.get(e.join(",")))
            .filter(([ y, x ]) => d_old[y][x] === -1)
            .map(([ y, x ]) => { d_old[y][x] = i; return [ y, x ]; }), i + 1)
        : [];

    d_old[s[0]][s[1]] = 0;
    r([ s ], 1);

    let d = d_old.map(r => [ -1, ...r, -1 ])
    d = [ [ ...d[0] ].fill(-1), ...d, [ ...d[0] ].fill(-1) ];
    
    const f = d
        .map(r => r.flatMap(e => [ e, -1 ]).slice(0, -1))
        .flatMap(r => [ r, [ ...r ].fill(-1) ])
        .slice(0, -1);

    for (let y = 0; y < d.length - 1; y++) {
        for (let x = 0; x < d[0].length - 1; x++) {
            f[2 * y][2 * x + 1] =
                (Math.abs(f[2 * y][2 * x] - f[2 * y][2 * x + 2]) === 1)
                    ? 1
                    : -1;
            f[2 * y + 1][2 * x] =
                (Math.abs(f[2 * y][2 * x] - f[2 * y + 2][2 * x]) === 1)
                    ? 1
                    : -1;
        }
    }
    for (let y = 0; y < d.length - 1; y++) {
        let x = f[0].length - 1;
        f[2 * y + 1][x] =
            (Math.abs(f[2 * y][x] - f[2 * y + 2][x]) === 1) ? 1 : -1;
    }
    for (let x = 0; x < d[0].length - 1; x++) {
        let y = f.length - 1;
        f[y][2 * x + 1] =
            (Math.abs(f[y][2 * x] - f[y][2 * x + 2]) === 1) ? 1 : -1;
    }

    const j = Array
        .from({ length: f.length },
            (_, y) => Array.from({ length: f[0].length }, (_, x) => [ y, x ]));


    for (let y = 0; y < f.length; y++) {
        for (let x = 0; x < f[0].length; x++) {
            if (f[y][x] !== -1) j[y][x] = [ ...s ];
        }
    }
    for (let y = 0; y < f.length; y++) {
        for (let x = 0; x < f[0].length - 1; x++) {
            if (f[y][x] !== -1 || f[y][x + 1] !== -1) continue;
            merge(j, [ y, x ], [ y, x + 1 ]);
        }
    }
    for (let y = 0; y < f.length - 1; y++) {
        for (let x = 0; x < f[0].length; x++) {
            if (f[y][x] !== -1 || f[y + 1][x] !== -1) continue;
            merge(j, [ y, x ], [ y + 1, x ]);
        }
    }

    const k = j.map((r, y) => r.map((_, x) => id(j, [ y, x ]).join(",")));
    return m
        .map((r, y) => r.map((_, x) => +(d_old[y][x] === -1
            && k[(y + 1) * 2][(x + 1) * 2] !== k[0][0])))
        .flat()
        .reduce((p, c) => p + c);
};

console.log(part2("input"));
