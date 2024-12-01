const m = (v, a) => v.map(n => (([ d, s ]) => d + n - s)
    (a.filter(([ _, s, l ]) => s <= n && n < s + l)[0] ?? [ n, n, 1]));

const part1 = file => {
    const [ s, ...r ] = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n\n")

    return Math.min(...r.map(e => e
        .split("\n")
        .slice(1)
        .map(e => e.split(" ").map(n => +n)))
        .reduce((p, c) => m(p, c), s.match(/\d+/g).map(e => +e)));
}; 

console.log(part1("input"));
