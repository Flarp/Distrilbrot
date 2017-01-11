let computeSteps = cwrap("mandelbrot_steps", "number", ["string", "string", "string"])
let computeGrid = Module._mandelbrot_grid

onmessage = (m) => {
  message = JSON.parse(m.data.work)
  
  if (message.type === "steps") {
    let steps = computeSteps(message.xcenter, message.ycenter, message.startingzoom)
    postMessage({result:steps})
  } else if (message.type === "grid") {
    let grid = computeGrid(message.xoffset, message.yoffset, message.zoom)
    postMessage({result:grid})
  }
}
