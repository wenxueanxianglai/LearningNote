const Koa = require("koa");
const app = new Koa();

app.use(async (ctx) => {
    if (ctx === '/') {

    } else if (ctx === '/users'){
        if (ctx.method === 'GET') {
            ctx.body = '这是用户列表页'
        } else if (ctx.method === 'POST') {
            ctx.body = '创建用户'
        } else {
            ctx.status = 405;
        }
    }
});


app.listen(3000);



// app.use(async (ctx, next) => {
//     await next();
//     ctx.body = "Hello workd";
//   });
  
//   app.use(async (ctx) => {
//     console.log(2);
//   });
  