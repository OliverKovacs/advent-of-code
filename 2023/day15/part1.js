const hash = s => s
    .split("")
    .map(c => c.charCodeAt(0))
    .reduce((p, c) => ((p + c) * 17) % 256, 0);

const part1 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .replace(/\n/g, "")
    .split(",")
    .map(hash)
    .reduce((p, c) => p + c);

console.log(part1("input"));
