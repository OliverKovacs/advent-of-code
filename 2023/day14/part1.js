const part1 = file => {
    const map = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(""));

    let change = true;
    while (change) {
        change = false;
        for (let i = 1; i < map.length; i++) {
            for (let j = 0; j < map[0].length; j++) {
                if (map[i][j] !== "O") continue;
                if (map[i - 1][j] !== ".") continue;
                map[i][j] = ".";
                map[i - 1][j] = "O";
                change = true;
            }
        }
    }

    return map
        .reverse()
        .map((row, i) => row.filter(e => e === "O").length * (i + 1))
        .reduce((p, c) => p + c);
};

console.log(part1("input"));
