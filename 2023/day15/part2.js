const hash = s => s
    .split("")
    .map(c => c.charCodeAt(0))
    .reduce((p, c) => ((p + c) * 17) % 256, 0);

const part2 = file => {
    const boxes = Array.from({ length: 256 }, () => { return {}; });
    require("node:fs")
        .readFileSync(file, "utf-8")
        .replace(/\n/g, "")
        .split(",")
        .map(e => e.split(/-|=/))
        .map(e => [ e, hash(e[0]) ])
        .forEach(([ [ key, value ], idx ]) => value
            ? boxes[idx][key] = +value
            : delete boxes[idx][key]);

    return boxes
        .map(e => Object.values(e).reduce((p, c, i) => p + c * (i + 1), 0))
        .reduce((p, c, i) => p + c * (i + 1));
};

console.log(part2("input"));
