const L = { "L": 0, "R": 1 };
const gcd = (a, b) => b ? gcd(b, a % b) : a;
const lcm = (a, b) => a * b / gcd(a, b);
const part2 = file => {
    const g = new Map();
    const [ I, _, ...M ] = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1)

    M
        .map(e => e.match(/\w+/g))
        .forEach(([ f, l, r ]) => g.set(f, [ l, r ]));

    return Array.from(g.keys())
        .filter(e => e[2] === "A")
        .map(c => {
            let i = 0;
            for (; c[2] !== "Z"; c = g.get(c)[L[I[i++ % I.length]]]) {}
            return i;
        })
        .reduce(lcm);
} 

console.log(part2("input"));
