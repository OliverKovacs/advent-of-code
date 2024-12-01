const parse = string => string
    .split(", ")
    .map(e => +e);

const add = (v1, v2) => [ v1[0] + v2[0], v1[1] + v2[1] ];

const scalar = (s, v) => [ s * v[0], s * v[1] ];

const determinant = m => m[0][0] * m[1][1] - m[1][0] * m[0][1];

const inverse = m => {
    const s = 1 / determinant(m);
    return [ [ s * m[1][1], s * -m[0][1] ], [ s * -m[1][0], s * m[0][0] ] ];
};

const matmul = (m1, m2) => {
    const out = [];
    for (let i = 0; i < m2.length; i++) {
        out[i] = [];
        for (let j = 0; j < m1[0].length; j++) {
            out[i][j] = 0;
            for (let k = 0; k < m1.length; k++) {
                out[i][j] += m2[i][k] * m1[k][j];
            }
        }
    }
    return out;
};

const intersect = ([ p1, v1 ], [ p2, v2 ]) => {
    const inv = inverse([ v1, scalar(-1, v2) ]);
    const p = [ [ p2[0] - p1[0], p2[1] - p1[1] ] ];
    const [ t1, t2 ] = matmul(inv, p)[0];
    const [ x, y ] = add(p1, scalar(t1, v1));
    return { x, y, t1, t2 };
};

const isParallel = (v1, v2) => v1[0] / v2[0] === v1[1] / v2[1];

const part1 = file => {
    const min = { debug: 7, input: 200000000000000 }[file];
    const max = { debug: 27, input: 400000000000000 }[file];

    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(row => row.split(" @ ").map(parse))
        .map(([ [ px, py ], [ vx, vy ] ]) => [ [ px, py ], [ vx, vy ] ]);

    let count = 0;
    for (let i = 0; i < input.length; i++) {
        for (let j = i + 1; j < input.length; j++) {
            const [ p1, v1 ] = input[i];
            const [ p2, v2 ] = input[j];
            if (isParallel(v1, v2)) continue;
            const { x, y, t1, t2 } = intersect([ p1, v1 ], [ p2, v2 ]);
            if (t1 < 0 || t2 < 0
                || x < min || max < x
                || y < min || max < y
            ) continue;
            count++;
        }
    }
    return count;
}

console.log(part1("input"));
