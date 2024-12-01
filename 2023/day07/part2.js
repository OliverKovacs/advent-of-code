const V = Object.fromEntries([ "J" ]
    .concat(Array.from({ length: 8 }, (_, i) => `${i + 2}`))
    .concat([ "T", "Q", "K", "A" ])
    .map((e, i) => [ e, i ]));

const s = (a, b) => a.reduce((p, c, i) => p === 0 ? c - b[i] : p, 0);

const c1 = a => a
    .reduce((p, c) => [ ...p, c
        ? [ c ]
        : Array.from({ length: 12 }, (_, i) => i + 1) ], [])
    .reduce((p, c) => p.flatMap(e1 => c.map(e2 => [ ...e1, e2 ])), [ [] ])
    .map(c2)
    .map(e => e.join(","))
    .filter((e, i, a) => a.indexOf(e) === i)
    .map(e => e.split(","))
    .sort(s)
    .at(-1)

const c2 = a => Object
    .values(a.reduce((p, c) => { return { ...p, [c]: (p[c] ?? 0) + 1 }; }, {}))
    .sort((a, b) => b - a);

const part2 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l.split(" "))
    .map(([ a, b ]) => [ a.split("").map(e => V[e]), +b ])
    .map(([ a, b ]) => [ c1(a), a, b ])
    .sort((a, b) => s(a[1], b[1]))
    .sort((a, b) => s(a[0], b[0]))
    .map((e, i) => e[2] * (i + 1))
    .reduce((p, c) => p + c);

console.log(part2("input"))
