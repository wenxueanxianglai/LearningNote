const http = require("http");
const fs = require("fs");

const querystring = require("querystring");
const urlLib = require("url");

let server = http.createServer((req, res) => {
  //解析数据
  let str = "";
  req.on("data", function (data) {
    str += data;
  });

  req.on("end", function () {
    let obj = urlLib.parse(req.url, true);

    const url = obj.pathname;
    const GET = obj.query;
    const POST = querystring.parse(str);

    if (url != "/favicon.ico") {
      var file_name = "./www" + url;
      fs.readFile(file_name, function (err, data) {
        if (err) {
          res.write("404");
        } else {
          res.write(data);
        }

        res.end();
      });
    }
  });
});

server.listen(8080);
