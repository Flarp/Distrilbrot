const distri = require('../Distri-Node/index.js')


const express = require("express")
const static = require("serve-static")
const app = express()

app.use(static("/root/Distri-JS/build"))


const Distri = require("../Distri-Node")
const work = Array(360*640)
for (let x = 0; x < 360*640; x++) {
  work[x] = {x:String(Math.floor(x/640)),y:String(x%360),zoom:0}
}
const server = new Distri.DistriServer({
  connection: {
    port: 8081
  },
  work,
  files: {
    javascript: 'localhost:8080/final.js'
  }
})

server.server.on('connection', ws => {
  ws.on('message', m => {
    console.log(m)
  })
})

server.on("workgroup_complete",(i,o,res,rej) => {
  console.log(i,o)
  res(o)
})

server.on("workgroup_accepted",(i,o) => console.log(i,o))


app.listen(8080, () => console.log('listening'))

