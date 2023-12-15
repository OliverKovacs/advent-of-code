const part1 = file => {
    const wins = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1)
        .map(l => l
            .split(": ")[1]
            .split("|")
            .map(e => e.match(/\d+/g).map(n => +n)))
        .map(([ a, b ]) => a.filter(e => b.indexOf(e) !== -1).length);

    const amounts = Array.from({ length: wins.length }, () => 1);
    for (let i = 0; i < amounts.length; i++) {
        for (let j = 0; j < wins[i]; j++) {
            amounts[i + j + 1] += amounts[i];
        }
    }

    return amounts.reduce((p, c) => p + c);
};

console.log(part1("input"));
