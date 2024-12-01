const cache = new Map();
const replace = (s, c) => s[0] + c + s.slice(2);
const recurse = (s, e) => {
    const key = s + ";" + e.join(",");
    const known = cache.get(key);
    if (known !== undefined) return known;
    const out = _recurse(s, e);
    cache.set(key, out);
    return out;
};
const _recurse = (s, e) => {
    let ns = s.slice(1);
    let ne = e.slice(1);
    switch(s[1]) {
        case ".": 
            if (s[0] === ".") return recurse(ns, e);
            if (e[0] !== 0) return 0;
            return recurse(ns, ne);
        case "#":
            if (e.length === 0) return 0;
            if (s[0] === ".") return recurse(ns, [ e[0] - 1, ...ne ]);
            if (e[0] === 0) return 0;
            return recurse(ns, [ e[0] - 1, ...ne ]);
        case "?":
            return recurse(replace(s, "."), e) + recurse(replace(s, "#"), e);
        case undefined: {
            if (e.length === 0) return 1;
            return 0;
        }
    }
};
const five = (s, i) => Array(5).fill(s).join(i ? "," : "?");

const part2 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(line => line.split(" "))
    .map(line => line.map(five))
    .map(([ a, b ]) => recurse("." + a + ".", b.split(",").map(e => +e)))
    .reduce((p, c) => p + c);

console.log(part2("input"));
