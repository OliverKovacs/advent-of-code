const dijkstra = (map, start) => {
    const out = Array(map.length)
        .fill(0)
        .map(() => Array(map[0].length).fill(-1));

    const next = ([ y, x ]) => [ [ -1, 0 ], [ 1, 0 ], [ 0, -1], [ 0, 1 ] ]
        .map(([ y1, x1 ]) => [ y + y1, x + x1 ])
        .filter(([ y, x ]) => y >= 0 && x >= 0 && y < map.length && x < map[0].length)
        .filter(([ y, x ]) => map[y][x] === ".")
        .filter(([ y, x ]) => out[y][x] === -1);

    let heap = [ [ start ], [] ];
    for (let i = 0; heap[i % 2].length !== 0; i++) {
        heap[(i + 1) % 2] = [];
        for (const [ y, x ] of heap[i % 2]) {
            if (out[y][x] !== -1) continue;
            heap[(i + 1) % 2] = heap[(i + 1) % 2].concat(next([ y, x ]));
            out[y][x] = i;
        }
    }

    return out;
};

const count = map => {
    const out = [ 0, 0 ];
    for (let y = 0; y < map.length; y++) {
        for (let x = 0; x < map[0].length; x++) {
            if (map[y][x] !== -1) out[map[y][x] % 2]++;
        }
    }
    return out;
}

const part1 = file => {
    // const n = 26501365;
    n = 5000;

    console.log("n", n)

    const input = require("node:fs")
        .readFileSync(file, "utf-8")
        .slice(0, -1)
        .split("\n")
        .map(line => line.split(""))

    const h = input.length;
    const w = input[0].length;

    let start;
    outer: for (let y = 0; y < input.length; y++) {
        for (let x = 0; x < input[0].length; x++) {
            if (input[y][x] !== "S") continue;
            start = [ y, x ];
            break outer;
        }
    }
    input[start[0]][start[1]] = ".";

    const next = ([ y, x ], l) => [ [ -1, 0 ], [ 1, 0 ], [ 0, -1], [ 0, 1 ] ]
        .map(([ y1, x1 ]) => [ y + y1, x + x1 ])
        .filter(([ y, x ]) => (0 <= y && y < h) || (0 <= x && x < w))
        .filter(([ y, x ]) => input[((y % h) + h) % h][((x % w) + w) % w] == ".")
        .filter(e => !l.get(e.join(",")));
    
    // cross
    let heap = [ [ start ], [] ]
    let output = [ 0, 0 ];
    let lastlast = new Map();
    for (let i = 0; i < n + 1; i++) {
        if (!(i % 10000)) console.log(i, i * 100 / 26501365)
        heap[(i + 1) % 2] = [];
        last = new Map()
        for (const tile of heap[i % 2]) {
            if (last.get(tile.join(","))) continue;
            heap[(i + 1) % 2] = heap[(i + 1) % 2].concat(next(tile, lastlast));
            last.set(tile.join(","), true);
            output[i % 2]++;
        }
        lastlast = last;
    }


    // corners
    const center = dijkstra(input, start);
    console.log(center)
    for (let i = 0; i < 2; i++) {
        for (let j = 0; j < 2; j++) {
            const tmp_n = n - center.at(i * -1).at(j * -1);
            corner = dijkstra(input, [ i * (h - 1), j * (w - 1) ]);
            const max = Math.max(...corner.flat())
            const stride = w;
            
            const layers = Math.floor(tmp_n / stride);
            const left = tmp_n % stride;

            let count = 0;
            for (let y = 0; y < h; y++) {
                for (let x = 0; x < w; x++) {
                    if (corner[y][x] < left) count++;
                }
            }
            
            // gauss
            const sum = layers * (layers + 1) / 2;
            
            const tiles = sum * w * h + count * (layers + 1);

            console.log(stride)
            console.log(max)
            console.log("tiles", tiles)
        }
    }

    console.log(output);
    return output[n % 2];
};

console.log(part1("debug"));
