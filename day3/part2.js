const part2 = file => {
    const M1 = new Map();
    const M2 = new Map();

    const lines = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1);

    const numbers = lines.flatMap((l, i) => Array
        .from(l.matchAll(/\d+/g))
        .map(e => [ +e[0], e.index, i, e[0].length ]))
    numbers.forEach(([ v ], i) => M1.set(i, v));
    numbers.map(([ _, x, y, length ], i) => Array
        .from({ length }, (_, i) => `${x + i},${y}`)
        .forEach(c => M2.set(c, i)));

    return lines
        .flatMap((l, i) => Array
            .from(l.matchAll(/\*/g))
            .map(e => [ e.index, i ]))
        .map(([ x, y ]) => Array
            .from({ length: 9 }, (_, i) => i)
            .map(i => [ x + (i % 3) - 1 , y + Math.floor(i / 3) - 1 ])
            .map(([ x, y ]) => M2.get(`${x},${y}`))
            .filter(e => e !== undefined)
            .filter((e, i, a) => i === a.indexOf(e)))
        .filter(e => e.length === 2)
        .map(e => e
            .map(n => M1.get(n))
            .reduce((p, c) => p * c))
        .reduce((p, c) => p + c);
}; 

console.log(part2("input"));

