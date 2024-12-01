const L = { red: 12, green: 13, blue: 14 };
const part1 = input => require("node:fs")
    .readFileSync(input, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l.split(": "))
    .map(([ _, d ], i) => [ i + 1, d
        .split(/[;,]\ /g)
        .map(e => e.split(" "))
        .reduce((p, [ v, c ]) => p && (+v <= L[c]), true) ])
    .filter(([ _, b ]) => b)
    .map(([ e ]) => e)
    .reduce((p, c) => p + c);

console.log(part1("input"));
