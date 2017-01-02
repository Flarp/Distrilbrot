const Distri = require('distri-node')

const server = new Distri.DistriServer({
  connection: {
    port: 8080
  }
  
})
