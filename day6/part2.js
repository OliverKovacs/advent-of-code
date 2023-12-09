const part2 = file => {
    const [ t, d ] = require("node:fs")
        .readFileSync(file, "utf-8")
        .replace(/ +/g, "")
        .match(/\d+/g)
        .map(e => +e);
    return ((a, b) => Math.ceil(a + b - 1) - Math.floor(a - b + 1) + 1)
        (t/2, Math.sqrt(Math.pow(-t/2, 2) - d));
}; 

console.log(part2("input"));
