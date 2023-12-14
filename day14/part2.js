const f = i => [ 0, 0, 1 ].at(i);
const t = i => [ 0, -1, 0 ].at(i);
const tilt = (map, d) => {
    let change = true;
    while (change) {
        change = false;
        for (let i = f(d[0]); i < map.length + t(d[0]); i++) {
            for (let j = f(d[1]); j < map[0].length + t(d[1]); j++) {
                if (map[i][j] !== "O") continue;
                if (map[i + d[0]][j + d[1]] !== ".") continue;
                map[i][j] = ".";
                map[i + d[0]][j + d[1]] = "O";
                change = true;
            }
        }
    }
    return map;
};

const part2 = file => {
    const map = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(""));
    
    const history = [];
    for (let i = 0;; i++) {
        tilt(map, [ -1, 0 ]);
        tilt(map, [ 0, -1 ]);
        tilt(map, [ 1, 0 ]);
        tilt(map, [ 0, 1 ]);
        const current = map.map(row => row.join("")).join(";");
        const index = history.indexOf(current);
        history.push(current);
        if (index === -1) continue;
        const phase = i - index;
        const solution = index + ((1000000000 - index - 1) % phase);
        return history[solution]
            .split(";")
            .map(line => line.split(""))
            .reverse()
            .map((row, i) => row.filter(e => e === "O").length * (i + 1))
            .reduce((p, c) => p + c);
    }

};

console.log(part2("input"));
