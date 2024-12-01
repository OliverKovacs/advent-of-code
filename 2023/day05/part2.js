const op = (range, map) => {
    const n = [ [ Math.max(range[0], map[0]), Math.min(range[1], map[1]) ] ].filter(([a, b]) => a <= b);
    const o = [
        [ range[0], Math.min(range[1], map[0] - 1) ],
        [ Math.max(range[0], map[1] + 1), range[1] ],
    ].filter(([a, b]) => a <= b);
    return { n, o };
}; 

const next = (r, mappings) => {
    let out = [];
    for (let m of mappings) {
        const { o, n } = op(r, [ m[1], m[1] + m[2] - 1 ]);
        if (n.length === 0)
        continue;
        out.push([ n[0][0] + m[0] - m[1], n[0][1] + m[0] - m[1] ]);
        out = out.concat(o.flatMap(e => next(e, mappings)));
        return out;
    }
    out.push(r);
    return out;
}

const part1 = file => {
    let [ s, ...r ] = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n\n")

    s = s.match(/\d+/g).map(e => +e);

    let ranges = [];
    for (let i = 0; i < s.length; i += 2) {
        ranges.push([ s[i], s[i] + s[i + 1] - 1 ]);
    }

    const mappings = r.map(e => e
        .split("\n")
        .slice(1)
        .map(e => e.split(" ").map(n => +n)));
    
    let out;
    for (let m of mappings) {
        out = [];
        for (let r of ranges) out = out.concat(next(r, m));
        ranges = out;
    }

    return Math.min(...out.flatMap(e => e))
}; 

console.log(part1("input"));
