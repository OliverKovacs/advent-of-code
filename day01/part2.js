const N = [
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
];

const L = Object.fromEntries(N.flatMap((s, i) => [
    [ s, i + 1 ],
    [ i + 1, i + 1],
]));

const part2 = file => require("node:fs")
    .readFileSync(file, "utf-8")
    .split("\n")
    .slice(0, -1)
    .map(l => (a => [ a[0], a.at(-1) ])(Array
        .from(l.matchAll(
            new RegExp(`(?=(\\d|${N.join("|")}))`, "g")),
            m => L[m[1]],
        )))
    .map(([ a, b ]) => a * 10 + b)
    .reduce((p, c) => p + c);

console.log(part2("input"));
