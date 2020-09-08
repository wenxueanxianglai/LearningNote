// 直接退出
// const http = require('http')

// const hostname = '127.0.0.1'
// const port = 3000

// const server = http.createServer((req, res) => {
//   res.statusCode = 200
//   res.setHeader('Content-Type', 'text/plain')
//   res.end('exit!\n')
//   process.exit(1);
// })

// server.listen(port, hostname, () => {
//   console.log(`服务器运行在 http://${hostname}:${port}/`)
// })


const express = require('express')

const app = express()

app.get('/', (req, res) => {
  res.send('你好')
})

const server = app.listen(3000, () => console.log('服务器已就绪'))

process.on('SIGTERM', () => {
  server.close(() => {
    console.log('进程已终止')
  })
})