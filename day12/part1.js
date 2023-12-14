const toRegex = string => new RegExp("^\\.*" + string
    .split(",")
    .map(e => `#{${e}}\\.+`)
    .join("") + "$");

const toCombinations = string => string
    .split("")
    .map(c => c === "?" ? [ ".", "#" ] : [ c ])
    .reduce((p, c) => p.flatMap(s => c.map(e => s + e)), [ "" ])
    .map(e => `${e}.`);

const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(line => line.split(" "))
    .map(([ a, b ]) => [ toCombinations(a), toRegex(b) ])
    .map(([ strings, regex ]) => strings.map(s => regex.test(s)))
    .flat()
    .reduce((p, c) => p + c);

console.log(part1("input"));
