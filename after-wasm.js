const fs = require("fs")
const wasm = fs.readFileSync("./mandelbrot-wasm.wasm")
let js = fs.readFileSync("./mandelbrot-wasm.js", "utf8")
const values = new Array(wasm.length)
for (let x = 0; x < wasm.length; x++) {
  values[x] = wasm[x]  
}

js = js.split("MANDELBROT_WEBASSEMBLY_PLACEHOLDER").join(`[${String(values)}]`)

fs.writeFileSync("./mandelbrot-wasm.js", js)
