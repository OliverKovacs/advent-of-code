const fill = array => {
    const out = [];
    let i = 0;
    for (let e of array) {
        i += +e * (1000000 - 1);
        out.push(++i);
    }
    return out;
};

const part2 = file => {
    const map = require("node:fs")
        .readFileSync(file, "utf-8")
        .split("\n")
        .slice(0, -1)
        .map(r => r.split("").map(e => +(e === "#")));
    
    const stars = [];
    for (let y = 0; y < map.length; y++) {
        for (let x = 0; x < map[0].length; x++) {
            if (!map[y][x]) continue;
            stars.push([ y, x ]);
        }
    }

    const dy = fill(map.map(r => r.every(e => !e)));
    const dx = fill(map[0].map((_, x) => map.map(r => r[x]).every(e => !e)));

    const distance =
        (a, b) => Math.abs(dy[a[0]] - dy[b[0]]) + Math.abs(dx[a[1]] - dx[b[1]]);

    let sum = 0;
    for (let i = 0; i < stars.length; i++) {
        for (let j = i + 1; j < stars.length; j++) {
            sum += distance(stars[i], stars[j]);
        }
    }
    return sum;
}

console.log(part2("input"));
