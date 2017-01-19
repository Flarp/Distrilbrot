const Distri = require('distri-node')

let work = Array(360*640)

for (let x = 0; x < 360*640; x++) {
  work[x] = { x: Math.floor(x/640), y: x%360, zoom: 1 }
}

const server = new Distri.DistriServer({
  connection: {
    port: 8081
  },
  work: work
})
