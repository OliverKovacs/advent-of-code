const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => l
        .split(": ")[1]
        .split("|")
        .map(e => e.match(/\d+/g).map(n => +n)))
    .map(([ a, b ]) => a.filter(e => b.indexOf(e) !== -1).length)
    .filter(e => e > 0)
    .map(e => Math.pow(2, e - 1))
    .reduce((p, c) => p + c);

console.log(part1("input"));
