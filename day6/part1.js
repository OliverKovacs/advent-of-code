const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l.match(/\d+/g).map(e => +e))
    .reduce((p, c) => p.map((e, i) => [ e, c[i]]))
    .map(([ t, d ]) => [ t/2, Math.sqrt(Math.pow(-t/2, 2) - d) ])
    .map(([ a, b ]) => [ Math.floor(a - b + 1), Math.ceil(a + b - 1) ])
    .map(([ a, b ]) => b - a + 1)
    .reduce((p, c) => p * c);

console.log(part1("input"));
