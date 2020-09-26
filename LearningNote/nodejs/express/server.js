// 这个写法就和express很相似了
var express = require("./register");
var app = express();

var http = require('http');

// 监听的是8081端口，那每次被调用都会回调app方法
http.createServer(app).listen(8081);


// 注册
app.register('/login', (req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('login');
})

// 注册
app.register('/resigster', (req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('resigster');
})
