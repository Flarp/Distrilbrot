const args = process.argv.slice(2)
const fs = require("fs")


if (!args.includes("--wasm")) {
  const asm = fs.readFileSync("./mandelbrot.js", "utf8")
  fs.writeFileSync("./final.js", asm)
} else {
    
  let final = `

  if (typeof WebAssembly !== "undefined") {
    MANDELBROT_WEBASSEMBLY_PLACEHOLDER  
  } else {
    MANDELBROT_ASM_JS_PLACEHOLDER    
  }
  `
  const wasmJS = fs.readFileSync("./mandelbrot-wasm.js", "utf8")
  final = final.split("MANDELBROT_WEBASSEMBLY_PLACEHOLDER").join(wasmJS)
  
  const wasm = fs.readFileSync("./mandelbrot-wasm.wasm")
  const values = new Array(wasm.length)
  for (let x = 0; x < wasm.length; x++) {
    values[x] = wasm[x]  
  }

  final = final.split("MANDELBROT_WEBASSEMBLY_BINARY_PLACEHOLDER").join(`[${String(values)}]`)

  const asmJS = fs.readFileSync("./mandelbrot.js", "utf8")

  final = final.split("MANDELBROT_ASM_JS_PLACEHOLDER").join(asmJS)

  fs.writeFileSync("./final.js", final)

}





