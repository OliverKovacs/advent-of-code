const L = { "L": 0, "R": 1 };
const part1 = file => {
    const g = new Map();
    const [ I, _, ...M ] = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1)

    M
        .map(e => e.match(/\w+/g))
        .forEach(([ f, l, r ]) => g.set(f, [ l, r ]));
    
    let i = 0;
    for (let c = "AAA"; c !== "ZZZ"; c = g.get(c)[L[I[i++ % I.length]]]) {}
    return i;
} 

console.log(part1("input"));
