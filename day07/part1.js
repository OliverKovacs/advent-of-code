const V = Object.fromEntries(Array
    .from({ length: 8 }, (_, i) => `${i + 2}`)
    .concat([ "T", "J", "Q", "K", "A" ])
    .map((e, i) => [ e, i ]));

const s = (a, b) => a.reduce((p, c, i) => p === 0 ? c - b[i] : p, 0);

const c = a => Object
    .values(a.reduce((p, c) => { return { ...p, [c]: (p[c] ?? 0) + 1 }; }, {}))
    .sort((a, b) => b - a);

const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l.split(" "))
    .map(([ a, b ]) => [ a.split("").map(e => V[e]), +b ])
    .map(([ a, b ]) => [ c(a), a, b ])
    .sort((a, b) => s(a[1], b[1]))
    .sort((a, b) => s(a[0], b[0]))
    .map((e, i) => e[2] * (i + 1))
    .reduce((p, c) => p + c);

console.log(part1("input"))
