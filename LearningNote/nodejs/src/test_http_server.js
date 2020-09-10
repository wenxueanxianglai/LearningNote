const http = require("http");
const fs = require("fs");
const querystring = require("querystring");
const urlLib = require("url");

var users = {};

var server = http.createServer(function (req, res) {
  //解析数据
  var str = "";
  req.on("data", function (data) {
    str += data;
  });

  req.on("end", function () {
    var obj = urlLib.parse(req.url, true);

    const url = obj.pathname;
    const GET = obj.query;
    const POST = querystring.parse(str);

    // 区分 接口 文件
    if (url == "/user") {
      // 接口
      switch (GET.act) {
        case "reg":
          if (users[GET.user]) {
            res.write('{"OK": false, "msg": "此用户已存在"}');
          } else {
            users[GET.user] = GET.pass;
            res.write('{"OK": true, "msg": "注册成功！"}');
          }
          break;
        case "login":
          if (users[GET.name] == null) {
            res.write('{"OK": false, "msg": "此用户不存在"}');
          } else if (users[GET.user] != GET.pass) {
            res.write('{"OK": false, "msg": "密码有误"}');
          } else {
            res.write('{"OK": true, "msg": "成功！"}');
          }
          break;
        default:
          res.write('{"OK": false, "msg": "未知的act"}');
      }
      res.end();
    } else {
      // 文件
      //读取文件
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
