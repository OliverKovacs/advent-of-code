const L = { red: 0, green: 1, blue: 2 };
const D = Array.from({ length: 3 }, (_, i) => [ i, 0 ]);
const part2 = input => require("node:fs")
    .readFileSync(input, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l.split(": "))
    .map(([ _, d ]) => d
        .split("; ")
        .map(e => Object.values(Object.fromEntries([ ...D, ...e
            .split(", ")
            .map(e => e.split(" "))
            .map(([ v, c ]) => [ L[c], +v ]) ])))
        .reduce((p, c) => p.map((e, i) => Math.max(e, c[i])), [ 0, 0, 0 ])
        .reduce((p, c) => p * c))
    .reduce((p, c) => p + c)

console.log(part2("input"));
