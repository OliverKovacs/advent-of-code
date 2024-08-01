const part1 = file => {
    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(""))

    let start;
    outer: for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < input[0].length; x++) {
            if (input[y][x] !== "S") continue;
            start = [ y, x ];
            break outer;
        }
    }
    input[start[0]][start[1]] = ".";

    const next = ([ y, x ]) => [ [ -1, 0 ], [ 1, 0 ], [ 0, -1], [ 0, 1 ] ]
        .map(([ y1, x1 ]) => [ y + y1, x + x1 ])
        .filter(([ y, x ]) => y >= 0
            && x >= 0
            && y < input.length
            && x < input[0].length)
        .filter(([ y, x ]) => input[y][x] == ".");
    
    let sym = "XY";
    let heap = [ [ start ], [] ];
    for (let i = 0; i < 65; i++) {
        heap[(i + 1) % 2] = [];
        for (const tile of heap[i % 2]) {
            if (input[tile[0]][tile[1]] !== ".") continue;
            heap[(i + 1) % 2] = heap[(i + 1) % 2].concat(next(tile));
            input[tile[0]][tile[1]] = sym[i % 2];
        }
    }
        
    return input
        .flat()
        .filter(char => char === "X")
        .length;
};

console.log(part1("input"));
