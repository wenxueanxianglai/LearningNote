const http = require("http");
const fs = require("fs");

var server = http.createServer(function (req, res) {
  // req.url = > /index.html
  var file_name = "./www/test.txt"; // + req.url;

  //fs.open(file_name);
  fs.readFile(file_name, function (err, data) {
    if (err) {
      console.log("resd faild");
      res.write("404");
    } else {
      res.write(data.toString());
    }

    res.end();
  });
});

server.listen(8080);
