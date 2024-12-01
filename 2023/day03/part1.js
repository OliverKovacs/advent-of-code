const check = a => ([ x, y ]) => x >= 0
    && y >= 0
    && x < a[0].length
    && y < a.length
    && !/[\d\.]/.test(a[y][x]);

const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map((l, i, a) => Array
        .from(l.matchAll(/\d+/g))
        .map(e => [ +e[0], e.index, i, e[0].length ])
        .map(([ v, x, y, l ]) => [ v, Array
            .from({ length: l + 2 }, (_, i) => i - 1)
            .flatMap(i => [ [ x + i, y - 1 ], [ x + i, y + 1 ] ])
            .concat([ [ x - 1, y ], [ x + l, y ] ])
            .map(check(a))
            .reduce((p, c) => p || c) ]))
    .flatMap(e => e)
    .filter(([ _, b ]) => b)
    .map(([ e, ]) => e)
    .reduce((p, c) => p + c);

console.log(part1("input"));
