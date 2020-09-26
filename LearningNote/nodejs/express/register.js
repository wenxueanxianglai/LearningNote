var url = require("url");

let express = () => {
  // 所有的路由 都会 注册在这里
  var Funcs = {};

  let app = (req, res) => {
    // 每一次调用app， 都会从 Funcs 里面去查找这个方法， 然后调用
    if (Funcfs[url.parse(req.url).pathname]) {
      Funcs[url.parse(req.url).pathname](req, res);
    } else {
      // 如果不存在 就 返回页面不存在
      res.writeHead(200, { "Content-Type": "text/plain" });
      res.end("页面不存在");
    }
  };

  // 注册路由方法， 全部放在 F 上
  app.register = (path, func) => {
      Funcs[path] = func;
  }

  return app;
};

module.exports = express;


