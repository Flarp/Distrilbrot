const Distri = require("distri-node")

let work = Array(360*640)

for (let x = 0; x < 360*640; x++) {
  work[x] = { x: Math.floor(x/640), y: x%360, zoom: 0 }
}

const server = new Distri.DistriServer({
  connection: {
    port: process.env.PORT || 8080
  },
  work
})

let state = "steps"

server.on("workgroup_complete", (i,o,res,rej) => {
  new Promise((resolve, reject) => {
    Distri.CheckPercentage(o,100,resolve,reject)
  })
  .then(result => (result | 0 === result) ? res() : rej())
  .catch(rej)
})

server.on("all_work_complete", () => {
  state = state === "steps" ? "grid" : "steps"
})

