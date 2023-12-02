const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => (a => [ a[0], a.at(-1) ])(l
        .match(new RegExp("\\d", "g"))
        .map(c => +c)))
    .map(([ a, b ]) => a * 10 + b)
    .reduce((p, c) => p + c);

console.log(part1("input"));
