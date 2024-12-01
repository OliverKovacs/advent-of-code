const condition = string => {
    return [
        { "<": "lt", ">": "gt"}[string.match(/<|>/)],
        (([ a, b ]) => [ a, +b ])(string.split(/<|>/))
    ];
};

const statement = string => string.indexOf(":") === -1
    ? [ "true", string ]
    : (([ a, b ]) => [ condition(a), b ])(string.split(":"));

const evaluate = (input, rules) => {
    let current = "in"
    let index = 0;
    while (current !== "A" && current !== "R") {
        console.log(current, index)
        const tmp = rules[current][index];
        if (tmp[0] === "true" || (tmp[0][0] === "lt" && input[tmp[0][1][0]] < tmp[0][1][1]) || (tmp[0][0] === "gt" && input[tmp[0][1][0]] > tmp[0][1][1])) {
            current = tmp[1];
            index = 0;
            continue;
        }
        index++
    }
    return current;
};  

const part1 = file => {
    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n\n");

    const rules = Object.fromEntries(input[0]
        .split("\n")
        .map(e => e.split("{"))
        .map(([ k, v ]) => [ k, v.slice(0, -1).split(",").map(statement) ]))

    const data = input[1]
        .split("\n")
        .map(e => Object.fromEntries(e
            .slice(1, -1)
            .split(",")
            .map(s => s.split("="))
            .map(([ k, v ]) => [ k, +v ])))

    console.log(rules, data);

    return data
        .filter(e => evaluate(e, rules) === "A")
        .map(e => Object.values(e))
        .flat()
        .reduce((p, c) => p + c);
};

console.log(part1("input"));
