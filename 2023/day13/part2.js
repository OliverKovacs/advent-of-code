const count = num => num
    .toString(2)
    .match(/1/g)
    ?.length ?? 0;

const equal = (a, b) => a
    .slice(0, b.length)
    .map((e, i) => count(e ^ b[i]))
    .reduce((p, c) => p + c) === 1;

const find = (arr, rarr, s) => {
    for (let i = 1; i < arr.length; i++) {
        if (equal(arr.slice(i), rarr.slice(arr.length - i))) return i * s;
    }
    return 0;
}

const reflection = pat => {
    const rows = pat
        .map(e => e.split("").reduce((p, c, i) => p | ((c === "#") << i), 0));
    const cols = pat[0]
        .split("")
        .map((_, i) => pat.reduce((p, c, j) => p | ((c[i] === "#") << j), 0));
    const rrows = rows.reduce((p, c) => [ c, ...p ], []);
    const rcols = cols.reduce((p, c) => [ c, ...p ], []);
    return find(rows, rrows, 100) + find(cols, rcols, 1);
};

const part2 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .slice(0, -1)
    .split("\n\n")
    .map(pat => pat.split("\n"))
    .map(reflection)
    .reduce((p, c) => p + c);

console.log(part2("input"));
